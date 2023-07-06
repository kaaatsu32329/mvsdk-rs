use std::any::Any;
use std::cell::RefCell;
use std::rc::Rc;

use super::c_bindings::*;
use super::constants::RAW_CALLBACK;
use super::{CamFail, CamRes, Camera};

pub struct ImageInfo {
    pub width: u32,
    pub height: u32,
    pub time_stamp: u32,
    pub exposure_time: u32,
    pub analog_gain: f32,
    pub gamma: i32,
    pub contrast: i32,
    pub saturation: i32,
    pub r_gain: f32,
    pub g_gain: f32,
    pub b_gain: f32,
}

/// Trat that should be implemented on struct to pass custom callback
/// Check Example 3 from README for implementation example
pub trait CamCallBackCtx {
    //<'a> {
    /// Called once before capturing
    fn allocate_cam_buf(&mut self, img_size: usize, n_images: usize) -> CamRes<()>;

    /// Called when capturing. Camera will write in buffer returned by this function.
    /// Note, if size will be too small, Camera will reserve more memory with warning
    fn get_cam_buf(&mut self) -> Rc<RefCell<Vec<u8>>>;

    /// Called after buffer is filled with image.
    /// if error happaned during capturing, buf_is_valid will be false
    fn process_cam_buf(&mut self, buf_is_valid: bool, image_info: ImageInfo);

    /// Used for casting back from dyn CamCallBackCtx
    fn as_any(&self) -> &dyn Any;
}

impl Camera {
    /// How long wait in Camera::prepare_img before fail (milliseconds)
    pub fn set_prepare_img_timeout(&mut self, ms: u32) {
        self.prepare_timeout = ms;
    }

    /// Reserved memory in image buffer just enough for n_images
    pub fn reserve_img_buf(&mut self, n_images: usize) -> CamRes<()> {
        self.img_size = self.calc_image_size()?;
        let buf_size = self.img_size * n_images;
        if self.img_buf.len() < buf_size {
            self.img_buf.reserve(buf_size);
            unsafe { self.img_buf.set_len(buf_size) };
        }
        Ok(())
    }

    /// Resize image buffer to fit n_images
    pub fn resize_img_buf(&mut self, n_images: usize) -> CamRes<()> {
        self.img_size = self.calc_image_size()?;
        let buf_size = self.img_size * n_images;
        if self.img_buf.len() < buf_size {
            self.img_buf.reserve(buf_size);
            unsafe { self.img_buf.set_len(buf_size) };
        } else {
            self.img_buf.resize(buf_size, 0);
        }
        Ok(())
    }

    /// Should be used before Camera::get_img to prepare image in polling
    pub fn prepare_image(&mut self) -> CamRes<()> {
        unsafe {
            let status = CameraGetImageBuffer(
                self.h_camera,
                &mut self.frame_info,
                &mut self.pby_kernel_buffer,
                self.prepare_timeout,
            );
            if status != 0 {
                return Err(CamFail::new(status));
            }
        }
        Ok(())
    }

    pub fn get_image(&mut self) -> CamRes<(&Vec<u8>, ImageInfo)> {
        unsafe {
            let status = CameraImageProcess(
                self.h_camera,
                self.pby_kernel_buffer,
                &mut self.img_buf[0],
                &mut self.frame_info,
            );
            if status != 0 {
                return Err(CamFail::new(status));
            }
            let status = CameraReleaseImageBuffer(self.h_camera, self.pby_kernel_buffer);
            if status != 0 {
                return Err(CamFail::new(status));
            }
        }
        Ok((
            &self.img_buf,
            ImageInfo {
                width: self.frame_info.iWidth as u32,
                height: self.frame_info.iHeight as u32,
                time_stamp: self.frame_info.uiTimeStamp,
                exposure_time: self.frame_info.uiExpTime,
                analog_gain: self.frame_info.fAnalogGain,
                gamma: self.frame_info.iGamma,
                contrast: self.frame_info.iContrast,
                saturation: self.frame_info.iSaturation,
                r_gain: self.frame_info.fRgain,
                g_gain: self.frame_info.fGgain,
                b_gain: self.frame_info.fBgain,
            },
        ))
    }

    /// Should be used before any triggering.
    /// Reserves image buffer to fit n_images and apllies default callback if callback_ctx=None
    /// Otherwise applies custom callback, and calles CamCallBackCtx::allocate_cam_buf
    pub fn set_callback_context(
        &mut self,
        n_images: usize,
        callback_ctx: Option<Box<dyn CamCallBackCtx>>,
    ) -> CamRes<()> {
        // update image size in case user changed resolution/chanels
        match callback_ctx {
            Some(mut callback_ctx) => {
                self.img_size = self.calc_image_size()?;
                callback_ctx.allocate_cam_buf(self.img_size, n_images)?;
                self.custom_callback_context = Some(callback_ctx);
                self.apply_raw_callback(custom_callback_wrapper)?;
            }
            None => {
                // allocate Camera's image buffer
                self.resize_img_buf(n_images)?;
                self.clear_trigger_counter();
                self.custom_callback_context = None;
                self.apply_raw_callback(default_callback)?;
            }
        }
        Ok(())
    }

    pub fn get_callback_context(&mut self) -> Option<Box<dyn CamCallBackCtx>> {
        self.custom_callback_context.take()
    }

    pub fn get_image_buf(&self) -> &Vec<u8> {
        &self.img_buf
    }

    /// Should be called before next capturing session with default callback.
    /// If not called, default callback will allocate more memory in callback
    pub fn clear_trigger_counter(&mut self) {
        self.trig_count = 0;
    }

    pub fn software_trigger(&self) -> CamRes<()> {
        unsafe {
            let status = CameraSoftTrigger(self.h_camera);
            if status != 0 {
                return Err(CamFail::new(status));
            }
        }
        Ok(())
    }

    pub fn polling_software_trigger(&self) {
        unsafe { while CameraSoftTrigger(self.h_camera) != 0 {} }
    }

    fn apply_raw_callback(&mut self, callback: RAW_CALLBACK) -> CamRes<()> {
        unsafe {
            let status = CameraSetCallbackFunction(
                self.h_camera,
                Some(callback),
                self as *mut Camera as PVOID,
                &mut None as *mut CAMERA_SNAP_PROC,
            );
            if status != 0 {
                Err(CamFail::new(status))
            } else {
                Ok(())
            }
        }
    }
}

unsafe extern "C" fn default_callback(
    h_camera: CameraHandle,
    pframe_buffer: *mut BYTE,
    pframe_head: *mut tSdkFrameHead,
    context: PVOID,
) {
    let camera: *mut Camera = context as *mut Camera;
    let trig_count = (*camera).trig_count;
    let trig_buf = &mut (*camera).img_buf;
    let img_size = (*camera).img_size;
    if (trig_count + 1) * img_size > trig_buf.len() {
        println!("Callback: Warnings: Buffer turned out to be too small. Allocating in callback may slow down program. 
                    Please specify correct number of images in prepare_trigger()");
        (*camera)
            .reserve_img_buf(trig_count * 2)
            .unwrap_or_else(|err| {
                eprintln!("Callback: Error while allocating buffer: {:?}", err);
                return;
            });
    }
    let status = CameraImageProcess(
        h_camera,
        pframe_buffer,
        &mut (*trig_buf)[trig_count * img_size],
        pframe_head,
    );
    if status != 0 {
        eprintln!("Callback: CameraImageProcess error: {}", status);
    }
    let status = CameraReleaseImageBuffer(h_camera, pframe_buffer);
    if status != 0 {
        eprintln!("Callback: CameraReleaseImageBuffer error: {}", status);
    }
    (*camera).trig_count += 1;
}

unsafe extern "C" fn custom_callback_wrapper(
    h_camera: CameraHandle,
    pframe_buffer: *mut BYTE,
    pframe_head: *mut tSdkFrameHead,
    context: PVOID,
) {
    let camera: *mut Camera = context as *mut Camera;
    let img_size = (*camera).img_size;

    match &mut (*camera).custom_callback_context {
        Some(callback) => {
            let mut buf_is_valid = true;
            {
                let buf = callback.get_cam_buf();
                let mut buf = buf.borrow_mut();
                if buf.len() < img_size {
                    println!("Callback: Warning: buffer that user returned is too small. Reserve in callback may slow down your program.
                            \nPlease consider fixing CallBackContext::allocate_buffer");
                    buf.reserve(img_size);
                    buf.set_len(img_size);
                }
                let status = CameraImageProcess(h_camera, pframe_buffer, &mut buf[0], pframe_head);
                if status != 0 {
                    buf_is_valid = false;
                    eprintln!(
                        "Callback: CameraReleaseImageBuffer error: {:?}",
                        CamFail::new(status)
                    );
                }
                let status = CameraReleaseImageBuffer(h_camera, pframe_buffer);
                if status != 0 {
                    buf_is_valid = false;
                    eprintln!(
                        "Callback: CameraReleaseImageBuffer error: {:?}",
                        CamFail::new(status)
                    );
                }
            }

            callback.process_cam_buf(
                buf_is_valid,
                ImageInfo {
                    width: (*pframe_head).iWidth as u32,
                    height: (*pframe_head).iHeight as u32,
                    time_stamp: (*pframe_head).uiTimeStamp,
                    exposure_time: (*pframe_head).uiExpTime,
                    analog_gain: (*pframe_head).fAnalogGain,
                    gamma: (*pframe_head).iGamma,
                    contrast: (*pframe_head).iContrast,
                    saturation: (*pframe_head).iSaturation,
                    r_gain: (*pframe_head).fRgain,
                    g_gain: (*pframe_head).fGgain,
                    b_gain: (*pframe_head).fBgain,
                },
            );
        }
        None => {
            eprintln!("Callback: custom_callback_context is None. Doing nothing.")
        }
    }
}

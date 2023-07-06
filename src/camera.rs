pub mod c_bindings;
pub mod constants;
pub mod status;

mod capture;
mod helpers;
mod info;
mod settings;

// use std::{cell::RefCell, rc::Rc, any::Any};

use self::c_bindings::*;
use helpers::default_capabilities;

pub use capture::{CamCallBackCtx, ImageInfo};
pub use constants::{CamImgFormat, LutMode, TriggerMode};
pub use status::CamFail;

/// Result returned by all functions that can fail.
///
/// # Example
/// ```
/// let camera = match Camera::new() {
///     Ok(camera) => camera,
///     Err(err) => {
///         match err {
///             CamFail::NO_DEVICE_FOUND => {
///                 panic!("Plug in camera!");
///             },
///             _ => {
///                 panic!("Failed with code: {:?}", err);
///             }
///         }
///     },
/// };
/// ```
pub type CamRes<T> = Result<T, CamFail>;

// pub type CamResolution = tSdkImageResolution;

pub struct CameraResolution {
    __idx: usize,
    pub width: u32,
    pub height: u32,
}

/// Main struct. Should be singleton
pub struct Camera {
    img_buf: Vec<u8>,                  // image buffer - used when retrieving camera
    h_camera: CameraHandle,            // handler of camera used internally by library
    capabilities: tSdkCameraCapbility, // library struct that incapsulates all capabilities of the camera
    #[allow(dead_code)]
    dev_info: tSdkCameraDevInfo,

    frame_info: tSdkFrameHead,    // is used for retrieving image info
    pby_kernel_buffer: *mut BYTE, // is used for image retrieving

    prepare_timeout: u32, // how long for camera to prepare image..

    trig_count: usize, // if counter < trig_buf.len(), then trig_buf[counter++]=image else pass
    img_size: usize,   // size of one image. Depends on rgb/grayscale, 10bit mode, resolution

    // used for customg callback
    custom_callback_context: Option<Box<dyn CamCallBackCtx>>,
}

impl Camera {
    pub fn new() -> CamRes<Camera> {
        let mut h_camera = 0;
        let mut capabilities = default_capabilities();
        // initialize sdk
        unsafe {
            let status = CameraSdkInit(0);
            if status != 0 {
                return Err(CamFail::new(status));
            }
        }

        // check available device
        let mut t_camera_enum_list = tSdkCameraDevInfo::default();
        let mut camera_counts: CameraHandle = 1;
        unsafe {
            let enum_status = CameraEnumerateDevice(&mut t_camera_enum_list, &mut camera_counts);
            if enum_status != 0 {
                return Err(CamFail::new(enum_status));
            }
            if camera_counts == 0 {
                return Err(CamFail::NO_DEVICE_FOUND);
            }
        }

        // initialize camera
        unsafe {
            let init_status = CameraInit(&mut t_camera_enum_list, -1, -1, &mut h_camera);
            if init_status != 0 {
                return Err(CamFail::new(init_status));
            }
        }

        // camera capabilities
        unsafe {
            let camera_cap_status = CameraGetCapability(h_camera, &mut capabilities);
            if camera_cap_status != 0 {
                return Err(CamFail::new(camera_cap_status));
            }
        }

        // if camera supports RGB, put it in RGH mode
        unsafe {
            let status: i32;
            if capabilities.sIspCapacity.bMonoSensor == 1 {
                status = CameraSetIspOutFormat(h_camera, CAMERA_MEDIA_TYPE_MONO8);
            } else {
                status = CameraSetIspOutFormat(h_camera, CAMERA_MEDIA_TYPE_BGR8);
            }
            if status != 0 {
                return Err(CamFail::new(status));
            }
        }

        let mut this = Camera {
            img_buf: Vec::new(),
            h_camera,
            capabilities,
            dev_info: t_camera_enum_list,
            frame_info: tSdkFrameHead::default(),
            pby_kernel_buffer: 0 as *mut BYTE,
            prepare_timeout: 1000,
            trig_count: 0,
            img_size: 0,
            custom_callback_context: None,
        };

        // calculate memory needed for one image
        this.img_size = this.calc_image_size()?;

        // allocate image buffer
        this.reserve_img_buf(1)?;

        this.play()?;

        Ok(this)
    }

    /// Puts camera in a standby mode
    pub fn pause(&self) -> CamRes<()> {
        unsafe {
            let status = CameraPause(self.h_camera);
            if status != 0 {
                Err(CamFail::new(status))
            } else {
                Ok(())
            }
        }
    }

    /// Resume from stanby called by Camera::pause or just activate camera
    pub fn play(&self) -> CamRes<()> {
        unsafe {
            let status = CameraPlay(self.h_camera);
            if status != 0 {
                Err(CamFail::new(status))
            } else {
                Ok(())
            }
        }
    }

    /// Stop camera - all changes to settings will be ignored
    pub fn stop(&self) -> CamRes<()> {
        unsafe {
            let status = CameraStop(self.h_camera);
            if status != 0 {
                Err(CamFail::new(status))
            } else {
                Ok(())
            }
        }
    }
}

impl Drop for Camera {
    fn drop(&mut self) {
        unsafe {
            if self.pby_kernel_buffer != 0 as *mut BYTE {
                CameraReleaseImageBuffer(self.h_camera, self.pby_kernel_buffer);
            }
            CameraUnInit(self.h_camera);
        }
    }
}

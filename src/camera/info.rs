use super::{c_bindings::*, CameraResolution};
use super::constants::{CamImgFormat, TriggerMode, LutMode};
use super::{CamRes, Camera, CamFail};

impl Camera {
    /// Returns maximum supported resolution of the camera in format (width, height)
    pub fn get_max_resolution(&self) -> (u32, u32) {
        let width = self.capabilities.sResolutionRange.iWidthMax;
        let height = self.capabilities.sResolutionRange.iHeightMax;
        (width as u32, height as u32)
    }

    /// Returns true if camera supports RGB mode
    pub fn is_rgb(&self) -> bool {
        self.capabilities.sIspCapacity.bMonoSensor == 0
    }

    /// Current resolution: (width, height)
    pub fn get_current_resolution(&self) -> CamRes<CameraResolution> {
        unsafe {
            let mut curr_resolution = tSdkImageResolution::default();
            let status = CameraGetImageResolution(self.h_camera, &mut curr_resolution);
            if status != 0 { 
                Err(CamFail::new(status)) 
            } else { 
                Ok(CameraResolution{
                    __idx: curr_resolution.iIndex as usize,
                    width: curr_resolution.iWidth as u32,
                    height: curr_resolution.iHeight as u32,
                }) 
            }
        }
    }

    /// Returns cached size in bytes needed for one image in current camera configuration
    pub fn get_image_size(&self) -> usize {
        self.img_size
    }

    /// Calculates size in bytes needed for one image in current camera configuration
    pub fn calc_image_size(&self) -> CamRes<usize> {
        let CameraResolution {width, height, ..} = self.get_current_resolution()?;
        let mut result = (width * height) as usize;
        if self.is_rgb() {
            result *= 3;
        }
        // TODO: go over all formats
        if let CamImgFormat::MONO16 | CamImgFormat::RGB16  = self.get_image_format()? {
            result *= 2;
        }
        Ok(result)
    }

    /// Since library provides less posibilities, then raw C library, you can get raw handler to 
    /// camera, and call unsafe c functions from camera::c_bindings
    /// 
    /// # Example
    /// ```
    /// use mvsdk_rust::camera::c_bindings;
    /// let mut camera = Camera::new().unwrap();
    /// let h_camera = camera.get_raw_handler();
    /// unsafe {
    ///     c_bindings::CameraSetAntiFlick(h_camera, 1);
    /// }
    /// ```
    pub fn get_raw_handler(&self) -> i32 {
        self.h_camera
    }

    #[allow(dead_code)]
    fn get_device_info(&self) -> tSdkCameraDevInfo {
        self.dev_info
    }

    pub fn get_image_format(&self) -> CamRes<CamImgFormat> {
        unsafe {
            let mut mtype: u32 = 0;
            let status = CameraGetIspOutFormat(self.h_camera, &mut mtype);
            if status != 0 { 
                return Err(CamFail::new(status));
            } else { 
                let fmt = CamImgFormat::from_raw(mtype)?;
                return Ok(fmt);
            }
        }
    }

    pub fn is_exposure_auto(&self) -> CamRes<bool> {
        unsafe {
            let mut is_auto: i32 = 0;
            let status = CameraGetAeState(self.h_camera, &mut is_auto);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(is_auto == 1) }
        }
    }

    pub fn get_sharpness(&self) -> CamRes<i32> {
        unsafe {
            let mut sharpness: i32 = 0;
            let status = CameraGetSharpness(self.h_camera, &mut sharpness);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(sharpness) }
        }
    }

    pub fn get_trigger_delay_us(&self) -> CamRes<u32> {
        unsafe {
            let mut delay: u32 = 0;
            let status = CameraGetTriggerDelayTime(self.h_camera, &mut delay);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(delay) }
        }
    }

    pub fn get_trigger_period_us(&self) -> CamRes<u32> {
        unsafe {
            let mut period: u32 = 0;
            let status = CameraGetTriggerPeriodTime(self.h_camera, &mut period);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(period) }
        }
    }

    pub fn get_trigger_count(&self) -> CamRes<i32> {
        unsafe {
            let mut count: i32 = 0;
            let status = CameraGetTriggerCount(self.h_camera, &mut count);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(count) }
        }
    }

    pub fn get_trigger_mode(&self) -> CamRes<TriggerMode> {
        unsafe {
            let mut mode: i32 = 0;
            let status = CameraGetTriggerMode(self.h_camera, &mut mode);
            let mode = TriggerMode::from_raw(mode)?;
            if status != 0 { Err(CamFail::new(status)) } else { Ok(mode) }
        }
    }

    pub fn get_lut_mode(&self) -> CamRes<LutMode> {
        unsafe {
            let mut mode: i32 = 0;
            let status = CameraGetLutMode(self.h_camera, &mut mode);
            let mode = LutMode::from_raw(mode)?;
            if status != 0 { Err(CamFail::new(status)) } else { Ok(mode) }
        }
    }

    pub fn get_lut_preset(&self) -> CamRes<i32> {
        unsafe {
            let mut preset: i32 = 0;
            let status = CameraGetLutPresetSel(self.h_camera, &mut preset);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(preset) }
        }
    }

    pub fn get_analog_gain(&self) -> CamRes<i32> {
        unsafe {
            let mut gain: i32 = 0;
            let status = CameraGetAnalogGain(self.h_camera, &mut gain);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(gain) }
        }
    }

    pub fn get_exposure_time_us(&self) -> CamRes<f64> {
        unsafe {
            let mut exposure: f64 = 0f64;
            let status = CameraGetExposureTime(self.h_camera, &mut exposure);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(exposure) }
        }
    }

    pub fn get_capabilities(&self) -> tSdkCameraCapbility {
        self.capabilities
    }

    pub fn get_supported_resolutions(&self) -> Vec<CameraResolution> {
        let resolutions = self.capabilities.pImageSizeDesc;
        let n_resolutions = self.capabilities.iImageSizeDesc;
        let mut supported_resolutions: Vec<CameraResolution> = Vec::new();
        supported_resolutions.reserve(n_resolutions as usize);

        for i in 0..n_resolutions {
            unsafe {
                let raw_resolution = *resolutions.add(i as usize);
                supported_resolutions.push( CameraResolution {
                    __idx: i as usize,
                    width: raw_resolution.iWidth as u32,
                    height: raw_resolution.iHeight as u32,
                } );
            }
        }
        supported_resolutions
    }
}

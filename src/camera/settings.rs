use super::{c_bindings::*, CameraResolution};
use super::{CamRes, Camera, CamFail, constants::{CamImgFormat, TriggerMode, LutMode}};

impl Camera {
    pub fn use_manual_exposure(&self) -> CamRes<()> {
        unsafe {
            let status = CameraSetAeState(self.h_camera, 0);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn use_auto_exposure(&self) -> CamRes<()> {
        unsafe {
            let status = CameraSetAeState(self.h_camera, 1);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_exposure_time(&self, us: f64) -> CamRes<()> {
        unsafe {
            let status = CameraSetExposureTime(self.h_camera, us);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_analog_gain(&self, gain: i32) -> CamRes<()> {
        unsafe {
            let status = CameraSetAnalogGain(self.h_camera, gain);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    /// Pass one of structs returned by Camera::get_supported_resolutions
    pub fn set_resolution(&mut self, resolution: CameraResolution) -> CamRes<()> {
        unsafe {
            let resolutions = self.capabilities.pImageSizeDesc;
            let n_resolutions = self.capabilities.iImageSizeDesc as usize;
            if resolution.__idx >= n_resolutions {
                return Err(CamFail::PARAMETER_INVALID);
            }
            
            let status = CameraSetImageResolution(
                self.h_camera, 
                resolutions.add(resolution.__idx)
            );
            if status != 0 { 
                return Err(CamFail::new(status)) 
            }
        }
        self.img_size = self.calc_image_size()?;
        Ok(())
    }

    pub fn set_image_format(&mut self, fmt: CamImgFormat) -> CamRes<()> {
        unsafe {
            let status = CameraSetIspOutFormat(self.h_camera, fmt as u32);
            if status != 0 { 
                return Err(CamFail::new(status));
            } 
        }
        self.img_size = self.calc_image_size()?;
        Ok(())
    }

    pub fn set_sharpness(&self, sharpness: i32) -> CamRes<()> {
        unsafe {
            let status = CameraSetSharpness(self.h_camera, sharpness);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_trigger_delay_time(&self, us: u32) -> CamRes<()> {
        unsafe {
            let status = CameraSetTriggerDelayTime(self.h_camera, us);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_trigger_period_time(&self, us: u32) -> CamRes<()> {
        unsafe {
            let status = CameraSetTriggerPeriodTime(self.h_camera, us);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_trigger_count(&self, count: i32) -> CamRes<()> {
        unsafe {
            let status = CameraSetTriggerCount(self.h_camera, count);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_trigger_mode(&self, mode: TriggerMode) -> CamRes<()> {
        unsafe {
            let status = CameraSetTriggerMode(self.h_camera, mode as i32);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_lut_mode(&self, mode: LutMode) -> CamRes<()> {
        unsafe {
            let status = CameraSetLutMode(self.h_camera, mode as i32);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }

    pub fn set_lut_preset(&self, preset: i32) -> CamRes<()> {
        unsafe {
            let status = CameraSelectLutPreset(self.h_camera, preset);
            if status != 0 { Err(CamFail::new(status)) } else { Ok(()) }
        }
    }
}

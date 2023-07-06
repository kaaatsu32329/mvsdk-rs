use super::c_bindings::*;

pub fn default_capabilities() -> tSdkCameraCapbility {
    tSdkCameraCapbility {
        pTriggerDesc: &mut tSdkTrigger::default(),
        iTriggerDesc: 0,
        pImageSizeDesc: &mut tSdkImageResolution::default(),
        iImageSizeDesc: 0,
        pClrTempDesc: &mut tSdkColorTemperatureDes::default(),
        iClrTempDesc: 0,
        pMediaTypeDesc: &mut tSdkMediaType::default(),
        iMediaTypdeDesc: 0,
        pFrameSpeedDesc: &mut tSdkFrameSpeed::default(),
        iFrameSpeedDesc: 0,
        pPackLenDesc: &mut tSdkPackLength::default(),
        iPackLenDesc: 0,
        iOutputIoCounts: 0,
        iInputIoCounts: 0,
        pPresetLutDesc: &mut tSdkPresetLut::default(),
        iPresetLut: 0,
        iUserDataMaxLen: 0,
        bParamInDevice: 0,
        pAeAlmSwDesc: &mut tSdkAeAlgorithm::default(),
        iAeAlmSwDesc: 0,
        pAeAlmHdDesc: &mut tSdkAeAlgorithm::default(),
        iAeAlmHdDesc: 0,
        pBayerDecAlmSwDesc: &mut tSdkBayerDecodeAlgorithm::default(),
        iBayerDecAlmSwDesc: 0,
        pBayerDecAlmHdDesc: &mut tSdkBayerDecodeAlgorithm::default(),
        iBayerDecAlmHdDesc: 0,
        sExposeDesc: tSdkExpose::default(),
        sResolutionRange: tSdkResolutionRange::default(),
        sRgbGainRange: tRgbGainRange::default(),
        sSaturationRange: tSaturationRange::default(),
        sGammaRange: tGammaRange::default(),
        sContrastRange: tContrastRange::default(),
        sSharpnessRange: tSharpnessRange::default(),
        sIspCapacity: tSdkIspCapacity::default(),

    }
}

#[allow(dead_code)]
pub fn default_camera_frame() -> sCameraFrame {
    sCameraFrame {
        head: tSdkFrameHead::default(),
        pBuffer: 0 as *mut BYTE
    }
}
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
extern crate lazy_static;

pub mod camera;

#[cfg(test)]
use camera::c_bindings::*;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn init_test() {
        let mut iCameraCounts: i32 = 1;
        let _iStatus: i32 = -1;
        let mut tCameraEnumList = tSdkCameraDevInfo::default();
        let _hCamera: i32;
        let _tCapability: tSdkCameraCapbility;
        let _sFrameInfo: tSdkFrameHead;
        let _pbyBuffer: *mut BYTE;
        let _iDisplayFrames: i32 = 10000;
        let _channel: i32 = 3;

        unsafe {
            let status = CameraSdkInit(1);
            // println!("SDK init status: {}", status);
            assert_eq!(status, 0);
        }

        unsafe {
            let camera_status = CameraEnumerateDevice(
                &mut tCameraEnumList as *mut tSdkCameraDevInfo,
                &mut iCameraCounts as *mut INT,
            );
            // println!("state = {}", camera_status);
            assert_eq!(camera_status, CAMERA_STATUS_NO_DEVICE_FOUND);
        }
    }
}

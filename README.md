# MVSDK-Rust

## Note

This workspace was copied from [`crates.io`](https://crates.io/crates/mvsdk).

## Description

rust wrapper on raw bindings of MVSDK - [Mindvision](http://www.mindvision.com.cn/) industrial camera SDK

In case you want to get raw c bindings, use `Camera::get_raw_handler` to get camera handler, and use `mvsdk::camera::c_bindings::*` to get access to unsafe C bindings.

### API examples
1. Polling example
```rust
use mvsdk::camera::Camera;
fn main() {
    let mut camera = Camera::new().unwrap();
    camera.use_auto_exposure().unwrap();    // exposure will be automatically determined by camera
    camera.set_prepare_img_timeout(1000);   // how long to wait for one capture before fail
    // reserve inner buffer for one image. You can skip this, and camera will allocate this
    // on fly with warning
    camera.reserve_img_buf(1).unwrap();

    let n_images = 10;
    for _ in 0..n_images {
         // Fails if camera can't make capture
        camera.prepare_image().unwrap();
        let (_, image_info) = camera.get_image().unwrap();
        let (width, height) = (image_info.width, image_info.height);
        // Now do whatever you want to do with images. 
        // Make sure you copied buffer before calling next camera.get_img()
        // -- snip --
    }
}
```
2. Default callback example

You can create your own callback (example 3), but usually default callback is enough.

- There is inner buffer, that is preallocated with Camera::prepare_trigger.
- Default callback makes camera write to this buffer, them moves pointer on camera.img_size bytes.
- Later you can get immutable reference to this buffer, for you needs
```rust
use mvsdk::camera::{Camera, TriggerMode, LutMode, CameraResolution};
use std::{time, thread};
fn main() {
    let mut camera = Camera::new().unwrap();
    let n_images = 10;
    let wait_time_ms = 60;

    // use software trigger mode
    camera.set_trigger_mode(TriggerMode::SoftWareTrigger).unwrap();

    // some settings
    camera.use_manual_exposure().unwrap();
    camera.set_analog_gain(1).unwrap();
    camera.set_exposure_time(16777f64).unwrap();
    camera.set_trigger_delay_time(0).unwrap();
    camera.set_lut_mode(LutMode::PRESET).unwrap();
    camera.set_lut_preset(3).unwrap();

    // reserve memory for images, callback_ctx=None means use default callback
    // Very important to use this function! Otherwise trigger will be ignored
    camera.set_callback_context(n_images, None).unwrap();
    for i in 0..n_images {
        // if you wait too little time, this trigger will fail
        // if you don't know how long you have to wait, consider using
        // camera::polling_software_trigger
        camera.software_trigger().unwrap();
        thread::sleep(time::Duration::from_millis(wait_time_ms));
    }
    // all captures are saved to images_buf
    let images_buf = camera.get_image_buf();

    // new images starts each image_size bytes
    let image_size = camera.get_image_size();
    assert_eq!(images_buf.len(), image_size * n_images);
    let CameraResolution {width, height, ..} = camera.get_current_resolution().unwrap();
    // your code that does something with images
    // -- snip --
}
```

3. Custom callback example

This is example of custom callback that calculates average value of all captures.

Note, that in this case using custom callback is more memory efficient, than default callback, 
since you don't have to preallocate memory for all images beforehand, and there is no copying.

You have to implemet `camera::CamCallBackCtx` trait
```rust 
use mvsdk::camera::{Camera, CamCallBackCtx, ImageInfo, CamRes, TriggerMode, LutMode, CamImgFormat};
use std::{time, thread, rc::Rc, cell::RefCell};
struct AverageCallbackCtx {
    avg: f64,
    buf: Rc<RefCell<Vec<u8>>>,
    img_size: usize,
    n_images: usize,
}
impl AverageCallbackCtx {
    pub fn new() -> AverageCallbackCtx {
        AverageCallbackCtx {
            avg: 0f64,
            buf: Rc::new(RefCell::new(Vec::new())),
            img_size: 0,
            n_images: 0,
        }
    }

    pub fn get_avg(&self) -> f64 {
        if self.n_images > 0 {
            return self.avg / self.n_images as f64;
        }
        return 0f64;
    }
}
impl CamCallBackCtx for AverageCallbackCtx {
    // This will be called once when applying callback. Make sure to allocate enough memory
    fn allocate_cam_buf(&mut self, img_size: usize, n_images: usize) -> CamRes<()> {
        let mut buf_ref = self.buf.borrow_mut();
        buf_ref.resize(img_size, 0);
        self.img_size = img_size;
        self.n_images = n_images;
        Ok(())
    }

    // Camera will write in the buffer returned by this function on each callback
    fn get_cam_buf(&mut self) -> Rc<RefCell<Vec<u8>>> {
        return Rc::clone(&self.buf);
    }

    // Thus function will be called after camera buffer is filled.
    fn process_cam_buf(&mut self, buf_is_valid: bool, image_info: ImageInfo) {
        if buf_is_valid {
            let buf_ref = self.buf.borrow();
            let mut local_avg = 0f64;
            for i in 0..self.img_size {
                local_avg += buf_ref[i] as f64; 
            }
            local_avg /= self.img_size as f64;
            self.avg += local_avg;
        }
    }

    fn as_any(&self) -> &dyn std::any::Any {
        self
    }
}
fn main() {
    let mut camera = Camera::new().unwrap();
    // use software trigger mode, some settings (The same as in Example 2)
    // use software trigger mode
    camera.set_trigger_mode(TriggerMode::SoftWareTrigger).unwrap();

    // some settings
    camera.use_manual_exposure().unwrap();
    camera.set_analog_gain(1).unwrap();
    camera.set_exposure_time(16777f64).unwrap();
    camera.set_trigger_delay_time(0).unwrap();
    camera.set_lut_mode(LutMode::PRESET).unwrap();
    camera.set_lut_preset(3).unwrap();
    camera.set_image_format(CamImgFormat::MONO8).unwrap();

    let n_images = 10;
    let wait_time = 33;
    let avg_ctx = AverageCallbackCtx::new();
    
    // reserve memory for images. Camera takes ownership of context.
    camera.set_callback_context(n_images, Some(Box::new(avg_ctx))).unwrap();
    for _ in 0..n_images {
        camera.software_trigger().unwrap();
        thread::sleep(time::Duration::from_millis(wait_time));
    }
    // return ownership of the context
    if let Some(avg_ctx) = camera.get_callback_context() {
        if let Some(avg_ctx) = avg_ctx.as_any().downcast_ref::<AverageCallbackCtx>() {
            println!("Average value: {}", avg_ctx.get_avg());
        }
    }
}
```
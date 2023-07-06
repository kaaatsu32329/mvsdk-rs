#[cfg(feature = "compile_bindings")]
extern crate bindgen;
#[cfg(feature = "compile_bindings")]
use std::env;
#[cfg(feature = "compile_bindings")]
use std::path::PathBuf;
use std::env;

fn main() {
    // Tell cargo to tell rustc to link the libMVSDK.so shared library.
    let mut link_search = String::from("cargo:rustc-link-search=");
    match env::var("LIB_MVSDK_PATH") {
        Ok(mvsdk_path) => {
            link_search += &(mvsdk_path + ":");
        },
        Err(_) => {},
    }
    link_search += "/usr/lib/";
    println!("{}", link_search);
    // println!(r"cargo:rustc-link-search=/usr/lib/");
    println!("cargo:rustc-link-lib=MVSDK");

    #[cfg(feature = "compile_bindings")]
    {
         // Tell cargo to invalidate the built crate whenever the wrapper changes
        println!("cargo:rerun-if-changed=./c-include/CameraApi.h");
        println!("cargo:rerun-if-changed=./c-include/CameraDefine.h");
        println!("cargo:rerun-if-changed=./c-include/CameraStatus.h");
        // The bindgen::Builder is the main entry point
        // to bindgen, and lets you build up options for
        // the resulting bindings.
        let bindings = bindgen::Builder::default()
            // The input header we would like to generate
            // bindings for.
            .header("./c-include/CameraApi.h")
            .header("./c-include/CameraDefine.h")
            .header("./c-include/CameraStatus.h")
            // Tell cargo to invalidate the built crate whenever any of the
            // included header files changed.
            .parse_callbacks(Box::new(bindgen::CargoCallbacks))
            // Finish the builder and generate the bindings.
            .generate()
            // Unwrap the Result and panic on failure.
            .unwrap_or_else(|err| {
                panic!("Unable to generate bindings: {:?}", err);
            });

        // Write the bindings to the $OUT_DIR/bindings.rs file.
        let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
        bindings
            .write_to_file(out_path.join("bindings.rs"))
            .unwrap_or_else(|err| {
                panic!("Couldn't write bindings: {:?}", err);
            });
    }
}

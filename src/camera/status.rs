use lazy_static::lazy_static;

/// Is returned when something went wrong.
/// All statuses have direct correspondance in c library.
#[derive(Clone, Copy, Debug)]
pub enum CamFail {
    FAILED = -1,
    INTERNAL_ERROR = -2,
    UNKNOW = -3,
    NOT_SUPPORTED = -4,
    NOT_INITIALIZED = -5,
    PARAMETER_INVALID = -6,
    PARAMETER_OUT_OF_BOUND = -7,
    UNENABLED = -8,
    USER_CANCEL = -9,
    PATH_NOT_FOUND = -10,
    SIZE_DISMATCH = -11,
    TIME_OUT = -12,
    IO_ERROR = -13,
    COMM_ERROR = -14,
    BUS_ERROR = -15,
    NO_DEVICE_FOUND = -16,
    NO_LOGIC_DEVICE_FOUND = -17,
    DEVICE_IS_OPENED = -18,
    DEVICE_IS_CLOSED = -19,
    DEVICE_VEDIO_CLOSED = -20,
    NO_MEMORY = -21,
    FILE_CREATE_FAILED = -22,
    FILE_INVALID = -23,
    WRITE_PROTECTED = -24,
    GRAB_FAILED = -25,
    LOST_DATA = -26,
    EOF_ERROR = -27,
    BUSY = -28,
    WAIT = -29,
    IN_PROCESS = -30,
    IIC_ERROR = -31,
    SPI_ERROR = -32,
    USB_CONTROL_ERROR = -33,
    USB_BULK_ERROR = -34,
    SOCKET_INIT_ERROR = -35,
    GIGE_FILTER_INIT_ERROR = -36,
    NET_SEND_ERROR = -37,
    DEVICE_LOST = -38,
    DATA_RECV_LESS = -39,
    FUNCTION_LOAD_FAILED = -40,
    CRITICAL_FILE_LOST = -41,
    SENSOR_ID_DISMATCH = -42,
    OUT_OF_RANGE = -43,
    REGISTRY_ERROR = -44,
    ACCESS_DENY = -45,
    CAMERA_NEED_RESET = -46,
    ISP_MOUDLE_NOT_INITIALIZED = -47,
    ISP_DATA_CRC_ERROR = -48,
    MV_TEST_FAILED = -49,
    INTERNAL_ERR1 = -50,
    U3V_NO_CONTROL_EP = -51,
    U3V_CONTROL_ERROR = -52,

    // my statues
    INVALID_STATUS = -53,
}

lazy_static! {
    pub static ref STATUS_TO_FAIL: Vec<CamFail> = vec![
        CamFail::FAILED,   // should not be used
        CamFail::FAILED,
        CamFail::INTERNAL_ERROR,
        CamFail::UNKNOW,
        CamFail::NOT_SUPPORTED,
        CamFail::NOT_INITIALIZED,
        CamFail::PARAMETER_INVALID,
        CamFail::PARAMETER_OUT_OF_BOUND,
        CamFail::UNENABLED,
        CamFail::USER_CANCEL,
        CamFail::PATH_NOT_FOUND,
        CamFail::SIZE_DISMATCH,
        CamFail::TIME_OUT,
        CamFail::IO_ERROR,
        CamFail::COMM_ERROR,
        CamFail::BUS_ERROR,
        CamFail::NO_DEVICE_FOUND,
        CamFail::NO_LOGIC_DEVICE_FOUND,
        CamFail::DEVICE_IS_OPENED,
        CamFail::DEVICE_IS_CLOSED,
        CamFail::DEVICE_VEDIO_CLOSED,
        CamFail::NO_MEMORY,
        CamFail::FILE_CREATE_FAILED,
        CamFail::FILE_INVALID,
        CamFail::WRITE_PROTECTED,
        CamFail::GRAB_FAILED,
        CamFail::LOST_DATA,
        CamFail::EOF_ERROR,
        CamFail::BUSY,
        CamFail::WAIT,
        CamFail::IN_PROCESS,
        CamFail::IIC_ERROR,
        CamFail::SPI_ERROR,
        CamFail::USB_CONTROL_ERROR,
        CamFail::USB_BULK_ERROR,
        CamFail::SOCKET_INIT_ERROR,
        CamFail::GIGE_FILTER_INIT_ERROR,
        CamFail::NET_SEND_ERROR,
        CamFail::DEVICE_LOST,
        CamFail::DATA_RECV_LESS,
        CamFail::FUNCTION_LOAD_FAILED,
        CamFail::CRITICAL_FILE_LOST,
        CamFail::SENSOR_ID_DISMATCH,
        CamFail::OUT_OF_RANGE,
        CamFail::REGISTRY_ERROR,
        CamFail::ACCESS_DENY,
        CamFail::CAMERA_NEED_RESET,
        CamFail::ISP_MOUDLE_NOT_INITIALIZED,
        CamFail::ISP_DATA_CRC_ERROR,
        CamFail::MV_TEST_FAILED,
        CamFail::INTERNAL_ERR1,
        CamFail::U3V_NO_CONTROL_EP,
        CamFail::U3V_CONTROL_ERROR,
    ];
}

impl CamFail {
    pub fn new(status: i32) -> CamFail {
        let idx = -status as usize;
        if idx > STATUS_TO_FAIL.len() || status > 0 {
            return CamFail::INVALID_STATUS;
        }
        STATUS_TO_FAIL[idx]
    }
}

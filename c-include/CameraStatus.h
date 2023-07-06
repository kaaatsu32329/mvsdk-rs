
#ifndef __CAMERA_STATUS_DEF__
#define __CAMERA_STATUS_DEF__

typedef int CameraSdkStatus;


#define SDK_SUCCESS(_FUC_)              ((_FUC_) == CAMERA_STATUS_SUCCESS)

#define SDK_UNSUCCESS(_FUC_)            ((_FUC_) != CAMERA_STATUS_SUCCESS)

#define SDK_UNSUCCESS_RETURN(_FUC_,RET) if((RET = (_FUC_)) != CAMERA_STATUS_SUCCESS)\
                                        {\
                                            return RET;\
                                        }

#define SDK_UNSUCCESS_BREAK(_FUC_)      if((_FUC_) != CAMERA_STATUS_SUCCESS)\
                                        {\
                                            break;\
                                        }



#define CAMERA_STATUS_SUCCESS                    0  
#define CAMERA_STATUS_FAILED                    -1  
#define CAMERA_STATUS_INTERNAL_ERROR            -2  
#define CAMERA_STATUS_UNKNOW                    -3  
#define CAMERA_STATUS_NOT_SUPPORTED             -4  
#define CAMERA_STATUS_NOT_INITIALIZED           -5  
#define CAMERA_STATUS_PARAMETER_INVALID         -6  
#define CAMERA_STATUS_PARAMETER_OUT_OF_BOUND    -7  
#define CAMERA_STATUS_UNENABLED                 -8  
#define CAMERA_STATUS_USER_CANCEL               -9  
#define CAMERA_STATUS_PATH_NOT_FOUND            -10 
#define CAMERA_STATUS_SIZE_DISMATCH             -11 
#define CAMERA_STATUS_TIME_OUT                  -12 
#define CAMERA_STATUS_IO_ERROR                  -13 
#define CAMERA_STATUS_COMM_ERROR                -14 
#define CAMERA_STATUS_BUS_ERROR                 -15 
#define CAMERA_STATUS_NO_DEVICE_FOUND           -16 
#define CAMERA_STATUS_NO_LOGIC_DEVICE_FOUND     -17 
#define CAMERA_STATUS_DEVICE_IS_OPENED          -18 
#define CAMERA_STATUS_DEVICE_IS_CLOSED          -19 
#define CAMERA_STATUS_DEVICE_VEDIO_CLOSED       -20 
#define CAMERA_STATUS_NO_MEMORY                 -21 
#define CAMERA_STATUS_FILE_CREATE_FAILED        -22 
#define CAMERA_STATUS_FILE_INVALID              -23 
#define CAMERA_STATUS_WRITE_PROTECTED           -24 
#define CAMERA_STATUS_GRAB_FAILED               -25 
#define CAMERA_STATUS_LOST_DATA                 -26 
#define CAMERA_STATUS_EOF_ERROR                 -27 
#define CAMERA_STATUS_BUSY                      -28 
#define CAMERA_STATUS_WAIT                      -29 
#define CAMERA_STATUS_IN_PROCESS                -30 
#define CAMERA_STATUS_IIC_ERROR                 -31 
#define CAMERA_STATUS_SPI_ERROR                 -32 
#define CAMERA_STATUS_USB_CONTROL_ERROR         -33 
#define CAMERA_STATUS_USB_BULK_ERROR            -34 
#define CAMERA_STATUS_SOCKET_INIT_ERROR         -35 
#define CAMERA_STATUS_GIGE_FILTER_INIT_ERROR    -36 
#define CAMERA_STATUS_NET_SEND_ERROR            -37 
#define CAMERA_STATUS_DEVICE_LOST               -38 
#define CAMERA_STATUS_DATA_RECV_LESS            -39 
#define CAMERA_STATUS_FUNCTION_LOAD_FAILED      -40 
#define CAMERA_STATUS_CRITICAL_FILE_LOST        -41 
#define CAMERA_STATUS_SENSOR_ID_DISMATCH        -42 
#define CAMERA_STATUS_OUT_OF_RANGE              -43 
#define CAMERA_STATUS_REGISTRY_ERROR            -44 
#define CAMERA_STATUS_ACCESS_DENY               -45 
#define CAMERA_STATUS_CAMERA_NEED_RESET         -46 
#define CAMERA_STATUS_ISP_MOUDLE_NOT_INITIALIZED -47
#define CAMERA_STATUS_ISP_DATA_CRC_ERROR        -48 
#define CAMERA_STATUS_MV_TEST_FAILED            -49 
#define CAMERA_STATUS_INTERNAL_ERR1             -50	
#define CAMERA_STATUS_U3V_NO_CONTROL_EP			-51	
#define CAMERA_STATUS_U3V_CONTROL_ERROR			-52	




#define CAMERA_AIA_PACKET_RESEND                          0x0100
#define CAMERA_AIA_NOT_IMPLEMENTED                        0x8001
#define CAMERA_AIA_INVALID_PARAMETER                      0x8002
#define CAMERA_AIA_INVALID_ADDRESS                        0x8003
#define CAMERA_AIA_WRITE_PROTECT                          0x8004
#define CAMERA_AIA_BAD_ALIGNMENT                          0x8005
#define CAMERA_AIA_ACCESS_DENIED                          0x8006
#define CAMERA_AIA_BUSY                                   0x8007
#define CAMERA_AIA_DEPRECATED                             0x8008
#define CAMERA_AIA_PACKET_UNAVAILABLE                     0x800C
#define CAMERA_AIA_DATA_OVERRUN                           0x800D
#define CAMERA_AIA_INVALID_HEADER                         0x800E
#define CAMERA_AIA_PACKET_NOT_YET_AVAILABLE               0x8010
#define CAMERA_AIA_PACKET_AND_PREV_REMOVED_FROM_MEMORY    0x8011
#define CAMERA_AIA_PACKET_REMOVED_FROM_MEMORY             0x8012
#define CAMERA_AIA_NO_REF_TIME                            0x0813
#define CAMERA_AIA_PACKET_TEMPORARILY_UNAVAILABLE         0x0814
#define CAMERA_AIA_OVERFLOW                               0x0815
#define CAMERA_AIA_ACTION_LATE                            0x0816
#define CAMERA_AIA_ERROR                                  0x8FFF





#endif

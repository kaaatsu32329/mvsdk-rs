#pragma once
#ifndef _CAMERA_DEFINE_H_
#define _CAMERA_DEFINE_H_

#include "CameraStatus.h"

#define MAX_CROSS_LINE 9

typedef int CameraHandle;
typedef int INT;
typedef int LONG;
typedef unsigned int UINT;
typedef unsigned long long UINT64;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef void* PVOID;
typedef void* HWND;
typedef char* LPCTSTR;
typedef unsigned short USHORT;
typedef short SHORT;
 typedef unsigned char* LPBYTE;
typedef char CHAR;
typedef char TCHAR;
typedef  unsigned short WORD;
typedef INT HANDLE;
typedef void VOID;
typedef unsigned int ULONG;
typedef void* LPVOID;
typedef unsigned char UCHAR;
typedef void* HMODULE;

#define TRUE 1
#define FALSE 0
typedef enum
{
    LUTMODE_PARAM_GEN=0,
    LUTMODE_PRESET,     
    LUTMODE_USER_DEF    
}emSdkLutMode;

typedef enum
{
    RUNMODE_PLAY=0,
    RUNMODE_PAUSE,
    RUNMODE_STOP 
}emSdkRunMode;

typedef enum
{
    DISPLAYMODE_SCALE=0, 
    DISPLAYMODE_REAL
}emSdkDisplayMode;

typedef enum
{
  RECORD_STOP = 0,
  RECORD_START,  
  RECORD_PAUSE
}emSdkRecordMode;

typedef enum
{
    MIRROR_DIRECTION_HORIZONTAL = 0,
    MIRROR_DIRECTION_VERTICAL      
}emSdkMirrorDirection;


typedef enum
{
	ROTATE_DIRECTION_0=0,		//~english Do not rotate
	ROTATE_DIRECTION_90=1,	//~english Counterclockwise 90 degrees
	ROTATE_DIRECTION_180=2,	//~english Counterclockwise 180 degrees
	ROTATE_DIRECTION_270=3,	//~english Counterclockwise 270 degrees
}emSdkRotateDirection;

typedef enum
{
    FRAME_SPEED_LOW = 0, 
    FRAME_SPEED_NORMAL,  
    FRAME_SPEED_HIGH,    
    FRAME_SPEED_SUPER    
}emSdkFrameSpeed;

typedef enum
{
    FILE_JPG = 1,
    FILE_BMP = 2,
    FILE_RAW = 4,
    FILE_PNG = 8,
    FILE_BMP_8BIT = 16,	
    FILE_PNG_8BIT = 32, 
	  FILE_RAW_16BIT = 64
}emSdkFileType;

typedef enum
{
    CONTINUATION = 0,
    SOFT_TRIGGER,    
    EXTERNAL_TRIGGER 
} emSdkSnapMode;

typedef enum
{
    LIGHT_FREQUENCY_50HZ = 0,
    LIGHT_FREQUENCY_60HZ     
}emSdkLightFrequency;

typedef enum
{
    PARAMETER_TEAM_DEFAULT = 0xff,
    PARAMETER_TEAM_A = 0,
    PARAMETER_TEAM_B = 1,
    PARAMETER_TEAM_C = 2,
    PARAMETER_TEAM_D = 3
}emSdkParameterTeam;


typedef enum
{
  PARAM_MODE_BY_MODEL = 0,  
  PARAM_MODE_BY_NAME, 
  PARAM_MODE_BY_SN,        
  PARAM_MODE_IN_DEVICE      
}emSdkParameterMode;


typedef enum
{
  PROP_SHEET_INDEX_EXPOSURE = 0,
  PROP_SHEET_INDEX_ISP_COLOR,
  PROP_SHEET_INDEX_ISP_LUT,
  PROP_SHEET_INDEX_ISP_SHAPE,
  PROP_SHEET_INDEX_VIDEO_FORMAT,
  PROP_SHEET_INDEX_RESOLUTION,
  PROP_SHEET_INDEX_IO_CTRL,
  PROP_SHEET_INDEX_TRIGGER_SET,
  PROP_SHEET_INDEX_OVERLAY,
  PROP_SHEET_INDEX_DEVICE_INFO,
  PROP_SHEET_INDEX_WDR,
  PROP_SHEET_INDEX_MULTI_EXPOSURE
}emSdkPropSheetMask;

typedef enum
{
  SHEET_MSG_LOAD_PARAM_DEFAULT = 0,
  SHEET_MSG_LOAD_PARAM_GROUP,      
  SHEET_MSG_LOAD_PARAM_FROMFILE,   
  SHEET_MSG_SAVE_PARAM_GROUP       
}emSdkPropSheetMsg;

typedef enum
{
  REF_WIN_AUTO_EXPOSURE = 0,
  REF_WIN_WHITE_BALANCE,
}emSdkRefWinType;

typedef enum
{
  RES_MODE_PREVIEW = 0,
  RES_MODE_SNAPSHOT,
}emSdkResolutionMode;

typedef enum
{
  CT_MODE_AUTO = 0,
  CT_MODE_PRESET,  
  CT_MODE_USER_DEF  
}emSdkClrTmpMode;

typedef enum
{
  LUT_CHANNEL_ALL = 0,
  LUT_CHANNEL_RED,    
  LUT_CHANNEL_GREEN,  
  LUT_CHANNEL_BLUE,   
}emSdkLutChannel;

typedef enum
{
  ISP_PROCESSSOR_PC = 0,
  ISP_PROCESSSOR_DEVICE 
}emSdkIspProcessor;

typedef enum
{
  STROBE_SYNC_WITH_TRIG_AUTO = 0,    
  STROBE_SYNC_WITH_TRIG_MANUAL, 
  STROBE_ALWAYS_HIGH,                
  STROBE_ALWAYS_LOW                  
}emStrobeControl;

typedef enum
{
  EXT_TRIG_LEADING_EDGE = 0, 
  EXT_TRIG_TRAILING_EDGE,    
  EXT_TRIG_HIGH_LEVEL, 
  EXT_TRIG_LOW_LEVEL          
}emExtTrigSignal;

typedef enum
{
  EXT_TRIG_EXP_STANDARD = 0, 
  EXT_TRIG_EXP_GRR,          
}emExtTrigShutterMode;

typedef enum
{
  IOMODE_TRIG_INPUT=0,		    ///\~english Trigger input
  IOMODE_STROBE_OUTPUT=1,		  ///\~english Strobe output
  IOMODE_GP_INPUT=2,			    ///\~english Universal input
  IOMODE_GP_OUTPUT=3,			    ///\~english Universal output
  IOMODE_PWM_OUTPUT=4,		    ///\~english PWM output
  IOMODE_ROTARYENC_INPUT=5,   ///\~english rotary input
}emCameraGPIOMode;


typedef enum 
{
	IOFORMAT_SINGLE=0,			///<\~english single ended
	IOFORMAT_RS422=1,			  ///<\~english Differential RS422
	IOFORMAT_RS422_TERM=2,	///<\~english Differential RS422 and Termination Enable
}emCameraGPIOFormat;


typedef enum
{
	CAMERA_GET_IMAGE_PRIORITY_OLDEST=0,		///< \~english	Get the oldest frame in the cache
	CAMERA_GET_IMAGE_PRIORITY_NEWEST=1,		///< \~english Get the latest frame in the cache (older than this frame will be discarded)

	/// \~english All frames in the cache are discarded, and if the camera is now being exposed or transmitted it will be immediately interrupted, waiting to receive the next frame
	/// \note Some models do not support this feature. For cameras that do not support this feature this flag is equivalent to @link #CAMERA_GET_IMAGE_PRIORITY_OLDEST @endlink
	CAMERA_GET_IMAGE_PRIORITY_NEXT=2,
}emCameraGetImagePriority;


typedef enum
{
	CAMERA_ST_CLEAR_BUFFER_BEFORE	= 0x1,	///\~english Empty camera-cached frames before soft triggering
}emCameraSoftTriggerExFlags;

typedef struct
{
    char acProductSeries[32];
    char acProductName[32];  
    char acFriendlyName[32];
    char acLinkName[32];     
    char acDriverVersion[32];
    char acSensorType[32];   
    char acPortType[32];     
    char acSn[32];           
    UINT uInstance;          
} tSdkCameraDevInfo;

#define EXT_TRIG_MASK_GRR_SHUTTER  1	///< \~english Shutter supports GRR mode
#define EXT_TRIG_MASK_LEVEL_MODE   2	///< \~english Support level trigger
#define EXT_TRIG_MASK_DOUBLE_EDGE  4	///< \~english Supports bilateral triggering

#define MASK_2X2_HD     (1<<0)   
#define MASK_3X3_HD     (1<<1)
#define MASK_4X4_HD     (1<<2)
#define MASK_5X5_HD     (1<<3)
#define MASK_6X6_HD     (1<<4)
#define MASK_7X7_HD     (1<<5)
#define MASK_8X8_HD     (1<<6)
#define MASK_9X9_HD     (1<<7)
#define MASK_10X10_HD   (1<<8)
#define MASK_11X11_HD   (1<<9)
#define MASK_12X12_HD   (1<<10)
#define MASK_13X13_HD   (1<<11)
#define MASK_14X14_HD   (1<<12)
#define MASK_15X15_HD   (1<<13)
#define MASK_16X16_HD   (1<<14)
#define MASK_17X17_HD   (1<<15)
#define MASK_2X2_SW     (1<<16)   
#define MASK_3X3_SW     (1<<17)
#define MASK_4X4_SW     (1<<18)
#define MASK_5X5_SW     (1<<19)
#define MASK_6X6_SW     (1<<20)
#define MASK_7X7_SW     (1<<21)
#define MASK_8X8_SW     (1<<22)
#define MASK_9X9_SW     (1<<23)
#define MASK_10X10_SW   (1<<24)
#define MASK_11X11_SW   (1<<25)
#define MASK_12X12_SW   (1<<26)
#define MASK_13X13_SW   (1<<27)
#define MASK_14X14_SW   (1<<28)
#define MASK_15X15_SW   (1<<29)
#define MASK_16X16_SW   (1<<30)
#define MASK_17X17_SW   (1<<31)

typedef struct
{
  INT iHeightMax;         
  INT iHeightMin;         
  INT iWidthMax;          
  INT iWidthMin;          
  UINT uSkipModeMask;     
  UINT uBinSumModeMask;    
  UINT uBinAverageModeMask;
  UINT uResampleMask;     
} tSdkResolutionRange;


typedef struct
{
  INT     iIndex;
  char    acDescription[32]; 
  UINT    uBinSumMode;    
  UINT    uBinAverageMode;
  UINT    uSkipMode;         
  UINT    uResampleMask;     
  INT     iHOffsetFOV;       
  INT     iVOffsetFOV;       
  INT     iWidthFOV;         
  INT     iHeightFOV;        
  INT     iWidth;            
  INT     iHeight;           
  INT     iWidthZoomHd; 
  INT     iHeightZoomHd;
  INT     iWidthZoomSw; 
  INT     iHeightZoomSw;
} tSdkImageResolution;

typedef struct
{
    INT  iIndex;           
    char acDescription[32];
} tSdkColorTemperatureDes;

typedef struct
{
    INT  iIndex;            
    char acDescription[32]; 
} tSdkFrameSpeed;

typedef struct
{
    UINT  uiTargetMin;     
    UINT  uiTargetMax;     
    UINT  uiAnalogGainMin; 
    UINT  uiAnalogGainMax; 
    float fAnalogGainStep;
    UINT  uiExposeTimeMin; 
    UINT  uiExposeTimeMax; 
} tSdkExpose;

typedef struct
{
  INT   iIndex;            
  char  acDescription[32]; 
} tSdkTrigger;

typedef struct
{
    INT  iIndex;             
    char acDescription[32]; 
    UINT iPackSize;
} tSdkPackLength;

typedef struct
{
    INT  iIndex;
    char acDescription[32];    
} tSdkPresetLut;

typedef struct
{
    INT  iIndex;                
    char acDescription[32];     
} tSdkAeAlgorithm;

typedef struct
{
    INT  iIndex;               
    char acDescription[32];    
} tSdkBayerDecodeAlgorithm;


typedef struct
{
  INT iTotal;           
    INT iCapture;       
    INT iLost;          
} tSdkFrameStatistic;

typedef struct
{
  INT     iIndex;             
  char    acDescription[32];  
  UINT    iMediaType;         
} tSdkMediaType;

typedef struct
{
  INT iMin;       
  INT iMax;       
} tGammaRange;

typedef struct
{
    INT iMin;   
    INT iMax;   
} tContrastRange;

typedef struct
{
    INT iRGainMin;
    INT iRGainMax;
    INT iGGainMin;
    INT iGGainMax;
    INT iBGainMin;
    INT iBGainMax;
} tRgbGainRange;

typedef struct
{
    INT iMin;   
    INT iMax;   
} tSaturationRange;

typedef struct
{
  INT iMin;   
  INT iMax;   
} tSharpnessRange;

typedef struct
{
    BOOL bMonoSensor;       
    BOOL bWbOnce;           
    BOOL bAutoWb;           
    BOOL bAutoExposure;     
    BOOL bManualExposure;   
    BOOL bAntiFlick;        
    BOOL bDeviceIsp;        
    BOOL bForceUseDeviceIsp;
    BOOL bZoomHD;        
} tSdkIspCapacity;

typedef struct
{

  tSdkTrigger   *pTriggerDesc;         
  INT           iTriggerDesc;          

  tSdkImageResolution   *pImageSizeDesc;
  INT                   iImageSizeDesc; 

  tSdkColorTemperatureDes *pClrTempDesc;
  INT                     iClrTempDesc;

  tSdkMediaType     *pMediaTypeDesc;    
  INT               iMediaTypdeDesc;    

  tSdkFrameSpeed    *pFrameSpeedDesc;  
  INT               iFrameSpeedDesc;   

  tSdkPackLength    *pPackLenDesc;     
  INT               iPackLenDesc;      

  INT           iOutputIoCounts;      
  INT           iInputIoCounts;       

  tSdkPresetLut  *pPresetLutDesc;     
  INT            iPresetLut;           

  INT           iUserDataMaxLen;       
  BOOL          bParamInDevice;        

  tSdkAeAlgorithm   *pAeAlmSwDesc;     
  int                iAeAlmSwDesc;    

  tSdkAeAlgorithm    *pAeAlmHdDesc;    
  int                iAeAlmHdDesc;    

  tSdkBayerDecodeAlgorithm   *pBayerDecAlmSwDesc; 
  int                        iBayerDecAlmSwDesc;  

  tSdkBayerDecodeAlgorithm   *pBayerDecAlmHdDesc; 
  int                        iBayerDecAlmHdDesc; 

  tSdkExpose            sExposeDesc;     
  tSdkResolutionRange   sResolutionRange;
  tRgbGainRange         sRgbGainRange;   
  tSaturationRange      sSaturationRange;
  tGammaRange           sGammaRange;     
  tContrastRange        sContrastRange;  
  tSharpnessRange       sSharpnessRange; 
  tSdkIspCapacity       sIspCapacity;    


} tSdkCameraCapbility;


typedef struct
{
  UINT    uiMediaType;   
  UINT    uBytes;       
  INT     iWidth;         
  INT     iHeight;        
  INT     iWidthZoomSw;  
  INT     iHeightZoomSw;  
  BOOL    bIsTrigger;    
  UINT    uiTimeStamp;    
  UINT    uiExpTime;      
  float   fAnalogGain;    
  INT     iGamma;       
  INT     iContrast;      
  INT     iSaturation;    
  float   fRgain;         
  float   fGgain;         
  float   fBgain;         
}tSdkFrameHead;

typedef struct sCameraFrame
{
  tSdkFrameHead   head;    
  BYTE *          pBuffer; 
}tSdkFrame;

typedef void (*CAMERA_SNAP_PROC)(CameraHandle hCamera, BYTE *pFrameBuffer, tSdkFrameHead* pFrameHead,PVOID pContext);

typedef void (*CAMERA_PAGE_MSG_PROC)(CameraHandle hCamera,UINT MSG,UINT uParam,PVOID pContext);

typedef void (*CAMERA_CONNECTION_STATUS_CALLBACK)(CameraHandle hCamera,UINT MSG,UINT uParam,PVOID pContext);



#define CAMERA_MEDIA_TYPE_MONO                           0x01000000
#define CAMERA_MEDIA_TYPE_RGB                            0x02000000
#define CAMERA_MEDIA_TYPE_COLOR                          0x02000000
#define CAMERA_MEDIA_TYPE_CUSTOM                         0x80000000
#define CAMERA_MEDIA_TYPE_COLOR_MASK                     0xFF000000
#define CAMERA_MEDIA_TYPE_OCCUPY1BIT                     0x00010000
#define CAMERA_MEDIA_TYPE_OCCUPY2BIT                     0x00020000
#define CAMERA_MEDIA_TYPE_OCCUPY4BIT                     0x00040000
#define CAMERA_MEDIA_TYPE_OCCUPY8BIT                     0x00080000
#define CAMERA_MEDIA_TYPE_OCCUPY10BIT                    0x000A0000
#define CAMERA_MEDIA_TYPE_OCCUPY12BIT                    0x000C0000
#define CAMERA_MEDIA_TYPE_OCCUPY16BIT                    0x00100000
#define CAMERA_MEDIA_TYPE_OCCUPY24BIT                    0x00180000
#define CAMERA_MEDIA_TYPE_OCCUPY32BIT                    0x00200000
#define CAMERA_MEDIA_TYPE_OCCUPY36BIT                    0x00240000
#define CAMERA_MEDIA_TYPE_OCCUPY48BIT                    0x00300000
#define CAMERA_MEDIA_TYPE_OCCUPY64BIT					 0x00400000

#define CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_MASK      0x00FF0000
#define CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_SHIFT     16

#define CAMERA_MEDIA_TYPE_PIXEL_SIZE(type)                 (((type) & CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_MASK)>>CAMERA_MEDIA_TYPE_EFFECTIVE_PIXEL_SIZE_SHIFT)

#define CAMERA_MEDIA_TYPE_ID_MASK                        0x0000FFFF
#define CAMERA_MEDIA_TYPE_COUNT                          0x46

/*mono*/
#define CAMERA_MEDIA_TYPE_MONO1P             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY1BIT | 0x0037)
#define CAMERA_MEDIA_TYPE_MONO2P             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY2BIT | 0x0038)
#define CAMERA_MEDIA_TYPE_MONO4P             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY4BIT | 0x0039)
#define CAMERA_MEDIA_TYPE_MONO8              (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0001)
#define CAMERA_MEDIA_TYPE_MONO8S             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0002)
#define CAMERA_MEDIA_TYPE_MONO10             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0003)
#define CAMERA_MEDIA_TYPE_MONO10_PACKED      (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0004)
#define CAMERA_MEDIA_TYPE_MONO12             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0005)
#define CAMERA_MEDIA_TYPE_MONO12_PACKED      (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0006)
#define CAMERA_MEDIA_TYPE_MONO14             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0025)
#define CAMERA_MEDIA_TYPE_MONO16             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0007)

/*Bayer */
#define CAMERA_MEDIA_TYPE_BAYGR8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0008)
#define CAMERA_MEDIA_TYPE_BAYRG8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x0009)
#define CAMERA_MEDIA_TYPE_BAYGB8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x000A)
#define CAMERA_MEDIA_TYPE_BAYBG8             (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY8BIT | 0x000B)

#define CAMERA_MEDIA_TYPE_BAYGR10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0026)
#define CAMERA_MEDIA_TYPE_BAYRG10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0027)
#define CAMERA_MEDIA_TYPE_BAYGB10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0028)
#define CAMERA_MEDIA_TYPE_BAYBG10_MIPI       (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY10BIT | 0x0029)


#define CAMERA_MEDIA_TYPE_BAYGR10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000C)
#define CAMERA_MEDIA_TYPE_BAYRG10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000D)
#define CAMERA_MEDIA_TYPE_BAYGB10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000E)
#define CAMERA_MEDIA_TYPE_BAYBG10            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x000F)

#define CAMERA_MEDIA_TYPE_BAYGR12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0010)
#define CAMERA_MEDIA_TYPE_BAYRG12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0011)
#define CAMERA_MEDIA_TYPE_BAYGB12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0012)
#define CAMERA_MEDIA_TYPE_BAYBG12            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0013)


#define CAMERA_MEDIA_TYPE_BAYGR10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0026)
#define CAMERA_MEDIA_TYPE_BAYRG10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0027)
#define CAMERA_MEDIA_TYPE_BAYGB10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0028)
#define CAMERA_MEDIA_TYPE_BAYBG10_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0029)

#define CAMERA_MEDIA_TYPE_BAYGR12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002A)
#define CAMERA_MEDIA_TYPE_BAYRG12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002B)
#define CAMERA_MEDIA_TYPE_BAYGB12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002C)
#define CAMERA_MEDIA_TYPE_BAYBG12_PACKED     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x002D)

#define CAMERA_MEDIA_TYPE_BAYGR16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x002E)
#define CAMERA_MEDIA_TYPE_BAYRG16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x002F)
#define CAMERA_MEDIA_TYPE_BAYGB16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0030)
#define CAMERA_MEDIA_TYPE_BAYBG16            (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0031)

/*RGB */
#define CAMERA_MEDIA_TYPE_RGB8               (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0014)
#define CAMERA_MEDIA_TYPE_BGR8               (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0015)
#define CAMERA_MEDIA_TYPE_RGBA8              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x0016)
#define CAMERA_MEDIA_TYPE_BGRA8              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x0017)
#define CAMERA_MEDIA_TYPE_RGB10              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0018)
#define CAMERA_MEDIA_TYPE_BGR10              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0019)
#define CAMERA_MEDIA_TYPE_RGB12              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x001A)
#define CAMERA_MEDIA_TYPE_BGR12              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x001B)
#define CAMERA_MEDIA_TYPE_RGB16              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0033)
#define CAMERA_MEDIA_TYPE_BGR16              (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x004B)
#define CAMERA_MEDIA_TYPE_RGBA16             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY64BIT | 0x0064)
#define CAMERA_MEDIA_TYPE_BGRA16             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY64BIT | 0x0051)
#define CAMERA_MEDIA_TYPE_RGB10V1_PACKED     (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x001C)
#define CAMERA_MEDIA_TYPE_RGB10P32           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY32BIT | 0x001D)
#define CAMERA_MEDIA_TYPE_RGB12V1_PACKED     (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY36BIT | 0X0034)
#define CAMERA_MEDIA_TYPE_RGB565P            (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0035)
#define CAMERA_MEDIA_TYPE_BGR565P            (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0X0036)

/*YUV and YCbCr*/
#define CAMERA_MEDIA_TYPE_YUV411_8_UYYVYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x001E)
#define CAMERA_MEDIA_TYPE_YUV422_8_UYVY      (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x001F)
#define CAMERA_MEDIA_TYPE_YUV422_8           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0032)
#define CAMERA_MEDIA_TYPE_YUV8_UYV           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0020)
#define CAMERA_MEDIA_TYPE_YCBCR8_CBYCR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x003A)
//CAMERA_MEDIA_TYPE_YCBCR422_8 : YYYYCbCrCbCr
#define CAMERA_MEDIA_TYPE_YCBCR422_8             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x003B)
#define CAMERA_MEDIA_TYPE_YCBCR422_8_CBYCRY      (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0043)
#define CAMERA_MEDIA_TYPE_YCBCR411_8_CBYYCRYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x003C)
#define CAMERA_MEDIA_TYPE_YCBCR601_8_CBYCR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x003D)
#define CAMERA_MEDIA_TYPE_YCBCR601_422_8         (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x003E)
#define CAMERA_MEDIA_TYPE_YCBCR601_422_8_CBYCRY  (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0044)
#define CAMERA_MEDIA_TYPE_YCBCR601_411_8_CBYYCRYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x003F)
#define CAMERA_MEDIA_TYPE_YCBCR709_8_CBYCR           (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0040)
#define CAMERA_MEDIA_TYPE_YCBCR709_422_8             (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0041)
#define CAMERA_MEDIA_TYPE_YCBCR709_422_8_CBYCRY      (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY16BIT | 0x0045)
#define CAMERA_MEDIA_TYPE_YCBCR709_411_8_CBYYCRYY    (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0042)

/*RGB Planar */
#define CAMERA_MEDIA_TYPE_RGB8_PLANAR        (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY24BIT | 0x0021)
#define CAMERA_MEDIA_TYPE_RGB10_PLANAR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0022)
#define CAMERA_MEDIA_TYPE_RGB12_PLANAR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0023)
#define CAMERA_MEDIA_TYPE_RGB16_PLANAR       (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY48BIT | 0x0024)



/*MindVision 12bit packed bayer*/
#define CAMERA_MEDIA_TYPE_BAYGR12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0060)
#define CAMERA_MEDIA_TYPE_BAYRG12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0061)
#define CAMERA_MEDIA_TYPE_BAYGB12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0062)
#define CAMERA_MEDIA_TYPE_BAYBG12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0063)

/*MindVision 12bit packed monochome*/
#define CAMERA_MEDIA_TYPE_MONO12_PACKED_MV     (CAMERA_MEDIA_TYPE_MONO | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0064)
#define CAMERA_MEDIA_TYPE_YUV420P_MV			     (CAMERA_MEDIA_TYPE_COLOR | CAMERA_MEDIA_TYPE_OCCUPY12BIT | 0x0065)
#endif

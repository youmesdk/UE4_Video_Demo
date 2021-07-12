#ifndef ue4_sdk_YouMeErrorCode_h
#define ue4_sdk_YouMeErrorCode_h

#define MAX_DEVICE_ID_LENGTH 512


typedef enum YouMeUserRole {
    YOUME_USER_NONE = 0,         
    YOUME_USER_TALKER_FREE,      
    YOUME_USER_TALKER_ON_DEMAND, 
    YOUME_USER_LISTENER,         
    YOUME_USER_COMMANDER,        
    YOUME_USER_HOST,             
    YOUME_USER_GUSET,            
} YouMeUserRole_t;

typedef enum YouMeAVStatisticType
{
    YOUME_AVS_AUDIO_CODERATE = 1,               
    YOUME_AVS_VIDEO_CODERATE = 2,               
    YOUME_AVS_VIDEO_FRAMERATE = 3,              
    YOUME_AVS_AUDIO_PACKET_UP_LOSS_RATE = 4,    
    YOUME_AVS_AUDIO_PACKET_DOWN_LOSS_RATE = 5,  
    YOUME_AVS_VIDEO_PACKET_UP_LOSS_RATE = 6,    
    YOUME_AVS_VIDEO_PACKET_DOWN_LOSS_RATE = 7,  
    YOUME_AVS_AUDIO_DELAY_MS = 8,               
    YOUME_AVS_VIDEO_DELAY_MS = 9,               
    YOUME_AVS_VIDEO_BLOCK = 10,                 
    YOUME_AVS_AUDIO_PACKET_UP_LOSS_HALF = 11,   
    YOUME_AVS_VIDEO_PACKET_UP_LOSS_HALF = 12,   
    YOUME_AVS_RECV_DATA_STAT = 13,              
    YOUME_AVS_VIDEO_SHARE_CODERATE  = 14,       
    YOUME_AVS_VIDEO_SHARE_FRAMERATE = 15,       
    YOUME_AVS_VIDEO_RESOLUTION = 16,            
    YOUME_AVS_VIDEO_SHARE_RESOLUTION = 17,      
    YOUME_AVS_SEND_DATA_STAT = 18,             
} YouMeAVStatisticType_t;

typedef enum YouMeAudioRouteType
{
    YOUME_AUDIO_ROUTE_SPEAKER               = 0,    
    YOUME_AUDIO_ROUTE_EARPIECE              = 1,    
    YOUME_AUDIO_ROUTE_HEADSET               = 2,    
    YOUME_AUDIO_ROUTE_HEADSET_BLUETOOTH     = 3,    
} YouMeAudioRouteType_t;


typedef enum YouMeEvent {
    YOUME_EVENT_INIT_OK                      = 0,   
    YOUME_EVENT_INIT_FAILED                  = 1,   
    YOUME_EVENT_JOIN_OK                      = 2,   
    YOUME_EVENT_JOIN_FAILED                  = 3,   
    YOUME_EVENT_LEAVED_ONE                   = 4,   
    YOUME_EVENT_LEAVED_ALL                   = 5,   
    YOUME_EVENT_PAUSED                       = 6,   
    YOUME_EVENT_RESUMED                      = 7,   
    YOUME_EVENT_SPEAK_SUCCESS                = 8,   
    YOUME_EVENT_SPEAK_FAILED                 = 9,  
    YOUME_EVENT_RECONNECTING                 = 10,  
    YOUME_EVENT_RECONNECTED                  = 11, 
    YOUME_EVENT_REC_PERMISSION_STATUS        = 12,  
    YOUME_EVENT_BGM_STOPPED                  = 13, 
    YOUME_EVENT_BGM_FAILED                   = 14,  
    //YOUME_EVENT_MEMBER_CHANGE              = 15,  

    YOUME_EVENT_OTHERS_MIC_ON                = 16,  
    YOUME_EVENT_OTHERS_MIC_OFF               = 17, 
    YOUME_EVENT_OTHERS_SPEAKER_ON            = 18,  
    YOUME_EVENT_OTHERS_SPEAKER_OFF           = 19,  
    YOUME_EVENT_OTHERS_VOICE_ON              = 20,  
    YOUME_EVENT_OTHERS_VOICE_OFF             = 21,  
    YOUME_EVENT_MY_MIC_LEVEL                 = 22,  
        
    YOUME_EVENT_MIC_CTR_ON                   = 23,  
    YOUME_EVENT_MIC_CTR_OFF                  = 24,  
    YOUME_EVENT_SPEAKER_CTR_ON               = 25, 
    YOUME_EVENT_SPEAKER_CTR_OFF              = 26,  
    
    YOUME_EVENT_LISTEN_OTHER_ON              = 27,  
    YOUME_EVENT_LISTEN_OTHER_OFF             = 28,  
	
    YOUME_EVENT_LOCAL_MIC_ON		         = 29,  
    YOUME_EVENT_LOCAL_MIC_OFF		         = 30,  
    YOUME_EVENT_LOCAL_SPEAKER_ON	         = 31,  
    YOUME_EVENT_LOCAL_SPEAKER_OFF	         = 32,  

    YOUME_EVENT_GRABMIC_START_OK             = 33,  
    YOUME_EVENT_GRABMIC_START_FAILED         = 34,  
    YOUME_EVENT_GRABMIC_STOP_OK              = 35,  
    YOUME_EVENT_GRABMIC_STOP_FAILED          = 36,  
    YOUME_EVENT_GRABMIC_REQUEST_OK	         = 37,  
    YOUME_EVENT_GRABMIC_REQUEST_FAILED       = 38,  
    YOUME_EVENT_GRABMIC_REQUEST_WAIT         = 39, 
    YOUME_EVENT_GRABMIC_RELEASE_OK           = 40,  
    YOUME_EVENT_GRABMIC_RELEASE_FAILED       = 41,  
    YOUME_EVENT_GRABMIC_ENDMIC               = 42,  

    YOUME_EVENT_GRABMIC_NOTIFY_START         = 43,  
    YOUME_EVENT_GRABMIC_NOTIFY_STOP          = 44,  
    YOUME_EVENT_GRABMIC_NOTIFY_HASMIC        = 45,  
    YOUME_EVENT_GRABMIC_NOTIFY_NOMIC         = 46,  

    YOUME_EVENT_INVITEMIC_SETOPT_OK          = 47,  
    YOUME_EVENT_INVITEMIC_SETOPT_FAILED      = 48,  
    YOUME_EVENT_INVITEMIC_REQUEST_OK         = 49,  
    YOUME_EVENT_INVITEMIC_REQUEST_FAILED     = 50,  
    YOUME_EVENT_INVITEMIC_RESPONSE_OK        = 51,  
    YOUME_EVENT_INVITEMIC_RESPONSE_FAILED    = 52, 
    YOUME_EVENT_INVITEMIC_STOP_OK            = 53,  
    YOUME_EVENT_INVITEMIC_STOP_FAILED        = 54,  

    YOUME_EVENT_INVITEMIC_CAN_TALK           = 55,  
    YOUME_EVENT_INVITEMIC_CANNOT_TALK        = 56,  

    YOUME_EVENT_INVITEMIC_NOTIFY_CALL        = 57,  
    YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER      = 58,  
    YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL      = 59,  
	
	YOUME_EVENT_SEND_MESSAGE_RESULT          = 60, 
    YOUME_EVENT_MESSAGE_NOTIFY               = 61,  
    
    YOUME_EVENT_KICK_RESULT                  = 64,  
    YOUME_EVENT_KICK_NOTIFY                  = 65,  
    
    YOUME_EVENT_FAREND_VOICE_LEVEL           = 66, 
    
    YOUME_EVENT_OTHERS_BE_KICKED             = 67, 
    //68-71 talk已占用
	YOUME_EVENT_SPEAK_RECORD_ON				 = 68,	
	YOUME_EVENT_SPEAK_RECORD_OFF			 = 69,	
	YOUME_EVENT_SPEAK_RECORD_RESET			 = 70,	
    
    YOUME_EVENT_EFFECT_PLAY_COMPLETE            = 71,   
    YOUME_EVENT_AUDIO_START_FAIL                = 72,   
    YOUME_EVENT_AUDIO_INPUT_DEVICE_CONNECT      = 73,   
    YOUME_EVENT_AUDIO_INPUT_DEVICE_DISCONNECT   = 74,   

    YOUME_EVENT_SWITCH_OUTPUT                = 75, 
	YOUME_EVENT_BGM_OR_SPEAR_RECORD          = 76, 
    YOUME_EVENT_AUDIO_ROUTE_CHANGE           = 77, 

    YOUME_EVENT_OTHERS_VIDEO_ON              = 200, 

    YOUME_EVENT_MASK_VIDEO_BY_OTHER_USER     = 204, 
    YOUME_EVENT_RESUME_VIDEO_BY_OTHER_USER   = 205, 
    YOUME_EVENT_MASK_VIDEO_FOR_USER          = 206, 
    YOUME_EVENT_RESUME_VIDEO_FOR_USER        = 207, 
    YOUME_EVENT_OTHERS_VIDEO_SHUT_DOWN       = 208, 
    YOUME_EVENT_OTHERS_VIDEO_INPUT_START     = 209, 
    YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP      = 210, 
    
    YOUME_EVENT_MEDIA_DATA_ROAD_PASS         = 211, 
    YOUME_EVENT_MEDIA_DATA_ROAD_BLOCK        = 212, 
    
    YOUME_EVENT_QUERY_USERS_VIDEO_INFO       = 213, 
    YOUME_EVENT_SET_USERS_VIDEO_INFO         = 214, 
    
    YOUME_EVENT_LOCAL_VIDEO_INPUT_START      = 215, 
    YOUME_EVENT_LOCAL_VIDEO_INPUT_STOP       = 216, 
    
    YOUME_EVENT_START_PUSH                   = 217,
    YOUME_EVENT_SET_PUSH_MIX                 = 218, 
    YOUME_EVENT_ADD_PUSH_MIX_USER            = 219, 
    YOUME_EVENT_OTHER_SET_PUSH_MIX           = 220, 

    YOUME_EVENT_LOCAL_SHARE_INPUT_START      = 221,
    YOUME_EVENT_LOCAL_SHARE_INPUT_STOP       = 222, 
    YOUME_EVENT_OTHERS_SHARE_INPUT_START     = 223,
    YOUME_EVENT_OTHERS_SHARE_INPUT_STOP      = 224, 
    
    YOUME_EVENT_SET_USERS_VIDEO_INFO_NOTIFY  = 225, 
    
    YOUME_EVENT_OTHER_PLAY_BACKGRAOUND_MUSIC = 226,
    YOUME_EVENT_OTHER_STOP_BACKGRAOUND_MUSIC = 227,

    YOUME_EVENT_OTHERS_DATA_ERROR            = 300, 
    YOUME_EVENT_OTHERS_NETWORK_BAD           = 301,
    YOUME_EVENT_OTHERS_BLACK_FULL            = 302,
    YOUME_EVENT_OTHERS_GREEN_FULL            = 303, 
    YOUME_EVENT_OTHERS_BLACK_BORDER          = 304, 
    YOUME_EVENT_OTHERS_GREEN_BORDER          = 305,
    YOUME_EVENT_OTHERS_BLURRED_SCREEN        = 306, 
    YOUME_EVENT_OTHERS_ENCODER_ERROR         = 307, 
    YOUME_EVENT_OTHERS_DECODER_ERROR         = 308, 
    
    YOUME_EVENT_CAMERA_DEVICE_CONNECT        = 400, 
    YOUME_EVENT_CAMERA_DEVICE_DISCONNECT     = 401, 

    YOUME_EVENT_AUDIO_HOWLING_DETECTION      = 450, 

    // video encode param report
    YOUME_EVENT_VIDEO_ENCODE_PARAM_REPORT    = 500,
    YOUME_EVENT_VIDEO_DECODE_PARAM_REPORT    = 501,

    // p2p/server route
    YOUME_EVENT_RTP_ROUTE_P2P                = 600, 
    YOUME_EVENT_RTP_ROUTE_SEREVER            = 601, 
    YOUME_EVENT_RTP_ROUTE_CHANGE_TO_SERVER   = 602, 
    YOUME_EVENT_RTP_ROUTE_SERVER_WITH_P2P_PROBE   = 603,

    YOUME_EVENT_RECOGNIZE_MODULE_INIT_START  = 700, 
    YOUME_EVENT_RECOGNIZE_MODULE_INIT_END    = 701, 
    YOUME_EVENT_RECOGNIZE_MODULE_UNINIT      = 702, 
    YOUME_EVENT_RECOGNIZE_MODULE_ERR         = 703, 

    // for windows/mac share
	YOUME_EVENT_LOCAL_SHARE_WINDOW_CLOSED	 = 725, 
    YOUME_EVENT_LOCAL_SHARE_WINDOW_INVSIABLE = 726, 
    YOUME_EVENT_LOCAL_SHARE_WINDOW_ISICONIC  = 727, 
    YOUME_EVENT_LOCAL_SHARE_WINDOW_NORMAL    = 728, 
	YOUME_EVENT_LOCAL_SHARE_WINDOW_MOVE		 = 729, 

    YOUME_EVENT_EOF                          = 1000,
    
} YouMeEvent_t;

typedef enum YouMeKickReason
{
    YOUME_KICK_ADMIN = 1,          
    YOUME_KICK_RELOGIN = 2,         
} YouMeKickReason_t;


typedef enum YouMeBroadcast
{
	YOUME_BROADCAST_NONE = 0,
	YOUME_BROADCAST_GRABMIC_BROADCAST_GETMIC = 1,	    
	YOUME_BROADCAST_GRABMIC_BROADCAST_FREEMIC = 2,	    
	YOUME_BROADCAST_INVITEMIC_BROADCAST_CONNECT = 3,	
	YOUME_BROADCAST_INVITEMIC_BROADCAST_DISCONNECT = 4, 
}YouMeBroadcast_t;

typedef enum YouMeErrorCode {
    YOUME_SUCCESS                            = 0,    
    
    
    YOUME_ERROR_API_NOT_SUPPORTED            = -1,   
    YOUME_ERROR_INVALID_PARAM                = -2,   
    YOUME_ERROR_ALREADY_INIT                 = -3,   
    YOUME_ERROR_NOT_INIT                     = -4,   

    YOUME_ERROR_CHANNEL_EXIST                = -5,   
    YOUME_ERROR_CHANNEL_NOT_EXIST            = -6,   
    YOUME_ERROR_WRONG_STATE                  = -7,   
    YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK   = -8,   
    YOUME_ERROR_WRONG_CHANNEL_MODE           = -9,   
    YOUME_ERROR_TOO_MANY_CHANNELS            = -10,  
    YOUME_ERROR_TOKEN_ERROR                  = -11,  
    YOUME_ERROR_NOT_IN_CHANNEL               = -12,  
    YOUME_ERROR_BE_KICK                      = -13,  
    YOUME_ERROR_DEVICE_NOT_VALID             = -14,  
    YOUME_ERROR_API_NOT_ALLOWED              = -15,  
    YOUME_ERROR_NO_LANG_CODE                 = -16,  

    
    YOUME_ERROR_MEMORY_OUT                   = -100, 
    YOUME_ERROR_START_FAILED                 = -101, 
    YOUME_ERROR_STOP_FAILED                  = -102, 
    YOUME_ERROR_ILLEGAL_SDK                  = -103, 
    YOUME_ERROR_SERVER_INVALID               = -104, 
    YOUME_ERROR_NETWORK_ERROR                = -105, 
    YOUME_ERROR_SERVER_INTER_ERROR           = -106, 
    YOUME_ERROR_QUERY_RESTAPI_FAIL           = -107, 
    YOUME_ERROR_USER_ABORT                   = -108, 
    YOUME_ERROR_SEND_MESSAGE_FAIL            = -109, 
    YOUME_ERROR_SET_PUSH_PARAM_FAIL          = -110, 
    YOUME_ERROR_INIT_SHARE_FAIL              = -111, 
    YOUME_ERROR_START_SHARE_FAIL             = -112, 
    YOUME_ERROR_SHARE_NO_PERMISSION          = -113,

    
    YOUME_ERROR_REC_INIT_FAILED              = -201, 
    YOUME_ERROR_REC_NO_PERMISSION            = -202, 
    YOUME_ERROR_REC_NO_DATA                  = -203, 
    YOUME_ERROR_REC_OTHERS                   = -204, 
    YOUME_ERROR_REC_PERMISSION_UNDEFINED     = -205, 
    

	YOUME_ERROR_GRABMIC_FULL				 = -301, 
	YOUME_ERROR_GRABMIC_HASEND				 = -302, 

	
	YOUME_ERROR_INVITEMIC_NOUSER			 = -401, 
	YOUME_ERROR_INVITEMIC_OFFLINE			 = -402, 
	YOUME_ERROR_INVITEMIC_REJECT			 = -403, 
	YOUME_ERROR_INVITEMIC_TIMEOUT			 = -404, 

    YOUME_ERROR_CAMERA_OPEN_FAILED           = -501, 
    YOUME_ERROR_CAMERA_EXCEPTION             = -502, 

	YOUME_ERROR_NOT_PROCESS                  = -601, 
   
    YOUME_ERROR_UNKNOWN                      = -1000,

} YouMeErrorCode_t;

typedef enum SERVER_MODE {
    SERVER_MODE_FORMAL               = 0,
    SERVER_MODE_TEST                 = 1,
    SERVER_MODE_DEV                  = 2,
    SERVER_MODE_DEMO                 = 3,
    SERVER_MODE_FIXED_IP_VALIDATE    = 4,
    SERVER_MODE_FIXED_IP_REDIRECT    = 5,
    SERVER_MODE_FIXED_IP_MCU         = 6,
    SERVER_MODE_FIXED_IP_PRIVATE_SERVICE = 7
}SERVER_MODE_t;

typedef enum YOUME_RTC_SERVER_REGION {
    RTC_CN_SERVER       = 0,  
    RTC_HK_SERVER       = 1,  
    RTC_US_SERVER       = 2,  
    RTC_SG_SERVER       = 3,  
    RTC_KR_SERVER       = 4,  
    RTC_AU_SERVER       = 5,  
    RTC_DE_SERVER       = 6,  
    RTC_BR_SERVER       = 7,  
    RTC_IN_SERVER       = 8,  
    RTC_JP_SERVER       = 9,  
    RTC_IE_SERVER       = 10, 
    RTC_USW_SERVER      = 11, 
    RTC_USM_SERVER      = 12, 
    RTC_CA_SERVER       = 13, 
    RTC_LON_SERVER      = 14, 
    RTC_FRA_SERVER      = 15, 
    RTC_DXB_SERVER      = 16, 
    RTC_NAF_SERVER      = 17, 
    RTC_CAF_SERVER      = 18, 
    RTC_SAF_SERVER      = 19, 
    RTC_EAF_SERVER      = 20, 
    RTC_WAF_SERVER      = 21, 
    RTC_RUS_SERVER      = 22, 

    RTC_NCN_SERVER      = 201, 
    RTC_NECN_SERVER     = 202, 
    RTC_ECN_SERVER      = 203, 
    RTC_CCN_SERVER      = 204, 
    RTC_SCN_SERVER      = 205, 
    RTC_WSCN_SERVER     = 206, 

    RTC_EXT_SERVER     = 10000, 
    RTC_DEFAULT_SERVER = 10001, 
}YOUME_RTC_SERVER_REGION_t;

typedef enum YOUME_LOG_LEVEL{
    LOG_DISABLED = 0,
    LOG_FATAL = 1,
    LOG_ERROR = 10,
    LOG_WARNING = 20,
    LOG_INFO = 40,
    LOG_DEBUG = 50,
    LOG_VERBOSE = 60
} YOUME_LOG_LEVEL_t;

typedef enum YOUME_SAMPLE_RATE{
    SAMPLE_RATE_8 = 8000,
    SAMPLE_RATE_16 = 16000,
    SAMPLE_RATE_24 = 24000,
    SAMPLE_RATE_32 = 32000,
    SAMPLE_RATE_44 = 44100,
    SAMPLE_RATE_48 = 48000
} YOUME_SAMPLE_RATE_t;

typedef enum YOUME_AUDIO_QUALITY {
    LOW_QUALITY = 0,
    HIGH_QUALITY
} YOUME_AUDIO_QUALITY_t;

typedef enum YouMeVideoRenderMode {
    YOUME_VIDEO_RENDER_MODE_HIDDEN = 0,
    YOUME_VIDEO_RENDER_MODE_FIT = 1,
    YOUME_VIDEO_RENDER_MODE_ADAPTIVE = 2,
    YOUME_VIDEO_RENDER_MODE_STRETCH = 3
}YouMeVideoRenderMode_t;

typedef enum YouMeVideoMirrorMode {
    YOUME_VIDEO_MIRROR_MODE_AUTO = 0,            
    YOUME_VIDEO_MIRROR_MODE_ENABLED = 1,         
    YOUME_VIDEO_MIRROR_MODE_DISABLED = 2,        
    YOUME_VIDEO_MIRROR_MODE_NEAR = 3,            
    YOUME_VIDEO_MIRROR_MODE_FAR = 4              
}YouMeVideoMirrorMode_t;


typedef enum YOUME_VIDEO_FMT{
    VIDEO_FMT_RGBA32 = 0,
    VIDEO_FMT_BGRA32 = 1,
    VIDEO_FMT_YUV420P = 2,
    VIDEO_FMT_NV21 = 3,
    VIDEO_FMT_YV12 = 4,
    VIDEO_FMT_CVPIXELBUFFER  = 5,
    VIDEO_FMT_TEXTURE = 6,
    VIDEO_FMT_TEXTURE_OES = 7,
    VIDEO_FMT_RGB24 = 8,
    VIDEO_FMT_NV12 = 9,
    VIDEO_FMT_H264 = 10,
    VIDEO_FMT_ABGR32 = 11,
    VIDEO_FMT_TEXTURE_YUV = 12,
    VIDEO_FMT_ENCRYPT = 13,
}YOUME_VIDEO_FMT_t;

typedef enum YOUME_VIDEO_SHARE_TYPE {
    VIDEO_SHARE_TYPE_DEVICE = 1,    
    VIDEO_SHARE_TYPE_WINDOW = 2,    
    VIDEO_SHARE_TYPE_SCREEN = 3,    
    VIDEO_SHARE_TYPE_UNKNOW,
}YOUME_VIDEO_SHARE_TYPE_t;

typedef enum PcmCallBackFlag{
    PcmCallbackFlag_Remote = 0x1,       
    PcmCallbackFlag_Record = 0x2,      
    PcmCallbackFlag_Mix = 0x4,          
} PcmCallBackFlag_t;

typedef enum  YouMeLanguageCode
{
    LANG_AUTO,
    LANG_AF,            
    LANG_AM,            
    LANG_AR,            
    LANG_AR_AE,            
    LANG_AR_BH,            
    LANG_AR_DZ,            
    LANG_AR_KW,            
    LANG_AR_LB,            
    LANG_AR_OM,            
    LANG_AR_SA,            
    LANG_AR_SD,            
    LANG_AR_TN,            
    LANG_AZ,            
    LANG_BE,            
    LANG_BG,            
    LANG_BN,            
    LANG_BS,            
    LANG_CA,            
    LANG_CA_ES,            
    LANG_CO,            
    LANG_CS,            
    LANG_CY,            
    LANG_DA,            
    LANG_DE,            
    LANG_DE_CH,            
    LANG_DE_LU,            
    LANG_EL,            
    LANG_EN,            
    LANG_EN_CA,            
    LANG_EN_IE,            
    LANG_EN_ZA,            
    LANG_EO,            
    LANG_ES,            
    LANG_ES_BO,            
    LANG_ES_AR,            
    LANG_ES_CO,            
    LANG_ES_CR,            
    LANG_ES_ES,            
    LANG_ET,           
    LANG_ES_PA,            
    LANG_ES_SV,            
    LANG_ES_VE,            
    LANG_ET_EE,            
    LANG_EU,            
    LANG_FA,            
    LANG_FI,            
    LANG_FR,           
    LANG_FR_BE,            
    LANG_FR_CA,           
    LANG_FR_CH,         
    LANG_FR_LU,          
    LANG_FY,          
    LANG_GA,           
    LANG_GD,         
    LANG_GL,         
    LANG_GU,         
    LANG_HA,        
    LANG_HI,          
	LANG_HR,
	LANG_HT,           
    LANG_HU,            
    LANG_HY,            
    LANG_ID,            
    LANG_IG,            
    LANG_IS,         
    LANG_IT,           
    LANG_IT_CH,           
    LANG_JA,           
    LANG_KA,            
    LANG_KK,          
    LANG_KN,           
    LANG_KM,           
    LANG_KO,           
    LANG_KO_KR,          
    LANG_KU,           
    LANG_KY,           
    LANG_LA,         
    LANG_LB,           
    LANG_LO,          
    LANG_LT,          
    LANG_LV,          
    LANG_MG,          
    LANG_MI,          
    LANG_MK,         
    LANG_ML,         
    LANG_MN,         
    LANG_MR,          
    LANG_MS,          
    LANG_MT,          
    LANG_MY,         
    LANG_NL,         
    LANG_NL_BE,         
    LANG_NE,            
    LANG_NO,          
    LANG_NY,           
    LANG_PL,         
    LANG_PS,         
    LANG_PT,         
    LANG_PT_BR,         
    LANG_RO,          
    LANG_RU,         
    LANG_SD,          
    LANG_SI,            
    LANG_SK,         
    LANG_SL,          
    LANG_SM,           
    LANG_SN,         
    LANG_SO,          
    LANG_SQ,         
    LANG_SR,        
    LANG_ST,        
    LANG_SU,          
    LANG_SV,           
    LANG_SV_SE,         
    LANG_SW,          
    LANG_TA,         
    LANG_TE,          
    LANG_TG,         
    LANG_TH,           
    LANG_TL,          
    LANG_TR,           
    LANG_UK,          
    LANG_UR,          
    LANG_UZ,         
    LANG_VI,         
    LANG_XH,         
    LANG_YID,          
    LANG_YO,          
    LANG_ZH,         
    LANG_ZH_TW,      
    LANG_ZU             
} YouMeLanguageCode_t;

typedef enum YoumeTransRouteType {
    YOUME_TRANS_ROUTE_SERVER = 0,  
    YOUME_TRANS_ROUTE_P2P    = 1,  
}YoumeRtpRouteType_t;

typedef struct YMAudioFrameInfo {
    int channels;
    int sampleRate;
    int bytesPerFrame;
    int isFloat;
    int isBigEndian;
    int isSignedInteger;
    int isNonInterleaved;
    unsigned long long timestamp;
} YMAudioFrameInfo_t;

typedef enum YMVideoCodecType{
    YOUME_VIDEO_CODEC_H264 = 0,
    YOUME_VIDEO_CODEC_H265,
    YOUME_VIDEO_CODEC_VP8,
    YOUME_VIDEO_CODEC_VP9,
}YMVideoCodecType_t;


typedef enum YMVideoStreamType{
    YOUME_VIDEO_STREAM_MAIN = 0,
    YOUME_VIDEO_STREAM_SUB,
    YOUME_VIDEO_STREAM_SHARE,
    YOUME_VIDEO_STREAM_MAIN_AND_SHARE,
    YOUME_VIDEO_STREAM_SUB_AND_SHARE,
}YMVideoStreamType_t;

#endif

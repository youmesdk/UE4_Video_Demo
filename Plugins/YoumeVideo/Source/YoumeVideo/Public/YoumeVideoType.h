// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YouMeConstDefine.h"
#include "YoumeVideoType.generated.h"



UENUM(BlueprintType)
enum class EYVUserRole : uint8
{
	USER_NONE = 0,         // Illegal users, this parameter cannot be passed when calling the API
	USER_TALKER_FREE,      // Free-speaker, suitable for group calls (it is recommended that the number of group members is at most 10), everyone can speak at any time, and can only be in one voice channel at a time
	USER_TALKER_ON_DEMAND, // You can speak only after requesting microphone permission by grabbing the microphone, etc. It is suitable for larger groups or unions (such as dozens of people). Only one or a few people can speak at the same time, and only one voice at the same time In the channel
	USER_LISTENER,         // The audience, the audience of the anchor/conductor/guest, can only be in one voice channel at the same time, only listening but not speaking
	USER_COMMANDER,        // Commander, country/gang, etc., can only speak in one voice channel at a time, can speak at any time, can play background music, and can monitor their own voice while wearing headphones
	USER_HOST,             // The host, the host of a broadcast voice channel, can only speak in one voice channel at a time, can speak at any time, can play background music, and can monitor his own voice while wearing headphones
	USER_GUSET             // The guest, the host or guest invited by the host, can only speak in one voice channel at the same time, and they can speak at any time
};

UENUM(BlueprintType)
enum class EYVAVStatisticType : uint8
{
	AVS_AUDIO_CODERATE,               //Audio transmission bit rate, userid is itself: uplink bit rate, userid others: downlink bit rate, unit Bps
	AVS_VIDEO_CODERATE,               //Camera video transmission bit rate, userid is self: uplink bit rate, userid others: downlink bit rate, unit Bps
	AVS_VIDEO_FRAMERATE,              //Video frame rate, userid is self: uplink frame rate, userid others: downlink frame rate
	AVS_AUDIO_PACKET_UP_LOSS_RATE,    //Audio upstream packet loss rate (full process), per thousand
	AVS_AUDIO_PACKET_DOWN_LOSS_RATE,  //Audio downstream packet loss rate (full process), per thousand
	AVS_VIDEO_PACKET_UP_LOSS_RATE,    //Video upstream packet loss rate (full process), per thousand
	AVS_VIDEO_PACKET_DOWN_LOSS_RATE,  //Video downstream packet loss rate (full process), per thousand
	AVS_AUDIO_DELAY_MS,               //Audio delay (RTT), in milliseconds
	AVS_VIDEO_DELAY_MS,               //Video delay (RTT), in milliseconds
	AVS_VIDEO_BLOCK,                  //Video freezes, has it happened?
	AVS_AUDIO_PACKET_UP_LOSS_HALF,    //Audio upstream server packet loss rate (half journey), per thousand
	AVS_VIDEO_PACKET_UP_LOSS_HALF,    //Server packet loss rate of video upstream (half journey), per thousand
	AVS_RECV_DATA_STAT,               //Downlink bandwidth, unit Bps
	AVS_VIDEO_SHARE_CODERATE,         //Shared video transmission bit rate, userid is self: uplink bit rate, userid others: downlink bit rate, unit Bps
	AVS_VIDEO_SHARE_FRAMERATE,        //Shared video transmission frame rate, userid is self: uplink frame rate, userid others: downlink frame rate
	AVS_VIDEO_RESOLUTION,             //Video resolution is reported, userid is self: uplink resolution, userid others: downlink resolution
	AVS_VIDEO_SHARE_RESOLUTION,       //Shared stream resolution report, userid is self: uplink resolution, userid others: downlink resolution
	AVS_SEND_DATA_STAT                //Uplink bandwidth, unit Bps
};

UENUM(BlueprintType)
enum class EYVAudioRouteType : uint8
{
	AUDIO_ROUTE_SPEAKER = 0,    // Phone speaker
	AUDIO_ROUTE_EARPIECE = 1,    // earpiece
	AUDIO_ROUTE_HEADSET = 2,    // headset
	AUDIO_ROUTE_HEADSET_BLUETOOTH = 3,    // Bluetooth earphone
};

UENUM(BlueprintType)
enum class EYVEvent : uint8
{
	INIT_OK, // SDK initialized successfully
	INIT_FAILED,   // SDK initialization failed
	JOIN_OK,   // Successfully entered the voice channel
	JOIN_FAILED,   // Failed to enter the voice channel
	LEAVED_ONE,   // Exit a single voice channel complete
	LEAVED_ALL,   // Exit all voice channels complete
	PAUSED,   // Pause voice channel complete
	RESUMED,   // Restore voice channel complete
	SPEAK_SUCCESS,   // Switch to speak to the specified channel successfully (applicable to multi-channel mode)
	SPEAK_FAILED,   // Failed to switch to speak to the specified channel (applicable to multi-channel mode)
	RECONNECTING,  // Disconnected, reconnecting
	RECONNECTED,  // Successfully reconnected after disconnection
	REC_PERMISSION_STATUS,  // Notify recording permission status
	BGM_STOPPED,  // Notify the end of background music playback
	BGM_FAILED,  // Notify background music playback failed
	//MEMBER_CHANGE,  // Channel membership changes

	OTHERS_MIC_ON,  // Other user microphones open
	OTHERS_MIC_OFF,  // Other users’ microphones turned off
	OTHERS_SPEAKER_ON,  // Other user speakers are turned on
	OTHERS_SPEAKER_OFF,  // Other users' speakers are off
	OTHERS_VOICE_ON,  // Other users enter the speaking state
	OTHERS_VOICE_OFF,  // Other users enter silent state
	MY_MIC_LEVEL,  // Microphone voice level

	MIC_CTR_ON,  // The microphone was opened by another user
	MIC_CTR_OFF,  // The microphone was turned off by another user
	SPEAKER_CTR_ON,  // The speaker is turned on by another user
	SPEAKER_CTR_OFF,  // The speaker was turned off by another user

	LISTEN_OTHER_ON,  // Unblock someone's voice
	LISTEN_OTHER_OFF,  // Block someone's voice

	LOCAL_MIC_ON,  // Own microphone on
	LOCAL_MIC_OFF,  // Own microphone off
	LOCAL_SPEAKER_ON,  // Own speakers are turned on
	LOCAL_SPEAKER_OFF,  // Own speakers off

	GRABMIC_START_OK,  // Successfully initiated the grabbing activity
	GRABMIC_START_FAILED,  // Failed to initiate a grabbing activity
	GRABMIC_STOP_OK,  // Successfully stopped grabbing activities
	GRABMIC_STOP_FAILED,  // Failed to stop grabbing activities
	GRABMIC_REQUEST_OK,  // Successfully grab the microphone (can speak)
	GRABMIC_REQUEST_FAILED,  // Failed to grab microphone
	GRABMIC_REQUEST_WAIT,  // Enter the waiting queue for grabbing microphone (only this event will be called back in weight mode)
	GRABMIC_RELEASE_OK,  // Release microphone successfully
	GRABMIC_RELEASE_FAILED,  // Failed to release wheat
	GRABMIC_ENDMIC,  // No longer occupy the microphone (the time when the wheat is used or other reasons)

	GRABMIC_NOTIFY_START,  // [Notice] Grab microphone activity starts
	GRABMIC_NOTIFY_STOP,  // [Notice] The microphone grab event is over
	GRABMIC_NOTIFY_HASMIC,  // [Notice] There is a microphone to grab
	GRABMIC_NOTIFY_NOMIC,  // [Notice] There is no microphone to grab

	INVITEMIC_SETOPT_OK,  // The microphone is set successfully
	INVITEMIC_SETOPT_FAILED,  // Failed to set up microphone
	INVITEMIC_REQUEST_OK,  // The request to connect to the microphone is successful (connected, need to wait for the other party to respond)
	INVITEMIC_REQUEST_FAILED,  // The request to connect to the microphone failed
	INVITEMIC_RESPONSE_OK,  // Responding to the microphone successfully
	INVITEMIC_RESPONSE_FAILED,  // Response to microphone failure
	INVITEMIC_STOP_OK,  // Successfully stop connecting to the microphone
	INVITEMIC_STOP_FAILED,  // Failed to stop connecting to the microphone

	INVITEMIC_CAN_TALK,  // Both parties can talk (the responder has agreed)
	INVITEMIC_CANNOT_TALK,  // The two parties can no longer talk (one of the parties ended the microphone connection or the microphone connection time is up)

	INVITEMIC_NOTIFY_CALL,  // [Notification] Someone requested to connect to your microphone
	INVITEMIC_NOTIFY_ANSWER,  // [Notification] The other party responded to your request to connect to the microphone (Agree/Reject/Timeout, if agreed, both parties can talk)
	INVITEMIC_NOTIFY_CANCEL,  // [Notice] During the microphone connection, the other party ended the microphone connection or the microphone connection time is up

	SEND_MESSAGE_RESULT,  // Notification of the success or failure of sendMessage, param is the returned requestID
	MESSAGE_NOTIFY,  // Message received, param is the message content

	KICK_RESULT,  // Kicking response
	KICK_NOTIFY,  // Kicked notice

	FAREND_VOICE_LEVEL,  // The volume of the far-end speaker

	OTHERS_BE_KICKED,  // Other people in the room were kicked out of the room
	
	SPEAK_RECORD_ON,	// Loudspeaker recording start notification (success, failure)
	SPEAK_RECORD_OFF,	// Loudspeaker recording close notification (success, failure)
	SPEAK_RECORD_RESET,	// Restart notification recorded in the speaker (success, failure)

	EFFECT_PLAY_COMPLETE,   // Sound effect playback completed
	AUDIO_START_FAIL,   // Audio failed to start, the device may be occupied by other apps
	AUDIO_INPUT_DEVICE_CONNECT,   // The audio capture device is plugged in, and the mobile terminal is invalid
	AUDIO_INPUT_DEVICE_DISCONNECT,   // The audio capture device is unplugged, and the mobile terminal is invalid

	SWITCH_OUTPUT, // Switch speaker/handset
	BGM_OR_SPEAR_RECORD, // Background music or internal recording, only one can be opened at the same time
	AUDIO_ROUTE_CHANGE, // Audio route change event (YouMeAudioRouteType_t)

	OTHERS_VIDEO_ON, // Receive video streams from other users

	MASK_VIDEO_BY_OTHER_USER, // Video is blocked by other users
	RESUME_VIDEO_BY_OTHER_USER, // The video was restored by another user
	MASK_VIDEO_FOR_USER, // Whose video is blocked
	RESUME_VIDEO_FOR_USER, // Whose video was restored
	OTHERS_VIDEO_SHUT_DOWN, // The video stream of other users is disconnected (including network interruption)
	OTHERS_VIDEO_INPUT_START, // Other users start video input (start the camera under internal capture/start input under external input)
	OTHERS_VIDEO_INPUT_STOP, // Other user video input stop (stop camera under internal capture/stop input under external input)

	MEDIA_DATA_ROAD_PASS, // The audio and video data path is connected, and it is checked regularly. The PASS event will be received when the data is received at the beginning, and then will be sent when it changes.
	MEDIA_DATA_ROAD_BLOCK, // Audio and video data path is blocked

	QUERY_USERS_VIDEO_INFO, // Query user video information return
	SET_USERS_VIDEO_INFO, // Set user to receive video information return

	LOCAL_VIDEO_INPUT_START, // Start of local video input (start camera under internal collection/start input under external input)
	LOCAL_VIDEO_INPUT_STOP, // Local video input stop (stop camera under internal capture/stop input under external input)

	START_PUSH, // Set the return event of startPush
	SET_PUSH_MIX, // Set the return event of setPushMix
	ADD_PUSH_MIX_USER, // Set the return event of addPushMixUser, parameter userID
	OTHER_SET_PUSH_MIX, // When I called setPushMix and didn’t stop, someone in the room called setPushMix and I was kicked.

	LOCAL_SHARE_INPUT_START, // Local shared video input starts
	LOCAL_SHARE_INPUT_STOP, // Local shared video input stopped
	OTHERS_SHARE_INPUT_START, // Other users share video input start
	OTHERS_SHARE_INPUT_STOP, // Other users sharing video input stops

	SET_USERS_VIDEO_INFO_NOTIFY, // Set the user to receive the notification of video information to the sender

	OTHER_PLAY_BACKGRAOUND_MUSIC, // Others play background music
	OTHER_STOP_BACKGRAOUND_MUSIC, // Other people stop background music

	OTHERS_DATA_ERROR, // data error
	OTHERS_NETWORK_BAD, // Bad network
	OTHERS_BLACK_FULL, // Black screen
	OTHERS_GREEN_FULL, // Green screen
	OTHERS_BLACK_BORDER, // Black border
	OTHERS_GREEN_BORDER, // Green edge
	OTHERS_BLURRED_SCREEN, // Huaping
	OTHERS_ENCODER_ERROR, // Coding error
	OTHERS_DECODER_ERROR, // Decoding error

	CAMERA_DEVICE_CONNECT, // The camera device is plugged in, and the mobile terminal is invalid
	CAMERA_DEVICE_DISCONNECT, // The camera device is unplugged, the mobile terminal is invalid

	AUDIO_HOWLING_DETECTION, // Howling detected

	// video encode param report
	VIDEO_ENCODE_PARAM_REPORT,
	VIDEO_DECODE_PARAM_REPORT,

	// p2p/server route
	RTP_ROUTE_P2P, // P2P channel detection ok, current channel is P2P
	RTP_ROUTE_SEREVER, // P2P path detection failed, the current path is server forwarding
	RTP_ROUTE_CHANGE_TO_SERVER, // P2P detection fails during operation, switch to server forwarding
	RTP_ROUTE_SERVER_WITH_P2P_PROBE, // In server forwarding mode, P2P detection is successful

	RECOGNIZE_MODULE_INIT_START, // Speech recognition initialization starts
	RECOGNIZE_MODULE_INIT_END, // Speech recognition initialization completed
	RECOGNIZE_MODULE_UNINIT, // End of speech recognition
	RECOGNIZE_MODULE_ERR, // Speech recognition error

	// for windows/mac share
	LOCAL_SHARE_WINDOW_CLOSED, // The sharing window is closed
	LOCAL_SHARE_WINDOW_INVSIABLE, // The sharing window is hidden and invisible
	LOCAL_SHARE_WINDOW_ISICONIC, // The shared window is minimized
	LOCAL_SHARE_WINDOW_NORMAL, // The sharing window returns to normal
	LOCAL_SHARE_WINDOW_MOVE, // The position of the sharing window has changed

	LOCAL_EOF
};

UENUM(BlueprintType)
enum class EYVKickReason : uint8
{
	KICK_ADMIN,           // Admin kicks people
	KICK_RELOGIN,         // Multi-terminal login kicked
};

UENUM(BlueprintType)
enum class EYVBroadcast : uint8
{
	BROADCAST_NONE = 0,
	BROADCAST_GRABMIC_BROADCAST_GETMIC = 1,	    // Someone grabbed the microphone
	BROADCAST_GRABMIC_BROADCAST_FREEMIC = 2,	    // Someone released the microphone
	BROADCAST_INVITEMIC_BROADCAST_CONNECT = 3,	// A and B are connecting microphones
	BROADCAST_INVITEMIC_BROADCAST_DISCONNECT = 4, // A and B canceled the microphone connection
};

UENUM(BlueprintType)
enum class EYVErrorCode : uint8
{
	SUCCESS,    // success

	// Parameters and status check
	ERROR_API_NOT_SUPPORTED,   // The SDK being used does not support a specific API
	ERROR_INVALID_PARAM,   // Incoming parameter error
	ERROR_ALREADY_INIT,   // Initialized
	ERROR_NOT_INIT,   // It has not been initialized. Before calling a function, you must call the initialization and ensure that the initialization is successful according to the return value.
	ERROR_CHANNEL_EXIST,   // The channel to join already exists
	ERROR_CHANNEL_NOT_EXIST,   // The channel to be quit does not exist, or the channel specified by other operations does not exist
	ERROR_WRONG_STATE,   // State error
	ERROR_NOT_ALLOWED_MOBILE_NETWROK,   // Mobile network is not allowed
	ERROR_WRONG_CHANNEL_MODE,   // Multi-channel interface is called in single channel mode, or vice versa
	ERROR_TOO_MANY_CHANNELS,  // Joined too many channels at the same time
	ERROR_TOKEN_ERROR,  // Incoming token authentication error
	ERROR_NOT_IN_CHANNEL,  // User is not on this channel
	ERROR_BE_KICK,  // Was kicked and was not allowed to enter the room during the prohibited time
	ERROR_DEVICE_NOT_VALID,  // The set device is unavailable
	ERROR_API_NOT_ALLOWED,  // No permission for specific functions
	ERROR_NO_LANG_CODE,  // The translation function specifies a language that does not exist

	// Internal operation error
	ERROR_MEMORY_OUT, // Memory error
	ERROR_START_FAILED, // Failed to start engine
	ERROR_STOP_FAILED, //  Failed to stop the engine
	ERROR_ILLEGAL_SDK, // Illegal use of SDK
	ERROR_SERVER_INVALID, // Voice service is unavailable
	ERROR_NETWORK_ERROR, // Network Error
	ERROR_SERVER_INTER_ERROR, // Server internal error
	ERROR_QUERY_RESTAPI_FAIL, // Failed to request RestApi information
	ERROR_USER_ABORT, // The user requested to interrupt the current operation
	ERROR_SEND_MESSAGE_FAIL, // Failed to send message
	ERROR_SET_PUSH_PARAM_FAIL, // Failed to set Push parameters to the server
	ERROR_INIT_SHARE_FAIL, // Failed to initialize shared device
	ERROR_START_SHARE_FAIL, // Failed to start video sharing
	ERROR_SHARE_NO_PERMISSION, // Shared video does not have permission


	// Microphone suppression error
	ERROR_REC_INIT_FAILED, // Failed to initialize the recording module
	ERROR_REC_NO_PERMISSION, // No recording permission
	ERROR_REC_NO_DATA, // Although the initialization is successful, there is no audio data output. For example, when the recording permission of oppo series mobile phones is prohibited
	ERROR_REC_OTHERS, // Errors in other recording modules
	ERROR_REC_PERMISSION_UNDEFINED, // The recording permission is not determined. When iOS displays the dialog box whether to allow recording permission, this error code is returned

	// Microphone grab error
	ERROR_GRABMIC_FULL, // Failed to grab the microphone, the number of people is full
	ERROR_GRABMIC_HASEND, // Failed to grab the microphone, the activity has ended

	// Microphone connection error
	ERROR_INVITEMIC_NOUSER, // Failed to connect to the microphone, the user does not exist
	ERROR_INVITEMIC_OFFLINE, // Failed to connect to the microphone, the user is offline
	ERROR_INVITEMIC_REJECT, // Failed to connect to the microphone, the user refused
	ERROR_INVITEMIC_TIMEOUT, // Failed to connect to the microphone, there are two situations: 1. When the microphone is connected, the other party does not answer after timeout 2. During the call, the time for both parties to talk is up

	ERROR_CAMERA_OPEN_FAILED, // Failed to open camera
	ERROR_CAMERA_EXCEPTION, // Camera device is abnormal

	ERROR_NOT_PROCESS, // Do not make any changes

	ERROR_UNKNOWN // unknown mistake
};

UENUM(BlueprintType)
enum class EYVServerMode : uint8
{
	MODE_FORMAL,
	MODE_TEST,
	MODE_DEV,
	MODE_DEMO,
	MODE_FIXED_IP_VALIDATE,
	MODE_FIXED_IP_REDIRECT,
	MODE_FIXED_IP_MCU,
	MODE_FIXED_IP_PRIVATE_SERVICE
};

UENUM(BlueprintType)
enum class EYVRtcServerRegion : uint8
{
	RTC_CN_SERVER,  // China
	RTC_HK_SERVER,  // Hong Kong
	RTC_US_SERVER,  // Eastern United States
	RTC_SG_SERVER,  // Singapore
	RTC_KR_SERVER,  // Korea
	RTC_AU_SERVER,  // Australia
	RTC_DE_SERVER,  // Germany
	RTC_BR_SERVER,  // Brazil
	RTC_IN_SERVER,  // India
	RTC_JP_SERVER,  // Japan
	RTC_IE_SERVER,  // Ireland
	RTC_USW_SERVER, // Western America
	RTC_USM_SERVER, // Central America
	RTC_CA_SERVER,  // Canada
	RTC_LON_SERVER, // London
	RTC_FRA_SERVER, // Frankfurt
	RTC_DXB_SERVER, // Dubai
	RTC_NAF_SERVER, // north africa
	RTC_CAF_SERVER, // Central Africa
	RTC_SAF_SERVER, // South Africa
	RTC_EAF_SERVER, // East Africa
	RTC_WAF_SERVER, // West Africa
	RTC_RUS_SERVER, // Russia

	RTC_NCN_SERVER, // north china
	RTC_NECN_SERVER, // northeast
	RTC_ECN_SERVER, // East China
	RTC_CCN_SERVER, // Central China
	RTC_SCN_SERVER, // South China
	RTC_WSCN_SERVER, // southwest

	RTC_EXT_SERVER, // Use extension server
	RTC_DEFAULT_SERVER // Default server
};

UENUM(BlueprintType)
enum class EYVLogLevel : uint8
{
	LOG_DISABLED,
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO,
	LOG_DEBUG,
	LOG_VERBOSE
};

UENUM(BlueprintType)
enum class EYVSampleRate : uint8
{
	SAMPLE_RATE_8,
	SAMPLE_RATE_16,
	SAMPLE_RATE_24,
	SAMPLE_RATE_32,
	SAMPLE_RATE_44,
	SAMPLE_RATE_48
};

UENUM(BlueprintType)
enum class EYVVudioQuality : uint8
{
	LOW_QUALITY,
	HIGH_QUALITY
};

UENUM(BlueprintType)
enum class EYVVideoRenderMode : uint8
{
	VIDEO_RENDER_MODE_HIDDEN,
	VIDEO_RENDER_MODE_FIT,
	VIDEO_RENDER_MODE_ADAPTIVE,
	VIDEO_RENDER_MODE_STRETCH
};

UENUM(BlueprintType)
enum class EYVVideoMirrorMode : uint8
{
	VIDEO_MIRROR_MODE_AUTO,            //Internal acquisition self-adaptive mirroring, external acquisition is closed mirroring
	VIDEO_MIRROR_MODE_ENABLED,         //Both near and far ends are mirrored
	VIDEO_MIRROR_MODE_DISABLED,        //Close mirror
	VIDEO_MIRROR_MODE_NEAR,            //Near-end mirror
	VIDEO_MIRROR_MODE_FAR              //Remote mirroring
};

UENUM(BlueprintType)
enum class EYVVideoFmt : uint8
{
	VIDEO_FMT_RGBA32,
	VIDEO_FMT_BGRA32,
	VIDEO_FMT_YUV420P,
	VIDEO_FMT_NV21,
	VIDEO_FMT_YV12,
	VIDEO_FMT_CVPIXELBUFFER,
	VIDEO_FMT_TEXTURE,
	VIDEO_FMT_TEXTURE_OES,
	VIDEO_FMT_RGB24,
	VIDEO_FMT_NV12,
	VIDEO_FMT_H264,
	VIDEO_FMT_ABGR32,
	VIDEO_FMT_TEXTURE_YUV,
	VIDEO_FMT_ENCRYPT
};

UENUM(BlueprintType)
enum class EYVVideoShareType : uint8
{
	VIDEO_SHARE_TYPE_DEVICE,    // device capture(eg:camera)
	VIDEO_SHARE_TYPE_WINDOW,    // window capture
	VIDEO_SHARE_TYPE_SCREEN,    // screen capture
	VIDEO_SHARE_TYPE_UNKNOW,
};

UENUM(BlueprintType)
enum class EYVPcmCallBackFlag : uint8
{
	PcmCallbackFlag_Remote,       //Remote pcm callback
	PcmCallbackFlag_Record,       //Local recording callback
	PcmCallbackFlag_Mix           //Callback after local recording and remote pcm mix
};

UENUM(BlueprintType)
enum class EYVLanguageCode : uint8
{
	LANG_AUTO,
	LANG_AF,            // Afrikaans
	LANG_AM,            // Amharic
	LANG_AR,            // Arabic
	LANG_AR_AE,         // Arabic + United Arab Emirates
	LANG_AR_BH,         // Arabic + Bahrain
	LANG_AR_DZ,         // Arabic+Algeria
	LANG_AR_KW,         // Arabic+Kuwait
	LANG_AR_LB,         // Arabic + Lebanon
	LANG_AR_OM,         // Arabic+Oman
	LANG_AR_SA,         // Arabic + Saudi Arabia
	LANG_AR_SD,         // Arabic + Sudan
	LANG_AR_TN,         // Arabic + Tunisia
	LANG_AZ,            // Azerbaijan
	LANG_BE,            // Belarusian
	LANG_BG,            // Bulgarian
	LANG_BN,            // Bengal
	LANG_BS,            // Bosnian
	LANG_CA,            // Catalan
	LANG_CA_ES,         // Catalan + Spain
	LANG_CO,            // Corsica
	LANG_CS,            // Czech
	LANG_CY,            // Welsh
	LANG_DA,            // Danish
	LANG_DE,            // German
	LANG_DE_CH,         // German+Swiss
	LANG_DE_LU,         // German+Luxembourg
	LANG_EL,            // Greek
	LANG_EN,            // English
	LANG_EN_CA,         // English+Canada
	LANG_EN_IE,         // English + Ireland
	LANG_EN_ZA,         // English + South Africa
	LANG_EO,            // Esperanto
	LANG_ES,            // Spanish
	LANG_ES_BO,         // Spanish + Bolivia
	LANG_ES_AR,         // Spanish + Argentina
	LANG_ES_CO,         // Spanish + Colombia
	LANG_ES_CR,         // Spanish + Costa Rica
	LANG_ES_ES,         // Spanish+Spain
	LANG_ET,            // Estonian
	LANG_ES_PA,         // Spanish + Panama
	LANG_ES_SV,         // Spanish + El Salvador
	LANG_ES_VE,         // Spanish + Venezuela
	LANG_ET_EE,         // Estonian + Estonia
	LANG_EU,            // Basque
	LANG_FA,            // Persian
	LANG_FI,            // Finnish
	LANG_FR,            // French
	LANG_FR_BE,         // French + Belgium
	LANG_FR_CA,         // French+Canada
	LANG_FR_CH,         // French+Switzerland
	LANG_FR_LU,         // French+Luxembourg
	LANG_FY,            // Friesland
	LANG_GA,            // Irish
	LANG_GD,            // Scottish Gaelic
	LANG_GL,            // Galicia
	LANG_GU,            // Gujarati
	LANG_HA,            // Hausa
	LANG_HI,            // Hindi
	LANG_HR,            // Croatian
	LANG_HT,            // Haitian Creole
	LANG_HU,            // Hungarian
	LANG_HY,            // Armenia
	LANG_ID,            // Indonesia
	LANG_IG,            // Ibo
	LANG_IS,            // Icelandic
	LANG_IT,            // Italian
	LANG_IT_CH,         // Italian+Switzerland
	LANG_JA,            // Japanese
	LANG_KA,            // Georgian
	LANG_KK,            // Kazakh
	LANG_KN,            // Canada
	LANG_KM,            // Cambodian
	LANG_KO,            // Korean
	LANG_KO_KR,         // Korean + South Korea
	LANG_KU,            // Kurdish
	LANG_KY,            // Kyrgyzstan
	LANG_LA,            // Latin
	LANG_LB,            // Luxembourgish
	LANG_LO,            // Laos
	LANG_LT,            // Lithuanian
	LANG_LV,            // Latvian + Leto
	LANG_MG,            // Malgas
	LANG_MI,            // gross profit
	LANG_MK,            // Macedonian
	LANG_ML,            // Malayalam
	LANG_MN,            // Mongolia
	LANG_MR,            // Marathi
	LANG_MS,            // Malay
	LANG_MT,            // Malta
	LANG_MY,            // Myanmar
	LANG_NL,            // Dutch
	LANG_NL_BE,         // Dutch + Belgium
	LANG_NE,            // Nepal
	LANG_NO,            // Norwegian
	LANG_NY,            // Chichewa
	LANG_PL,            // Polish
	LANG_PS,            // Pashto
	LANG_PT,            // Portuguese
	LANG_PT_BR,         // Portuguese + Brazil
	LANG_RO,            // Romanian
	LANG_RU,            // Russian
	LANG_SD,            // Sindh
	LANG_SI,            // Sinhala
	LANG_SK,            // Slovak
	LANG_SL,            // Slovenian
	LANG_SM,            // Samoa
	LANG_SN,            // Shona
	LANG_SO,            // Somalia
	LANG_SQ,            // Albanian
	LANG_SR,            // Serbian
	LANG_ST,            // Sesotho
	LANG_SU,            // Sundanese
	LANG_SV,            // Swedish
	LANG_SV_SE,         // Swedish+Sweden
	LANG_SW,            // Swahili
	LANG_TA,            // Tamil
	LANG_TE,            // Telugu
	LANG_TG,            // Tajikistan
	LANG_TH,            // Thai
	LANG_TL,            // Philippines
	LANG_TR,            // Turkish
	LANG_UK,            // Ukrainian
	LANG_UR,            // Urdu
	LANG_UZ,            // Uzbekistan
	LANG_VI,            // Vietnam
	LANG_XH,            // Kossa
	LANG_YID,           // Yiddish
	LANG_YO,            // Yoruba
	LANG_ZH,            // Chinese
	LANG_ZH_TW,         // Traditional Chinese
	LANG_ZU             // Zulu
};

UENUM(BlueprintType)
enum class EYVTransRouteType : uint8
{
	TRANS_ROUTE_SERVER,   // The transmission path is server forwarding
	TRANS_ROUTE_P2P       // The transmission path is a local area network
};

UENUM(BlueprintType)
enum class EYVVideoCodecType : uint8
{
	VIDEO_CODEC_H264,
	VIDEO_CODEC_H265,
	VIDEO_CODEC_VP8,
	VIDEO_CODEC_VP9
};

UENUM(BlueprintType)
enum class EYVVideoStreamType : uint8
{
	VIDEO_STREAM_MAIN = 0,
	VIDEO_STREAM_SUB,
	VIDEO_STREAM_SHARE,
	VIDEO_STREAM_MAIN_AND_SHARE,
	VIDEO_STREAM_SUB_AND_SHARE
};

namespace YoumeVideoUtils
{
	EYVUserRole ConvertUserRole(YouMeUserRole_t UserRole);

	YouMeUserRole_t ReverseUserRole(EYVUserRole UserRole);

	EYVAVStatisticType ConvertAVStatisticType(YouMeAVStatisticType_t Type);

	EYVAudioRouteType ConvertAudioRouteType(YouMeAudioRouteType_t Type);

	EYVEvent ConvertEvent(YouMeEvent_t Event);

	EYVKickReason ConvertKickReason(YouMeKickReason_t Reason);

	EYVBroadcast ConvertBroadcast(YouMeBroadcast_t Broadcast);

	EYVErrorCode ConvertErrorCode(YouMeErrorCode_t ErrorCode);

	EYVServerMode ConvertServerMode(SERVER_MODE_t Mode);

	EYVRtcServerRegion ConvertRtcServerRegion(YOUME_RTC_SERVER_REGION_t Region);

	YOUME_RTC_SERVER_REGION ReverseRtcServerRegion(EYVRtcServerRegion Region);

	EYVLogLevel ConvertLogLevel(YOUME_LOG_LEVEL_t Level);

	YOUME_LOG_LEVEL ReverseLogLevel(EYVLogLevel Level);

	EYVSampleRate ConvertSampleRate(YOUME_SAMPLE_RATE_t Rate);

	YOUME_SAMPLE_RATE ReverseSampleRate(EYVSampleRate Rate);

	EYVVudioQuality ConvertVudioQuality(YOUME_AUDIO_QUALITY_t VudioQuality);

	YOUME_AUDIO_QUALITY ReverseVudioQuality(EYVVudioQuality VudioQuality);

	EYVVideoRenderMode ConvertVideoRenderMode(YouMeVideoRenderMode_t Mode);

	EYVVideoMirrorMode ConvertVideoMirrorMode(YouMeVideoMirrorMode_t Mode);

	YouMeVideoMirrorMode ReverseVideoMirrorMode(EYVVideoMirrorMode Mode);

	EYVVideoFmt ConvertVideoFmt(YOUME_VIDEO_FMT_t Fmt);

	EYVVideoShareType ConvertVideoShareType(YOUME_VIDEO_SHARE_TYPE_t Type);

	EYVPcmCallBackFlag ConvertPcmCallBackFlag(PcmCallBackFlag_t Flag);

	PcmCallBackFlag ReversePcmCallBackFlag(EYVPcmCallBackFlag Flag);

	EYVLanguageCode ConvertLanguageCode(YouMeLanguageCode_t Code);

	YouMeLanguageCode ReverseLanguageCode(EYVLanguageCode Code);

	EYVTransRouteType ConvertTransRouteType(YoumeRtpRouteType_t Type);

	EYVVideoCodecType ConvertVideoCodecType(YMVideoCodecType_t Type);

	EYVVideoStreamType ConvertVideoStreamType(YMVideoStreamType_t Type);
}

UCLASS(BlueprintType)
class YOUMEVIDEO_API UYVAudioFrameInfo : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 channels;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 sampleRate;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 bytesPerFrame;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 isFloat;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 isBigEndian;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 isSignedInteger;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 isNonInterleaved;

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int64 timestamp;
};

USTRUCT(BlueprintType)
struct FUserVideoInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		FString userId;
	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 resolutionType;   // Support resolution, 0: large stream, 1: small stream, 2: shared stream
	UPROPERTY(BlueprintReadWrite, Category = "YoumeVideo")
		int32 bitResolutionType; // Bit field, 0 unsubscribe, 1:0 stream 2:1 stream 4:2 stream, combinable
};


/**
 *
 */
UCLASS()
class YOUMEVIDEO_API UYoumeVideoType : public UObject
{
	GENERATED_BODY()

};

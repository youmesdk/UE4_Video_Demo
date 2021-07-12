

#ifndef ue4_sdk_IYouMeVoiceEngine_h
#define ue4_sdk_IYouMeVoiceEngine_h
#include <string>
#include <vector>
#include "IYouMeEventCallback.h"
#include "IYouMeVideoCallback.h"
#include "YouMeConstDefine.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include "Windows/AllowWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_START
#include <wtypes.h>
THIRD_PARTY_INCLUDES_END
#ifdef YOUMEDLL_EXPORTS
#define YOUMEDLL_API __declspec(dllexport)
#else
#define YOUMEDLL_API __declspec(dllimport)
#endif
#else
#define YOUMEDLL_API __attribute ((visibility("default")))
#endif
class YOUMEDLL_API IYouMeVoiceEngine
{
public:
	static IYouMeVoiceEngine* getInstance();

	static void destroy();

public:
	YouMeErrorCode init(IYouMeEventCallback* pEventCallback, const char* pAPPKey, const char* pAPPSecret,
		YOUME_RTC_SERVER_REGION serverRegionId, const char* pExtServerRegionName);

	void setToken(const char* pToken, uint32_t uTimeStamp = 0);

	YouMeErrorCode unInit();

	bool isInited();

	YouMeErrorCode setUserLogPath(const char* pFilePath);

	YouMeErrorCode setTCPMode(int iUseTCP);

	void setServerRegion(YOUME_RTC_SERVER_REGION regionId, const char* extRegionName, bool bAppend);

	YouMeErrorCode setOutputToSpeaker(bool bOutputToSpeaker);

	void setSpeakerMute(bool bOn);

	bool getSpeakerMute();

	bool getMicrophoneMute();

	void setMicrophoneMute(bool mute);

	void setAutoSendStatus(bool bAutoSend);

	unsigned int getVolume();

	void setVolume(const unsigned int& uiVolume);

	bool getUseMobileNetworkEnabled();

	void setUseMobileNetworkEnabled(bool bEnabled);

	YouMeErrorCode setLocalConnectionInfo(const char* pLocalIP, int iLocalPort, const char* pRemoteIP, int iRemotePort, int iNetType);

	YouMeErrorCode setLocalConnectionExtraInfo(bool bNoSignaling, int iConnectTimeout, int iKeepAliveTimeout);

	void clearLocalConnectionInfo();

	YouMeErrorCode setRouteChangeFlag(bool enable);

	YouMeErrorCode setVideoQualityMode(int mode);

	YouMeErrorCode joinChannelSingleMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, bool bVideoAutoRecv = true);

	YouMeErrorCode joinChannelMultiMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole);

	YouMeErrorCode joinChannelSingleMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, const char* pJoinAppKey, bool bVideoAutoRecv = true);

	YouMeErrorCode speakToChannel(const char* pChannelID);

	YouMeErrorCode leaveChannelMultiMode(const char* pChannelID);

	YouMeErrorCode leaveChannelAll();

	YouMeErrorCode setUserRole(YouMeUserRole_t eUserRole);

	YouMeUserRole_t getUserRole();

	bool isInChannel(const char* pChannelID);

	bool isInChannel();

	YouMeErrorCode getChannelUserList(const char* channelID, int maxCount, bool notifyMemChange);

	YouMeErrorCode setOtherMicMute(const char* pUserID, bool mute);

	YouMeErrorCode setOtherSpeakerMute(const char* pUserID, bool mute);

	YouMeErrorCode setListenOtherVoice(const char* pUserID, bool on);

	YouMeErrorCode inputVideoFrame(void* data, int len, int width, int	height, int fmt, int rotation, int mirror, uint64_t timestamp, int streamID = 0);

	YouMeErrorCode inputVideoFrameForShare(void* data, int len, int width, int  height, int fmt, int rotation, int mirror, uint64_t timestamp);

	YouMeErrorCode inputVideoFrameForIOS(void* pixelbuffer, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);

	YouMeErrorCode inputVideoFrameForIOSShare(void* pixelbuffer, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);

#if PLATFORM_ANDROID
	
	YouMeErrorCode inputVideoFrameForAndroid(int textureId, float* matrix, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);

	
	YouMeErrorCode inputVideoFrameForAndroidShare(int textureId, float* matrix, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);
#endif

	
	YouMeErrorCode stopInputVideoFrame();

	
	YouMeErrorCode stopInputVideoFrameForShare();

	
	YouMeErrorCode inputAudioFrame(void* data, int len, uint64_t timestamp, int channels = 1, int bInterleaved = 0);

	
	YouMeErrorCode inputAudioFrameForMix(int streamId, void* data, int len, YMAudioFrameInfo frameInfo, uint64_t timestamp);

	
	YouMeErrorCode playBackgroundMusic(const char* pFilePath, bool bRepeat);

	
	YouMeErrorCode pauseBackgroundMusic();

	
	YouMeErrorCode resumeBackgroundMusic();

	
	YouMeErrorCode stopBackgroundMusic();

	
	bool isBackgroundMusicPlaying();

	
	YouMeErrorCode setBackgroundMusicVolume(int vol);

	
	YouMeErrorCode setHeadsetMonitorOn(bool micEnabled, bool bgmEnabled = true);

	
	YouMeErrorCode setReverbEnabled(bool enabled);

	
	YouMeErrorCode setVadCallbackEnabled(bool enabled);

	
	YouMeErrorCode setSpeakerRecordOn(bool enabled);

	
	bool isSpeakerRecording();

	
	YouMeErrorCode cleanSpeakerRecordCache();

	
	YouMeErrorCode setMicLevelCallback(int maxLevel);

	
	YouMeErrorCode setFarendVoiceLevelCallback(int maxLevel);

	
	YouMeErrorCode setReleaseMicWhenMute(bool enabled);

	
	YouMeErrorCode setExitCommModeWhenHeadsetPlugin(bool enabled);

	
	YouMeErrorCode setCommMode(bool enabled);

	
	YouMeErrorCode setForceDisableAEC(bool disable);

	
	YouMeErrorCode setForceDisableAGC(bool disable);


	YouMeErrorCode pauseChannel();


	YouMeErrorCode resumeChannel();


	void setRecordingTimeMs(unsigned int timeMs);


	void setPlayingTimeMs(unsigned int timeMs);


	YouMeErrorCode setPcmCallbackEnable(IYouMePcmCallback* pcmCallback, int flag, bool bOutputToSpeaker = true, int nOutputSampleRate = 16000, int nOutputChannel = 1);


	YouMeErrorCode setTranscriberEnabled(bool enable, IYouMeTranscriberCallback* transcriberCallback);


	YouMeErrorCode setVideoPreDecodeCallbackEnable(IYouMeVideoPreDecodeCallback* preDecodeCallback, bool needDecodeandRender = true);


	YouMeErrorCode setVideoEncodeParamCallbackEnable(bool isReport);


	const char* getSdkVersion();


	int getSDKVersion();


	YouMeErrorCode  requestRestApi(const char* strCommand, const char* strQueryBody, int* requestID = NULL);


	void setRestApiCallback(IRestApiCallback* cb);


	void setMemberChangeCallback(IYouMeMemberChangeCallback* cb);


	void setNotifyCallback(IYouMeChannelMsgCallback* cb);


	YouMeErrorCode setGrabMicOption(const char* pChannelID, int mode, int maxAllowCount, int maxTalkTime, unsigned int voteTime);


	YouMeErrorCode startGrabMicAction(const char* pChannelID, const char* pContent);


	YouMeErrorCode stopGrabMicAction(const char* pChannelID, const char* pContent);


	YouMeErrorCode requestGrabMic(const char* pChannelID, int score, bool isAutoOpenMic, const char* pContent);


	YouMeErrorCode releaseGrabMic(const char* pChannelID);



	YouMeErrorCode setInviteMicOption(const char* pChannelID, int waitTimeout, int maxTalkTime);


	YouMeErrorCode requestInviteMic(const char* pChannelID, const char* pUserID, const char* pContent);


	YouMeErrorCode responseInviteMic(const char* pUserID, bool isAccept, const char* pContent);


	YouMeErrorCode stopInviteMic();


	YouMeErrorCode  sendMessage(const char* pChannelID, const char* pContent, const char* pUserID, int* requestID);


	void setExternalInputMode(bool bInputModeEnabled);


	YouMeErrorCode openVideoEncoder(const char* pFilePath);


	int createRender(const char* userId);


	int deleteRender(int renderId);


	int deleteRender(const char* userId);


	YouMeErrorCode maskVideoByUserId(const char* userId, bool mask);


	YouMeErrorCode setVideoCallback(IYouMeVideoFrameCallback* cb);


	YouMeErrorCode startCapture();


	YouMeErrorCode stopCapture();


	YouMeErrorCode setVideoPreviewFps(int fps);


	YouMeErrorCode setVideoFps(int fps);


	YouMeErrorCode setVideoFpsForSecond(int fps);


	YouMeErrorCode setVideoFpsForShare(int fps);


	YouMeErrorCode setVideoLocalResolution(int width, int height);


	YouMeErrorCode setCaptureFrontCameraEnable(bool enable);


	YouMeErrorCode switchCamera();


	YouMeErrorCode resetCamera();



	YouMeErrorCode kickOtherFromChannel(const char* pUserID, const char* pChannelID, int lastTime);


	void setLogLevel(YOUME_LOG_LEVEL consoleLevel, YOUME_LOG_LEVEL fileLevel);


	YouMeErrorCode setExternalInputSampleRate(YOUME_SAMPLE_RATE inputSampleRate, YOUME_SAMPLE_RATE mixedCallbackSampleRate);


	YouMeErrorCode setVideoSmooth(int enable);


	YouMeErrorCode setVideoUpFeedback(int enable);


	YouMeErrorCode setVideoNetAdjustmode(int mode);


	YouMeErrorCode setVideoNetResolution(int width, int height);


	YouMeErrorCode setVideoNetResolutionForSecond(int width, int height);


	YouMeErrorCode setVideoNetResolutionForShare(int width, int height);


	void setAVStatisticInterval(int interval);


	void setAVStatisticCallback(IYouMeAVStatisticCallback* cb);


	void setAVStatisticNewCallback(IYouMeAVStatisticNewCallback* cb);


	void setAudioQuality(YOUME_AUDIO_QUALITY quality);


	void setVideoCodeBitrate(unsigned int maxBitrate, unsigned int minBitrate);


	void setVideoCodeBitrateForSecond(unsigned int maxBitrate, unsigned int minBitrate);


	void setVideoCodeBitrateForShare(unsigned int maxBitrate, unsigned int minBitrate);


	unsigned int getCurrentVideoCodeBitrate();


	YouMeErrorCode setVBR(bool useVBR);


	YouMeErrorCode setVBRForSecond(bool useVBR);


	YouMeErrorCode setVBRForShare(bool useVBR);


	void setVideoHardwareCodeEnable(bool bEnable);


	bool getVideoHardwareCodeEnable();


	bool getUseGL();


	void setVideoNoFrameTimeout(int timeout);


	YouMeErrorCode queryUsersVideoInfo(std::vector<std::string>& userList)
#if PLATFORM_ANDROID
	{
		return YOUME_ERROR_UNKNOWN;
	}
#else
		;
#endif


	struct userVideoInfo
	{
		std::string userId;
		int resolutionType;  
		int bitResolutionType; 
	};


	YouMeErrorCode setUsersVideoInfo(std::vector<IYouMeVoiceEngine::userVideoInfo>& videoInfoList)
#if PLATFORM_ANDROID
	{
		return YOUME_ERROR_UNKNOWN;
	}
#else
		;
#endif



	YouMeErrorCode queryUsersVideoInfo(const char* userList);


	YouMeErrorCode setUsersVideoInfo(const char* videoInfoList);


	YouMeErrorCode openBeautify(bool open);


	YouMeErrorCode beautifyChanged(float param);


	bool releaseMicSync();


	bool resumeMicSync();


	int getCameraCount();


	const char* getCameraName(int cameraId);


	YouMeErrorCode setOpenCameraId(int cameraId);


	int getRecordDeviceCount();


	bool getRecordDeviceInfo(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceUId[MAX_DEVICE_ID_LENGTH]);


	bool getCurrentRecordDeviceInfo(char* deviceUId);


	YouMeErrorCode setRecordDevice(const char* deviceUId);




	void setMixVideoSize(int width, int height);


	void addMixOverlayVideo(const char* userId, int x, int y, int z, int width, int height);


	void removeMixOverlayVideo(const char* userId);


	void removeAllOverlayVideo();


	YouMeErrorCode setExternalFilterEnabled(bool enabled);



	int enableLocalVideoRender(bool enabled);

	int enableLocalVideoSend(bool enabled);


	int muteAllRemoteVideoStreams(bool mute);


	int setDefaultMuteAllRemoteVideoStreams(bool mute);


	int muteRemoteVideoStream(const char* uid, bool mute);


#if PLATFORM_IOS // || PLATFORM_ANDROID
	bool isCameraZoomSupported();
	float setCameraZoomFactor(float zoomFactor);
	bool isCameraFocusPositionInPreviewSupported();
	bool setCameraFocusPositionInPreview(float x, float y);
	bool isCameraTorchSupported();
	bool setCameraTorchOn(bool isOn);
	bool isCameraAutoFocusFaceModeSupported();
	bool setCameraAutoFocusFaceModeEnabled(bool enable);
#endif


	void setLocalVideoMirrorMode(YouMeVideoMirrorMode mode);


	void setLocalVideoPreviewMirror(bool enable);


	void setRecvCustomDataCallback(IYouMeCustomDataCallback* pCallback);


	void setTranslateCallback(IYouMeTranslateCallback* pCallback);

	YouMeErrorCode inputCustomData(const void* data, int len, uint64_t timestamp, const char* userId = "");



	YouMeErrorCode setVideoFrameRawCbEnabled(bool enabled);


	YouMeErrorCode startPush(const char* pushUrl);

	YouMeErrorCode stopPush();


	YouMeErrorCode setPushMix(const char* pushUrl, int width, int height);

	YouMeErrorCode clearPushMix();


	YouMeErrorCode addPushMixUser(const char* userId, int x, int y, int z, int width, int height);

	YouMeErrorCode removePushMixUser(const char* userId);

#if PLATFORM_WINDOWS   

	YouMeErrorCode StartShareStream(int mode, HWND renderHandle, HWND captureHandle);


	YouMeErrorCode setShareExclusiveWnd(HWND windowid);


	void GetWindowInfoList(HWND* pHwnd, char* pWinName, int* winCount);


	void GetScreenInfoList(HWND* pHwnd, char* pScreenName, int* screenCount);


	YouMeErrorCode startSaveScreen(const char* filePath, HWND renderHandle, HWND captureHandle);


	void enableShareBorder(bool bEnable);

#elif PLATFORM_MAC

	YouMeErrorCode checkSharePermission();


	YouMeErrorCode setShareExclusiveWnd(int windowid);

	void setShareContext(void* context);


	void GetWindowInfoList(char* pWinOwner, char* pWinName, int* pWinId, int* winCount);


	void enableShareBorder(bool bEnable);
#endif

#if PLATFORM_MAC

	YouMeErrorCode StartShareStream(int mode, int windowid);
#endif


	void StopShareStream();


	YouMeErrorCode startSaveScreen(const char* filePath);


	void stopSaveScreen();


	char* GetShareVideoData(int* len, int* width, int* height, int* fmt);


	YouMeErrorCode switchResolutionForLandscape();


	YouMeErrorCode resetResolutionForPortrait();


	YouMeErrorCode translateText(unsigned int* requestID, const char* text, YouMeLanguageCode destLangCode, YouMeLanguageCode srcLangCode);

	YouMeErrorCode inviteSipUser(const char* userId, const char* gatewayUrl);


	YouMeErrorCode setVideoCodecType(int codecType);

private:

	IYouMeVoiceEngine();
	~IYouMeVoiceEngine();
};


#endif

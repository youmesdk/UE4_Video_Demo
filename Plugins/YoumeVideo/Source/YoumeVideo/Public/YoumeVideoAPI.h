// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "YoumeVideoType.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "YoumeVideoTexture.h"
#include "YoumeVideoAPI.generated.h"

/**
 *
 */
UCLASS()
class YOUMEVIDEO_API UYoumeVideoAPI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void BindObserver(TScriptInterface<IYoumeVideoObserver> Observer);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void UnbindObserver();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode Start(const FString appKey, const FString aPPSecret,
			EYVRtcServerRegion serverRegionId, const FString extServerRegionName);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StartPcm(EYVPcmCallBackFlag pcmFlag, bool outputToSpeaker, int32 outputSampleRate, int32 outputChannel);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void Close();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetToken(const FString token, int32 timeStamp);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsInited();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetUserLogPath(const FString filePath);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetTCPMode(int32 useTCP);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetServerRegion(const EYVRtcServerRegion regionId, const FString extRegionName, bool append);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetOutputToSpeaker(bool outputToSpeaker);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetSpeakerMute(bool isOn);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetSpeakerMute();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetMicrophoneMute();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetMicrophoneMute(bool mute);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetAutoSendStatus(bool autoSend);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 GetVolume();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetVolume(int32 uiVolume);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetUseMobileNetworkEnabled();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetUseMobileNetworkEnabled(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetLocalConnectionInfo(const FString localIP, int localPort, const FString remoteIP, int remotePort, int netType);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetLocalConnectionExtraInfo(bool noSignaling, int connectTimeout, int keepAliveTimeout);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void ClearLocalConnectionInfo();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetRouteChangeFlag(bool enable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoQualityMode(int mode);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode JoinChannelSingleMode(const FString userID, const FString channelID, const EYVUserRole userRole, bool videoAutoRecv);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode JoinChannelMultiMode(const FString userID, const FString channelID, EYVUserRole userRole);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode JoinChannelSingleModeByKey(const FString userID, const FString channelID, EYVUserRole userRole, const FString joinAppKey, bool videoAutoRecv);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SpeakToChannel(const FString channelID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode LeaveChannelMultiMode(const FString channelID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode LeaveChannelAll();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetUserRole(const EYVUserRole userRole);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVUserRole GetUserRole();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsInChannelByID(const FString channelID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsInChannel();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode GetChannelUserList(const FString channelID, int32 maxCount, bool notifyMemChange);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetOtherMicMute(const FString userID, bool mute);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetOtherSpeakerMute(const FString userID, bool mute);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetListenOtherVoice(const FString userID, bool isOn);

	// inputVideoFrame -> inputVideoFrameForAndroidShare Not Suit

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopInputVideoFrame();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopInputVideoFrameForShare();

	// inputAudioFrame -> inputAudioFrameForMix Not Suit

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode PlayBackgroundMusic(const FString filePath, bool repeat);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode PauseBackgroundMusic();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ResumeBackgroundMusic();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopBackgroundMusic();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsBackgroundMusicPlaying();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetBackgroundMusicVolume(int vol);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetHeadsetMonitorOn(bool micEnabled, bool bgmEnabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetReverbEnabled(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetSpeakerRecordOn(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsSpeakerRecording();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode CleanSpeakerRecordCache();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetReleaseMicWhenMute(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetExitCommModeWhenHeadsetPlugin(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetCommMode(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetForceDisableAEC(bool disable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetForceDisableAGC(bool disable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode PauseChannel();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ResumeChannel();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetRecordingTimeMs(int32 timeMs);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetPlayingTimeMs(int32 timeMs);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static FString GetSdkVersion();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode RequestRestApi(const FString command, const FString queryBody, int32& requestID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetGrabMicOption(const FString channelID, int32 mode, int32 maxAllowCount, int32 maxTalkTime, int32 voteTime);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StartGrabMicAction(const FString channelID, const FString content);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopGrabMicAction(const FString channelID, const FString content);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode RequestGrabMic(const FString channelID, int32 score, bool autoOpenMic, const FString content);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ReleaseGrabMic(const FString channelID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetInviteMicOption(const FString channelID, int32 waitTimeout, int32 maxTalkTime);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode RequestInviteMic(const FString channelID, const FString userID, const FString content);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ResponseInviteMic(const FString userID, bool isAccept, const FString content);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopInviteMic();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SendMessage(const FString channelID, const FString content, const FString userID, int32& requestID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetExternalInputMode(bool inputModeEnabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode OpenVideoEncoder(const FString filePath);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 CreateRender(const FString userId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 DeleteRender(int32 renderId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 DeleteRenderByUser(const FString userId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode MaskVideoByUserId(const FString userId, bool mask);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StartCapture();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopCapture();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoPreviewFps(int32 fps);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoFps(int32 fps);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoFpsForSecond(int32 fps);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoFpsForShare(int32 fps);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoLocalResolution(int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetCaptureFrontCameraEnable(bool enable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SwitchCamera();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ResetCamera();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode KickOtherFromChannel(const FString userID, const FString channelID, int lastTime);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetLogLevel(EYVLogLevel consoleLevel, EYVLogLevel fileLevel);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetExternalInputSampleRate(EYVSampleRate inputSampleRate, EYVSampleRate mixedCallbackSampleRate);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoSmooth(int32 enable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoUpFeedback(int enable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoNetAdjustmode(int32 mode);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoNetResolution(int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoNetResolutionForSecond(int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoNetResolutionForShare(int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetAVStatisticInterval(int32 interval);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetAudioQuality(EYVVudioQuality quality);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetVideoCodeBitrate(int32 maxBitrate, int32 minBitrate);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetVideoCodeBitrateForSecond(int32 maxBitrate, int32 minBitrate);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetVideoCodeBitrateForShare(int32 maxBitrate, int32 minBitrate);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 GetCurrentVideoCodeBitrate();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVBR(bool useVBR);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVBRForSecond(bool useVBR);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVBRForShare(bool useVBR);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetVideoHardwareCodeEnable(bool enable);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetVideoHardwareCodeEnable();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetUseGL();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetVideoNoFrameTimeout(int32 timeout);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode QueryUsersVideoInfo(TArray<FString> userList);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetUsersVideoInfo(TArray<FUserVideoInfo> videoInfoList);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode OpenBeautify(bool open);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode BeautifyChanged(float param);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool ReleaseMicSync();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool ResumeMicSync();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 GetCameraCount();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static FString GetCameraName(int32 cameraId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetOpenCameraId(int cameraId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 GetRecordDeviceCount();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetRecordDeviceInfo(int32 index, const FString deviceName, const FString  deviceUId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool GetCurrentRecordDeviceInfo(const FString deviceUId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetRecordDevice(const FString deviceUId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetMixVideoSize(int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void AddMixOverlayVideo(const FString userId, int32 x, int32 y, int32 z, int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void RemoveMixOverlayVideoById(const FString userId);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void RemoveAllOverlayVideo();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetExternalFilterEnabled(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 EnableLocalVideoRender(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 EnableLocalVideoSend(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 MuteAllRemoteVideoStreams(bool mute);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 SetDefaultMuteAllRemoteVideoStreams(bool mute);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static int32 MuteRemoteVideoStream(const FString uid, bool mute);

	// #if PLATFORM_IOS || PLATFORM_ANDROID

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsCameraZoomSupported();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static float SetCameraZoomFactor(float zoomFactor);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsCameraFocusPositionInPreviewSupported();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool SetCameraFocusPositionInPreview(float x, float y);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsCameraTorchSupported();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool SetCameraTorchOn(bool isOn);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool IsCameraAutoFocusFaceModeSupported();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static bool SetCameraAutoFocusFaceModeEnabled(bool enable);

	// #endif

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetLocalVideoMirrorMode(EYVVideoMirrorMode mode);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void SetLocalVideoPreviewMirror(bool enable);

	// inputCustomData Not Suit

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoFrameRawCbEnabled(bool enabled);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StartPush(const FString pushUrl);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StopPush();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetPushMix(const FString pushUrl, int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ClearPushMix();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode AddPushMixUser(const FString userId, int32 x, int32 y, int32 z, int32 width, int32 height);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode RemovePushMixUser(const FString userId);

	// StartShareStream --> startSaveScreen Not Suit

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void EnableShareBorder(bool enable);

	// #if PLATFORM_MAC

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode CheckSharePermission();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetShareExclusiveWnd(int32 windowid);

	// setShareContext -> GetWindowInfoList EnableShareBorder Not Suit

	// UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
	// static void GetWindowInfoList(FString& winOwner, FString& winName, int32& winId, int32& winCount);

	// UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
	// static void EnableShareBorder(bool enable);

	// #endif

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void StopShareStream();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode StartSaveScreen(const FString filePath);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static void StopSaveScreen();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static FString GetShareVideoData(int32& len, int32& width, int32& height, int32& fmt);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SwitchResolutionForLandscape();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode ResetResolutionForPortrait();

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode TranslateText(const FString text, EYVLanguageCode destLangCode, EYVLanguageCode srcLangCode, int32& requestID);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode InviteSipUser(const FString userId, const FString gatewayUrl);

	UFUNCTION(BlueprintCallable, Category = "YoumeVideoAPI")
		static EYVErrorCode SetVideoCodecType(int32 codecType);

	static void CreateMixTexture();

	static void CreateUserTexture(const FString userId);

public:

	static UYoumeVideoTexture* MixTexture;

	static TMap<FString, UYoumeVideoTexture*> UserTextures;

	static double MixTime;

	static TMap<FString, double> UserTimes;
};

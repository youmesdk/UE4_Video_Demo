// Fill out your copyright notice in the Description page of Project Settings.


#include "YoumeVideoAPI.h"
#include "YoumeVideoWork.h"

UYoumeVideoTexture* UYoumeVideoAPI::MixTexture;

TMap<FString, UYoumeVideoTexture*> UYoumeVideoAPI::UserTextures;

double UYoumeVideoAPI::MixTime;

TMap<FString, double> UYoumeVideoAPI::UserTimes;

void UYoumeVideoAPI::CreateMixTexture()
{
	MixTexture = NewObject<UYoumeVideoTexture>();
	MixTexture->AddToRoot();
	MixTexture->UpdateResource();
}

void UYoumeVideoAPI::CreateUserTexture(const FString userId)
{
	UYoumeVideoTexture* UserTexture = NewObject<UYoumeVideoTexture>();
	UserTexture->AddToRoot();
	UserTexture->UpdateResource();
	UserTextures.Add(userId, UserTexture);

	UserTimes.Add(userId, 0);
}

void UYoumeVideoAPI::BindObserver(TScriptInterface<IYoumeVideoObserver> Observer)
{
	FYoumeVideoWork::Instance()->BindObserver(Observer);
}

void UYoumeVideoAPI::UnbindObserver()
{
	FYoumeVideoWork::Instance()->UnbindObserver();

	if (MixTexture)
	{
		MixTexture->RemoveFromRoot();
		MixTexture = NULL;
	}

	for (TMap<FString, UYoumeVideoTexture*>::TIterator It(UserTextures); It; ++It)
	{
		It.Value()->RemoveFromRoot();
	}
	UserTextures.Empty();

	MixTime = 0;
	UserTimes.Empty();
}

EYVErrorCode UYoumeVideoAPI::Start(const FString appKey, const FString aPPSecret, EYVRtcServerRegion serverRegionId, const FString extServerRegionName)
{
	return FYoumeVideoWork::Instance()->Start(appKey, aPPSecret, serverRegionId, extServerRegionName);
}

EYVErrorCode UYoumeVideoAPI::StartPcm(EYVPcmCallBackFlag pcmFlag, bool outputToSpeaker, int32 outputSampleRate, int32 outputChannel)
{
	return FYoumeVideoWork::Instance()->StartPcm(pcmFlag, outputToSpeaker, outputSampleRate, outputChannel);
}

void UYoumeVideoAPI::Close()
{
	return FYoumeVideoWork::Instance()->Close();
}

void UYoumeVideoAPI::SetToken(const FString token, int32 timeStamp)
{
	FYoumeVideoWork::Manager()->setToken(TCHAR_TO_UTF8(*token), (uint32_t)timeStamp);
}

bool UYoumeVideoAPI::IsInited()
{
	return FYoumeVideoWork::Manager()->isInited();
}

EYVErrorCode UYoumeVideoAPI::SetUserLogPath(const FString filePath)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setUserLogPath(TCHAR_TO_UTF8(*filePath)));
}

EYVErrorCode UYoumeVideoAPI::SetTCPMode(int32 useTCP)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setTCPMode(useTCP));
}

void UYoumeVideoAPI::SetServerRegion(const EYVRtcServerRegion regionId, const FString extRegionName, bool append)
{
	return FYoumeVideoWork::Manager()->setServerRegion(YoumeVideoUtils::ReverseRtcServerRegion(regionId), TCHAR_TO_UTF8(*extRegionName), append);
}

EYVErrorCode UYoumeVideoAPI::SetOutputToSpeaker(bool outputToSpeaker)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setOutputToSpeaker(outputToSpeaker));
}

void UYoumeVideoAPI::SetSpeakerMute(bool isOn)
{
	return FYoumeVideoWork::Manager()->setSpeakerMute(isOn);
}

bool UYoumeVideoAPI::GetSpeakerMute()
{
	return FYoumeVideoWork::Manager()->getSpeakerMute();
}

bool UYoumeVideoAPI::GetMicrophoneMute()
{
	return FYoumeVideoWork::Manager()->getMicrophoneMute();
}

void UYoumeVideoAPI::SetMicrophoneMute(bool mute)
{
	FYoumeVideoWork::Manager()->setMicrophoneMute(mute);
}

void UYoumeVideoAPI::SetAutoSendStatus(bool autoSend)
{
	FYoumeVideoWork::Manager()->setAutoSendStatus(autoSend);
}

int32 UYoumeVideoAPI::GetVolume()
{
	return FYoumeVideoWork::Manager()->getVolume();
}

void UYoumeVideoAPI::SetVolume(int32 uiVolume)
{
	FYoumeVideoWork::Manager()->setVolume((const unsigned int&)uiVolume);
}

bool UYoumeVideoAPI::GetUseMobileNetworkEnabled()
{
	return FYoumeVideoWork::Manager()->getUseMobileNetworkEnabled();
}

void UYoumeVideoAPI::SetUseMobileNetworkEnabled(bool enabled)
{
	return FYoumeVideoWork::Manager()->setUseMobileNetworkEnabled(enabled);
}

EYVErrorCode UYoumeVideoAPI::SetLocalConnectionInfo(const FString localIP, int localPort, const FString remoteIP, int remotePort, int netType)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setLocalConnectionInfo(TCHAR_TO_UTF8(*localIP), localPort, TCHAR_TO_UTF8(*remoteIP), remotePort, netType));
}

EYVErrorCode UYoumeVideoAPI::SetLocalConnectionExtraInfo(bool noSignaling, int connectTimeout, int keepAliveTimeout)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setLocalConnectionExtraInfo(noSignaling, connectTimeout, keepAliveTimeout));
}

void UYoumeVideoAPI::ClearLocalConnectionInfo()
{
	FYoumeVideoWork::Manager()->clearLocalConnectionInfo();
}

EYVErrorCode UYoumeVideoAPI::SetRouteChangeFlag(bool enable)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setRouteChangeFlag(enable));
}

EYVErrorCode UYoumeVideoAPI::SetVideoQualityMode(int mode)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoQualityMode(mode));
}

EYVErrorCode UYoumeVideoAPI::JoinChannelSingleMode(const FString userID, const FString channelID, const EYVUserRole userRole, bool videoAutoRecv)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->joinChannelSingleMode(TCHAR_TO_UTF8(*userID), TCHAR_TO_UTF8(*channelID), YoumeVideoUtils::ReverseUserRole(userRole), videoAutoRecv));
}

EYVErrorCode UYoumeVideoAPI::JoinChannelMultiMode(const FString userID, const FString channelID, EYVUserRole userRole)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->joinChannelMultiMode(TCHAR_TO_UTF8(*userID), TCHAR_TO_UTF8(*channelID), YoumeVideoUtils::ReverseUserRole(userRole)));
}

EYVErrorCode UYoumeVideoAPI::JoinChannelSingleModeByKey(const FString userID, const FString channelID, EYVUserRole userRole, const FString joinAppKey, bool videoAutoRecv)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->joinChannelSingleMode(TCHAR_TO_UTF8(*userID), TCHAR_TO_UTF8(*channelID), YoumeVideoUtils::ReverseUserRole(userRole), TCHAR_TO_UTF8(*joinAppKey), videoAutoRecv));
}

EYVErrorCode UYoumeVideoAPI::SpeakToChannel(const FString channelID)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->speakToChannel(TCHAR_TO_UTF8(*channelID)));
}

EYVErrorCode UYoumeVideoAPI::LeaveChannelMultiMode(const FString channelID)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->leaveChannelMultiMode(TCHAR_TO_UTF8(*channelID)));
}

EYVErrorCode UYoumeVideoAPI::LeaveChannelAll()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->leaveChannelAll());
}

EYVErrorCode UYoumeVideoAPI::SetUserRole(const EYVUserRole userRole)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setUserRole(YoumeVideoUtils::ReverseUserRole(userRole)));
}

EYVUserRole UYoumeVideoAPI::GetUserRole()
{
	return YoumeVideoUtils::ConvertUserRole(FYoumeVideoWork::Manager()->getUserRole());
}

bool UYoumeVideoAPI::IsInChannelByID(const FString channelID)
{
	return FYoumeVideoWork::Manager()->isInChannel(TCHAR_TO_UTF8(*channelID));
}

bool UYoumeVideoAPI::IsInChannel()
{
	return FYoumeVideoWork::Manager()->isInChannel();
}

EYVErrorCode UYoumeVideoAPI::GetChannelUserList(const FString channelID, int32 maxCount, bool notifyMemChange)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->getChannelUserList(TCHAR_TO_UTF8(*channelID), maxCount, notifyMemChange));
}

EYVErrorCode UYoumeVideoAPI::SetOtherMicMute(const FString userID, bool mute)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setOtherMicMute(TCHAR_TO_UTF8(*userID), mute));
}

EYVErrorCode UYoumeVideoAPI::SetOtherSpeakerMute(const FString userID, bool mute)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setOtherSpeakerMute(TCHAR_TO_UTF8(*userID), mute));
}

EYVErrorCode UYoumeVideoAPI::SetListenOtherVoice(const FString userID, bool isOn)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setListenOtherVoice(TCHAR_TO_UTF8(*userID), isOn));
}

EYVErrorCode UYoumeVideoAPI::StopInputVideoFrame()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopInputVideoFrame());
}

EYVErrorCode UYoumeVideoAPI::StopInputVideoFrameForShare()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopInputVideoFrameForShare());
}

EYVErrorCode UYoumeVideoAPI::PlayBackgroundMusic(const FString filePath, bool repeat)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->playBackgroundMusic(TCHAR_TO_UTF8(*filePath), repeat));
}

EYVErrorCode UYoumeVideoAPI::PauseBackgroundMusic()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->pauseBackgroundMusic());
}

EYVErrorCode UYoumeVideoAPI::ResumeBackgroundMusic()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->resumeBackgroundMusic());
}

EYVErrorCode UYoumeVideoAPI::StopBackgroundMusic()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopBackgroundMusic());
}

bool UYoumeVideoAPI::IsBackgroundMusicPlaying()
{
	return FYoumeVideoWork::Manager()->isBackgroundMusicPlaying();
}

EYVErrorCode UYoumeVideoAPI::SetBackgroundMusicVolume(int vol)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setBackgroundMusicVolume(vol));
}

EYVErrorCode UYoumeVideoAPI::SetHeadsetMonitorOn(bool micEnabled, bool bgmEnabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setHeadsetMonitorOn(micEnabled, bgmEnabled));
}

EYVErrorCode UYoumeVideoAPI::SetReverbEnabled(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setReverbEnabled(enabled));
}

EYVErrorCode UYoumeVideoAPI::SetSpeakerRecordOn(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setSpeakerRecordOn(enabled));
}

bool UYoumeVideoAPI::IsSpeakerRecording()
{
	return FYoumeVideoWork::Manager()->isSpeakerRecording();
}

EYVErrorCode UYoumeVideoAPI::CleanSpeakerRecordCache()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->cleanSpeakerRecordCache());
}

EYVErrorCode UYoumeVideoAPI::SetReleaseMicWhenMute(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setReleaseMicWhenMute(enabled));
}

EYVErrorCode UYoumeVideoAPI::SetExitCommModeWhenHeadsetPlugin(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setExitCommModeWhenHeadsetPlugin(enabled));
}

EYVErrorCode UYoumeVideoAPI::SetCommMode(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setCommMode(enabled));
}

EYVErrorCode UYoumeVideoAPI::SetForceDisableAEC(bool disable)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setForceDisableAEC(disable));
}

EYVErrorCode UYoumeVideoAPI::SetForceDisableAGC(bool disable)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setForceDisableAGC(disable));
}

EYVErrorCode UYoumeVideoAPI::PauseChannel()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->pauseChannel());
}

EYVErrorCode UYoumeVideoAPI::ResumeChannel()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->resumeChannel());
}

void UYoumeVideoAPI::SetRecordingTimeMs(int32 timeMs)
{
	return FYoumeVideoWork::Manager()->setRecordingTimeMs((unsigned int)timeMs);
}

void UYoumeVideoAPI::SetPlayingTimeMs(int32 timeMs)
{
	return FYoumeVideoWork::Manager()->setPlayingTimeMs((unsigned int)timeMs);
}

FString UYoumeVideoAPI::GetSdkVersion()
{
	return FString(UTF8_TO_TCHAR(FYoumeVideoWork::Manager()->getSdkVersion()));
}

EYVErrorCode UYoumeVideoAPI::RequestRestApi(const FString command, const FString queryBody, int32& requestID)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->requestRestApi(TCHAR_TO_UTF8(*command), TCHAR_TO_UTF8(*queryBody), &requestID));
}

EYVErrorCode UYoumeVideoAPI::SetGrabMicOption(const FString channelID, int32 mode, int32 maxAllowCount, int32 maxTalkTime, int32 voteTime)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setGrabMicOption(TCHAR_TO_UTF8(*channelID), mode, maxAllowCount, maxTalkTime, (unsigned int)voteTime));
}

EYVErrorCode UYoumeVideoAPI::StartGrabMicAction(const FString channelID, const FString content)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->startGrabMicAction(TCHAR_TO_UTF8(*channelID), TCHAR_TO_UTF8(*content)));
}

EYVErrorCode UYoumeVideoAPI::StopGrabMicAction(const FString channelID, const FString content)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopGrabMicAction(TCHAR_TO_UTF8(*channelID), TCHAR_TO_UTF8(*content)));
}

EYVErrorCode UYoumeVideoAPI::RequestGrabMic(const FString channelID, int32 score, bool autoOpenMic, const FString content)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->requestGrabMic(TCHAR_TO_UTF8(*channelID), score, autoOpenMic, TCHAR_TO_UTF8(*content)));
}

EYVErrorCode UYoumeVideoAPI::ReleaseGrabMic(const FString channelID)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->releaseGrabMic(TCHAR_TO_UTF8(*channelID)));
}

EYVErrorCode UYoumeVideoAPI::SetInviteMicOption(const FString channelID, int32 waitTimeout, int32 maxTalkTime)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setInviteMicOption(TCHAR_TO_UTF8(*channelID), waitTimeout, maxTalkTime));
}

EYVErrorCode UYoumeVideoAPI::RequestInviteMic(const FString channelID, const FString userID, const FString content)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->requestInviteMic(TCHAR_TO_UTF8(*channelID), TCHAR_TO_UTF8(*userID), TCHAR_TO_UTF8(*content)));
}

EYVErrorCode UYoumeVideoAPI::ResponseInviteMic(const FString userID, bool isAccept, const FString content)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->responseInviteMic(TCHAR_TO_UTF8(*userID), isAccept, TCHAR_TO_UTF8(*content)));
}

EYVErrorCode UYoumeVideoAPI::StopInviteMic()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopInviteMic());
}

EYVErrorCode UYoumeVideoAPI::SendMessage(const FString channelID, const FString content, const FString userID, int32& requestID)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->sendMessage(TCHAR_TO_UTF8(*channelID), TCHAR_TO_UTF8(*content), TCHAR_TO_UTF8(*userID), &requestID));
}

void UYoumeVideoAPI::SetExternalInputMode(bool inputModeEnabled)
{
	FYoumeVideoWork::Manager()->setExternalInputMode(inputModeEnabled);
}

EYVErrorCode UYoumeVideoAPI::OpenVideoEncoder(const FString filePath)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->openVideoEncoder(TCHAR_TO_UTF8(*filePath)));
}

int32 UYoumeVideoAPI::CreateRender(const FString userId)
{
	return FYoumeVideoWork::Manager()->createRender(TCHAR_TO_UTF8(*userId));
}

int32 UYoumeVideoAPI::DeleteRender(int32 renderId)
{
	return FYoumeVideoWork::Manager()->deleteRender(renderId);
}

int32 UYoumeVideoAPI::DeleteRenderByUser(const FString userId)
{
	return FYoumeVideoWork::Manager()->deleteRender(TCHAR_TO_UTF8(*userId));
}

EYVErrorCode UYoumeVideoAPI::MaskVideoByUserId(const FString userId, bool mask)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->maskVideoByUserId(TCHAR_TO_UTF8(*userId), mask));
}

EYVErrorCode UYoumeVideoAPI::StartCapture()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->startCapture());
}

EYVErrorCode UYoumeVideoAPI::StopCapture()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopCapture());
}

EYVErrorCode UYoumeVideoAPI::SetVideoPreviewFps(int32 fps)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoPreviewFps(fps));
}

EYVErrorCode UYoumeVideoAPI::SetVideoFps(int32 fps)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoFps(fps));
}

EYVErrorCode UYoumeVideoAPI::SetVideoFpsForSecond(int32 fps)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoFpsForSecond(fps));
}

EYVErrorCode UYoumeVideoAPI::SetVideoFpsForShare(int32 fps)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoFpsForShare(fps));
}

EYVErrorCode UYoumeVideoAPI::SetVideoLocalResolution(int32 width, int32 height)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoLocalResolution(width, height));
}

EYVErrorCode UYoumeVideoAPI::SetCaptureFrontCameraEnable(bool enable)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setCaptureFrontCameraEnable(enable));
}

EYVErrorCode UYoumeVideoAPI::SwitchCamera()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->switchCamera());
}

EYVErrorCode UYoumeVideoAPI::ResetCamera()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->resetCamera());
}

EYVErrorCode UYoumeVideoAPI::KickOtherFromChannel(const FString userID, const FString channelID, int lastTime)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->kickOtherFromChannel(TCHAR_TO_UTF8(*userID), TCHAR_TO_UTF8(*channelID), lastTime));
}

void UYoumeVideoAPI::SetLogLevel(EYVLogLevel consoleLevel, EYVLogLevel fileLevel)
{
	return FYoumeVideoWork::Manager()->setLogLevel(YoumeVideoUtils::ReverseLogLevel(consoleLevel), YoumeVideoUtils::ReverseLogLevel(fileLevel));
}

EYVErrorCode UYoumeVideoAPI::SetExternalInputSampleRate(EYVSampleRate inputSampleRate, EYVSampleRate mixedCallbackSampleRate)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setExternalInputSampleRate(YoumeVideoUtils::ReverseSampleRate(inputSampleRate), YoumeVideoUtils::ReverseSampleRate(mixedCallbackSampleRate)));
}

EYVErrorCode UYoumeVideoAPI::SetVideoSmooth(int32 enable)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoSmooth(enable));
}

EYVErrorCode UYoumeVideoAPI::SetVideoUpFeedback(int enable)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoUpFeedback(enable));
}

EYVErrorCode UYoumeVideoAPI::SetVideoNetAdjustmode(int32 mode)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoNetAdjustmode(mode));
}

EYVErrorCode UYoumeVideoAPI::SetVideoNetResolution(int32 width, int32 height)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoNetResolution(width, height));
}

EYVErrorCode UYoumeVideoAPI::SetVideoNetResolutionForSecond(int32 width, int32 height)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoNetResolutionForSecond(width, height));
}

EYVErrorCode UYoumeVideoAPI::SetVideoNetResolutionForShare(int32 width, int32 height)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoNetResolutionForShare(width, height));
}

void UYoumeVideoAPI::SetAVStatisticInterval(int32 interval)
{
	FYoumeVideoWork::Manager()->setAVStatisticInterval(interval);
}

void UYoumeVideoAPI::SetAudioQuality(EYVVudioQuality quality)
{
	FYoumeVideoWork::Manager()->setAudioQuality(YoumeVideoUtils::ReverseVudioQuality(quality));
}

void UYoumeVideoAPI::SetVideoCodeBitrate(int32 maxBitrate, int32 minBitrate)
{
	FYoumeVideoWork::Manager()->setVideoCodeBitrate((unsigned int)maxBitrate, (unsigned int)minBitrate);
}

void UYoumeVideoAPI::SetVideoCodeBitrateForSecond(int32 maxBitrate, int32 minBitrate)
{
	FYoumeVideoWork::Manager()->setVideoCodeBitrateForSecond((unsigned int)maxBitrate, (unsigned int)minBitrate);
}

void UYoumeVideoAPI::SetVideoCodeBitrateForShare(int32 maxBitrate, int32 minBitrate)
{
	FYoumeVideoWork::Manager()->setVideoCodeBitrateForShare((unsigned int)maxBitrate, (unsigned int)minBitrate);
}

int32 UYoumeVideoAPI::GetCurrentVideoCodeBitrate()
{
	return FYoumeVideoWork::Manager()->getCurrentVideoCodeBitrate();
}

EYVErrorCode UYoumeVideoAPI::SetVBR(bool useVBR)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVBR(useVBR));
}

EYVErrorCode UYoumeVideoAPI::SetVBRForSecond(bool useVBR)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVBRForSecond(useVBR));
}

EYVErrorCode UYoumeVideoAPI::SetVBRForShare(bool useVBR)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVBRForShare(useVBR));
}

void UYoumeVideoAPI::SetVideoHardwareCodeEnable(bool enable)
{
	FYoumeVideoWork::Manager()->setVideoHardwareCodeEnable(enable);
}

bool UYoumeVideoAPI::GetVideoHardwareCodeEnable()
{
	return FYoumeVideoWork::Manager()->getVideoHardwareCodeEnable();
}

bool UYoumeVideoAPI::GetUseGL()
{
	return FYoumeVideoWork::Manager()->getUseGL();
}

void UYoumeVideoAPI::SetVideoNoFrameTimeout(int32 timeout)
{
	FYoumeVideoWork::Manager()->setVideoNoFrameTimeout(timeout);
}

EYVErrorCode UYoumeVideoAPI::QueryUsersVideoInfo(TArray<FString> userList)
{
	std::vector<std::string> tmpUserList;
	for (auto& user : userList)
	{
		tmpUserList.push_back(std::string(TCHAR_TO_UTF8(*user)));
	}
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->queryUsersVideoInfo(tmpUserList));
}

EYVErrorCode UYoumeVideoAPI::SetUsersVideoInfo(TArray<FUserVideoInfo> videoInfoList)
{
	std::vector<IYouMeVoiceEngine::userVideoInfo> tmpVideoInfoList;
	for (auto& info : videoInfoList)
	{
		IYouMeVoiceEngine::userVideoInfo tmpInfo;
		tmpInfo.userId = std::string(TCHAR_TO_UTF8(*info.userId));
		tmpInfo.bitResolutionType = info.bitResolutionType;
		tmpInfo.resolutionType = info.resolutionType;
		tmpVideoInfoList.push_back(tmpInfo);
	}
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setUsersVideoInfo(tmpVideoInfoList));
}

EYVErrorCode UYoumeVideoAPI::OpenBeautify(bool open)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->openBeautify(open));
}

EYVErrorCode UYoumeVideoAPI::BeautifyChanged(float param)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->beautifyChanged(param));
}

bool UYoumeVideoAPI::ReleaseMicSync()
{
	return FYoumeVideoWork::Manager()->releaseMicSync();
}

bool UYoumeVideoAPI::ResumeMicSync()
{
	return FYoumeVideoWork::Manager()->resumeMicSync();
}

int32 UYoumeVideoAPI::GetCameraCount()
{
	return FYoumeVideoWork::Manager()->getCameraCount();
}

FString UYoumeVideoAPI::GetCameraName(int32 cameraId)
{
	return FString(UTF8_TO_TCHAR(FYoumeVideoWork::Manager()->getCameraName(cameraId)));
}

EYVErrorCode UYoumeVideoAPI::SetOpenCameraId(int cameraId)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setOpenCameraId(cameraId));
}

int32 UYoumeVideoAPI::GetRecordDeviceCount()
{
	return FYoumeVideoWork::Manager()->getRecordDeviceCount();
}

bool UYoumeVideoAPI::GetRecordDeviceInfo(int32 index, const FString deviceName, const FString deviceUId)
{
	return FYoumeVideoWork::Manager()->getRecordDeviceInfo(index, TCHAR_TO_UTF8(*deviceName), TCHAR_TO_UTF8(*deviceUId));
}

bool UYoumeVideoAPI::GetCurrentRecordDeviceInfo(const FString deviceUId)
{
	return FYoumeVideoWork::Manager()->getCurrentRecordDeviceInfo(TCHAR_TO_UTF8(*deviceUId));
}

EYVErrorCode UYoumeVideoAPI::SetRecordDevice(const FString deviceUId)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setRecordDevice(TCHAR_TO_UTF8(*deviceUId)));
}

void UYoumeVideoAPI::SetMixVideoSize(int32 width, int32 height)
{
	FYoumeVideoWork::Manager()->setMixVideoSize(width, height);
}

void UYoumeVideoAPI::AddMixOverlayVideo(const FString userId, int32 x, int32 y, int32 z, int32 width, int32 height)
{
	FYoumeVideoWork::Manager()->addMixOverlayVideo(TCHAR_TO_UTF8(*userId), x, y, z, width, height);
}

void UYoumeVideoAPI::RemoveMixOverlayVideoById(const FString userId)
{
	FYoumeVideoWork::Manager()->removeMixOverlayVideo(TCHAR_TO_UTF8(*userId));
}

void UYoumeVideoAPI::RemoveAllOverlayVideo()
{
	FYoumeVideoWork::Manager()->removeAllOverlayVideo();
}

EYVErrorCode UYoumeVideoAPI::SetExternalFilterEnabled(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setExternalFilterEnabled(enabled));
}

int32 UYoumeVideoAPI::EnableLocalVideoRender(bool enabled)
{
	return FYoumeVideoWork::Manager()->enableLocalVideoRender(enabled);
}

int32 UYoumeVideoAPI::EnableLocalVideoSend(bool enabled)
{
	return FYoumeVideoWork::Manager()->enableLocalVideoSend(enabled);
}

int32 UYoumeVideoAPI::MuteAllRemoteVideoStreams(bool mute)
{
	return FYoumeVideoWork::Manager()->muteAllRemoteVideoStreams(mute);
}

int32 UYoumeVideoAPI::SetDefaultMuteAllRemoteVideoStreams(bool mute)
{
	return FYoumeVideoWork::Manager()->setDefaultMuteAllRemoteVideoStreams(mute);
}

int32 UYoumeVideoAPI::MuteRemoteVideoStream(const FString uid, bool mute)
{
	return FYoumeVideoWork::Manager()->muteRemoteVideoStream(TCHAR_TO_UTF8(*uid), mute);
}


bool UYoumeVideoAPI::IsCameraZoomSupported()
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->isCameraZoomSupported();
#else
	return false;
#endif
}

float UYoumeVideoAPI::SetCameraZoomFactor(float zoomFactor)
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->setCameraZoomFactor(zoomFactor);
#else
	return 0.f;
#endif
}

bool UYoumeVideoAPI::IsCameraFocusPositionInPreviewSupported()
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->isCameraFocusPositionInPreviewSupported();
#else
	return false;
#endif
}

bool UYoumeVideoAPI::SetCameraFocusPositionInPreview(float x, float y)
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->setCameraFocusPositionInPreview(x, y);
#else
	return false;
#endif
}

bool UYoumeVideoAPI::IsCameraTorchSupported()
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->isCameraTorchSupported();
#else
	return false;
#endif
}

bool UYoumeVideoAPI::SetCameraTorchOn(bool isOn)
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->setCameraTorchOn(isOn);
#else
	return false;
#endif
}

bool UYoumeVideoAPI::IsCameraAutoFocusFaceModeSupported()
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->isCameraAutoFocusFaceModeSupported();
#else
	return false;
#endif
}

bool UYoumeVideoAPI::SetCameraAutoFocusFaceModeEnabled(bool enable)
{
#if PLATFORM_IOS // || PLATFORM_ANDROID
	return FYoumeVideoWork::Manager()->setCameraAutoFocusFaceModeEnabled(enable);
#else
	return false;
#endif
}

void UYoumeVideoAPI::SetLocalVideoMirrorMode(EYVVideoMirrorMode mode)
{
	FYoumeVideoWork::Manager()->setLocalVideoMirrorMode(YoumeVideoUtils::ReverseVideoMirrorMode(mode));
}

void UYoumeVideoAPI::SetLocalVideoPreviewMirror(bool enable)
{
	FYoumeVideoWork::Manager()->setLocalVideoPreviewMirror(enable);
}

EYVErrorCode UYoumeVideoAPI::SetVideoFrameRawCbEnabled(bool enabled)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoFrameRawCbEnabled(enabled));
}

EYVErrorCode UYoumeVideoAPI::StartPush(const FString pushUrl)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->startPush(TCHAR_TO_UTF8(*pushUrl)));
}

EYVErrorCode UYoumeVideoAPI::StopPush()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->stopPush());
}

EYVErrorCode UYoumeVideoAPI::SetPushMix(const FString pushUrl, int32 width, int32 height)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setPushMix(TCHAR_TO_UTF8(*pushUrl), width, height));
}

EYVErrorCode UYoumeVideoAPI::ClearPushMix()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->clearPushMix());
}

EYVErrorCode UYoumeVideoAPI::AddPushMixUser(const FString userId, int32 x, int32 y, int32 z, int32 width, int32 height)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->addPushMixUser(TCHAR_TO_UTF8(*userId), x, y, z, width, height));
}

EYVErrorCode UYoumeVideoAPI::RemovePushMixUser(const FString userId)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->removePushMixUser(TCHAR_TO_UTF8(*userId)));
}

void UYoumeVideoAPI::EnableShareBorder(bool enable)
{
#if PLATFORM_MAC
	FYoumeVideoWork::Manager()->enableShareBorder(enable);
#endif
}

EYVErrorCode UYoumeVideoAPI::CheckSharePermission()
{
#if PLATFORM_MAC
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->checkSharePermission());
#else
	return EYVErrorCode::ERROR_UNKNOWN;
#endif
}

EYVErrorCode UYoumeVideoAPI::SetShareExclusiveWnd(int32 windowid)
{
#if PLATFORM_MAC
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setShareExclusiveWnd(windowid));
#else
	return EYVErrorCode::ERROR_UNKNOWN;
#endif
}

void UYoumeVideoAPI::StopShareStream()
{
	FYoumeVideoWork::Manager()->StopShareStream();
}

EYVErrorCode UYoumeVideoAPI::StartSaveScreen(const FString filePath)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->startSaveScreen(TCHAR_TO_UTF8(*filePath)));
}

void UYoumeVideoAPI::StopSaveScreen()
{
	FYoumeVideoWork::Manager()->stopSaveScreen();
}

FString UYoumeVideoAPI::GetShareVideoData(int32& len, int32& width, int32& height, int32& fmt)
{
	// return FString(UTF8_TO_TCHAR(FYoumeVideoWork::Manager()->GetShareVideoData(&len, &width, &height, &fmt)));
	return FString();
}

EYVErrorCode UYoumeVideoAPI::SwitchResolutionForLandscape()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->switchResolutionForLandscape());
}

EYVErrorCode UYoumeVideoAPI::ResetResolutionForPortrait()
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->resetResolutionForPortrait());
}

EYVErrorCode UYoumeVideoAPI::TranslateText(const FString text, EYVLanguageCode destLangCode, EYVLanguageCode srcLangCode, int32& requestID)
{
	unsigned int tmpRequestID = 0;
	EYVErrorCode Error = YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->translateText(&tmpRequestID, TCHAR_TO_UTF8(*text), YoumeVideoUtils::ReverseLanguageCode(destLangCode), YoumeVideoUtils::ReverseLanguageCode(srcLangCode)));
	requestID = (int32)tmpRequestID;
	return Error;
}

EYVErrorCode UYoumeVideoAPI::InviteSipUser(const FString userId, const FString gatewayUrl)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->inviteSipUser(TCHAR_TO_UTF8(*userId), TCHAR_TO_UTF8(*gatewayUrl)));
}

EYVErrorCode UYoumeVideoAPI::SetVideoCodecType(int32 codecType)
{
	return YoumeVideoUtils::ConvertErrorCode(FYoumeVideoWork::Manager()->setVideoCodecType(codecType));
}

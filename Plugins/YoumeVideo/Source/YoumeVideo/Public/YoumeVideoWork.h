// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Interface.h"
#include "YoumeVideoType.h"
#include "YoumeVideoObserver.h"
#include "IYouMeVoiceEngine.h"
#include "YoumeVideoTextureSample.h"


/**
 *
 */
class YOUMEVIDEO_API FYoumeVideoWork : public IYouMeEventCallback
	, IYouMeVideoFrameCallback
	, IYouMeAudioFrameCallback
	, IYouMeAVStatisticCallback
	, IYouMeAVStatisticNewCallback
	, IYouMePcmCallback
	, IYouMeTranscriberCallback
	, IYouMeTranslateCallback
	, IYouMeVideoPreDecodeCallback
	, IRestApiCallback
	, IYouMeMemberChangeCallback
	, IYouMeChannelMsgCallback
	, IYouMeCustomDataCallback
{
public:

	FYoumeVideoWork();

	~FYoumeVideoWork();

	static FYoumeVideoWork* Instance();

	static IYouMeVoiceEngine* Manager();

	EYVErrorCode Start(const FString appKey, const FString aPPSecret,
		EYVRtcServerRegion serverRegionId, const FString extServerRegionName);

	EYVErrorCode StartPcm(EYVPcmCallBackFlag pcmFlag, bool outputToSpeaker, int32 outputSampleRate, int32 outputChannel);

	void Close();

	void BindObserver(TScriptInterface<IYoumeVideoObserver> Listener);

	void UnbindObserver();

private:

	static FYoumeVideoWork* YVWork;

	static IYouMeVoiceEngine* YVEngine;

	UObject* YVObserver;

	/** Video sample object pool. */
	FYoumeVideoTextureSamplePool* VideoSamplePool;

	const int32 RenderSpace = 3;

public:

#pragma region IYouMeEventCallback

	void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char* channel, const char* param) override;

#pragma endregion

#pragma region IYouMeVideoFrameCallback

	void onVideoFrameCallback(const char* userId, void* data, int len, int width, int height, int fmt, uint64_t timestamp) override;


	void onVideoFrameMixedCallback(void* data, int len, int width, int height, int fmt, uint64_t timestamp) override;


	void onVideoFramePreviewCallback(void* data, int len, int width, int height, int fmt, uint64_t timestamp, int rotation, int mirror) override;


	void onVideoFrameCallbackGLESForIOS(const char* userId, void* buffer, int width, int height, int fmt, uint64_t timestamp) override;


	void onVideoFrameMixedCallbackGLESForIOS(void* buffer, int width, int height, int fmt, uint64_t timestamp) override;


	void onVideoFrameCallbackGLESForAndroid(const char* userId, int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp) override;


	void onVideoFrameMixedCallbackGLESForAndroid(int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp) override;


	int onVideoRenderFilterCallback(int textureId, int width, int height, int rotation, int mirror) override;

    
#if PLATFORM_MAC || PLATFORM_IOS
    
    int32 GetRotationFromDeviceOrientation();
    
#endif
    

#pragma endregion

#pragma region IYouMeAudioFrameCallback

	void onAudioFrameCallback(const char* userId, void* data, int len, uint64_t timestamp) override;

	void onAudioFrameMixedCallback(void* data, int len, uint64_t timestamp) override;

#pragma endregion

#pragma region IYouMeAVStatisticCallback

	void onAVStatistic(YouMeAVStatisticType type, const char* userID, int value) override;

#pragma endregion

#pragma region IYouMeAVStatisticNewCallback

	void onAVStatisticNew(YouMeAVStatisticType type, const char* userID, int value, const char* param) override;

#pragma endregion

#pragma region IYouMePcmCallback

	void onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;


	void onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;


	void onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;

#pragma endregion

#pragma region IYouMeTranscriberCallback

	void onSentenceBegin(std::string userid, int sentenceIndex) override;


	void onSentenceEnd(std::string userid, int sentenceIndex, std::string result, std::string transLang = "", std::string transResult = "") override;


	void onSentenceChanged(std::string userid, int sentenceIndex, std::string result, std::string transLang = "", std::string transResult = "") override;

#pragma endregion

#pragma region IYouMeTranslateCallback

	void onTranslateTextComplete(YouMeErrorCode errorcode, unsigned int requestID, const std::string& text, YouMeLanguageCode srcLangCode, YouMeLanguageCode destLangCode) override;

#pragma endregion

#pragma region IYouMeVideoPreDecodeCallback

	void onVideoPreDecode(const char* userId, void* data, int dataSizeInByte, unsigned long long timestamp, int type) override;

#pragma endregion

#pragma region IRestApiCallback

	void onRequestRestAPI(int requestID, const YouMeErrorCode& iErrorCode, const char* strQuery, const char* strResult) override;

#pragma endregion

#pragma region IYouMeMemberChangeCallback

	void onMemberChange(const char* channel, const char* listMemberChangeJson, bool bUpdate) override;

	void onMemberChange(const char* channel, const char* userID, bool isJoin, bool bUpdate) override;

#pragma endregion

#pragma region IYouMeChannelMsgCallback

	void onBroadcast(const YouMeBroadcast bc, const char* channel, const char* param1, const char* param2, const char* strContent) override;

#pragma endregion

#pragma region IYouMeCustomDataCallback

	void OnCustomDataNotify(const void* pData, int iDataLen, unsigned long long ulTimeSpan) override;

#pragma endregion
};

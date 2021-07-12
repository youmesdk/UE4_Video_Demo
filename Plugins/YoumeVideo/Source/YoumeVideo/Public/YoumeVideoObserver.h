// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Interface.h"
#include "YoumeVideoType.h"
#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "YoumeVideoTexture.h"
#include "YoumeVideoObserver.generated.h"

/**
 * 
 */

UINTERFACE(MinimalAPI)
class UYoumeVideoObserver : public UInterface
{
	GENERATED_BODY()
};

class YOUMEVIDEO_API IYoumeVideoObserver
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnEvent(const EYVEvent& event, const EYVErrorCode& error, const FString& channel, const FString& param);
	virtual void OnEvent_Implementation(const EYVEvent& event, const EYVErrorCode& error, const FString& channel, const FString& param) {}


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnMixTextureUpdate(UYoumeVideoTexture* OutTex);
	virtual void OnMixTextureUpdate_Implementation(UYoumeVideoTexture* OutTex) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnUserTextureUpdate(const FString& UserID, UYoumeVideoTexture* OutTex);
	virtual void OnUserTextureUpdate_Implementation(const FString& UserID, UYoumeVideoTexture* OutTex) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnAVStatistic(const EYVAVStatisticType& type, const FString& userID, const int32& value);
	virtual void OnAVStatistic_Implementation(const EYVAVStatisticType& type, const FString& userID, const int32& value) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnAVStatisticNew(const EYVAVStatisticType& type, const FString& userID, const int32& value, const FString& param);
	virtual void OnAVStatisticNew_Implementation(const EYVAVStatisticType& type, const FString& userID, const int32& value, const FString& param) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnSentenceBegin(const FString& userid, const int32& sentenceIndex);
	virtual void OnSentenceBegin_Implementation(const FString& userid, const int32& sentenceIndex) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnSentenceEnd(const FString& userid, const int32& sentenceIndex, const FString& result, const FString& transLang, const FString& transResult);
	virtual void OnSentenceEnd_Implementation(const FString& userid, const int32& sentenceIndex, const FString& result, const FString& transLang, const FString& transResult) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnSentenceChanged(const FString& userid, const int32& sentenceIndex, const FString& result, const FString& transLang, const FString& transResult);
	virtual void OnSentenceChanged_Implementation(const FString& userid, const int32& sentenceIndex, const FString& result, const FString& transLang, const FString& transResult) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnVideoTranslateTextComplete(const EYVErrorCode& errorcode, const int32& requestID, const FString& text, const EYVLanguageCode& srcLangCode, const EYVLanguageCode& destLangCode);
	virtual void OnVideoTranslateTextComplete_Implementation(const EYVErrorCode& errorcode, const int32& requestID, const FString& text, const EYVLanguageCode& srcLangCode, const EYVLanguageCode& destLangCode) {};



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnRequestRestAPI(const int32& requestID, const EYVErrorCode& errorcode, const FString& strQuery, const FString& strResult);
	virtual void OnRequestRestAPI_Implementation(const int32& requestID, const EYVErrorCode& errorcode, const FString& strQuery, const FString& strResult) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnMemberChange(const FString& channel, const FString& listMemberChangeJson, const bool bUpdate);
	virtual void OnMemberChange_Implementation(const FString& channel, const FString& listMemberChangeJson, const bool bUpdate) {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnMemberJoinChange(const FString& channel, const FString& userID, const bool bJoin, const bool bUpdate);
	virtual void OnMemberJoinChange_Implementation(const FString& channel, const FString& userID, const bool bJoin, const bool bUpdate) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YoumeVideo")
		void OnBroadcast(const EYVBroadcast& bc, const FString& channel, const FString& param1, const FString& param2, const FString& strContent);
	virtual void OnBroadcast_Implementation(const EYVBroadcast& bc, const FString& channel, const FString& param1, const FString& param2, const FString& strContent) {};


};

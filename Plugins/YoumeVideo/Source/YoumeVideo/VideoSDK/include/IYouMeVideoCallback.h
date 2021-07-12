
#ifndef IYouMeFrameCallback_h
#define IYouMeFrameCallback_h
#include <stdint.h>
#include <string>
#include "YouMeConstDefine.h"


class IYouMeVideoFrameCallback {
public:

    virtual void onVideoFrameCallback(const char* userId, void * data, int len, int width, int height, int fmt, uint64_t timestamp){};
    virtual void onVideoFrameMixedCallback(void * data, int len, int width, int height, int fmt, uint64_t timestamp){};
	virtual void onVideoFramePreviewCallback(void * data, int len, int width, int height, int fmt, uint64_t timestamp, int rotation,int mirror){};
    

	virtual void onVideoFrameCallbackGLESForIOS(const char* userId, void* pixelBuffer, int width, int height, int fmt, uint64_t timestamp){};
    virtual void onVideoFrameMixedCallbackGLESForIOS(void* pixelBuffer, int width, int height, int fmt, uint64_t timestamp){};
 

	virtual void onVideoFrameCallbackGLESForAndroid(const char* userId, int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp){};
    virtual void onVideoFrameMixedCallbackGLESForAndroid(int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp){};
  

    virtual int  onVideoRenderFilterCallback(int textureId, int width, int height, int rotation, int mirror){return 0;};
};

class IYouMeAudioFrameCallback {
public:
	virtual void onAudioFrameCallback(const char* userId, void* data, int len, uint64_t timestamp) = 0;
    virtual void onAudioFrameMixedCallback(void* data, int len, uint64_t timestamp) = 0;
};

class IYouMeAVStatisticCallback
{
public:
    virtual void onAVStatistic( YouMeAVStatisticType type,  const char* userID,  int value ) = 0 ;
};


class IYouMeAVStatisticNewCallback
{
public:
    virtual void onAVStatisticNew( YouMeAVStatisticType type,  const char* userID,  int value, const char* param) = 0 ;
};

#endif /* IYouMeFrameCallback_h */

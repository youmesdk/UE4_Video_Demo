
#import <Foundation/Foundation.h>
#import "YouMeConstDefine.h"

@interface MemberChangeOC: NSObject

@property (nonatomic, retain) NSString* userID ;

@property (nonatomic, assign) bool  isJoin;
@end

@protocol VoiceEngineCallback <NSObject>

- (void)onYouMeEvent:(YouMeEvent_t)eventType errcode:(YouMeErrorCode_t)iErrorCode roomid:(NSString *)roomid param:(NSString *)param;


- (void)onRequestRestAPI: (int)requestID iErrorCode:(YouMeErrorCode_t) iErrorCode  query:(NSString*) strQuery  result:(NSString*) strResult ;


- (void)onMemberChange:(NSString*) channelID changeList:(NSArray*) changeList isUpdate:(bool) isUpdate ;


- (void)onBroadcast:(YouMeBroadcast_t)bc strChannelID:(NSString*)channelID strParam1:(NSString*)param1 strParam2:(NSString*)param2 strContent:(NSString*)content;


- (void) onAVStatistic:(YouMeAVStatisticType_t)type  userID:(NSString*)userID  value:(int) value ;

- (void) onAVStatisticNew:(YouMeAVStatisticType_t)type  userID:(NSString*)userID  value:(int) value  strParam:(NSString*)strParam;


- (void)onAudioFrameCallback: (NSString*)userId data:(void*) data len:(int)len timestamp:(uint64_t)timestamp;

- (void)onAudioFrameMixedCallback: (void*)data len:(int)len timestamp:(uint64_t)timestamp;

- (void)onVideoFrameCallback: (NSString*)userId data:(void*) data len:(int)len width:(int)width height:(int)height fmt:(int)fmt timestamp:(uint64_t)timestamp;

- (void)onVideoFrameMixedCallback: (void*) data len:(int)len width:(int)width height:(int)height fmt:(int)fmt timestamp:(uint64_t)timestamp;

- (void)onVideoFrameCallbackForGLES:(NSString*)userId  pixelBuffer:(CVPixelBufferRef)pixelBuffer timestamp:(uint64_t)timestamp;

- (void)onVideoFrameMixedCallbackForGLES:(CVPixelBufferRef)pixelBuffer timestamp:(uint64_t)timestamp;


- (int)onVideoRenderFilterCallback:(int)textureId width:(int)width height:(int)height rotation:(int)rotation mirror:(int)mirror;


- (void)onCustomDataCallback: (const void*)data len:(int)len timestamp:(uint64_t)timestamp;

- (void)onTranslateTextComplete:(YouMeErrorCode_t)errorcode requestID:(unsigned int)requestID  text:(NSString*)text  srcLangCode:(YouMeLanguageCode_t)srcLangCode destLangCode:(YouMeLanguageCode_t)destLangCode;


- (void)onPcmDataRemote: (int)channelNum samplingRateHz:(int)samplingRateHz bytesPerSample:(int)bytesPerSample data:(void*) data dataSizeInByte:(int)dataSizeInByte;

- (void)onPcmDataRecord: (int)channelNum samplingRateHz:(int)samplingRateHz bytesPerSample:(int)bytesPerSample data:(void*) data dataSizeInByte:(int)dataSizeInByte;

- (void)onPcmDataMix: (int)channelNum samplingRateHz:(int)samplingRateHz bytesPerSample:(int)bytesPerSample data:(void*) data dataSizeInByte:(int)dataSizeInByte;

- (void)onVideoPreDecodeDataForUser:(const char *)userId data:(const void*)data len:(int)dataSizeInByte ts:(uint64_t)timestamp fameType:(int)type;

@end

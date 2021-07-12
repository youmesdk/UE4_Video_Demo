# Video SDK for UE4 状态码

## EYVEvent类型定义

枚举常量 |值| 含义
-------|------|------
INIT_OK                   |0|SDK初始化成功
INIT_FAILED               | 1|SDK初始化失败
JOIN_OK                   | 2| 进入语音频道成功
JOIN_FAILED               | 3| 进入语音频道失败
LEAVED_ONE                | 4|退出单个语音频道完成
LEAVED_ALL                | 5|退出所有语音频道完成
PAUSED                    | 6|暂停语音频道完成
RESUMED                   | 7| 恢复语音频道完成
SPEAK_SUCCESS             | 8|切换对指定频道讲话成功（适用于多频道模式）
SPEAK_FAILED              | 9| 切换对指定频道讲话失败（适用于多频道模式）
RECONNECTING              | 10| 断网了，正在重连
RECONNECTED               | 11|断网重连成功
REC_PERMISSION_STATUS     | 12|通知录音权限状态，成功获取权限时错误码为SUCCESS，获取失败为ERROR_REC_NO_PERMISSION（此时不管麦克风mute状态如何，都没有声音输出）
BGM_STOPPED               | 13| 通知背景音乐播放结束
BGM_FAILED                | 14| 通知背景音乐播放失败
OTHERS_MIC_ON             | 16| 其他用户麦克风打开
OTHERS_MIC_OFF            | 17| 其他用户麦克风关闭
OTHERS_SPEAKER_ON         | 18| 其他用户扬声器打开
OTHERS_SPEAKER_OFF        | 19| 其他用户扬声器关闭
OTHERS_VOICE_ON           | 20|其他用户进入讲话状态
OTHERS_VOICE_OFF          | 21| 其他用户进入静默状态
MY_MIC_LEVEL              | 22| 麦克风的语音级别
MIC_CTR_ON                | 23| 麦克风被其他用户打开
MIC_CTR_OFF               | 24| 麦克风被其他用户关闭
SPEAKER_CTR_ON            | 25| 扬声器被其他用户打开
SPEAKER_CTR_OFF           | 26| 扬声器被其他用户关闭
LISTEN_OTHER_ON           | 27| 取消屏蔽某人语音
LISTEN_OTHER_OFF          | 28| 屏蔽某人语音
LOCAL_MIC_ON              | 29| 自己的麦克风打开
LOCAL_MIC_OFF             | 30| 自己的麦克风关闭
LOCAL_SPEAKER_ON	      | 31| 自己的扬声器打开
LOCAL_SPEAKER_OFF	      | 32| 自己的扬声器关闭
GRABMIC_START_OK          | 33| 发起抢麦活动成功
GRABMIC_START_FAILED      | 34| 发起抢麦活动失败
GRABMIC_STOP_OK           | 35| 停止抢麦活动成功
GRABMIC_STOP_FAILED       | 36| 停止抢麦活动失败
GRABMIC_REQUEST_OK	      | 37| 抢麦成功（可以说话）
GRABMIC_REQUEST_FAILED    | 38| 抢麦失败
GRABMIC_REQUEST_WAIT      | 39| 进入抢麦等待队列（仅权重模式下会回调此事件）
GRABMIC_RELEASE_OK        | 40| 释放麦成功
GRABMIC_RELEASE_FAILED    | 41| 释放麦失败
GRABMIC_ENDMIC            | 42| 不再占用麦（到麦使用时间或者其他原因）
GRABMIC_NOTIFY_START      | 43| [通知]抢麦活动开始
GRABMIC_NOTIFY_STOP       | 44| [通知]抢麦活动结束
GRABMIC_NOTIFY_HASMIC     | 45| [通知]有麦可以抢
GRABMIC_NOTIFY_NOMIC      | 46| [通知]没有麦可以抢
INVITEMIC_SETOPT_OK       | 47| 连麦设置成功
INVITEMIC_SETOPT_FAILED   | 48| 连麦设置失败
INVITEMIC_REQUEST_OK      | 49| 请求连麦成功（连上了，需等待对方回应）
INVITEMIC_REQUEST_FAILED  | 50| 请求连麦失败
INVITEMIC_RESPONSE_OK     | 51| 响应连麦成功（被叫方无论同意/拒绝都会收到此事件，错误码是ERROR_INVITEMIC_REJECT表示拒绝）
INVITEMIC_RESPONSE_FAILED | 52| 响应连麦失败
INVITEMIC_STOP_OK         | 53| 停止连麦成功
INVITEMIC_STOP_FAILED     | 54| 停止连麦失败
INVITEMIC_CAN_TALK        | 55| 双方可以通话了（响应方已经同意）
INVITEMIC_CANNOT_TALK     | 56| 双方不可以再通话了（有一方结束了连麦或者连麦时间到）
INVITEMIC_NOTIFY_CALL     | 57| [通知]有人请求与你连麦
INVITEMIC_NOTIFY_ANSWER   | 58| [通知]对方对你的连麦请求作出了响应（同意/拒绝/超时，同意的话双方就可以通话了）
INVITEMIC_NOTIFY_CANCEL   | 59| [通知]连麦过程中，对方结束了连麦或者连麦时间到
SEND_MESSAGE_RESULT       | 60| sendMessage成功与否的通知，param为回传的requestID
MESSAGE_NOTIFY            | 61| 收到Message, param为message内容
KICK_RESULT               | 64| 踢人的应答, param: 被踢者ID
KICK_NOTIFY               | 65| 被踢通知   ,param: （踢人者ID，被踢原因，被禁时间）
FAREND_VOICE_LEVEL        | 66| 远端说话人音量大小,param:(说话人userid)
OTHERS_BE_KICKED          | 67| 房间里其他人被踢出房间
AUDIO_START_FAIL          | 72| 音频启动失败，可能是设备被其他应用占用
AUDIO_INPUT_DEVICE_CONNECT     | 73 |音频采集设备插入，移动端无效
AUDIO_INPUT_DEVICE_DISCONNECT   | 74 | 音频采集设备拔出，移动端无效
SWITCH_OUTPUT            | 75  | 切换扬声器/听筒
OTHERS_VIDEO_ON           | 200| 收到其它用户的视频流
MASK_VIDEO_BY_OTHER_USER  | 204| 视频被其他用户屏蔽
RESUME_VIDEO_BY_OTHER_USER| 205| 视频被其他用户恢复
MASK_VIDEO_FOR_USER       | 206| 屏蔽了谁的视频
RESUME_VIDEO_FOR_USER     | 207| 恢复了谁的视频
OTHERS_VIDEO_SHUT_DOWN    | 208| 其它用户的视频流断开（包含网络中断的情况）
OTHERS_VIDEO_INPUT_START  | 209| 其他用户视频输入开始（内部采集下开启摄像头/外部输入下开始input）
OTHERS_VIDEO_INPUT_STOP   | 210| 其他用户视频输入停止（内部采集下停止摄像头/外部输入下停止input）
MEDIA_DATA_ROAD_PASS      | 211| 音视频数据通路连通，定时检测，一开始收到数据会收到PASS事件，之后变化的时候会发送
MEDIA_DATA_ROAD_BLOCK     | 212| 音视频数据通路不通
QUERY_USERS_VIDEO_INFO    | 213| 查询用户视频信息返回
SET_USERS_VIDEO_INFO      | 214| 设置用户接收视频信息返回
LOCAL_VIDEO_INPUT_START   | 215| 本地视频输入开始（内部采集下开始摄像头/外部输入下开始input）
LOCAL_VIDEO_INPUT_STOP    | 216| 本地视频输入停止（内部采集下停止摄像头/外部输入下停止input）
 START_PUSH                    | 217|设置startPush的返回事件
    SET_PUSH_MIX                  | 218|设置setPushMix的返回事件
    ADD_PUSH_MIX_USER             | 219|设置addPushMixUser的返回事件，参数userID
    OTHER_SET_PUSH_MIX            | 220|在自己调用了setPushMix还没停止的情况下，房间内有别人调用setPushMix，自己被踢
LOCAL_SHARE_INPUT_START      | 221|本地共享视频输入开始
    LOCAL_SHARE_INPUT_STOP       | 222|本地共享视频输入停止
    OTHERS_SHARE_INPUT_START     | 223| 其他用户共享视频输入开始
    OTHERS_SHARE_INPUT_STOP      | 224|其他用户共享视频输入停止
SET_USERS_VIDEO_INFO_NOTIFY  | 225|设置用户接收视频信息给发送方的通知
OTHERS_DATA_ERROR         | 300| 数据错误
OTHERS_NETWORK_BAD        | 301| 网络不好
OTHERS_BLACK_FULL         | 302| 黑屏
OTHERS_GREEN_FULL         | 303| 绿屏
OTHERS_BLACK_BORDER       | 304| 黑边
OTHERS_GREEN_BORDER       | 305| 绿边
OTHERS_BLURRED_SCREEN     | 306| 花屏
OTHERS_ENCODER_ERROR      | 307| 编码错误
OTHERS_DECODER_ERROR      | 308| 解码错误
CAMERA_DEVICE_CONNECT     | 400| 摄像头设备插入，移动端无效
CAMERA_DEVICE_DISCONNECT  | 401| 摄像头设备拔出，移动端无效
EOF                       |1000|

## EYVErrorCode类型定义

枚举常量|值|含义
----|------|-----
SUCCESS                            |0| 成功
ERROR_API_NOT_SUPPORTED            |-1| 正在使用的SDK不支持特定的API
ERROR_INVALID_PARAM                |-2| 传入参数错误
ERROR_ALREADY_INIT                 |-3| 已经初始化
ERROR_NOT_INIT                     |-4| 还没有初始化，在调用某函数之前要先调用初始化并且要据返回值确保初始化成功
ERROR_CHANNEL_EXIST                |-5| 要加入的频道已经存在
ERROR_CHANNEL_NOT_EXIST            |-6| 要退出的频道不存在，或者其它操作指定的频道不存在
ERROR_WRONG_STATE                  |-7| 状态错误
ERROR_NOT_ALLOWED_MOBILE_NETWROK   |-8| 不允许使用移动网络
ERROR_WRONG_CHANNEL_MODE           |-9| 在单频道模式下调用了多频道接口，或者反之
ERROR_TOO_MANY_CHANNELS            |-10|同时加入了太多频道
ERROR_TOKEN_ERROR                  |-11|传入的token认证错误
ERROR_NOT_IN_CHANNEL               |-12|用户不在该频道
ERROR_BE_KICK                      |-13|被踢了，还在禁止时间内，不允许进入房间
ERROR_DEVICE_NOT_VALID             |-14|设置的设备不可用
ERROR_API_NOT_ALLOWED              |-15|没有特定功能的权限，需要的话请联系我们
ERROR_MEMORY_OUT                   |-100|内存错误
ERROR_START_FAILED                 |-101|启动引擎失败
ERROR_STOP_FAILED                  |-102|停止引擎失败
ERROR_ILLEGAL_SDK                  |-103|非法使用SDK
ERROR_SERVER_INVALID               |-104|语音服务不可用
ERROR_NETWORK_ERROR                |-105|网络错误
ERROR_SERVER_INTER_ERROR           |-106|服务器内部错误
ERROR_QUERY_RESTAPI_FAIL           |-107|请求RestApi信息失败了
ERROR_USER_ABORT                   |-108|用户请求中断当前操作
ERROR_SEND_MESSAGE_FAIL            |-109|发送消息失败
ERROR_SET_PUSH_PARAM_FAIL          |-110| 向服务器设置Push参数失败
ERROR_INIT_SHARE_FAIL              |-111| 初始化共享设备失败
ERROR_START_SHARE_FAIL             |-112| 开始视频共享失败
ERROR_REC_INIT_FAILED              |-201|录音模块初始化失败
ERROR_REC_NO_PERMISSION            |-202|没有录音权限
ERROR_REC_NO_DATA                  |-203|虽然初始化成功，但没有音频数据输出，比如oppo系列机在录音权限被禁止的时候
ERROR_REC_OTHERS                   |-204|其他录音模块的错误
ERROR_REC_PERMISSION_UNDEFINED     |-205|录音权限未确定，iOS显示是否允许录音权限对话框时，回的是这个错误码
ERROR_GRABMIC_FULL				 |-301|抢麦失败，人数满
ERROR_GRABMIC_HASEND				 |-302|抢麦失败，活动已经结束
ERROR_INVITEMIC_NOUSER			 |-401|连麦失败，用户不存在
ERROR_INVITEMIC_OFFLINE			 |-402|连麦失败，用户已离线
ERROR_INVITEMIC_REJECT			 |-403|连麦失败，用户拒绝
ERROR_INVITEMIC_TIMEOUT			 |-404|连麦失败，两种情况：1.连麦时，对方超时无应答 2.话中，双方通话时间到
ERROR_CAMERA_OPEN_FAILED           | -501|打开摄像头失败

ERROR_NOT_PROCESS                  | -601|不做任何改变
ERROR_UNKNOWN                      |-1000|未知错误



## RTC_SERVER_REGION类型定义

枚举常量|值|含义
----|------|-----
    RTC_CN_SERVER       | 0| 中国
    RTC_HK_SERVER       | 1| 香港
    RTC_US_SERVER       | 2| 美国东部
    RTC_SG_SERVER       | 3| 新加坡
    RTC_KR_SERVER       | 4| 韩国
    RTC_AU_SERVER       | 5| 澳洲
    RTC_DE_SERVER       | 6| 德国
    RTC_BR_SERVER       | 7| 巴西
    RTC_IN_SERVER       | 8| 印度
    RTC_JP_SERVER       | 9| 日本
    RTC_IE_SERVER       | 10|爱尔兰
    RTC_USW_SERVER      | 11|美国西部
    RTC_USM_SERVER      | 12|美国中部
    RTC_CA_SERVER       | 13|加拿大
    RTC_LON_SERVER      | 14| 伦敦
    RTC_FRA_SERVER      | 15|法兰克福
    RTC_DXB_SERVER      | 16| 迪拜
    RTC_EXT_SERVER      |10000|使用扩展服务器
    RTC_DEFAULT_SERVER  |10001|缺省服务器


## YouMeKickReason类型定义
枚举常量|值|含义
----|------|-----
KICK_ADMIN    |1     |管理员踢人
KICK_RELOGIN  |2     | 多端登录被踢

## YouMeBroadcast房间内的广播消息
枚举常量|值|含义
----|------|-----
BROADCAST_NONE    |0|
BROADCAST_GRABMIC_BROADCAST_GETMIC  |1| 有人抢到了麦
BROADCAST_GRABMIC_BROADCAST_FREEMIC    |2|有人释放了麦
BROADCAST_INVITEMIC_BROADCAST_CONNECT  |3| A和B正在连麦
BROADCAST_INVITEMIC_BROADCAST_DISCONNECT    |4|A和B取消了连麦


## LOG_LEVEL类型定义
枚举常量|值|含义
----|------|-----
LOG_DISABLED    | 0|禁用日志
LOG_FATAL       | 1|严重错误
LOG_ERROR       | 10|错误
LOG_WARNING     | 20|警告
LOG_INFO        | 40|信息
LOG_DEBUG       | 50|调试
LOG_VERBOSE     | 60|所有日志

## SAMPLE_RATE类型定义
枚举常量|值
----|------
SAMPLE_RATE_8  | 8000
SAMPLE_RATE_16 | 16000
SAMPLE_RATE_24 | 24000
SAMPLE_RATE_32 | 32000
SAMPLE_RATE_44 | 44100
SAMPLE_RATE_48 | 48000

## AUDIO_QUALITY类型定义
枚举常量|值
----|------
LOW_QUALITY  | 0    | 低音质
HIGH_QUALITY | 1    | 高音质

## YouMeVideoMirrorMode类型定义
枚举常量|值|含义
----|------|-----
VIDEO_MIRROR_MODE_AUTO | 0|            内部采集自适应镜像，外部采集为关闭镜像
VIDEO_MIRROR_MODE_ENABLED | 1|         近端和远端都镜像
VIDEO_MIRROR_MODE_DISABLED | 2|        关闭镜像
VIDEO_MIRROR_MODE_NEAR | 3|            近端镜像
VIDEO_MIRROR_MODE_FAR | 4  |            远端镜像

## VIDEO_FMT类型定义
枚举常量|值
----|------
VIDEO_FMT_RGBA32 |0
VIDEO_FMT_BGRA32 |1
VIDEO_FMT_YUV420P |2
VIDEO_FMT_NV21 |3
VIDEO_FMT_YV12 |4
VIDEO_FMT_CVPIXELBUFFER |5
VIDEO_FMT_TEXTURE |6
VIDEO_FMT_TEXTURE_OES |7
VIDEO_FMT_RGB24 | 8
VIDEO_FMT_NV12 | 9
VIDEO_FMT_H264 | 10

## YouMeUserRole类型定义

枚举常量|值|含义
----|------|-----
USER_NONE | 0|非法用户，调用API时不能传此参数
USER_TALKER_FREE|1|      自由讲话者，适用于小组通话（建议小组成员数最多10个），每个人都可以随时讲话, 同一个时刻只能在一个语音频道里面
USER_TALKER_ON_DEMAND|2 |需要通过抢麦等请求麦克风权限之后才可以讲话，适用于较大的组或工会等（比如几十个人），同一个时刻只能有一个或几个人能讲话, 同一个时刻只能在一个语音频道里面
USER_LISTENER|3         | 听众，主播/指挥/嘉宾的听众，同一个时刻只能在一个语音频道里面，只听不讲
USER_COMMANDER|4        |指挥，国家/帮派等的指挥官，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
USER_HOST|5            |主播，广播型语音频道的主持人，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
USER_GUSET|6            |嘉宾，主播或指挥邀请的连麦嘉宾，同一个时刻只能在一个语音频道里面， 可以随时讲话

## PcmCallBackFlag类型定义

枚举常量|值|含义
----|------|-----
PcmCallbackFlag_Remote | 0x1 |远端pcm回调
PcmCallbackFlag_Record | 0x2 |本地录音回调
PcmCallbackFlag_Mix    | 0x4 |本地录音和远端pcm进行mix之后的回调

## YouMeAVStatisticType类型定义
枚举常量|值|含义
----|------|-----
AVS_AUDIO_CODERATE | 1|         音频传输码率，单位：Byte/s
AVS_VIDEO_CODERATE | 2|         视频传输码率，单位：Byte/s
AVS_VIDEO_FRAMERATE |3|        视频帧率
AVS_AUDIO_PACKET_LOSS_RATE | 4| 音频丢包率,千分比
AVS_VIDEO_PACKET_LOSS_RATE | 5| 视频丢包率,千分比
AVS_VIDEO_BLOCK | 6|            视频卡顿,发生卡顿次数（一定时间内没有视频数据算一次卡顿）



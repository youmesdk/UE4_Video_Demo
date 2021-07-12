// Fill out your copyright notice in the Description page of Project Settings.


#include "YoumeVideoType.h"

EYVUserRole YoumeVideoUtils::ConvertUserRole(YouMeUserRole_t UserRole)
{
	switch (UserRole)
	{
	case YOUME_USER_NONE:
		return EYVUserRole::USER_NONE;
	case YOUME_USER_TALKER_FREE:
		return EYVUserRole::USER_TALKER_FREE;
	case YOUME_USER_TALKER_ON_DEMAND:
		return EYVUserRole::USER_TALKER_ON_DEMAND;
	case YOUME_USER_LISTENER:
		return EYVUserRole::USER_LISTENER;
	case YOUME_USER_COMMANDER:
		return EYVUserRole::USER_COMMANDER;
	case YOUME_USER_HOST:
		return EYVUserRole::USER_HOST;
	case YOUME_USER_GUSET:
		return EYVUserRole::USER_GUSET;
	}
	return EYVUserRole::USER_NONE;
}

YouMeUserRole_t YoumeVideoUtils::ReverseUserRole(EYVUserRole UserRole)
{
	switch (UserRole)
	{
	case EYVUserRole::USER_NONE:
		return YOUME_USER_NONE;
	case EYVUserRole::USER_TALKER_FREE:
		return YOUME_USER_TALKER_FREE;
	case EYVUserRole::USER_TALKER_ON_DEMAND:
		return YOUME_USER_TALKER_ON_DEMAND;
	case EYVUserRole::USER_LISTENER:
		return YOUME_USER_LISTENER;
	case EYVUserRole::USER_COMMANDER:
		return YOUME_USER_COMMANDER;
	case EYVUserRole::USER_HOST:
		return YOUME_USER_HOST;
	case EYVUserRole::USER_GUSET:
		return YOUME_USER_GUSET;
	}
	return YOUME_USER_NONE;
}

EYVAVStatisticType YoumeVideoUtils::ConvertAVStatisticType(YouMeAVStatisticType_t Type)
{
	switch (Type)
	{
		case YOUME_AVS_AUDIO_CODERATE:
			return EYVAVStatisticType::AVS_AUDIO_CODERATE;
		case YOUME_AVS_VIDEO_CODERATE:
			return EYVAVStatisticType::AVS_VIDEO_CODERATE;
		case YOUME_AVS_VIDEO_FRAMERATE:
			return EYVAVStatisticType::AVS_VIDEO_FRAMERATE;
		case YOUME_AVS_AUDIO_PACKET_UP_LOSS_RATE:
			return EYVAVStatisticType::AVS_AUDIO_PACKET_UP_LOSS_RATE;
		case YOUME_AVS_AUDIO_PACKET_DOWN_LOSS_RATE:
			return EYVAVStatisticType::AVS_AUDIO_PACKET_DOWN_LOSS_RATE;
		case YOUME_AVS_VIDEO_PACKET_UP_LOSS_RATE:
			return EYVAVStatisticType::AVS_VIDEO_PACKET_UP_LOSS_RATE;
		case YOUME_AVS_VIDEO_PACKET_DOWN_LOSS_RATE:
			return EYVAVStatisticType::AVS_VIDEO_PACKET_DOWN_LOSS_RATE;
		case YOUME_AVS_AUDIO_DELAY_MS:
			return EYVAVStatisticType::AVS_AUDIO_DELAY_MS;
		case YOUME_AVS_VIDEO_DELAY_MS:
			return EYVAVStatisticType::AVS_VIDEO_DELAY_MS;
		case YOUME_AVS_VIDEO_BLOCK:
			return EYVAVStatisticType::AVS_VIDEO_BLOCK;
		case YOUME_AVS_AUDIO_PACKET_UP_LOSS_HALF:
			return EYVAVStatisticType::AVS_AUDIO_PACKET_UP_LOSS_HALF;
		case YOUME_AVS_VIDEO_PACKET_UP_LOSS_HALF:
			return EYVAVStatisticType::AVS_VIDEO_PACKET_UP_LOSS_HALF;
		case YOUME_AVS_RECV_DATA_STAT:
			return EYVAVStatisticType::AVS_RECV_DATA_STAT;
		case YOUME_AVS_VIDEO_SHARE_CODERATE:
			return EYVAVStatisticType::AVS_VIDEO_SHARE_CODERATE;
		case YOUME_AVS_VIDEO_SHARE_FRAMERATE:
			return EYVAVStatisticType::AVS_VIDEO_SHARE_FRAMERATE;
		case YOUME_AVS_VIDEO_RESOLUTION:
			return EYVAVStatisticType::AVS_VIDEO_RESOLUTION;
		case YOUME_AVS_VIDEO_SHARE_RESOLUTION:
			return EYVAVStatisticType::AVS_VIDEO_SHARE_RESOLUTION;
		case YOUME_AVS_SEND_DATA_STAT:
			return EYVAVStatisticType::AVS_SEND_DATA_STAT;
	}
	return EYVAVStatisticType::AVS_AUDIO_CODERATE;
}

EYVAudioRouteType YoumeVideoUtils::ConvertAudioRouteType(YouMeAudioRouteType_t Type)
{
	switch (Type)
	{
	case YOUME_AUDIO_ROUTE_SPEAKER:
		return EYVAudioRouteType::AUDIO_ROUTE_SPEAKER;
	case YOUME_AUDIO_ROUTE_EARPIECE:
		return EYVAudioRouteType::AUDIO_ROUTE_EARPIECE;
	case YOUME_AUDIO_ROUTE_HEADSET:
		return EYVAudioRouteType::AUDIO_ROUTE_HEADSET;
	case YOUME_AUDIO_ROUTE_HEADSET_BLUETOOTH:
		return EYVAudioRouteType::AUDIO_ROUTE_HEADSET_BLUETOOTH;
	}
	return EYVAudioRouteType::AUDIO_ROUTE_SPEAKER;
}

EYVEvent YoumeVideoUtils::ConvertEvent(YouMeEvent_t Event)
{
	switch (Event)
	{
	case YOUME_EVENT_INIT_OK:
		return EYVEvent::INIT_OK;
	case YOUME_EVENT_INIT_FAILED:
		return EYVEvent::INIT_FAILED;
	case YOUME_EVENT_JOIN_OK:
		return EYVEvent::JOIN_OK;
	case YOUME_EVENT_JOIN_FAILED:
		return EYVEvent::JOIN_FAILED;
	case YOUME_EVENT_LEAVED_ONE:
		return EYVEvent::LEAVED_ONE;
	case YOUME_EVENT_LEAVED_ALL:
		return EYVEvent::LEAVED_ALL;
	case YOUME_EVENT_PAUSED:
		return EYVEvent::PAUSED;
	case YOUME_EVENT_RESUMED:
		return EYVEvent::RESUMED;
	case YOUME_EVENT_SPEAK_SUCCESS:
		return EYVEvent::SPEAK_SUCCESS;
	case YOUME_EVENT_SPEAK_FAILED:
		return EYVEvent::SPEAK_FAILED;
	case YOUME_EVENT_RECONNECTING:
		return EYVEvent::RECONNECTING;
	case YOUME_EVENT_RECONNECTED:
		return EYVEvent::RECONNECTED;
	case YOUME_EVENT_REC_PERMISSION_STATUS:
		return EYVEvent::REC_PERMISSION_STATUS;
	case YOUME_EVENT_BGM_STOPPED:
		return EYVEvent::BGM_STOPPED;
	case YOUME_EVENT_BGM_FAILED:
		return EYVEvent::BGM_FAILED;
	case YOUME_EVENT_OTHERS_MIC_ON:
		return EYVEvent::OTHERS_MIC_ON;
	case YOUME_EVENT_OTHERS_MIC_OFF:
		return EYVEvent::OTHERS_MIC_OFF;
	case YOUME_EVENT_OTHERS_SPEAKER_ON:
		return EYVEvent::OTHERS_SPEAKER_ON;
	case YOUME_EVENT_OTHERS_SPEAKER_OFF:
		return EYVEvent::OTHERS_SPEAKER_OFF;
	case YOUME_EVENT_OTHERS_VOICE_ON:
		return EYVEvent::OTHERS_VOICE_ON;
	case YOUME_EVENT_OTHERS_VOICE_OFF:
		return EYVEvent::OTHERS_VOICE_OFF;
	case YOUME_EVENT_MY_MIC_LEVEL:
		return EYVEvent::MY_MIC_LEVEL;
	case YOUME_EVENT_MIC_CTR_ON:
		return EYVEvent::MIC_CTR_ON;
	case YOUME_EVENT_MIC_CTR_OFF:
		return EYVEvent::MIC_CTR_OFF;
	case YOUME_EVENT_SPEAKER_CTR_ON:
		return EYVEvent::SPEAKER_CTR_ON;
	case YOUME_EVENT_SPEAKER_CTR_OFF:
		return EYVEvent::SPEAKER_CTR_OFF;
	case YOUME_EVENT_LISTEN_OTHER_ON:
		return EYVEvent::LISTEN_OTHER_ON;
	case YOUME_EVENT_LISTEN_OTHER_OFF:
		return EYVEvent::LISTEN_OTHER_OFF;
	case YOUME_EVENT_LOCAL_MIC_ON:
		return EYVEvent::LOCAL_MIC_ON;
	case YOUME_EVENT_LOCAL_MIC_OFF:
		return EYVEvent::LOCAL_MIC_OFF;
	case YOUME_EVENT_LOCAL_SPEAKER_ON:
		return EYVEvent::LOCAL_SPEAKER_ON;
	case YOUME_EVENT_LOCAL_SPEAKER_OFF:
		return EYVEvent::LOCAL_SPEAKER_OFF;
	case YOUME_EVENT_GRABMIC_START_OK:
		return EYVEvent::GRABMIC_START_OK;
	case YOUME_EVENT_GRABMIC_START_FAILED:
		return EYVEvent::GRABMIC_START_FAILED;
	case YOUME_EVENT_GRABMIC_STOP_OK:
		return EYVEvent::GRABMIC_STOP_OK;
	case YOUME_EVENT_GRABMIC_STOP_FAILED:
		return EYVEvent::GRABMIC_STOP_FAILED;
	case YOUME_EVENT_GRABMIC_REQUEST_OK:
		return EYVEvent::GRABMIC_REQUEST_OK;
	case YOUME_EVENT_GRABMIC_REQUEST_FAILED:
		return EYVEvent::GRABMIC_REQUEST_FAILED;
	case YOUME_EVENT_GRABMIC_REQUEST_WAIT:
		return EYVEvent::GRABMIC_REQUEST_WAIT;
	case YOUME_EVENT_GRABMIC_RELEASE_OK:
		return EYVEvent::GRABMIC_RELEASE_OK;
	case YOUME_EVENT_GRABMIC_RELEASE_FAILED:
		return EYVEvent::GRABMIC_RELEASE_FAILED;
	case YOUME_EVENT_GRABMIC_ENDMIC:
		return EYVEvent::GRABMIC_ENDMIC;
	case YOUME_EVENT_GRABMIC_NOTIFY_START:
		return EYVEvent::GRABMIC_NOTIFY_START;
	case YOUME_EVENT_GRABMIC_NOTIFY_STOP:
		return EYVEvent::GRABMIC_NOTIFY_STOP;
	case YOUME_EVENT_GRABMIC_NOTIFY_HASMIC:
		return EYVEvent::GRABMIC_NOTIFY_HASMIC;
	case YOUME_EVENT_GRABMIC_NOTIFY_NOMIC:
		return EYVEvent::GRABMIC_NOTIFY_NOMIC;
	case YOUME_EVENT_INVITEMIC_SETOPT_OK:
		return EYVEvent::INVITEMIC_SETOPT_OK;
	case YOUME_EVENT_INVITEMIC_SETOPT_FAILED:
		return EYVEvent::INVITEMIC_SETOPT_FAILED;
	case YOUME_EVENT_INVITEMIC_REQUEST_OK:
		return EYVEvent::INVITEMIC_REQUEST_OK;
	case YOUME_EVENT_INVITEMIC_REQUEST_FAILED:
		return EYVEvent::INVITEMIC_REQUEST_FAILED;
	case YOUME_EVENT_INVITEMIC_RESPONSE_OK:
		return EYVEvent::INVITEMIC_RESPONSE_OK;
	case YOUME_EVENT_INVITEMIC_RESPONSE_FAILED:
		return EYVEvent::INVITEMIC_RESPONSE_FAILED;
	case YOUME_EVENT_INVITEMIC_STOP_OK:
		return EYVEvent::INVITEMIC_STOP_OK;
	case YOUME_EVENT_INVITEMIC_STOP_FAILED:
		return EYVEvent::INVITEMIC_STOP_FAILED;
	case YOUME_EVENT_INVITEMIC_CAN_TALK:
		return EYVEvent::INVITEMIC_CAN_TALK;
	case YOUME_EVENT_INVITEMIC_CANNOT_TALK:
		return EYVEvent::INVITEMIC_CANNOT_TALK;
	case YOUME_EVENT_INVITEMIC_NOTIFY_CALL:
		return EYVEvent::INVITEMIC_NOTIFY_CALL;
	case YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER:
		return EYVEvent::INVITEMIC_NOTIFY_ANSWER;
	case YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL:
		return EYVEvent::INVITEMIC_NOTIFY_CANCEL;
	case YOUME_EVENT_SEND_MESSAGE_RESULT:
		return EYVEvent::SEND_MESSAGE_RESULT;
	case YOUME_EVENT_MESSAGE_NOTIFY:
		return EYVEvent::MESSAGE_NOTIFY;
	case YOUME_EVENT_KICK_RESULT:
		return EYVEvent::KICK_RESULT;
	case YOUME_EVENT_KICK_NOTIFY:
		return EYVEvent::KICK_NOTIFY;
	case YOUME_EVENT_FAREND_VOICE_LEVEL:
		return EYVEvent::FAREND_VOICE_LEVEL;
	case YOUME_EVENT_OTHERS_BE_KICKED:
		return EYVEvent::OTHERS_BE_KICKED;
	case YOUME_EVENT_SPEAK_RECORD_ON:
		return EYVEvent::SPEAK_RECORD_ON;
	case YOUME_EVENT_SPEAK_RECORD_OFF:
		return EYVEvent::SPEAK_RECORD_OFF;
	case YOUME_EVENT_SPEAK_RECORD_RESET:
		return EYVEvent::SPEAK_RECORD_RESET;
	case YOUME_EVENT_EFFECT_PLAY_COMPLETE:
		return EYVEvent::EFFECT_PLAY_COMPLETE;
	case YOUME_EVENT_AUDIO_START_FAIL:
		return EYVEvent::AUDIO_START_FAIL;
	case YOUME_EVENT_AUDIO_INPUT_DEVICE_CONNECT:
		return EYVEvent::AUDIO_INPUT_DEVICE_CONNECT;
	case YOUME_EVENT_AUDIO_INPUT_DEVICE_DISCONNECT:
		return EYVEvent::AUDIO_INPUT_DEVICE_DISCONNECT;
	case YOUME_EVENT_SWITCH_OUTPUT:
		return EYVEvent::SWITCH_OUTPUT;
	case YOUME_EVENT_BGM_OR_SPEAR_RECORD:
		return EYVEvent::BGM_OR_SPEAR_RECORD;
	case YOUME_EVENT_AUDIO_ROUTE_CHANGE:
		return EYVEvent::AUDIO_ROUTE_CHANGE;
	case YOUME_EVENT_OTHERS_VIDEO_ON:
		return EYVEvent::OTHERS_VIDEO_ON;
	case YOUME_EVENT_MASK_VIDEO_BY_OTHER_USER:
		return EYVEvent::MASK_VIDEO_BY_OTHER_USER;
	case YOUME_EVENT_RESUME_VIDEO_BY_OTHER_USER:
		return EYVEvent::RESUME_VIDEO_BY_OTHER_USER;
	case YOUME_EVENT_MASK_VIDEO_FOR_USER:
		return EYVEvent::MASK_VIDEO_FOR_USER;
	case YOUME_EVENT_RESUME_VIDEO_FOR_USER:
		return EYVEvent::RESUME_VIDEO_FOR_USER;
	case YOUME_EVENT_OTHERS_VIDEO_SHUT_DOWN:
		return EYVEvent::OTHERS_VIDEO_SHUT_DOWN;
	case YOUME_EVENT_OTHERS_VIDEO_INPUT_START:
		return EYVEvent::OTHERS_VIDEO_INPUT_START;
	case YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP:
		return EYVEvent::OTHERS_VIDEO_INPUT_STOP;
	case YOUME_EVENT_MEDIA_DATA_ROAD_PASS:
		return EYVEvent::MEDIA_DATA_ROAD_PASS;
	case YOUME_EVENT_MEDIA_DATA_ROAD_BLOCK:
		return EYVEvent::MEDIA_DATA_ROAD_BLOCK;
	case YOUME_EVENT_QUERY_USERS_VIDEO_INFO:
		return EYVEvent::QUERY_USERS_VIDEO_INFO;
	case YOUME_EVENT_SET_USERS_VIDEO_INFO:
		return EYVEvent::SET_USERS_VIDEO_INFO;
	case YOUME_EVENT_LOCAL_VIDEO_INPUT_START:
		return EYVEvent::LOCAL_VIDEO_INPUT_START;
	case YOUME_EVENT_LOCAL_VIDEO_INPUT_STOP:
		return EYVEvent::LOCAL_VIDEO_INPUT_STOP;
	case YOUME_EVENT_START_PUSH:
		return EYVEvent::START_PUSH;
	case YOUME_EVENT_SET_PUSH_MIX:
		return EYVEvent::SET_PUSH_MIX;
	case YOUME_EVENT_ADD_PUSH_MIX_USER:
		return EYVEvent::ADD_PUSH_MIX_USER;
	case YOUME_EVENT_OTHER_SET_PUSH_MIX:
		return EYVEvent::OTHER_SET_PUSH_MIX;
	case YOUME_EVENT_LOCAL_SHARE_INPUT_START:
		return EYVEvent::LOCAL_SHARE_INPUT_START;
	case YOUME_EVENT_LOCAL_SHARE_INPUT_STOP:
		return EYVEvent::LOCAL_SHARE_INPUT_STOP;
	case YOUME_EVENT_OTHERS_SHARE_INPUT_START:
		return EYVEvent::OTHERS_SHARE_INPUT_START;
	case YOUME_EVENT_OTHERS_SHARE_INPUT_STOP:
		return EYVEvent::OTHERS_SHARE_INPUT_STOP;
	case YOUME_EVENT_SET_USERS_VIDEO_INFO_NOTIFY:
		return EYVEvent::SET_USERS_VIDEO_INFO_NOTIFY;
	case YOUME_EVENT_OTHER_PLAY_BACKGRAOUND_MUSIC:
		return EYVEvent::OTHER_PLAY_BACKGRAOUND_MUSIC;
	case YOUME_EVENT_OTHER_STOP_BACKGRAOUND_MUSIC:
		return EYVEvent::OTHER_STOP_BACKGRAOUND_MUSIC;
	case YOUME_EVENT_OTHERS_DATA_ERROR:
		return EYVEvent::OTHERS_DATA_ERROR;
	case YOUME_EVENT_OTHERS_NETWORK_BAD:
		return EYVEvent::OTHERS_NETWORK_BAD;
	case YOUME_EVENT_OTHERS_BLACK_FULL:
		return EYVEvent::OTHERS_BLACK_FULL;
	case YOUME_EVENT_OTHERS_GREEN_FULL:
		return EYVEvent::OTHERS_GREEN_FULL;
	case YOUME_EVENT_OTHERS_BLACK_BORDER:
		return EYVEvent::OTHERS_BLACK_BORDER;
	case YOUME_EVENT_OTHERS_GREEN_BORDER:
		return EYVEvent::OTHERS_GREEN_BORDER;
	case YOUME_EVENT_OTHERS_BLURRED_SCREEN:
		return EYVEvent::OTHERS_BLURRED_SCREEN;
	case YOUME_EVENT_OTHERS_ENCODER_ERROR:
		return EYVEvent::OTHERS_ENCODER_ERROR;
	case YOUME_EVENT_OTHERS_DECODER_ERROR:
		return EYVEvent::OTHERS_DECODER_ERROR;
	case YOUME_EVENT_CAMERA_DEVICE_CONNECT:
		return EYVEvent::CAMERA_DEVICE_CONNECT;
	case YOUME_EVENT_CAMERA_DEVICE_DISCONNECT:
		return EYVEvent::CAMERA_DEVICE_DISCONNECT;
	case YOUME_EVENT_AUDIO_HOWLING_DETECTION:
		return EYVEvent::AUDIO_HOWLING_DETECTION;
	case YOUME_EVENT_VIDEO_ENCODE_PARAM_REPORT:
		return EYVEvent::VIDEO_ENCODE_PARAM_REPORT;
	case YOUME_EVENT_VIDEO_DECODE_PARAM_REPORT:
		return EYVEvent::VIDEO_DECODE_PARAM_REPORT;
	case YOUME_EVENT_RTP_ROUTE_P2P:
		return EYVEvent::RTP_ROUTE_P2P;
	case YOUME_EVENT_RTP_ROUTE_SEREVER:
		return EYVEvent::RTP_ROUTE_SEREVER;
	case YOUME_EVENT_RTP_ROUTE_CHANGE_TO_SERVER:
		return EYVEvent::RTP_ROUTE_CHANGE_TO_SERVER;
	case YOUME_EVENT_RTP_ROUTE_SERVER_WITH_P2P_PROBE:
		return EYVEvent::RTP_ROUTE_SERVER_WITH_P2P_PROBE;
	case YOUME_EVENT_RECOGNIZE_MODULE_INIT_START:
		return EYVEvent::RECOGNIZE_MODULE_INIT_START;
	case YOUME_EVENT_RECOGNIZE_MODULE_INIT_END:
		return EYVEvent::RECOGNIZE_MODULE_INIT_END;
	case YOUME_EVENT_RECOGNIZE_MODULE_UNINIT:
		return EYVEvent::RECOGNIZE_MODULE_UNINIT;
	case YOUME_EVENT_RECOGNIZE_MODULE_ERR:
		return EYVEvent::RECOGNIZE_MODULE_ERR;
	case YOUME_EVENT_LOCAL_SHARE_WINDOW_CLOSED:
		return EYVEvent::LOCAL_SHARE_WINDOW_CLOSED;
	case YOUME_EVENT_LOCAL_SHARE_WINDOW_INVSIABLE:
		return EYVEvent::LOCAL_SHARE_WINDOW_INVSIABLE;
	case YOUME_EVENT_LOCAL_SHARE_WINDOW_ISICONIC:
		return EYVEvent::LOCAL_SHARE_WINDOW_ISICONIC;
	case YOUME_EVENT_LOCAL_SHARE_WINDOW_NORMAL:
		return EYVEvent::LOCAL_SHARE_WINDOW_NORMAL;
	case YOUME_EVENT_LOCAL_SHARE_WINDOW_MOVE:
		return EYVEvent::LOCAL_SHARE_WINDOW_MOVE;
	case YOUME_EVENT_EOF:
		return EYVEvent::LOCAL_EOF;
	}
	return EYVEvent::LOCAL_EOF;
}

EYVKickReason YoumeVideoUtils::ConvertKickReason(YouMeKickReason_t Reason)
{
	switch (Reason)
	{
	case YOUME_KICK_ADMIN:
		return EYVKickReason::KICK_ADMIN;
	case YOUME_KICK_RELOGIN:
		return EYVKickReason::KICK_RELOGIN;
	}
	return EYVKickReason::KICK_ADMIN;
}

EYVBroadcast YoumeVideoUtils::ConvertBroadcast(YouMeBroadcast_t Broadcast)
{
	switch (Broadcast)
	{
	case YOUME_BROADCAST_NONE:
		return EYVBroadcast::BROADCAST_NONE;
	case YOUME_BROADCAST_GRABMIC_BROADCAST_GETMIC:
		return EYVBroadcast::BROADCAST_GRABMIC_BROADCAST_GETMIC;
	case YOUME_BROADCAST_GRABMIC_BROADCAST_FREEMIC:
		return EYVBroadcast::BROADCAST_GRABMIC_BROADCAST_FREEMIC;
	case YOUME_BROADCAST_INVITEMIC_BROADCAST_CONNECT:
		return EYVBroadcast::BROADCAST_INVITEMIC_BROADCAST_CONNECT;
	case YOUME_BROADCAST_INVITEMIC_BROADCAST_DISCONNECT:
		return EYVBroadcast::BROADCAST_INVITEMIC_BROADCAST_DISCONNECT;
	}
	return EYVBroadcast::BROADCAST_NONE;
}

EYVErrorCode YoumeVideoUtils::ConvertErrorCode(YouMeErrorCode_t ErrorCode)
{
	switch (ErrorCode)
	{
	case YOUME_SUCCESS:
		return EYVErrorCode::SUCCESS;
	case YOUME_ERROR_API_NOT_SUPPORTED:
		return EYVErrorCode::ERROR_API_NOT_SUPPORTED;
	case YOUME_ERROR_INVALID_PARAM:
		return EYVErrorCode::ERROR_INVALID_PARAM;
	case YOUME_ERROR_ALREADY_INIT:
		return EYVErrorCode::ERROR_ALREADY_INIT;
	case YOUME_ERROR_NOT_INIT:
		return EYVErrorCode::ERROR_NOT_INIT;
	case YOUME_ERROR_CHANNEL_EXIST:
		return EYVErrorCode::ERROR_CHANNEL_EXIST;
	case YOUME_ERROR_CHANNEL_NOT_EXIST:
		return EYVErrorCode::ERROR_CHANNEL_NOT_EXIST;
	case YOUME_ERROR_WRONG_STATE:
		return EYVErrorCode::ERROR_WRONG_STATE;
	case YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK:
		return EYVErrorCode::ERROR_NOT_ALLOWED_MOBILE_NETWROK;
	case YOUME_ERROR_WRONG_CHANNEL_MODE:
		return EYVErrorCode::ERROR_WRONG_CHANNEL_MODE;
	case YOUME_ERROR_TOO_MANY_CHANNELS:
		return EYVErrorCode::ERROR_TOO_MANY_CHANNELS;
	case YOUME_ERROR_TOKEN_ERROR:
		return EYVErrorCode::ERROR_TOKEN_ERROR;
	case YOUME_ERROR_NOT_IN_CHANNEL:
		return EYVErrorCode::ERROR_NOT_IN_CHANNEL;
	case YOUME_ERROR_BE_KICK:
		return EYVErrorCode::ERROR_BE_KICK;
	case YOUME_ERROR_DEVICE_NOT_VALID:
		return EYVErrorCode::ERROR_DEVICE_NOT_VALID;
	case YOUME_ERROR_API_NOT_ALLOWED:
		return EYVErrorCode::ERROR_API_NOT_ALLOWED;
	case YOUME_ERROR_NO_LANG_CODE:
		return EYVErrorCode::ERROR_NO_LANG_CODE;
	case YOUME_ERROR_MEMORY_OUT:
		return EYVErrorCode::ERROR_MEMORY_OUT;
	case YOUME_ERROR_START_FAILED:
		return EYVErrorCode::ERROR_START_FAILED;
	case YOUME_ERROR_STOP_FAILED:
		return EYVErrorCode::ERROR_STOP_FAILED;
	case YOUME_ERROR_ILLEGAL_SDK:
		return EYVErrorCode::ERROR_ILLEGAL_SDK;
	case YOUME_ERROR_SERVER_INVALID:
		return EYVErrorCode::ERROR_SERVER_INVALID;
	case YOUME_ERROR_NETWORK_ERROR:
		return EYVErrorCode::ERROR_NETWORK_ERROR;
	case YOUME_ERROR_SERVER_INTER_ERROR:
		return EYVErrorCode::ERROR_SERVER_INTER_ERROR;
	case YOUME_ERROR_QUERY_RESTAPI_FAIL:
		return EYVErrorCode::ERROR_QUERY_RESTAPI_FAIL;
	case YOUME_ERROR_USER_ABORT:
		return EYVErrorCode::ERROR_USER_ABORT;
	case YOUME_ERROR_SEND_MESSAGE_FAIL:
		return EYVErrorCode::ERROR_SEND_MESSAGE_FAIL;
	case YOUME_ERROR_SET_PUSH_PARAM_FAIL:
		return EYVErrorCode::ERROR_SET_PUSH_PARAM_FAIL;
	case YOUME_ERROR_INIT_SHARE_FAIL:
		return EYVErrorCode::ERROR_INIT_SHARE_FAIL;
	case YOUME_ERROR_START_SHARE_FAIL:
		return EYVErrorCode::ERROR_START_SHARE_FAIL;
	case YOUME_ERROR_SHARE_NO_PERMISSION:
		return EYVErrorCode::ERROR_SHARE_NO_PERMISSION;
	case YOUME_ERROR_REC_INIT_FAILED:
		return EYVErrorCode::ERROR_REC_INIT_FAILED;
	case YOUME_ERROR_REC_NO_PERMISSION:
		return EYVErrorCode::ERROR_REC_NO_PERMISSION;
	case YOUME_ERROR_REC_NO_DATA:
		return EYVErrorCode::ERROR_REC_NO_DATA;
	case YOUME_ERROR_REC_OTHERS:
		return EYVErrorCode::ERROR_REC_OTHERS;
	case YOUME_ERROR_REC_PERMISSION_UNDEFINED:
		return EYVErrorCode::ERROR_REC_PERMISSION_UNDEFINED;
	case YOUME_ERROR_GRABMIC_FULL:
		return EYVErrorCode::ERROR_GRABMIC_FULL;
	case YOUME_ERROR_GRABMIC_HASEND:
		return EYVErrorCode::ERROR_GRABMIC_HASEND;
	case YOUME_ERROR_INVITEMIC_NOUSER:
		return EYVErrorCode::ERROR_INVITEMIC_NOUSER;
	case YOUME_ERROR_INVITEMIC_OFFLINE:
		return EYVErrorCode::ERROR_INVITEMIC_OFFLINE;
	case YOUME_ERROR_INVITEMIC_REJECT:
		return EYVErrorCode::ERROR_INVITEMIC_REJECT;
	case YOUME_ERROR_INVITEMIC_TIMEOUT:
		return EYVErrorCode::ERROR_INVITEMIC_TIMEOUT;
	case YOUME_ERROR_CAMERA_OPEN_FAILED:
		return EYVErrorCode::ERROR_CAMERA_OPEN_FAILED;
	case YOUME_ERROR_CAMERA_EXCEPTION:
		return EYVErrorCode::ERROR_CAMERA_EXCEPTION;
	case YOUME_ERROR_NOT_PROCESS:
		return EYVErrorCode::ERROR_NOT_PROCESS;
	case YOUME_ERROR_UNKNOWN:
		return EYVErrorCode::ERROR_UNKNOWN;
	}
	return EYVErrorCode::ERROR_UNKNOWN;
}

EYVServerMode YoumeVideoUtils::ConvertServerMode(SERVER_MODE_t Mode)
{
	switch (Mode)
	{
	case SERVER_MODE_FORMAL:
		return EYVServerMode::MODE_FORMAL;
	case SERVER_MODE_TEST:
		return EYVServerMode::MODE_TEST;
	case SERVER_MODE_DEV:
		return EYVServerMode::MODE_DEV;
	case SERVER_MODE_DEMO:
		return EYVServerMode::MODE_DEMO;
	case SERVER_MODE_FIXED_IP_VALIDATE:
		return EYVServerMode::MODE_FIXED_IP_VALIDATE;
	case SERVER_MODE_FIXED_IP_REDIRECT:
		return EYVServerMode::MODE_FIXED_IP_REDIRECT;
	case SERVER_MODE_FIXED_IP_MCU:
		return EYVServerMode::MODE_FIXED_IP_MCU;
	case SERVER_MODE_FIXED_IP_PRIVATE_SERVICE:
		return EYVServerMode::MODE_FIXED_IP_PRIVATE_SERVICE;
	}
	return EYVServerMode::MODE_FORMAL;
}

EYVRtcServerRegion YoumeVideoUtils::ConvertRtcServerRegion(YOUME_RTC_SERVER_REGION_t Region)
{
	switch (Region)
	{
	case RTC_CN_SERVER:
		return EYVRtcServerRegion::RTC_CN_SERVER;
	case RTC_HK_SERVER:
		return EYVRtcServerRegion::RTC_HK_SERVER;
	case RTC_US_SERVER:
		return EYVRtcServerRegion::RTC_US_SERVER;
	case RTC_SG_SERVER:
		return EYVRtcServerRegion::RTC_SG_SERVER;
	case RTC_KR_SERVER:
		return EYVRtcServerRegion::RTC_KR_SERVER;
	case RTC_AU_SERVER:
		return EYVRtcServerRegion::RTC_AU_SERVER;
	case RTC_DE_SERVER:
		return EYVRtcServerRegion::RTC_DE_SERVER;
	case RTC_BR_SERVER:
		return EYVRtcServerRegion::RTC_BR_SERVER;
	case RTC_IN_SERVER:
		return EYVRtcServerRegion::RTC_IN_SERVER;
	case RTC_JP_SERVER:
		return EYVRtcServerRegion::RTC_JP_SERVER;
	case RTC_IE_SERVER:
		return EYVRtcServerRegion::RTC_IE_SERVER;
	case RTC_USW_SERVER:
		return EYVRtcServerRegion::RTC_USW_SERVER;
	case RTC_USM_SERVER:
		return EYVRtcServerRegion::RTC_USM_SERVER;
	case RTC_CA_SERVER:
		return EYVRtcServerRegion::RTC_CA_SERVER;
	case RTC_LON_SERVER:
		return EYVRtcServerRegion::RTC_LON_SERVER;
	case RTC_FRA_SERVER:
		return EYVRtcServerRegion::RTC_FRA_SERVER;
	case RTC_DXB_SERVER:
		return EYVRtcServerRegion::RTC_DXB_SERVER;
	case RTC_NAF_SERVER:
		return EYVRtcServerRegion::RTC_NAF_SERVER;
	case RTC_CAF_SERVER:
		return EYVRtcServerRegion::RTC_CAF_SERVER;
	case RTC_SAF_SERVER:
		return EYVRtcServerRegion::RTC_SAF_SERVER;
	case RTC_EAF_SERVER:
		return EYVRtcServerRegion::RTC_EAF_SERVER;
	case RTC_WAF_SERVER:
		return EYVRtcServerRegion::RTC_WAF_SERVER;
	case RTC_RUS_SERVER:
		return EYVRtcServerRegion::RTC_RUS_SERVER;
	case RTC_NCN_SERVER:
		return EYVRtcServerRegion::RTC_NCN_SERVER;
	case RTC_NECN_SERVER:
		return EYVRtcServerRegion::RTC_NECN_SERVER;
	case RTC_ECN_SERVER:
		return EYVRtcServerRegion::RTC_ECN_SERVER;
	case RTC_CCN_SERVER:
		return EYVRtcServerRegion::RTC_CCN_SERVER;
	case RTC_SCN_SERVER:
		return EYVRtcServerRegion::RTC_SCN_SERVER;
	case RTC_WSCN_SERVER:
		return EYVRtcServerRegion::RTC_WSCN_SERVER;
	case RTC_EXT_SERVER:
		return EYVRtcServerRegion::RTC_EXT_SERVER;
	case RTC_DEFAULT_SERVER:
		return EYVRtcServerRegion::RTC_DEFAULT_SERVER;
	}
	return EYVRtcServerRegion::RTC_DEFAULT_SERVER;
}

YOUME_RTC_SERVER_REGION YoumeVideoUtils::ReverseRtcServerRegion(EYVRtcServerRegion Region)
{
	switch (Region)
	{
	case EYVRtcServerRegion::RTC_CN_SERVER:
		return RTC_CN_SERVER;
	case EYVRtcServerRegion::RTC_HK_SERVER:
		return RTC_HK_SERVER;
	case EYVRtcServerRegion::RTC_US_SERVER:
		return RTC_US_SERVER;
	case EYVRtcServerRegion::RTC_SG_SERVER:
		return RTC_SG_SERVER;
	case EYVRtcServerRegion::RTC_KR_SERVER:
		return RTC_KR_SERVER;
	case EYVRtcServerRegion::RTC_AU_SERVER:
		return RTC_AU_SERVER;
	case EYVRtcServerRegion::RTC_DE_SERVER:
		return RTC_DE_SERVER;
	case EYVRtcServerRegion::RTC_BR_SERVER:
		return RTC_BR_SERVER;
	case EYVRtcServerRegion::RTC_IN_SERVER:
		return RTC_IN_SERVER;
	case EYVRtcServerRegion::RTC_JP_SERVER:
		return RTC_JP_SERVER;
	case EYVRtcServerRegion::RTC_IE_SERVER:
		return RTC_IE_SERVER;
	case EYVRtcServerRegion::RTC_USW_SERVER:
		return RTC_USW_SERVER;
	case EYVRtcServerRegion::RTC_USM_SERVER:
		return RTC_USM_SERVER;
	case EYVRtcServerRegion::RTC_CA_SERVER:
		return RTC_CA_SERVER;
	case EYVRtcServerRegion::RTC_LON_SERVER:
		return RTC_LON_SERVER;
	case EYVRtcServerRegion::RTC_FRA_SERVER:
		return RTC_FRA_SERVER;
	case EYVRtcServerRegion::RTC_DXB_SERVER:
		return RTC_DXB_SERVER;
	case EYVRtcServerRegion::RTC_NAF_SERVER:
		return RTC_NAF_SERVER;
	case EYVRtcServerRegion::RTC_CAF_SERVER:
		return RTC_CAF_SERVER;
	case EYVRtcServerRegion::RTC_SAF_SERVER:
		return RTC_SAF_SERVER;
	case EYVRtcServerRegion::RTC_EAF_SERVER:
		return RTC_EAF_SERVER;
	case EYVRtcServerRegion::RTC_WAF_SERVER:
		return RTC_WAF_SERVER;
	case EYVRtcServerRegion::RTC_RUS_SERVER:
		return RTC_RUS_SERVER;
	case EYVRtcServerRegion::RTC_NCN_SERVER:
		return RTC_NCN_SERVER;
	case EYVRtcServerRegion::RTC_NECN_SERVER:
		return RTC_NECN_SERVER;
	case EYVRtcServerRegion::RTC_ECN_SERVER:
		return RTC_ECN_SERVER;
	case EYVRtcServerRegion::RTC_CCN_SERVER:
		return RTC_CCN_SERVER;
	case EYVRtcServerRegion::RTC_SCN_SERVER:
		return RTC_SCN_SERVER;
	case EYVRtcServerRegion::RTC_WSCN_SERVER:
		return RTC_WSCN_SERVER;
	case EYVRtcServerRegion::RTC_EXT_SERVER:
		return RTC_EXT_SERVER;
	case EYVRtcServerRegion::RTC_DEFAULT_SERVER:
		return RTC_DEFAULT_SERVER;
	}
	return RTC_CN_SERVER;
}

EYVLogLevel YoumeVideoUtils::ConvertLogLevel(YOUME_LOG_LEVEL_t Level)
{
	switch (Level)
	{
	case LOG_DISABLED:
		return EYVLogLevel::LOG_DISABLED;
	case LOG_FATAL:
		return EYVLogLevel::LOG_FATAL;
	case LOG_ERROR:
		return EYVLogLevel::LOG_ERROR;
	case LOG_WARNING:
		return EYVLogLevel::LOG_WARNING;
	case LOG_INFO:
		return EYVLogLevel::LOG_INFO;
	case LOG_DEBUG:
		return EYVLogLevel::LOG_DEBUG;
	case LOG_VERBOSE:
		return EYVLogLevel::LOG_VERBOSE;
	}
	return EYVLogLevel::LOG_DISABLED;
}

YOUME_LOG_LEVEL YoumeVideoUtils::ReverseLogLevel(EYVLogLevel Level)
{
	switch (Level)
	{
	case EYVLogLevel::LOG_DISABLED:
		return LOG_DISABLED;
	case EYVLogLevel::LOG_FATAL:
		return LOG_FATAL;
	case EYVLogLevel::LOG_ERROR:
		return LOG_ERROR;
	case EYVLogLevel::LOG_WARNING:
		return LOG_WARNING;
	case EYVLogLevel::LOG_INFO:
		return LOG_INFO;
	case EYVLogLevel::LOG_DEBUG:
		return LOG_DEBUG;
	case EYVLogLevel::LOG_VERBOSE:
		return LOG_VERBOSE;
	}
	return LOG_DISABLED;
}

EYVSampleRate YoumeVideoUtils::ConvertSampleRate(YOUME_SAMPLE_RATE_t Rate)
{
	switch (Rate)
	{
	case SAMPLE_RATE_8:
		return EYVSampleRate::SAMPLE_RATE_8;
	case SAMPLE_RATE_16:
		return EYVSampleRate::SAMPLE_RATE_16;
	case SAMPLE_RATE_24:
		return EYVSampleRate::SAMPLE_RATE_24;
	case SAMPLE_RATE_32:
		return EYVSampleRate::SAMPLE_RATE_32;
	case SAMPLE_RATE_44:
		return EYVSampleRate::SAMPLE_RATE_44;
	case SAMPLE_RATE_48:
		return EYVSampleRate::SAMPLE_RATE_48;
	}
	return EYVSampleRate::SAMPLE_RATE_8;
}

YOUME_SAMPLE_RATE YoumeVideoUtils::ReverseSampleRate(EYVSampleRate Rate)
{
	switch (Rate)
	{
	case EYVSampleRate::SAMPLE_RATE_8:
		return SAMPLE_RATE_8;
	case EYVSampleRate::SAMPLE_RATE_16:
		return SAMPLE_RATE_16;
	case EYVSampleRate::SAMPLE_RATE_24:
		return SAMPLE_RATE_24;
	case EYVSampleRate::SAMPLE_RATE_32:
		return SAMPLE_RATE_32;
	case EYVSampleRate::SAMPLE_RATE_44:
		return SAMPLE_RATE_44;
	case EYVSampleRate::SAMPLE_RATE_48:
		return SAMPLE_RATE_48;
	}
	return SAMPLE_RATE_8;
}

EYVVudioQuality YoumeVideoUtils::ConvertVudioQuality(YOUME_AUDIO_QUALITY_t VudioQuality)
{
	switch (VudioQuality)
	{
	case LOW_QUALITY:
		return EYVVudioQuality::LOW_QUALITY;
	case HIGH_QUALITY:
		return EYVVudioQuality::HIGH_QUALITY;
	}
	return EYVVudioQuality::LOW_QUALITY;
}

YOUME_AUDIO_QUALITY YoumeVideoUtils::ReverseVudioQuality(EYVVudioQuality VudioQuality)
{
	switch (VudioQuality)
	{
	case EYVVudioQuality::LOW_QUALITY:
		return LOW_QUALITY;
	case EYVVudioQuality::HIGH_QUALITY:
		return HIGH_QUALITY;
	}
	return LOW_QUALITY;
}

EYVVideoRenderMode YoumeVideoUtils::ConvertVideoRenderMode(YouMeVideoRenderMode_t Mode)
{
	switch (Mode)
	{
	case YOUME_VIDEO_RENDER_MODE_HIDDEN:
		return EYVVideoRenderMode::VIDEO_RENDER_MODE_HIDDEN;
	case YOUME_VIDEO_RENDER_MODE_FIT:
		return EYVVideoRenderMode::VIDEO_RENDER_MODE_FIT;
	case YOUME_VIDEO_RENDER_MODE_ADAPTIVE:
		return EYVVideoRenderMode::VIDEO_RENDER_MODE_ADAPTIVE;
	case YOUME_VIDEO_RENDER_MODE_STRETCH:
		return EYVVideoRenderMode::VIDEO_RENDER_MODE_STRETCH;
	}
	return EYVVideoRenderMode::VIDEO_RENDER_MODE_HIDDEN;
}

EYVVideoMirrorMode YoumeVideoUtils::ConvertVideoMirrorMode(YouMeVideoMirrorMode_t Mode)
{
	switch (Mode)
	{
	case YOUME_VIDEO_MIRROR_MODE_AUTO:
		return EYVVideoMirrorMode::VIDEO_MIRROR_MODE_AUTO;
	case YOUME_VIDEO_MIRROR_MODE_ENABLED:
		return EYVVideoMirrorMode::VIDEO_MIRROR_MODE_ENABLED;
	case YOUME_VIDEO_MIRROR_MODE_DISABLED:
		return EYVVideoMirrorMode::VIDEO_MIRROR_MODE_DISABLED;
	case YOUME_VIDEO_MIRROR_MODE_NEAR:
		return EYVVideoMirrorMode::VIDEO_MIRROR_MODE_NEAR;
	case YOUME_VIDEO_MIRROR_MODE_FAR:
		return EYVVideoMirrorMode::VIDEO_MIRROR_MODE_FAR;
	}
	return EYVVideoMirrorMode::VIDEO_MIRROR_MODE_AUTO;
}

YouMeVideoMirrorMode YoumeVideoUtils::ReverseVideoMirrorMode(EYVVideoMirrorMode Mode)
{
	switch (Mode)
	{
	case EYVVideoMirrorMode::VIDEO_MIRROR_MODE_AUTO:
		return YOUME_VIDEO_MIRROR_MODE_AUTO;
	case EYVVideoMirrorMode::VIDEO_MIRROR_MODE_ENABLED:
		return YOUME_VIDEO_MIRROR_MODE_ENABLED;
	case EYVVideoMirrorMode::VIDEO_MIRROR_MODE_DISABLED:
		return YOUME_VIDEO_MIRROR_MODE_DISABLED;
	case EYVVideoMirrorMode::VIDEO_MIRROR_MODE_NEAR:
		return YOUME_VIDEO_MIRROR_MODE_NEAR;
	case EYVVideoMirrorMode::VIDEO_MIRROR_MODE_FAR:
		return YOUME_VIDEO_MIRROR_MODE_FAR;
	}
	return YOUME_VIDEO_MIRROR_MODE_AUTO;
}

EYVVideoFmt YoumeVideoUtils::ConvertVideoFmt(YOUME_VIDEO_FMT_t Fmt)
{
	switch (Fmt)
	{
	case VIDEO_FMT_RGBA32:
		return EYVVideoFmt::VIDEO_FMT_RGBA32;
	case VIDEO_FMT_BGRA32:
		return EYVVideoFmt::VIDEO_FMT_BGRA32;
	case VIDEO_FMT_YUV420P:
		return EYVVideoFmt::VIDEO_FMT_YUV420P;
	case VIDEO_FMT_NV21:
		return EYVVideoFmt::VIDEO_FMT_NV21;
	case VIDEO_FMT_YV12:
		return EYVVideoFmt::VIDEO_FMT_YV12;
	case VIDEO_FMT_CVPIXELBUFFER:
		return EYVVideoFmt::VIDEO_FMT_CVPIXELBUFFER;
	case VIDEO_FMT_TEXTURE:
		return EYVVideoFmt::VIDEO_FMT_TEXTURE;
	case VIDEO_FMT_TEXTURE_OES:
		return EYVVideoFmt::VIDEO_FMT_TEXTURE_OES;
	case VIDEO_FMT_RGB24:
		return EYVVideoFmt::VIDEO_FMT_RGB24;
	case VIDEO_FMT_NV12:
		return EYVVideoFmt::VIDEO_FMT_NV12;
	case VIDEO_FMT_H264:
		return EYVVideoFmt::VIDEO_FMT_H264;
	case VIDEO_FMT_ABGR32:
		return EYVVideoFmt::VIDEO_FMT_ABGR32;
	case VIDEO_FMT_TEXTURE_YUV:
		return EYVVideoFmt::VIDEO_FMT_TEXTURE_YUV;
	case VIDEO_FMT_ENCRYPT:
		return EYVVideoFmt::VIDEO_FMT_ENCRYPT;
	}
	return EYVVideoFmt::VIDEO_FMT_RGBA32;
}

EYVVideoShareType YoumeVideoUtils::ConvertVideoShareType(YOUME_VIDEO_SHARE_TYPE_t Type)
{
	switch (Type)
	{
	case VIDEO_SHARE_TYPE_DEVICE:
		return EYVVideoShareType::VIDEO_SHARE_TYPE_DEVICE;
	case VIDEO_SHARE_TYPE_WINDOW:
		return EYVVideoShareType::VIDEO_SHARE_TYPE_WINDOW;
	case VIDEO_SHARE_TYPE_SCREEN:
		return EYVVideoShareType::VIDEO_SHARE_TYPE_SCREEN;
	case VIDEO_SHARE_TYPE_UNKNOW:
		return EYVVideoShareType::VIDEO_SHARE_TYPE_UNKNOW;
	}
	return EYVVideoShareType::VIDEO_SHARE_TYPE_UNKNOW;
}

EYVPcmCallBackFlag YoumeVideoUtils::ConvertPcmCallBackFlag(PcmCallBackFlag_t Flag)
{
	switch (Flag)
	{
	case PcmCallbackFlag_Remote:
		return EYVPcmCallBackFlag::PcmCallbackFlag_Remote;
	case PcmCallbackFlag_Record:
		return EYVPcmCallBackFlag::PcmCallbackFlag_Record;
	case PcmCallbackFlag_Mix:
		return EYVPcmCallBackFlag::PcmCallbackFlag_Mix;
	}
	return EYVPcmCallBackFlag::PcmCallbackFlag_Mix;
}

PcmCallBackFlag YoumeVideoUtils::ReversePcmCallBackFlag(EYVPcmCallBackFlag Flag)
{
	switch (Flag)
	{
	case EYVPcmCallBackFlag::PcmCallbackFlag_Remote:
		return PcmCallbackFlag_Remote;
	case EYVPcmCallBackFlag::PcmCallbackFlag_Record:
		return PcmCallbackFlag_Record;
	case EYVPcmCallBackFlag::PcmCallbackFlag_Mix:
		return PcmCallbackFlag_Mix;
	}
	return PcmCallbackFlag_Remote;
}

EYVLanguageCode YoumeVideoUtils::ConvertLanguageCode(YouMeLanguageCode_t Code)
{
	switch (Code)
	{
	case LANG_AUTO:
		return EYVLanguageCode::LANG_AUTO;
	case LANG_AF:
		return EYVLanguageCode::LANG_AF;
	case LANG_AM:
		return EYVLanguageCode::LANG_AM;
	case LANG_AR:
		return EYVLanguageCode::LANG_AR;
	case LANG_AR_AE:
		return EYVLanguageCode::LANG_AR_AE;
	case LANG_AR_BH:
		return EYVLanguageCode::LANG_AR_BH;
	case LANG_AR_DZ:
		return EYVLanguageCode::LANG_AR_DZ;
	case LANG_AR_KW:
		return EYVLanguageCode::LANG_AR_KW;
	case LANG_AR_LB:
		return EYVLanguageCode::LANG_AR_LB;
	case LANG_AR_OM:
		return EYVLanguageCode::LANG_AR_OM;
	case LANG_AR_SA:
		return EYVLanguageCode::LANG_AR_SA;
	case LANG_AR_SD:
		return EYVLanguageCode::LANG_AR_SD;
	case LANG_AR_TN:
		return EYVLanguageCode::LANG_AR_TN;
	case LANG_AZ:
		return EYVLanguageCode::LANG_AZ;
	case LANG_BE:
		return EYVLanguageCode::LANG_BE;
	case LANG_BG:
		return EYVLanguageCode::LANG_BG;
	case LANG_BN:
		return EYVLanguageCode::LANG_BN;
	case LANG_BS:
		return EYVLanguageCode::LANG_BS;
	case LANG_CA:
		return EYVLanguageCode::LANG_CA;
	case LANG_CA_ES:
		return EYVLanguageCode::LANG_CA_ES;
	case LANG_CO:
		return EYVLanguageCode::LANG_CO;
	case LANG_CS:
		return EYVLanguageCode::LANG_CS;
	case LANG_CY:
		return EYVLanguageCode::LANG_CY;
	case LANG_DA:
		return EYVLanguageCode::LANG_DA;
	case LANG_DE:
		return EYVLanguageCode::LANG_DE;
	case LANG_DE_CH:
		return EYVLanguageCode::LANG_DE_CH;
	case LANG_DE_LU:
		return EYVLanguageCode::LANG_DE_LU;
	case LANG_EL:
		return EYVLanguageCode::LANG_EL;
	case LANG_EN:
		return EYVLanguageCode::LANG_EN;
	case LANG_EN_CA:
		return EYVLanguageCode::LANG_EN_CA;
	case LANG_EN_IE:
		return EYVLanguageCode::LANG_EN_IE;
	case LANG_EN_ZA:
		return EYVLanguageCode::LANG_EN_ZA;
	case LANG_EO:
		return EYVLanguageCode::LANG_EO;
	case LANG_ES:
		return EYVLanguageCode::LANG_ES;
	case LANG_ES_BO:
		return EYVLanguageCode::LANG_ES_BO;
	case LANG_ES_AR:
		return EYVLanguageCode::LANG_ES_AR;
	case LANG_ES_CO:
		return EYVLanguageCode::LANG_ES_CO;
	case LANG_ES_CR:
		return EYVLanguageCode::LANG_ES_CR;
	case LANG_ES_ES:
		return EYVLanguageCode::LANG_ES_ES;
	case LANG_ET:
		return EYVLanguageCode::LANG_ET;
	case LANG_ES_PA:
		return EYVLanguageCode::LANG_ES_PA;
	case LANG_ES_SV:
		return EYVLanguageCode::LANG_ES_SV;
	case LANG_ES_VE:
		return EYVLanguageCode::LANG_ES_VE;
	case LANG_ET_EE:
		return EYVLanguageCode::LANG_ET_EE;
	case LANG_EU:
		return EYVLanguageCode::LANG_EU;
	case LANG_FA:
		return EYVLanguageCode::LANG_FA;
	case LANG_FI:
		return EYVLanguageCode::LANG_FI;
	case LANG_FR:
		return EYVLanguageCode::LANG_FR;
	case LANG_FR_BE:
		return EYVLanguageCode::LANG_FR_BE;
	case LANG_FR_CA:
		return EYVLanguageCode::LANG_FR_CA;
	case LANG_FR_CH:
		return EYVLanguageCode::LANG_FR_CH;
	case LANG_FR_LU:
		return EYVLanguageCode::LANG_FR_LU;
	case LANG_FY:
		return EYVLanguageCode::LANG_FY;
	case LANG_GA:
		return EYVLanguageCode::LANG_GA;
	case LANG_GD:
		return EYVLanguageCode::LANG_GD;
	case LANG_GL:
		return EYVLanguageCode::LANG_GL;
	case LANG_GU:
		return EYVLanguageCode::LANG_GU;
	case LANG_HA:
		return EYVLanguageCode::LANG_HA;
	case LANG_HI:
		return EYVLanguageCode::LANG_HI;
	case LANG_HR:
		return EYVLanguageCode::LANG_HR;
	case LANG_HT:
		return EYVLanguageCode::LANG_HT;
	case LANG_HU:
		return EYVLanguageCode::LANG_HU;
	case LANG_HY:
		return EYVLanguageCode::LANG_HY;
	case LANG_ID:
		return EYVLanguageCode::LANG_ID;
	case LANG_IG:
		return EYVLanguageCode::LANG_IG;
	case LANG_IS:
		return EYVLanguageCode::LANG_IS;
	case LANG_IT:
		return EYVLanguageCode::LANG_IT;
	case LANG_IT_CH:
		return EYVLanguageCode::LANG_IT_CH;
	case LANG_JA:
		return EYVLanguageCode::LANG_JA;
	case LANG_KA:
		return EYVLanguageCode::LANG_KA;
	case LANG_KK:
		return EYVLanguageCode::LANG_KK;
	case LANG_KN:
		return EYVLanguageCode::LANG_KN;
	case LANG_KM:
		return EYVLanguageCode::LANG_KM;
	case LANG_KO:
		return EYVLanguageCode::LANG_KO;
	case LANG_KO_KR:
		return EYVLanguageCode::LANG_KO_KR;
	case LANG_KU:
		return EYVLanguageCode::LANG_KU;
	case LANG_KY:
		return EYVLanguageCode::LANG_KY;
	case LANG_LA:
		return EYVLanguageCode::LANG_LA;
	case LANG_LB:
		return EYVLanguageCode::LANG_LB;
	case LANG_LO:
		return EYVLanguageCode::LANG_LO;
	case LANG_LT:
		return EYVLanguageCode::LANG_LT;
	case LANG_LV:
		return EYVLanguageCode::LANG_LV;
	case LANG_MG:
		return EYVLanguageCode::LANG_MG;
	case LANG_MI:
		return EYVLanguageCode::LANG_MI;
	case LANG_MK:
		return EYVLanguageCode::LANG_MK;
	case LANG_ML:
		return EYVLanguageCode::LANG_ML;
	case LANG_MN:
		return EYVLanguageCode::LANG_MN;
	case LANG_MR:
		return EYVLanguageCode::LANG_MR;
	case LANG_MS:
		return EYVLanguageCode::LANG_MS;
	case LANG_MT:
		return EYVLanguageCode::LANG_MT;
	case LANG_MY:
		return EYVLanguageCode::LANG_MY;
	case LANG_NL:
		return EYVLanguageCode::LANG_NL;
	case LANG_NL_BE:
		return EYVLanguageCode::LANG_NL_BE;
	case LANG_NE:
		return EYVLanguageCode::LANG_NE;
	case LANG_NO:
		return EYVLanguageCode::LANG_NO;
	case LANG_NY:
		return EYVLanguageCode::LANG_NY;
	case LANG_PL:
		return EYVLanguageCode::LANG_PL;
	case LANG_PS:
		return EYVLanguageCode::LANG_PS;
	case LANG_PT:
		return EYVLanguageCode::LANG_PT;
	case LANG_PT_BR:
		return EYVLanguageCode::LANG_PT_BR;
	case LANG_RO:
		return EYVLanguageCode::LANG_RO;
	case LANG_RU:
		return EYVLanguageCode::LANG_RU;
	case LANG_SD:
		return EYVLanguageCode::LANG_SD;
	case LANG_SI:
		return EYVLanguageCode::LANG_SI;
	case LANG_SK:
		return EYVLanguageCode::LANG_SK;
	case LANG_SL:
		return EYVLanguageCode::LANG_SL;
	case LANG_SM:
		return EYVLanguageCode::LANG_SM;
	case LANG_SN:
		return EYVLanguageCode::LANG_SN;
	case LANG_SO:
		return EYVLanguageCode::LANG_SO;
	case LANG_SQ:
		return EYVLanguageCode::LANG_SQ;
	case LANG_SR:
		return EYVLanguageCode::LANG_SR;
	case LANG_ST:
		return EYVLanguageCode::LANG_ST;
	case LANG_SU:
		return EYVLanguageCode::LANG_SU;
	case LANG_SV:
		return EYVLanguageCode::LANG_SV;
	case LANG_SV_SE:
		return EYVLanguageCode::LANG_SV_SE;
	case LANG_SW:
		return EYVLanguageCode::LANG_SW;
	case LANG_TA:
		return EYVLanguageCode::LANG_TA;
	case LANG_TE:
		return EYVLanguageCode::LANG_TE;
	case LANG_TG:
		return EYVLanguageCode::LANG_TG;
	case LANG_TH:
		return EYVLanguageCode::LANG_TH;
	case LANG_TL:
		return EYVLanguageCode::LANG_TL;
	case LANG_TR:
		return EYVLanguageCode::LANG_TR;
	case LANG_UK:
		return EYVLanguageCode::LANG_UK;
	case LANG_UR:
		return EYVLanguageCode::LANG_UR;
	case LANG_UZ:
		return EYVLanguageCode::LANG_UZ;
	case LANG_VI:
		return EYVLanguageCode::LANG_VI;
	case LANG_XH:
		return EYVLanguageCode::LANG_XH;
	case LANG_YID:
		return EYVLanguageCode::LANG_YID;
	case LANG_YO:
		return EYVLanguageCode::LANG_YO;
	case LANG_ZH:
		return EYVLanguageCode::LANG_ZH;
	case LANG_ZH_TW:
		return EYVLanguageCode::LANG_ZH_TW;
	case LANG_ZU:
		return EYVLanguageCode::LANG_ZU;
	}
	return EYVLanguageCode::LANG_AUTO;
}

YouMeLanguageCode YoumeVideoUtils::ReverseLanguageCode(EYVLanguageCode Code)
{
	switch (Code)
	{
	case EYVLanguageCode::LANG_AUTO:
		return LANG_AUTO;
	case EYVLanguageCode::LANG_AF:
		return LANG_AF;
	case EYVLanguageCode::LANG_AM:
		return LANG_AM;
	case EYVLanguageCode::LANG_AR:
		return LANG_AR;
	case EYVLanguageCode::LANG_AR_AE:
		return LANG_AR_AE;
	case EYVLanguageCode::LANG_AR_BH:
		return LANG_AR_BH;
	case EYVLanguageCode::LANG_AR_DZ:
		return LANG_AR_DZ;
	case EYVLanguageCode::LANG_AR_KW:
		return LANG_AR_KW;
	case EYVLanguageCode::LANG_AR_LB:
		return LANG_AR_LB;
	case EYVLanguageCode::LANG_AR_OM:
		return LANG_AR_OM;
	case EYVLanguageCode::LANG_AR_SA:
		return LANG_AR_SA;
	case EYVLanguageCode::LANG_AR_SD:
		return LANG_AR_SD;
	case EYVLanguageCode::LANG_AR_TN:
		return LANG_AR_TN;
	case EYVLanguageCode::LANG_AZ:
		return LANG_AZ;
	case EYVLanguageCode::LANG_BE:
		return LANG_BE;
	case EYVLanguageCode::LANG_BG:
		return LANG_BG;
	case EYVLanguageCode::LANG_BN:
		return LANG_BN;
	case EYVLanguageCode::LANG_BS:
		return LANG_BS;
	case EYVLanguageCode::LANG_CA:
		return LANG_CA;
	case EYVLanguageCode::LANG_CA_ES:
		return LANG_CA_ES;
	case EYVLanguageCode::LANG_CO:
		return LANG_CO;
	case EYVLanguageCode::LANG_CS:
		return LANG_CS;
	case EYVLanguageCode::LANG_CY:
		return LANG_CY;
	case EYVLanguageCode::LANG_DA:
		return LANG_DA;
	case EYVLanguageCode::LANG_DE:
		return LANG_DE;
	case EYVLanguageCode::LANG_DE_CH:
		return LANG_DE_CH;
	case EYVLanguageCode::LANG_DE_LU:
		return LANG_DE_LU;
	case EYVLanguageCode::LANG_EL:
		return LANG_EL;
	case EYVLanguageCode::LANG_EN:
		return LANG_EN;
	case EYVLanguageCode::LANG_EN_CA:
		return LANG_EN_CA;
	case EYVLanguageCode::LANG_EN_IE:
		return LANG_EN_IE;
	case EYVLanguageCode::LANG_EN_ZA:
		return LANG_EN_ZA;
	case EYVLanguageCode::LANG_EO:
		return LANG_EO;
	case EYVLanguageCode::LANG_ES:
		return LANG_ES;
	case EYVLanguageCode::LANG_ES_BO:
		return LANG_ES_BO;
	case EYVLanguageCode::LANG_ES_AR:
		return LANG_ES_AR;
	case EYVLanguageCode::LANG_ES_CO:
		return LANG_ES_CO;
	case EYVLanguageCode::LANG_ES_CR:
		return LANG_ES_CR;
	case EYVLanguageCode::LANG_ES_ES:
		return LANG_ES_ES;
	case EYVLanguageCode::LANG_ET:
		return LANG_ET;
	case EYVLanguageCode::LANG_ES_PA:
		return LANG_ES_PA;
	case EYVLanguageCode::LANG_ES_SV:
		return LANG_ES_SV;
	case EYVLanguageCode::LANG_ES_VE:
		return LANG_ES_VE;
	case EYVLanguageCode::LANG_ET_EE:
		return LANG_ET_EE;
	case EYVLanguageCode::LANG_EU:
		return LANG_EU;
	case EYVLanguageCode::LANG_FA:
		return LANG_FA;
	case EYVLanguageCode::LANG_FI:
		return LANG_FI;
	case EYVLanguageCode::LANG_FR:
		return LANG_FR;
	case EYVLanguageCode::LANG_FR_BE:
		return LANG_FR_BE;
	case EYVLanguageCode::LANG_FR_CA:
		return LANG_FR_CA;
	case EYVLanguageCode::LANG_FR_CH:
		return LANG_FR_CH;
	case EYVLanguageCode::LANG_FR_LU:
		return LANG_FR_LU;
	case EYVLanguageCode::LANG_FY:
		return LANG_FY;
	case EYVLanguageCode::LANG_GA:
		return LANG_GA;
	case EYVLanguageCode::LANG_GD:
		return LANG_GD;
	case EYVLanguageCode::LANG_GL:
		return LANG_GL;
	case EYVLanguageCode::LANG_GU:
		return LANG_GU;
	case EYVLanguageCode::LANG_HA:
		return LANG_HA;
	case EYVLanguageCode::LANG_HI:
		return LANG_HI;
	case EYVLanguageCode::LANG_HR:
		return LANG_HR;
	case EYVLanguageCode::LANG_HT:
		return LANG_HT;
	case EYVLanguageCode::LANG_HU:
		return LANG_HU;
	case EYVLanguageCode::LANG_HY:
		return LANG_HY;
	case EYVLanguageCode::LANG_ID:
		return LANG_ID;
	case EYVLanguageCode::LANG_IG:
		return LANG_IG;
	case EYVLanguageCode::LANG_IS:
		return LANG_IS;
	case EYVLanguageCode::LANG_IT:
		return LANG_IT;
	case EYVLanguageCode::LANG_IT_CH:
		return LANG_IT_CH;
	case EYVLanguageCode::LANG_JA:
		return LANG_JA;
	case EYVLanguageCode::LANG_KA:
		return LANG_KA;
	case EYVLanguageCode::LANG_KK:
		return LANG_KK;
	case EYVLanguageCode::LANG_KN:
		return LANG_KN;
	case EYVLanguageCode::LANG_KM:
		return LANG_KM;
	case EYVLanguageCode::LANG_KO:
		return LANG_KO;
	case EYVLanguageCode::LANG_KO_KR:
		return LANG_KO_KR;
	case EYVLanguageCode::LANG_KU:
		return LANG_KU;
	case EYVLanguageCode::LANG_KY:
		return LANG_KY;
	case EYVLanguageCode::LANG_LA:
		return LANG_LA;
	case EYVLanguageCode::LANG_LB:
		return LANG_LB;
	case EYVLanguageCode::LANG_LO:
		return LANG_LO;
	case EYVLanguageCode::LANG_LT:
		return LANG_LT;
	case EYVLanguageCode::LANG_LV:
		return LANG_LV;
	case EYVLanguageCode::LANG_MG:
		return LANG_MG;
	case EYVLanguageCode::LANG_MI:
		return LANG_MI;
	case EYVLanguageCode::LANG_MK:
		return LANG_MK;
	case EYVLanguageCode::LANG_ML:
		return LANG_ML;
	case EYVLanguageCode::LANG_MN:
		return LANG_MN;
	case EYVLanguageCode::LANG_MR:
		return LANG_MR;
	case EYVLanguageCode::LANG_MS:
		return LANG_MS;
	case EYVLanguageCode::LANG_MT:
		return LANG_MT;
	case EYVLanguageCode::LANG_MY:
		return LANG_MY;
	case EYVLanguageCode::LANG_NL:
		return LANG_NL;
	case EYVLanguageCode::LANG_NL_BE:
		return LANG_NL_BE;
	case EYVLanguageCode::LANG_NE:
		return LANG_NE;
	case EYVLanguageCode::LANG_NO:
		return LANG_NO;
	case EYVLanguageCode::LANG_NY:
		return LANG_NY;
	case EYVLanguageCode::LANG_PL:
		return LANG_PL;
	case EYVLanguageCode::LANG_PS:
		return LANG_PS;
	case EYVLanguageCode::LANG_PT:
		return LANG_PT;
	case EYVLanguageCode::LANG_PT_BR:
		return LANG_PT_BR;
	case EYVLanguageCode::LANG_RO:
		return LANG_RO;
	case EYVLanguageCode::LANG_RU:
		return LANG_RU;
	case EYVLanguageCode::LANG_SD:
		return LANG_SD;
	case EYVLanguageCode::LANG_SI:
		return LANG_SI;
	case EYVLanguageCode::LANG_SK:
		return LANG_SK;
	case EYVLanguageCode::LANG_SL:
		return LANG_SL;
	case EYVLanguageCode::LANG_SM:
		return LANG_SM;
	case EYVLanguageCode::LANG_SN:
		return LANG_SN;
	case EYVLanguageCode::LANG_SO:
		return LANG_SO;
	case EYVLanguageCode::LANG_SQ:
		return LANG_SQ;
	case EYVLanguageCode::LANG_SR:
		return LANG_SR;
	case EYVLanguageCode::LANG_ST:
		return LANG_ST;
	case EYVLanguageCode::LANG_SU:
		return LANG_SU;
	case EYVLanguageCode::LANG_SV:
		return LANG_SV;
	case EYVLanguageCode::LANG_SV_SE:
		return LANG_SV_SE;
	case EYVLanguageCode::LANG_SW:
		return LANG_SW;
	case EYVLanguageCode::LANG_TA:
		return LANG_TA;
	case EYVLanguageCode::LANG_TE:
		return LANG_TE;
	case EYVLanguageCode::LANG_TG:
		return LANG_TG;
	case EYVLanguageCode::LANG_TH:
		return LANG_TH;
	case EYVLanguageCode::LANG_TL:
		return LANG_TL;
	case EYVLanguageCode::LANG_TR:
		return LANG_TR;
	case EYVLanguageCode::LANG_UK:
		return LANG_UK;
	case EYVLanguageCode::LANG_UR:
		return LANG_UR;
	case EYVLanguageCode::LANG_UZ:
		return LANG_UZ;
	case EYVLanguageCode::LANG_VI:
		return LANG_VI;
	case EYVLanguageCode::LANG_XH:
		return LANG_XH;
	case EYVLanguageCode::LANG_YID:
		return LANG_YID;
	case EYVLanguageCode::LANG_YO:
		return LANG_YO;
	case EYVLanguageCode::LANG_ZH:
		return LANG_ZH;
	case EYVLanguageCode::LANG_ZH_TW:
		return LANG_ZH_TW;
	case EYVLanguageCode::LANG_ZU:
		return LANG_ZU;
	}
	return LANG_AUTO;
}

EYVTransRouteType YoumeVideoUtils::ConvertTransRouteType(YoumeRtpRouteType_t Type)
{
	switch (Type)
	{
	case YOUME_TRANS_ROUTE_SERVER:
		return EYVTransRouteType::TRANS_ROUTE_SERVER;
	case YOUME_TRANS_ROUTE_P2P:
		return EYVTransRouteType::TRANS_ROUTE_P2P;
	}
	return EYVTransRouteType::TRANS_ROUTE_P2P;
}

EYVVideoCodecType YoumeVideoUtils::ConvertVideoCodecType(YMVideoCodecType_t Type)
{
	switch (Type)
	{
	case YOUME_VIDEO_CODEC_H264:
		return EYVVideoCodecType::VIDEO_CODEC_H264;
	case YOUME_VIDEO_CODEC_H265:
		return EYVVideoCodecType::VIDEO_CODEC_H265;
	case YOUME_VIDEO_CODEC_VP8:
		return EYVVideoCodecType::VIDEO_CODEC_VP8;
	case YOUME_VIDEO_CODEC_VP9:
		return EYVVideoCodecType::VIDEO_CODEC_VP9;
	}
	return EYVVideoCodecType::VIDEO_CODEC_H264;
}

EYVVideoStreamType YoumeVideoUtils::ConvertVideoStreamType(YMVideoStreamType_t Type)
{
	switch (Type)
	{
	case YOUME_VIDEO_STREAM_MAIN:
		return EYVVideoStreamType::VIDEO_STREAM_MAIN;
	case YOUME_VIDEO_STREAM_SUB:
		return EYVVideoStreamType::VIDEO_STREAM_SUB;
	case YOUME_VIDEO_STREAM_SHARE:
		return EYVVideoStreamType::VIDEO_STREAM_SHARE;
	case YOUME_VIDEO_STREAM_MAIN_AND_SHARE:
		return EYVVideoStreamType::VIDEO_STREAM_MAIN_AND_SHARE;
	case YOUME_VIDEO_STREAM_SUB_AND_SHARE:
		return EYVVideoStreamType::VIDEO_STREAM_SUB_AND_SHARE;
	}
	return EYVVideoStreamType::VIDEO_STREAM_MAIN;
}

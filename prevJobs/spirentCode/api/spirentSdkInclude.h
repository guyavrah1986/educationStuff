#pragma once

#define IN
#define OUT
#define INOUT

enum SpStatus
{
	SP_M2M_STATUS_SUCCESS = 0,
	SP_M2M_STATUS_GENERAL_FAUILRE
};

enum EnProtocolType
{
	SP_M2M_PROTOCOL_TYPE_LWM2M = 0,
	SP_M2M_PROTOCOL_TYPE_MQTT
};

enum SpEnRsrcType
{
	SP_M2M_RSRC_TYPE_PARENT_RSRC = 0,
	SP_M2M_RSRC_TYPE_INT,
	SP_M2M_RSRC_TYPE_FLOAT,
	SP_M2M_RSRC_TYPE_STRING
};

enum ErrorCode
{
	SP_M2M_ERROR_CODE_SUCCESS = 0,
	SP_M2M_ERROR_CODE_GENERAL_FAUILRE
};

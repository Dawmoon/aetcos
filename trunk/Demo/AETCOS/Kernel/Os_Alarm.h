////////////////////////////////////////////////////////////////////////////////
//	����: Os_Alarm.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: Alarm�������������
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-13	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _OS_ALARM_H_
#define _OS_ALARM_H_

////////////////////////////////////////////////////////////////////////////////
//	Includes
#include "Os_Cfg.h"
#include "Os_Task.h"
#include "Os_Event.h"

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions

#define	DeclareAlarm(AlarmName)
#define	ALARM_CALLBACK(AlarmCallBackName)	void Os_Alarm_##AlarmCallBackName(void)
#define	_ALARM_CALLBACK(AlarmCallBackName)	Os_Alarm_##AlarmCallBackName

////////////////////////////////////////////////////////////////////////////////
//	Type Definitions

typedef	uint32			TickType;
typedef	TickType		*TickRefType;

typedef struct
{
	TickType	maxAllowedValue;
	TickType	ticksPerBase;
	TickType	minCycle;
} AlarmBaseType;

typedef	AlarmBaseType	*AlarmBaseRefType;

typedef	uint8_least		AlarmType;

//Alarm��Ϣ��
typedef	struct
{
	AlarmType		alarmID;
	uint8_least		actionType;
	TaskTypeFunc	func;
	TaskType		taskID;
	EventMaskType	eventID;
	TaskStateType	alarmState;
	TickType		alarmTime;
	TickType		cycleTime;
} AlarmInfoType;

enum
{
	ALARM_CALLBACK_ACTION,
	ALARM_ACTIVATE_TASK,
	ALARM_SET_TASK_EVENT
};

////////////////////////////////////////////////////////////////////////////////
//	API Declaration

StatusType	GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
StatusType	GetAlarm(AlarmType AlarmID, TickRefType Tick);
StatusType	SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle);
StatusType	SetAbsAlarm(AlarmType AlarmID, TickType	start, TickType cycle);
StatusType	CancelAlarm(AlarmType AlarmID);

////////////////////////////////////////////////////////////////////////////////
//	Reinclude Prevention Ends
#endif
////////////////////////////////////////////////////////////////////////////////
//	����: Alarms.c
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: Alarmʾ��
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-23	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#include "Alarms.h"
#include "tasks.h"

////////////////////////////////////////////////////////////////////////////////
//	Alarm related data
//Ϊ���Ч��ֻ��һ��������
const	AlarmBaseType	AlarmBases=
{
	0xFFFF, CONF_TICKS_MS, 1
};

AlarmInfoType	AlarmInfos[] =
{
	{
		0,  //alarmID
		ALARM_CALLBACK_ACTION,
		_ALARM_CALLBACK(TestAlarm1),
		0,
		0,
		RUNNING,
		1000,
		1000
	},
	{
		1,
		ALARM_ACTIVATE_TASK,
		0,
		task5,
		0,
		SUSPENDED,
		0,
		0
	},
	{
		2,
		ALARM_SET_TASK_EVENT,
		0,
		task6,
		TESTEVENT4,
		SUSPENDED,
		0,
		0
	}
};


////////////////////////////////////////////////////////////////////////////////
//	Alarm Callbacks
ALARM_CALLBACK(TestAlarm1)
{
	LED_RES(5);
	//OS_TASK_SW();
}
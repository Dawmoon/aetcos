////////////////////////////////////////////////////////////////////////////////
//	名称: Alarms.c
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: Alarm示例
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-23	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#include "Alarms.h"
#include "tasks.h"

////////////////////////////////////////////////////////////////////////////////
//	Alarm related data
//为提高效率只用一个计数器
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
////////////////////////////////////////////////////////////////////////////////
//	名称: Hook.c
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 操作系统钩子实现
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-13	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#include "Hook.h"
#include "Alarms.h"

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
extern void InitAlarmSystem(void);
extern  TCB_Type        *Os_TCBCurr;


////////////////////////////////////////////////////////////////////////////////
//	Module global variables

////////////////////////////////////////////////////////////////////////////////
//	Function implementation

////////////////////////////////////////////////////////////
//	Function name:	ErrorHook
//	Description:	Run when an error occurs
//		Parameter:	Error	-  Error code
//	Return value:	none
//	Function calls:	none
//
//	History:
//	Ver.	Person				Date		Comment
//	------	-------				--------	--------
//	0.1		Destroyer PGB Kan	2008-09-18	Creation
////////////////////////////////////////////////////////////
void	ErrorHook(StatusType Error)
{
	static StatusType Errorlog[2];
	switch(Error)
	{
		default:
			break;
	}
}

////////////////////////////////////////////////////////////
//	Function name:	PreTaskHook
//	Description:	Run before a task is scheduled
//		Parameter:	none
//	Return value:	none
//	Function calls:	none
//
//	History:
//	Ver.	Person				Date		Comment
//	------	-------				--------	--------
//	0.1		Destroyer PGB Kan	2008-09-18	Creation
////////////////////////////////////////////////////////////
void	PreTaskHook(void)
{
	LED_ON(Os_TCBCurr->taskID);
}

////////////////////////////////////////////////////////////
//	Function name:	PostTaskHook
//	Description:	Run after a task is terminated
//		Parameter:	none
//	Return value:	none
//	Function calls:	none
//
////////////////////////////////////////////////////////////
void	PostTaskHook(void)
{
	LED_OFF(Os_TCBCurr->taskID);
}

////////////////////////////////////////////////////////////
//	Function name:	StartupHook
//	Description:	Run when the system is starting
//		Parameter:	none
//	Return value:	none
//	Function calls:	none
//
////////////////////////////////////////////////////////////
void	StartupHook(void)
{
	LED_RES(5);
	//Initial the alarms
	InitAlarmSystem();
	SetRelAlarm(TestAlarm1, 10000, 100);
	SetAbsAlarm(TestAlarm2, 30000, 8);
	SetRelAlarm(TestAlarm3,	30000, 10);
}

////////////////////////////////////////////////////////////
//	Function name:	ShutdownHook
//	Description:	Run when the system is going down
//		Parameter:	Error	- Error code
//	Return value:	none
//	Function calls:	none
//
////////////////////////////////////////////////////////////
void	ShutdownHook(StatusType Error)
{
	switch(Error)
	{
		default:
			break;
	}
}
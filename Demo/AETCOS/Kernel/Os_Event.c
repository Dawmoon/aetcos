////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Event.c
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 事件实现
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-13	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#include "Os_Event.h"

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
extern	EventMaskType	Os_Task_Event[];
extern	TaskType		Os_Res_Owner[];
extern  boolean			InterruptState;

extern  TCB_Type        Os_TCB[];
extern  TCB_Type        *Os_TCBCurr;
extern  TCB_Type        *Os_TCBReady;

////////////////////////////////////////////////////////////
//	Function name:	SetEvent
//	Description:	Activate the specified task from waiting
//		Parameter:	TaskID	-  The task to active
//					Mask	-  Event mask to be set
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	SetEvent(TaskType TaskID, EventMaskType Mask)
{
	#ifdef	_OS_DEBUG_
		if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
		{
			//Invalid task ID
			return E_OS_ID;
		}
		
		//Not extended task
		//return E_OS_ACCESS;
		
		if(Os_TCB[TaskID].state == SUSPENDED)
		{
			//Task state error
			return E_OS_STATE;
		}
	#endif
	
	if(Os_Task_Event[TaskID] & Mask)
	{
		Os_TCB[TaskID].state = READY;
	}
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	ClearEvent
//	Description:	Clear the event which the task is waiting
//		Parameter:	Mask	-  Event mask to be clear
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	ClearEvent(EventMaskType Mask)
{
	#ifdef	_OS_DEBUG_
		//Not extended task
		//return E_OS_ACCESS;
		
		if(InterruptState == TRUE)
		{
			//Call in interrupt
			return E_OS_CALLEVEL;
		}
	#endif
	
	Os_Task_Event[Os_TCBCurr->taskID] = Os_Task_Event[Os_TCBCurr->taskID] & (~Mask);
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	GetEvent
//	Description:	Get the event(s) which the specified task is waiting
//		Parameter:	TaskID	-  Specific task
//					Event	-  Buffer to store the event mask
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	GetEvent(TaskType TaskID, EventMaskRefType Event)
{
	#ifdef	_OS_DEBUG_
		if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
		{
			//Invalid task ID
			return E_OS_ID;
		}
		
		//Not extended task
		//return E_OS_ACCESS;
		
		if(Os_TCB[TaskID].state == SUSPENDED)
		{
			//Task state error
			return E_OS_STATE;
		}
	#endif
	
	*Event = Os_Task_Event[TaskID];
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	WaitEvent
//	Description:	Turn the task into waiting state till event occurs
//		Parameter:	Mask	-  Event(s) to wait
//	Return value:	Whether the operation succeeded
//	Function calls:	Schedule
//
////////////////////////////////////////////////////////////
StatusType	WaitEvent(EventMaskType Mask)
{
	#ifdef	_OS_DEBUG_
		//Not extended task
		//return E_OS_ACCESS;
		
		static	uint8_least	tmpIndex;
		for(tmpIndex = 0; tmpIndex < OS_MAX_RESOURCE; tmpIndex++)
		{
			if(Os_Res_Owner[tmpIndex] == Os_TCBCurr->taskID)
			{
				//Resource not released
				return E_OS_RESOURCE;
			}
		}
		
		if(Os_TCBCurr->state == SUSPENDED)
		{
			//Call in interrupt
			return E_OS_CALLEVEL;
		}
	#endif
	
	Os_Task_Event[Os_TCBCurr->taskID] = Os_Task_Event[Os_TCBCurr->taskID] | Mask;
	Os_TCBCurr->state = WAITING;
	
	//Schedule();
	
	return E_OK;
}
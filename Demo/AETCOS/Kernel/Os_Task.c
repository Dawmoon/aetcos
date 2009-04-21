////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Task.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 任务相关API实现
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-8	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#include "Os_Task.h"

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
extern	TaskType		Os_Res_Owner[];
extern	boolean			InterruptState;
extern  TCB_Type        Os_TCB[];


TCB_Type        *Os_TCBCurr =&Os_TCB[1];    //当前正在运行的任务

TCB_Type        *Os_TCBReady=&Os_TCB[1];    //准备好即将运行的任务

////////////////////////////////////////////////////////////
// 名称: ActivateTask
// 版本: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// 功能: Make the specified task "ready"   
// 调用: 无
// 参数: TaskID  -  The name of specific task
// 返回: Whether the operation succeeded
// 说明: 运行该函数后该任务恢复到初始状态
//
////////////////////////////////////////////////////////////
StatusType	ActivateTask(TaskType TaskID)
{
	if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
	{
		//Invalid TaskID
		return E_OS_ID;
	}
	
	//注意任务处于等待状态不能激活
	if( (Os_TCB[TaskID].state==WAITING) || (Os_TCB[TaskID].state==READY) || (Os_TCB[TaskID].state==RUNNING) )
	{
		return E_OS_LIMIT;
	}
	
	Os_TCB[TaskID].state = READY;
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	TerminateTask
//	Description:	Make the current task "suspend"
//		Parameter:	none
//	Return value:	Whether the operation succeeded
//	Function calls:	Schedule
//
////////////////////////////////////////////////////////////
StatusType	TerminateTask(void)
{
	#ifdef	_OS1_DEBUG_
		static	uint8_least	tmpIndex;
		for(tmpIndex = 0; tmpIndex < Os_Res_Num; tmpIndex++)
		{
			if(Os_Res_Owner[tmpIndex] == Os_TCBCurr->taskID)
			{
				//Resource not released
				return E_OS_RESOURCE;
			}
		}
		
		if(InterruptState == TRUE)
		{
			//Call in interrupt
			return E_OS_CALLEVEL;
		}
	#endif
	
	Os_TCBCurr->state = SUSPENDED;
	Schedule();
}

////////////////////////////////////////////////////////////
//	Function name:	ChainTask
//	Description:	Make the specified task run immediately after the current task ends
//		Parameter:	TaskID  -  The name of specific task
//	Return value:	Whether the operation succeeded
//	Function calls:	Schedule
//
////////////////////////////////////////////////////////////
StatusType	ChainTask(TaskType TaskID)
{
	//首先停止当前任务,然后运行指定任务
	Os_TCBCurr->state = SUSPENDED;
    
	//Too many activation
	if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
	{
		Schedule();
		return E_OS_ID;
	}
	
	//防止任务死循环
	if( (Os_TCBCurr->taskID==TaskID) || (Os_TCB[TaskID].state==READY) )
	{
	    Schedule();
	    return E_OS_LIMIT;
	}
	
	Os_TCBCurr = &Os_TCB[TaskID];
	Os_TCBCurr->state = RUNNING;
}

////////////////////////////////////////////////////////////
//	Function name:	GetTaskID
//	Description:	Get the ID of current task
//		Parameter:	TaskID  -  The buffer to recieve the task's ID
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	GetTaskID(TaskRefType TaskID)
{
	*TaskID = Os_TCBCurr->taskID;
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	GetTaskState
//	Description:	Get the state of specified task
//		Parameter:	TaskID  -  The name of specific task
//					State	-  The buffer to recieve the task's state
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	GetTaskState(TaskType TaskID, TaskStateRefType State)
{
	if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
	{
		return E_OS_ID;
	}

	*State = Os_TCB[TaskID].state;
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	Schedule
//	Description:	Schedule a task queue to run
//		Parameter:	none
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	Schedule(void)
{
	//static	sint8_least	tmpMaxTask = 1;
	TCB_Type    *tmpTCB;
	
	#ifdef	_OS1_DEBUG_
		for(tmpIndex = 0; tmpIndex < OS_MAX_RESOURCE; tmpIndex++)
		{
			if(Os_Res_Owner[tmpIndex] == Os_TCBCurr->taskID)
			{
				//Resource not released
				return E_OS_RESOURCE;
			}
		}
		
		if(InterruptState == TRUE)
		{
			//Call in interrupt
			return E_OS_CALLEVEL;
		}
	#endif
	
	//没有合适的则运行优先级最低的任务
	Os_TCBReady = &Os_TCB[0];
	
	for(tmpTCB=&Os_TCB[OS_MAX_TASK]; tmpTCB->taskID>0; tmpTCB--)
	{
		if(tmpTCB->state == READY)
		{
			tmpTCB->state = RUNNING;
			//Os_TCBCurr = &Os_TCB[tmpIndex];
			Os_TCBReady = tmpTCB;
			break;
		}
	}
	
	//当前任务正在进行,触发软中断进行任务切换
	if(Os_TCBCurr->state == RUNNING)
	{
	    Os_TCBCurr->state   = READY;
	    Os_TCBCurr=Os_TCBReady;
	    Os_TCBReady->state  = RUNNING;
	    
	    SuspendAllInterrupts();
	    OS_TASK_SW();   
	    ResumeAllInterrupts();
	}
	
	return E_OK;
}


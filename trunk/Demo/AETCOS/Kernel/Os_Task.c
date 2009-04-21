////////////////////////////////////////////////////////////////////////////////
//	����: Os_Task.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: �������APIʵ��
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-8	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#include "Os_Task.h"

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
extern	TaskType		Os_Res_Owner[];
extern	boolean			InterruptState;
extern  TCB_Type        Os_TCB[];


TCB_Type        *Os_TCBCurr =&Os_TCB[1];    //��ǰ�������е�����

TCB_Type        *Os_TCBReady=&Os_TCB[1];    //׼���ü������е�����

////////////////////////////////////////////////////////////
// ����: ActivateTask
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: Make the specified task "ready"   
// ����: ��
// ����: TaskID  -  The name of specific task
// ����: Whether the operation succeeded
// ˵��: ���иú����������ָ�����ʼ״̬
//
////////////////////////////////////////////////////////////
StatusType	ActivateTask(TaskType TaskID)
{
	if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
	{
		//Invalid TaskID
		return E_OS_ID;
	}
	
	//ע�������ڵȴ�״̬���ܼ���
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
	//����ֹͣ��ǰ����,Ȼ������ָ������
	Os_TCBCurr->state = SUSPENDED;
    
	//Too many activation
	if((TaskID < 0) || (TaskID >= OS_MAX_TASK))
	{
		Schedule();
		return E_OS_ID;
	}
	
	//��ֹ������ѭ��
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
	
	//û�к��ʵ����������ȼ���͵�����
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
	
	//��ǰ�������ڽ���,�������жϽ��������л�
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


////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Task.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 任务相关定义
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-10	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _OS_TASK_H_
#define _OS_TASK_H_

#include "Os_Cfg.h"
#include "Os_Resource.h"

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions
#define	DeclareTask(task)	TASK(task);

#define	TASK(task)			void Os_Task_##task(void)

#define	INVALID_TASK	    (-1)

////////////////////////////////////////////////////////////////////////////////
//	Type Definitions
typedef	void(*TaskTypeFunc)(void);
typedef	sint8_least		TaskType;
typedef TaskType		*TaskRefType;
typedef uint8_least		TaskStateType;
typedef TaskStateType	*TaskStateRefType;

//任务控制结构块
typedef	struct
{	
	TaskTypeFunc	func;       //任务函数
	const TaskType	taskID;     //任务ID,优先级,0表示优先级最低
	TaskStateType	state;      //当前状态
	//uint32          time;	
	//EventMaskType	eventType;
}TCB_Type;

//任务状态,与TaskStateType对应
enum
{
	RUNNING     =0x10,
	WAITING     =0x20,
	READY       =0x30,
	SUSPENDED   =0x40
};

//任务类型,基本类型或扩展类型
enum
{
	BASIC,
	EXTEND
};


////////////////////////////////////////////////////////////////////////////////
//	API Declaration
StatusType	ActivateTask(TaskType TaskID);
StatusType	TerminateTask(void);
StatusType	ChainTask(TaskType TaskID);
StatusType	GetTaskID(TaskRefType TaskID);
StatusType	GetTaskState(TaskType TaskID, TaskStateRefType State);
StatusType	Schedule(void);

////////////////////////////////////////////////////////////////////////////////
//	Reinclude Prevention Ends
#endif
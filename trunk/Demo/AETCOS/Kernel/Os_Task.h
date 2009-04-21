////////////////////////////////////////////////////////////////////////////////
//	����: Os_Task.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: ������ض���
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-10	�����ļ�
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

//������ƽṹ��
typedef	struct
{	
	TaskTypeFunc	func;       //������
	const TaskType	taskID;     //����ID,���ȼ�,0��ʾ���ȼ����
	TaskStateType	state;      //��ǰ״̬
	//uint32          time;	
	//EventMaskType	eventType;
}TCB_Type;

//����״̬,��TaskStateType��Ӧ
enum
{
	RUNNING     =0x10,
	WAITING     =0x20,
	READY       =0x30,
	SUSPENDED   =0x40
};

//��������,�������ͻ���չ����
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
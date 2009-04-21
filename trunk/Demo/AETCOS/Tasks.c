////////////////////////////////////////////////////////////////////////////////
//	����: Tasks.c
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: Ӧ�ó�������ʾ��
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-23	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#include "Tasks.h"
#include "includes.h"	//��������Ӧ�ò�������ļ�

EventMaskType			Os_Task_Event[] =
{
	0,
	TESTEVENT4,
	0,
	0,
	TESTEVENT3,
	0
};

//������ƽṹ��
TCB_Type Os_TCB[]=
{
    //0��ʾ���ȼ���͵�����,��������
    {_TASK(SystemIdle),0,READY},
    
    {_TASK(VehCtl),1,READY},
    {_TASK(EngCtl),2,READY},
    {_TASK(CCP),3,READY},
    {_TASK(task4),4,SUSPENDED},
    {_TASK(task5),5,WAITING},
    {_TASK(task6),6,SUSPENDED},
};

static OS_STK task1Stk[TASK_STACK_SIZE];
static OS_STK task2Stk[TASK_STACK_SIZE];
static OS_STK task3Stk[TASK_STACK_SIZE];
static OS_STK task4Stk[TASK_STACK_SIZE];
static OS_STK task5Stk[TASK_STACK_SIZE];

////////////////////////////////////////////////////////////////////////////////
//	Task Declaration
DeclareTask(VehCtl)
DeclareTask(EngCtl)
DeclareTask(CCP)
DeclareTask(task4)
DeclareTask(task5)
DeclareTask(task6)
DeclareTask(SystemIdle)

////////////////////////////////////////////////////////////////////////////////
//	Tasks
TASK(VehCtl)
{
	OS_STK *a;
    //a=(OS_STK *)malloc(22);	
    a=task1Stk;
    ActivateTask(EngCtl);
	VehCtl_task();
	TerminateTask();
}

TASK(EngCtl)
{
	EngCtl_Task();
	ActivateTask(CCP);
	TerminateTask();
}

TASK(CCP)
{
	//ClearEvent(TESTEVENT3);
	CCP_MainFunction();
	ActivateTask(VehCtl);
	//WaitEvent(TESTEVENT3);
	ChainTask(CCP);
}

TASK(task4)
{
	ActivateTask(EngCtl);
	//SetEvent(CCP, TESTEVENT3);
	TerminateTask();
}

TASK(task5)
{
	//AlarmPin2 = 1;
	//AlarmPin2 = 0;
	TerminateTask();
}

TASK(task6)
{
	ClearEvent(TESTEVENT4);
	LED_OFF(6);
	WaitEvent(TESTEVENT4);
	ActivateTask(VehCtl);
}

TASK(SystemIdle)
{
    register uint32 a=6;
    a=(1<<a);
    //DelayUs(20);
    
    ActivateTask(VehCtl);    
    TerminateTask();
}
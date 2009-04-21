/////////////////////////////////////////////////////////////////////////////
// ����: demo.c
// �汾: 1.0  Copyright (c) 2008 BYAE, All Rights Reserved
// ����: ����OS���������ļ�,�����������ҪTasks.c��main.c
// ����: CodeWarrior for MPC55XX v2.2 
// �޸���ʷ�� 
// �汾	����	  ����		���� 
// ----	-------	----------	---------------------------
// 1.0	�ƹ���	2008-10-24 	��������
//
/////////////////////////////////////////////////////////////////////////////
#include "Tasks.h"		//��ϵͳ���������صĳ���

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
	//VehCtl_task();
	TerminateTask();
}

TASK(EngCtl)
{
	//EngCtl_Task();
	ActivateTask(CCP);
	TerminateTask();
}

TASK(CCP)
{
	//ClearEvent(TESTEVENT3);
	//CCP_MainFunction();
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

uint32 testAddr=0x20010000;     //����ĳ����ַ
uint32 testData=100;            //��testAddr��Ӧ�����õ�ַ������ȡ����
void MCU_Init(void)
{
	//��ʼ��ϵͳʱ��
	FMPLL.SYNCR.R = 0x00080400;           	//Initial setting:PREDIV=0,MFD=0,RFD=1 
  											//Fsys=40 MHz for 20 MHz crystal 
  	while (FMPLL.SYNSR.B.LOCK != 1) {};   	// Wait for LOCK = 1 
  	if ((FMPLL.SYNSR.B.CALDONE != 1) | (FMPLL.SYNSR.B.CALPASS != 1)) {}
    
    //FMPLL.SYNCR.R = ((CONF_SYSCLK/CONF_INCLK*2-4) <<23) | 0x00080400;
 	//MFD��ϵͳʱ�����ⲿʱ�Ӿ���,PREDIV=0,RFD=1
 	//Fsys=Fref*(MFD+4)/(PREDIV+1)/(2^RFD)
 	
 	while (FMPLL.SYNSR.B.LOCK != 1) {};   	// Wait for LOCK = 1
 		//Init engclk 
 	//SIU.ECCR.B.ENGDIV = CONF_SYSCLK/CONF_ENGCLK/2;          //Set ENGCLK=Fsys/ENGDIV*2
}

int main(void) 
{
    MCU_Init();			
	//GPT_Init();
    //ReInitData();//����    
    //����ָ��ʱ���ڽ��յ����������BootLoaderģʽ
	//StartBootMode();

	StartOS(0);
			
}//end main













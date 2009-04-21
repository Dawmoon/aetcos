/////////////////////////////////////////////////////////////////////////////
// 名称: demo.c
// 版本: 1.0  Copyright (c) 2008 BYAE, All Rights Reserved
// 描述: 调试OS的主程序文件,是用这个则不需要Tasks.c和main.c
// 编译: CodeWarrior for MPC55XX v2.2 
// 修改历史： 
// 版本	作者	  日期		描述 
// ----	-------	----------	---------------------------
// 1.0	黄国钧	2008-10-24 	创建程序
//
/////////////////////////////////////////////////////////////////////////////
#include "Tasks.h"		//与系统任务调度相关的程序

EventMaskType			Os_Task_Event[] =
{
	0,
	TESTEVENT4,
	0,
	0,
	TESTEVENT3,
	0
};

//任务控制结构体
TCB_Type Os_TCB[]=
{
    //0表示优先级最低的任务,空闲任务
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

uint32 testAddr=0x20010000;     //测试某个地址
uint32 testData=100;            //与testAddr对应，将该地址的数读取出来
void MCU_Init(void)
{
	//初始化系统时钟
	FMPLL.SYNCR.R = 0x00080400;           	//Initial setting:PREDIV=0,MFD=0,RFD=1 
  											//Fsys=40 MHz for 20 MHz crystal 
  	while (FMPLL.SYNSR.B.LOCK != 1) {};   	// Wait for LOCK = 1 
  	if ((FMPLL.SYNSR.B.CALDONE != 1) | (FMPLL.SYNSR.B.CALPASS != 1)) {}
    
    //FMPLL.SYNCR.R = ((CONF_SYSCLK/CONF_INCLK*2-4) <<23) | 0x00080400;
 	//MFD由系统时钟与外部时钟决定,PREDIV=0,RFD=1
 	//Fsys=Fref*(MFD+4)/(PREDIV+1)/(2^RFD)
 	
 	while (FMPLL.SYNSR.B.LOCK != 1) {};   	// Wait for LOCK = 1
 		//Init engclk 
 	//SIU.ECCR.B.ENGDIV = CONF_SYSCLK/CONF_ENGCLK/2;          //Set ENGCLK=Fsys/ENGDIV*2
}

int main(void) 
{
    MCU_Init();			
	//GPT_Init();
    //ReInitData();//测试    
    //若在指定时间内接收到数据则进入BootLoader模式
	//StartBootMode();

	StartOS(0);
			
}//end main













////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Alarm.c
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: Alarm实现
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-13	创建文件
//  1.1     黄国钧  2009-03-17  使用Decrementer中断,1ms触发1次
//
////////////////////////////////////////////////////////////////////////////////
#include "Os_Alarm.h"

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
extern	AlarmInfoType			AlarmInfos[];
extern	const	AlarmBaseType	AlarmBases;

////////////////////////////////////////////////////////////////////////////////
//	Module global variables
TickType	NowTicks=0;

////////////////////////////////////////////////////////////
//	Function name:	GetAlarmBase
//	Description:	Get the information of the alarm's base
//		Parameter:	AlarmID
//					Info
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{	
	if(AlarmInfos[AlarmID].alarmID != AlarmID)
	{
		//Invalid alarm ID
		return E_OS_ID;
	}
	
	Info->maxAllowedValue	= AlarmBases.maxAllowedValue;
	Info->ticksPerBase		= AlarmBases.ticksPerBase;
	Info->minCycle			= AlarmBases.minCycle;
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	GetAlarm
//	Description:	Get the remaining ticks of the alarm
//		Parameter:	AlarmID
//					Tick
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	GetAlarm(AlarmType AlarmID, TickRefType Tick)
{
	if(AlarmInfos[AlarmID].alarmID != AlarmID)
	{
		//Invalid alarm ID
		return E_OS_ID;
	}
	
	if(AlarmInfos[AlarmID].alarmState != RUNNING)
	{
		//Specified alarm is not used
		return E_OS_NOFUNC;
	}
		
	*Tick = AlarmInfos[AlarmID].alarmTime;
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	SetRelAlarm
//	Description:	Enable an alarm by related tick value
//		Parameter:	AlarmID
//					increment
//					cycle
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle)
{
	//首先检查ID是否正确
	if(AlarmInfos[AlarmID].alarmID != AlarmID)
	{
		return E_OS_ID;
	}
	
	if(AlarmInfos[AlarmID].alarmState == RUNNING)
	{
		//Specified alarm is already in use
		return E_OS_STATE;
	}
	
	if(cycle < AlarmBases.minCycle)
	{
		//Invalid value
		return E_OS_VALUE;
	}

	AlarmInfos[AlarmID].alarmTime	= NowTicks+increment;
	AlarmInfos[AlarmID].cycleTime	= cycle;
	AlarmInfos[AlarmID].alarmState	= RUNNING;
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	SetAbsAlarm
//	Description:	Enable an alarm by absolute tick value
//		Parameter:	AlarmID
//					start
//					cycle
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	SetAbsAlarm(AlarmType AlarmID, TickType	start, TickType cycle)
{
	if(AlarmInfos[AlarmID].alarmID != AlarmID)
	{
		return E_OS_ID;
	}
	
	if(AlarmInfos[AlarmID].alarmState == RUNNING)
	{
		//Specified alarm is already in use
		return E_OS_STATE;
	}
	
	if(cycle < AlarmBases.minCycle)
	{
		//Invalid value
		return E_OS_VALUE;
	}
	
	AlarmInfos[AlarmID].alarmTime	= start;
	AlarmInfos[AlarmID].cycleTime	= cycle;
	AlarmInfos[AlarmID].alarmState	= RUNNING;
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	CancelAlarm
//	Description:	Disable an alarm
//		Parameter:	AlarmID
//	Return value:	Whether the operation succeeded 
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	CancelAlarm(AlarmType AlarmID)
{
	if(AlarmInfos[AlarmID].alarmID != AlarmID)
	{
		return E_OS_ID;
	}
	
	if(AlarmInfos[AlarmID].alarmState != RUNNING)
	{
		//Specified alarm is not in use
		return E_OS_NOFUNC;
	}	
	
	AlarmInfos[AlarmID].alarmState	= SUSPENDED;
	
	return E_OK;
}

////////////////////////////////////////////////////////////
//	Function name:	AlarmTickHandler
//	Description:	Time base interrupt handler on MPC5554
//		Parameter:	none
//	Return value:	none 
//	Function calls:	none
//
////////////////////////////////////////////////////////////
//中断处理程序,需要保存现场并放在指定的位置
void AlarmTickHandler(void)
{
	uint8_least     tmpAlarmIndex=0;
	AlarmInfoType   *info;
		
	NowTicks++;
	
	//循环检查每个闹钟的工作情况
	for(info=&AlarmInfos[0]; tmpAlarmIndex<OS_MAX_ALARM; tmpAlarmIndex++,info++)
	//for(info=&AlarmInfos[0]; (info->alarmID==tmpAlarmIndex) && (tmpAlarmIndex<CONF_OS_ALARM_NUM); tmpAlarmIndex++,info++)
	//for(info=&AlarmInfos[0]; AlarmInfos->alarmID < CONF_OS_ALARM_NUM; info++)
	{
		if(info->alarmState != RUNNING)
		{
			continue;
		}
		
		//info->alarmTime = info->alarmTime - 1;
		//if(0==info->alarmTime)
		if(NowTicks==info->alarmTime)
		{
			switch(info->actionType)
			{
				case ALARM_CALLBACK_ACTION:
					(*info->func)();
					break;
				case ALARM_ACTIVATE_TASK:
					ActivateTask(info->taskID);
					break;
				case ALARM_SET_TASK_EVENT:
					SetEvent(info->taskID, info->eventID);
					break;
				default:
					break;
			}//end switch
			
			//如果周期为0则只运行一次
			info->alarmTime += info->cycleTime;
		}	
	}//end for
}

////////////////////////////////////////////////////////////
//	Function name:	InitAlarmSystem
//	Description:	Initialize the alarm sub system
//		Parameter:	none
//	Return value:	none 
//	Function calls:	none
//
////////////////////////////////////////////////////////////
__asm void InitAlarmSystem(void)
{
	#define CONF_TCR_SET 0x04418000//[DIE]=1;[ARE]=1
	//#define CONF_TCR_SET 0x03818000
	//与TCR有关的设置		

	//TCR[DIE]=1
    //3  3 3  3 4  4 4  4 4  5 5  5 5  5 6  6
    //2  5 6  9 0  3 4  7 8  1 2  5 6  9 0  3
    //0000 0011 1000 0001 1000 0000 0000 0000
    //   0    3    8    1    8    0    0    0
    lis		r0, CONF_TCR_SET@h
    ori		r0, r0, CONF_TCR_SET@l
    mftcr	r5
    or		r0, r0, r5
    mttcr	r0	    
    
    //初始化TimeBase为0
    lis		r0, 0
    mttbu	r0
    mttbl	r0
    
    //写入经过多少个脉冲产生一个计数,中断
    //lis		r0, CONF_TICKS_MS@h
    //ori		r0, r0, CONF_TICKS_MS@l
    e_lis    r8,AlarmBases@ha
    e_add16i r3,r8,AlarmBases@l
    se_lwz   r0,4(r3)
    mtdecar r0
    mtdec   r0
    
    //3  3 3  3 4  4 4  4 4  5 5  5 5  5 6  6
    //2  5 6  9 0  3 4  7 8  1 2  5 6  9 0  3
    //0000 0000 0000 0000 0100 0000 0000 0000
    //   0    0    0    0    4    0    0    0	    
    mfhid0	r5    
    //写法1,采用或操作将某个位变1
    lis		r0, 0x0000
    ori		r0, r0, 0x4000
    or		r0, r5, r0
    mthid0	r0    
    //也可以采用位操作直接完成
    //se_bseti r5,17
    //mthid0  r5
    
    	
	blr
	#undef CONF_TCR_SET
}

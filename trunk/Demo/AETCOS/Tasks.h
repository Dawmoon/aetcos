////////////////////////////////////////////////////////////////////////////////
//	名称: Tasks.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 任务声明
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-23	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _TASKS_H_
#define _TASKS_H_

#include "Os.h"

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions
#define	_TASK(task)			Os_Task_##task

////////////////////////////////////////////////////////////////////////////////
enum
{
	SystemIdle,
		
	VehCtl,
	EngCtl,
	CCP,
	task4,
	task5,
	task6
};

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
extern	TASK(VehCtl);
extern	TASK(EngCtl);
extern	TASK(CCP);
extern	TASK(task4);
extern	TASK(task5);
extern	TASK(task6);
extern	TASK(SystemIdle);

#endif
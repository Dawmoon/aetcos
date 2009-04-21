////////////////////////////////////////////////////////////////////////////////
//	����: Tasks.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: ��������
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-23	�����ļ�
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
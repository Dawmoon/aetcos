////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Event.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 操作系统事件声明、定义
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-13	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _OS_EVENT_H_
#define _OS_EVENT_H_

#include "Os_Cfg.h"
#include "Os_Task.h"
#include "Os_Resource.h"

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions
#define	DeclareEvent(EventName)

#define	TESTEVENT1	(0x00000001)
#define	TESTEVENT2	(0x00000002)
#define	TESTEVENT3	(0x00000004)
#define	TESTEVENT4	(0x00000008)

////////////////////////////////////////////////////////////////////////////////
//	Type Definitions
typedef	uint32			EventMaskType;
typedef	EventMaskType	*EventMaskRefType;

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions

////////////////////////////////////////////////////////////////////////////////
//	API Declaration
StatusType	SetEvent(TaskType TaskID, EventMaskType Mask);
StatusType	ClearEvent(EventMaskType Mask);
StatusType	GetEvent(TaskType TaskID, EventMaskRefType Event);
StatusType	WaitEvent(EventMaskType Mask);

////////////////////////////////////////////////////////////////////////////////
//	Reinclude Prevention Ends
#endif
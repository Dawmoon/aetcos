////////////////////////////////////////////////////////////////////////////////
//	����: Os_Event.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: ����ϵͳ�¼�����������
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-13	�����ļ�
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
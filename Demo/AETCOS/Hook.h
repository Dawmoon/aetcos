////////////////////////////////////////////////////////////////////////////////
//	����: Hook.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: ����ϵͳ��������
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-13	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _OS_HOOK_H_
#define _OS_HOOK_H_

#include "Os.h"

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions
//TaskHookPin	DA20
#define	TaskHookPin	SIU.GPDO[48].B.PDO

#define	OSErrorGetServiceId

#define	OSError_

////////////////////////////////////////////////////////////////////////////////
//	API Declaration
void	ErrorHook(StatusType Error);
void	PreTaskHook(void);
void	PostTaskHook(void);
void	StartupHook(void);
void	ShutdownHook(StatusType Error);

#endif
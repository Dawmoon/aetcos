////////////////////////////////////////////////////////////////////////////////
//	名称: Hook.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 操作系统钩子声明
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-13	创建文件
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
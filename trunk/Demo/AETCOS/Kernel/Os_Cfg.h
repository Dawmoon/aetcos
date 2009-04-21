////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Cfg.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 操作系统配置文件
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		黄国钧	2009-04-19	在原Os_Common.h基础上创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef	_OS_CFG_H_
#define	_OS_CFG_H_

#include "CPU_Interrupt.h"

//定义最多允许的任务个数
#define	OS_MAX_TASK	        (6)

//每个扩展任务都有自己的堆栈
#define TASK_STACK_SIZE     (256)

//定义最多允许的Alarm个数
#define	OS_MAX_ALARM		(3)

#define	OS_MAX_RESOURCE	    (1)

#endif
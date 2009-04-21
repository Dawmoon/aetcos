////////////////////////////////////////////////////////////////////////////////
//	名称: Std_Types.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: AETCOS标准数据类型定义
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-08	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#include "CPU/Platform_Types.h"
#include "CPU/Compiler.h"
#include "MPC5534.h"

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions
#define	E_NOT_OK	(0x01)

#define	STD_HIGH	(0x01)
#define	STD_LOW		(0x00)

#define	STD_ACTIVE	(0x01)
#define	STD_IDLE	(0x00)

#define	STD_ON		(0x01)
#define	STD_OFF		(0x00)

//定义当前为调试版本
#define _OS_DEBUG_

//调试模式下信号指示用,开发板上用8路EMIOS作LED输出
#ifdef _OS_DEBUG_
    #define LED_INIT(PIN)   SIU.PCR[178+PIN].R=0x020E
    #define LED_ON(PIN)     SIU.GPDO[178+PIN].B.PDO  =1
    #define LED_OFF(PIN)    SIU.GPDO[178+PIN].B.PDO  =0
    #define LED_RES(PIN)    SIU.GPDO[178+PIN].B.PDO ^=1
#else
    #define LED_INIT(PIN)
    #define LED_ON(PIN)
    #define LED_OFF(PIN)
    #define LED_RES(PIN)
#endif

////////////////////////////////////////////////////////////////////////////////
//	Type Definitions
#ifndef STATUSTYPEDEFINED
	#define STATUSTYPEDEFINED
	#define E_OK	(0x00)
	
	typedef uint8_least StatusType;
#endif

typedef	uint8	Std_ReturnType;

typedef	struct
{
	uint16	vendorID;
	uint16	moduleID;
	uint8	instanceID;
	uint8	sw_major_version;
	uint8	sw_minor_version;
	uint8	sw_patch_version;
} Std_VersionInfoType;

typedef uint32 OS_STK;

enum
{
	//注意返回值为0表示无错误
	E_OS_ACCESS     =1,
	E_OS_CALLEVEL,
	E_OS_ID,
	E_OS_LIMIT,
	E_OS_NOFUNC,
	E_OS_RESOURCE,
	E_OS_STATE,
	E_OS_VALUE,
	
	//AUTOSAR增加的故障类型
	E_OS_SERVICEID,
	E_OS_ILLEGAL_ADDRESS,
	E_OS_MISSINGEND,
	E_OS_DISABLEDING,
	E_OS_STACKFAULT,
	E_OS_PROTECTION_MEMORY,
	E_OS_PROTECTION_TIME,
	E_OS_PROTECTION_ARRUVAL,
	E_OS_PROTECTION_LOCKED,
	E_OS_PROTECTION_ECXCEPTION
};

#endif
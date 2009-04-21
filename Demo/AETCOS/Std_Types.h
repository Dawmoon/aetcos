////////////////////////////////////////////////////////////////////////////////
//	����: Std_Types.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: AETCOS��׼�������Ͷ���
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-08	�����ļ�
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

//���嵱ǰΪ���԰汾
#define _OS_DEBUG_

//����ģʽ���ź�ָʾ��,����������8·EMIOS��LED���
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
	//ע�ⷵ��ֵΪ0��ʾ�޴���
	E_OS_ACCESS     =1,
	E_OS_CALLEVEL,
	E_OS_ID,
	E_OS_LIMIT,
	E_OS_NOFUNC,
	E_OS_RESOURCE,
	E_OS_STATE,
	E_OS_VALUE,
	
	//AUTOSAR���ӵĹ�������
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
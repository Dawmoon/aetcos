////////////////////////////////////////////////////////////////////////////////
//	名称: Platform_Types.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: MPC55xx基本数据类型定义
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-08	创建文件
//			黄国钧				将32位整数由int修改为long
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _PLATFORM_TYPES_H_
#define _PLATFORM_TYPES_H_

////////////////////////////////////////////////////////////////////////////////
//	Symbol definitions

#define	CPU_TYPE_8		(8)
#define CPU_TYPE_16		(16)
#define	CPU_TYPE_32		(32)

#define	MSB_FIRST		(0)
#define	LSB_FIRST		(1)

#define	HIGH_BYTE_FIRST	(0)
#define	LOW_BYTE_FIRST	(1)

#define	CPU_TYPE		CPU_TYPE_32
#define	CPU_BIT_ORDER	LSB_FIRST
#define	CPU_BYTE_ORDER	HIGH_BYTE_FIRST

#ifndef TRUE
	#define	TRUE	(1)
#endif

#ifndef FALSE
	#define	FALSE	(0)
#endif

////////////////////////////////////////////////////////////////////////////////
//	Type Definitions

typedef unsigned	char	boolean;
typedef	signed		char	sint8;
typedef unsigned	char	uint8;
typedef signed		short	sint16;
typedef unsigned	short	uint16;
typedef signed		long	sint32;
typedef unsigned	long	uint32;

typedef	signed		long	sint8_least;
typedef unsigned	long	uint8_least;
typedef signed		long	sint16_least;
typedef unsigned	long	uint16_least;
typedef signed		long	sint32_least;
typedef unsigned	long	uint32_least;

typedef				float	float32;
typedef				double	float64;

typedef	signed		char	INT8;
typedef unsigned	char	UINT8;
typedef signed		short	INT16;
typedef unsigned	short	UINT16;
typedef signed		long	INT32;
typedef unsigned	long	UINT32;

typedef				float	FLOAT32;
typedef				double	FLOAT64;

#endif
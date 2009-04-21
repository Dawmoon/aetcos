////////////////////////////////////////////////////////////////////////////////
//	名称: Compiler_Cfg.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 编译器特性配置文件
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-09	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _COMPILER_CFG_H_
#define _COMPILER_CFG_H_

//申明与编译器相关的数据段,与lcf文件相关
#pragma section RW 	".mapFlash"	
#pragma section RW	".varClb" data_mode=far_abs

//与设置MAP数据地址的几个宏
#ifdef CLB_VERSION
    //标定版本使用,外扩RAM区域
	#pragma section RW 	".mapRam"
	#define CREATE_ECU_MAP   __declspec(section ".mapRam")	
    #define EXTERN_ECU_MAP  extern
#else
    #define CREATE_ECU_MAP   __declspec(section ".mapFlash") const
    #define EXTERN_ECU_MAP  extern const
#endif

//定义标定变量所在段 
#define VAR_CLB(varName,dataType)  __declspec(section ".varClb" ) \
					volatile    dataType varName
//#define VAR_CLB(varName,dataType) volatile dataType varName

 
#endif
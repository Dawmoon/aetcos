////////////////////////////////////////////////////////////////////////////////
//	����: Compiler_Cfg.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: ���������������ļ�
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-09	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _COMPILER_CFG_H_
#define _COMPILER_CFG_H_

//�������������ص����ݶ�,��lcf�ļ����
#pragma section RW 	".mapFlash"	
#pragma section RW	".varClb" data_mode=far_abs

//������MAP���ݵ�ַ�ļ�����
#ifdef CLB_VERSION
    //�궨�汾ʹ��,����RAM����
	#pragma section RW 	".mapRam"
	#define CREATE_ECU_MAP   __declspec(section ".mapRam")	
    #define EXTERN_ECU_MAP  extern
#else
    #define CREATE_ECU_MAP   __declspec(section ".mapFlash") const
    #define EXTERN_ECU_MAP  extern const
#endif

//����궨�������ڶ� 
#define VAR_CLB(varName,dataType)  __declspec(section ".varClb" ) \
					volatile    dataType varName
//#define VAR_CLB(varName,dataType) volatile dataType varName

 
#endif
////////////////////////////////////////////////////////////////////////////////
//	����: Compiler.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: ���������Դ���Ԥ����
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-08	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _COMPILER_H_
#define	_COMPILER_H_

#include "Compiler_Cfg.h"

////////////////////////////////////////////////////////////////////////////////
//	Definitions
#define	AUTOMATIC
#define	TYPEDEF
#define STATIC		static
#define	NULL_PTR	((void *)0)
#define	INLINE		inline

////////////////////////////////////////////////////////////////////////////////
//	Macros for functions
#define	FUNC(rettype, memClass)						memClass rettype
#define P2VAR(ptrtype, memClass, ptrclass)			ptrclass ptrtype * memClass
#define P2CONST(ptrtype, memClass, ptrclass)		const ptrtype memClass * ptrclass
#define CONSTP2VAR(ptrtype, memClass, ptrclass)		ptrtype memClass * const ptrclass
#define CONSTP2CONST(ptrtype, memClass, ptrclass)	const ptrtype memClass * const ptrclass
#define P2FUNC(rettype, ptrclass, fctname)			rettype (* ptrclass fctname)

////////////////////////////////////////////////////////////////////////////////
//	Keywords for constants, variables
#define	CONST(consttype, memClass)					const memClass consttype
#define VAR(vartype, memClass)						memClass vartype


//#pragma CONST_SEG DEFAULT


#endif
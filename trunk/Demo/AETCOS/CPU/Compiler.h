////////////////////////////////////////////////////////////////////////////////
//	名称: Compiler.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 编译器特性代码预定义
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-08	创建文件
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
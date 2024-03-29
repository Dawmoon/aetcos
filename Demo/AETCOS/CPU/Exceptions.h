////////////////////////////////////////////////////////////////////////////////
//	名称: Exceptions.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: Setup of IVPR to point to the EXCEPTION_HANDLERS memory area 
//        defined in the linker command file.
//        Default setup of the IVORxx registers. 
//
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		黄国钧	2009-04-11	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

// Function declarations                                                      */

#ifdef __cplusplus
extern "C" {
#endif

#pragma section RX ".__exception_handlers"

// This function is used as default exceptions handler
__declspec (section ".__exception_handlers") void EXCEP_DefaultExceptionHandler(void);


// This function will setup the PowerPC Zen core IVPR and IVORxx registers.
// IVPR will be set to the EXCEPTION_HANDLERS memory area defined in the 
// linker command file (.lcf of the current build target)  
// IVORxx will be set by default to the exception handler function: __DefaultExceptionHandler__.
//
// If an Exception is used in the application code, the exception handler routine
// should be defined like the EXCEP_DefaultExceptionHandler function 
// (i.e. interrupt function, forced active and placed in the ".__exception_handlers"
// code section). The corresponding IVORxx register should then be set to this address.
//

__asm void EXCEP_InitExceptionHandlers(void);

#ifdef __cplusplus
}
#endif

#endif


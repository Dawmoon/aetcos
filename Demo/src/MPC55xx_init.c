////////////////////////////////////////////////////////////////////////////////
//	名称: MPC55xx_init.h
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述:MPC55XX系统初始化程序文件
//       复位后从EABI库中的__Start开始运行并调用usr_init()开始初始化
//       默认从内部FLASH启动并禁用看门狗
//
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		黄国钧	2009-04-11	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#include "Exceptions.h"    // IVPR and default exception handlers setup 
#include "CPU_Interrupt.h" // INTC Interrupts Requests configuration 
#include "MPC5534_HWInit.h"

#pragma section code_type ".init"

#define INIT_DERIVATIVE_INTERNAL_SETUP 1
#define INIT_EXTERNAL_BUS_INTERFACE_SETUP 1

#ifndef INIT_DERIVATIVE_INTERNAL_SETUP
#pragma error INIT_DERIVATIVE_INTERNAL_SETUP should be defined !
#endif

#ifndef INIT_EXTERNAL_BUS_INTERFACE_SETUP
#pragma error INIT_EXTERNAL_BUS_INTERFACE_SETUP should be defined !
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern __asm void __start();
//启动后程序从这里开始运行,具体实现在EABI的库中

__asm void usr_init();
//lint -esym(752,__start) 

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// usr_init():                                                   
//   Define here the needed hardware initializations at startup  

__asm void usr_init()
{
    // Add needed hardware initializations in this function 
    nofralloc

    mflr     r30                         // Save off return address in NV reg 

#if INIT_DERIVATIVE_INTERNAL_SETUP==1
    bl      INIT_Derivative              // Derivative specific hardware initializations 
#endif
#if INIT_EXTERNAL_BUS_INTERFACE_SETUP==1
    bl      INIT_ExternalBusAndMemory    // Set up access to external memory (inc. chip select and MMU) 
#endif
    bl      EXCEP_InitExceptionHandlers   // Set up Default Exception handling 
    bl      INTC_InitINTCInterrupts       // Set up INTC Interrupts Requests handling 

    mtlr    r30                          // Get saved return address 

    blr
}

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////////
// RCHW and Reset Vector setup:                               
//   The chip is by default setup to boot from internal Flash 
//   and the watchdog is disabled.                             

typedef void (*resetfuncptr)(void);

#pragma push // Save the current state 
#pragma section sconst_type ".__bam_bootarea"
extern const unsigned long bam_rchw;
extern const resetfuncptr bam_resetvector;

// RCHW_VALUE Flags 
#define RCHW_WTE 0x0400L        // Enable Watchdog 
#define RCHW_VLE 0x0100L        // Enable Variable Length Encoding
#define RCHW_PS0_32BITS 0x0000L // Boot from External Bus CS0, 32-bit CS0 port size. 
#define RCHW_PS0_16BITS 0x0200L // Boot from External Bus CS0, 16-bit CS0 port size. 
#define RCHW_BOOTIDENTIFIER 0x005AL

// Used RCHW value: boot from internal flash, watchdog disabled 
#if VLE_IS_ON == 1
#define RCHW_VALUE RCHW_BOOTIDENTIFIER|RCHW_PS0_32BITS|RCHW_VLE
#else
#define RCHW_VALUE RCHW_BOOTIDENTIFIER|RCHW_PS0_32BITS 
#endif

const unsigned long bam_rchw = (RCHW_VALUE)<<16;
const resetfuncptr bam_resetvector = __start;

#pragma pop

#ifdef __cplusplus
}
#endif


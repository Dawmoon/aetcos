////////////////////////////////////////////////////////////////////////////////
//	����: CPU_Interrupt.c
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: Contains the implementations of the generic interrupt controller handling
//        routines for the MPC55xx. The __INTCInterruptHandler__ is located at no specific 
//        address and is branched by the PowerPC Zen core to that location if the 
//        __initExternalInterrupts function has been called to setup the core to do so.
//        ĳЩ������ʹ����VLEָ��(�����λ��ǰ)
//
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		�ƹ���	2009-04-11	��ԭIntcInterrupts.c�����ϴ����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#include "CPU_Interrupt.h"
#include "mpc5500_spr.h"

//Ĭ�Ͻ�ֹ�ж�Ƕ��,�����Ҫ�����INTC_NESTED_INTERRUPT
#ifndef INTC_NESTED_INTERRUPT
    #define INTC_NESTED_INTERRUPT 0
#endif

////////////////////////////////////////////////////////////////////////////////
//������ݶ���
////////////////////////////////////////////////////////////////////////////////
boolean			    InterruptState;
union SPR_MSRVAL	cpu_msr;
union SPR_TCRVAL	cpu_tcr;

extern          Os_TCBCurr;
extern  		Os_TCBReady;

// Inline Assembler Defines                                                   
// This macro allows to use C defined address with the inline assembler
#define MAKE_HLI_ADDRESS(hli_name, c_expr) enum { hli_name=((int)(c_expr))  };

// Address of the IACKR Interrupt Controller register. 
MAKE_HLI_ADDRESS(INTC_IACKR, &INTC.IACKR.R)
// Address of the EOIR End-of-Interrupt Register register. 
MAKE_HLI_ADDRESS(INTC_EOIR, &INTC.EOIR.R)

// This is the Interrupt Service Routine Branch Table placed in memory
#define INTC_INTERRUPTS_REQUEST_VECTOR_TABLE_SIZE (308*4)

// Save the current state
#pragma push

//�ⲿ�жϵ��ж����������RAM�е�".__uninitialized_intc_handlertable"��
#pragma section data_type ".__initialized_intc_handlertable" ".__uninitialized_intc_handlertable"
//   Linker Command File (.lcf) to avoid the initialization at startup time.
//   This will decrease the code size, but the table won't be initialized to zero.
 
INTCInterruptFn INTCInterruptsHandlerTable[INTC_INTERRUPTS_REQUEST_VECTOR_TABLE_SIZE];
#pragma pop

//Ĭ�ϵ��쳣��ڵ�ַ,��LCF�ļ��л�ȡ
extern  EXCEPTION_HANDLERS;

union SPR_MSRVAL MSR;
union SPR_MSRVAL GetMSR(void)
{
    ;
}
////////////////////////////////////////////////////////////
// ����: INTC_InstallINTCInterruptHandler
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: ����ⲿ�жϴ�������ĳ���ж�Դ
// ����: ��
// ����: INTCInterruptFn handlerFn---ָ�����ⲿ�жϴ�����
//       unsigned short vectorNum----���жϺ����󶨵��ж��������
//       unsigned char psrPriority---�ж����ȼ�
// ����: void
// ˵��:This function can be used to install an interrupt handler for a given
//       interrupt vector. It will also set the Priority Status Register for the
//       source to the one given  
//
////////////////////////////////////////////////////////////
void INTC_InstallINTCInterruptHandler(INTCInterruptFn handlerFn, unsigned short vectorNum,
                                      unsigned char psrPriority)
{
    // Set the function pointer in the ISR Handler table 
    INTCInterruptsHandlerTable[vectorNum] = handlerFn;
    // Set the PSR Priority 
    INTC.PSR[vectorNum].B.PRI = psrPriority; 
}

////////////////////////////////////////////////////////////
// ����: INTC_InitINTCInterrupts
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: ��ʼ���ж�Դ   
// ����: ��
// ����: ��
// ����: void
// ˵��: This function will setup the PowerPC Zen core to jump to an Interrupt Service Routine
//       handler. This function can be used from user_init() (no stack frame, no memory access).
//
////////////////////////////////////////////////////////////
__asm void INTC_InitINTCInterrupts( void )
{
nofralloc

    mflr    r29
	
	//Ĭ�ϵ��жϴ�����
	lis     r0, EXCEPTION_HANDLERS@h
    ori     r0, r0, EXCEPTION_HANDLERS@l
    mtivpr  r0
    
    ////////////////////////////////////////////////////////////////////////////////
    // IVOR4 �ⲿ�ж�(SPR404)
    // This code enables the ISR handler for external interrupt code to address
    // INTC_INTCInterruptHandler (incl. large address by setting the IVPR value).
    lis     r0, INTC_INTCInterruptHandler@h
    ori     r0, r0, INTC_INTCInterruptHandler@l
    mtivor4 r0

    // Enable external interrupts in the Machine State Register. Set MSR[EE]=1. 
    wrteei  1

    // Set the location of the ISR Handler Table in INTC IACKR Register 
    lis     r0, INTCInterruptsHandlerTable@h
    ori     r0, r0, INTCInterruptsHandlerTable@l
    lis     r3,INTC_IACKR@h
    ori     r3,r3,INTC_IACKR@l
    stw     r0, 0(r3)

    mtlr    r29
    
    ////////////////////////////////////////////////////////////////////////////////
    //ϵͳʹ�õ��쳣����,(SPR 408),���ж�,����ָ��SC����
    lis     r0, OSCtxSw@h
	ori     r0, r0, OSCtxSw@l
	mtivor8 r0    
       
    ////////////////////////////////////////////////////////////////////////////////
    //IVOR10��ΪOS������ʱ��,���ɸ�TBU��������һ���ж�
	lis     r0, MPC5534TimeBaseHandler@h
	ori     r0, r0, MPC5534TimeBaseHandler@l
	mtivor10 r0

    blr
}

////////////////////////////////////////////////////////////
// ����: ResumeAllInterrupts
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: Resume all interrupts' state before "SuspendAllInterrupts" invoked      
// ����: ��
// ����: ��
// ����: void
// ˵��: 
////////////////////////////////////////////////////////////
__asm void	ResumeAllInterrupts(void)
{
	lwz		r0,cpu_msr.R
	mtmsr	r0
	blr
}

////////////////////////////////////////////////////////////
// ����: SuspendAllInterrupts
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: Store the current interrupts' state and disable all interrupts
// ����: ��
// ����: ��
// ����: void
// ˵��: 
////////////////////////////////////////////////////////////
__asm void	SuspendAllInterrupts(void)
{
	mfmsr	r0
	stw		r0,cpu_msr.R
	wrteei	0
	blr
}

////////////////////////////////////////////////////////////
// ����: ResumeOSInterrupts
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: Resume all OS used interrupts' state before "SuspendOSInterrupts" invoked
// ����: ��
// ����: ��
// ����: void
// ˵��: 
////////////////////////////////////////////////////////////
__asm void	ResumeOSInterrupts(void)
{
	lwz		r0,cpu_tcr.R
	mttcr	r0
	blr
}

////////////////////////////////////////////////////////////
// ����: SuspendOSInterrupts
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: Store the current OS used interrupts' state and disable all OS used interrupts
// ����: ��
// ����: ��
// ����: void
// ˵��: 
////////////////////////////////////////////////////////////
void	SuspendOSInterrupts(void)
{
	__asm
	{
		mftcr	r0
		stw		r0,cpu_tcr.R
	}
	
	cpu_tcr.B.DIE = ~cpu_tcr.B.DIE;
	
	__asm
	{
		lwz		r0,cpu_tcr.R
		mttcr	r0
	}
}

void StartupHook_SC(void)
{
    LED_RES(6);
    
}
//////////////////////////////////////////////////////////////////////////////
//����������жϺ���
//////////////////////////////////////////////////////////////////////////////

#pragma push 
#pragma force_active on
#pragma function_align 16 // We use 16 bytes alignment for Exception handlers 
// Handle the interrupt source by jumping to the ISR branch table (IACKR) 

#if INTC_NESTED_INTERRUPT == 0

__declspec(interrupt)
__declspec(section ".__exception_handlers")
//������Ƕ�׵��ⲿ�жϴ�����
void INTC_INTCInterruptHandler(void)
{
    INTCInterruptFn *handlerFn = (INTCInterruptFn*)(*(unsigned int*)&INTC.IACKR.R);
    //InterruptState=1;    
    (**handlerFn)();
    INTC.EOIR.R = 0;
    //InterruptState=0;   
}

#else

__declspec(interrupt)
__declspec(section ".__exception_handlers")
//����Ƕ�׵��ⲿ�жϴ�����
__asm void INTC_INTCInterruptHandler(void)
{
nofralloc
prolog:
    stwu    r1, -0x50 (r1)      // Create stack frame 
    stw r0,  0x24 (r1)          // Store r0 working register  

    // Save SRR0 and SRR1 
    mfsrr1  r0                  // Store SRR1 (must be done before enabling EE) 
    stw     r0,  0x10 (r1)
    mfsrr0  r0                  // Store SRR0 (must be done before enabling EE) 
    stw     r0,  0x0C (r1)

    // Clear request to processor; r3 contains the address of the ISR 
    stw     r3,  0x28 (r1)      // Store r3 
    lis     r3, INTC_IACKR@h    // Read pointer into ISR Vector Table & store in r3 
    ori     r3, r3, INTC_IACKR@l
    lwz     r3, 0x0(r3)         // Load INTC_IACKR, which clears request to processor 
    lwz     r3, 0x0(r3)         // Read ISR address from ISR Vector Table using pointer  

    // Enable processor recognition of interrupts 
    wrteei  1                   // Set MSR[EE]=1  

    // Save rest of context required by EABI 
    stw     r12, 0x4C (r1)      // Store r12 
    stw     r11, 0x48 (r1)      // Store r11 
    stw     r10, 0x44 (r1)      // Store r10 
    stw     r9,  0x40 (r1)      // Store r9 
    stw     r8,  0x3C (r1)      // Store r8 
    stw     r7,  0x38 (r1)      // Store r7 
    stw     r6,  0x34 (r1)      // Store r6 
    stw     r5,  0x30 (r1)      // Store r5 
    stw     r4,  0x2C (r1)      // Store r4 
    mfcr    r0                  // Store CR 
    stw     r0,  0x20 (r1)
    mfxer   r0                  // Store XER 
    stw     r0,  0x1C (r1)
    mfctr   r0                  // Store CTR 
    stw     r0,  0x18 (r1)
    mflr    r0                  // Store LR 
    stw     r0,  0x14 (r1)

    // Branch to ISR handler address from SW vector table 
    mtlr    r3                  // Store ISR address to LR to use for branching later  
    blrl                        // Branch to ISR, but return here 

epilog:
    // Restore context required by EABI (except working registers) 
    lwz     r0,  0x14 (r1)      // Restore LR 
    mtlr    r0
    lwz     r0,  0x18 (r1)      // Restore CTR 
    mtctr   r0
    lwz     r0,  0x1C (r1)      // Restore XER 
    mtxer   r0
    lwz     r0,  0x20 (r1)      // Restore CR 
    mtcrf   0xff, r0
    lwz     r5,  0x30 (r1)      // Restore r5 
    lwz     r6,  0x34 (r1)      // Restore r6 
    lwz     r7,  0x38 (r1)      // Restore r7 
    lwz     r8,  0x3C (r1)      // Restore r8 
    lwz     r9,  0x40 (r1)      // Restore r9 
    lwz     r10, 0x44 (r1)      // Restore r10 
    lwz     r11, 0x48 (r1)      // Restore r11 
    lwz     r12, 0x4C (r1)      // Restore r12 

    // Disable processor recognition of interrupts 
    wrteei  0

    // Ensure interrupt flag has finished clearing 
    mbar    0

    // Write 0 to INTC_EOIR, informing INTC to lower priority 
    li      r3, 0
    lis     r4, INTC_EOIR@h     // Load upper half of INTC_EOIR address to r4 
    ori     r4, r4, INTC_EOIR@l
    stw     r3, 0(r4)           // Write 0 to INTC_EOIR 

    // Restore Working Registers 
    lwz     r3,  0x28 (r1)      // Restore r3 
    lwz     r4,  0x2C (r1)      // Restore r4 

    // Retrieve SRR0 and SRR1 
    lwz     r0,  0x0C (r1)      // Restore SRR0 
    mtsrr0  r0
    lwz     r0,  0x10 (r1)      // Restore SRR1 
    mtsrr1  r0

    // Restore Other Working Registers 
    lwz     r0,  0x24 (r1)      // Restore r0 

    // Restore space on stack 
    addi    r1, r1, 0x50

    // End of Interrupt 
    rfi
}

#endif

////////////////////////////////////////////////////////////
//	Function name:	MPC5554TimeBaseHandler
//	Description:	Time base interrupt handler on MPC5554
//		Parameter:	none
//	Return value:	none 
//	Function calls:	none
//
////////////////////////////////////////////////////////////
__declspec(interrupt)
__declspec (section ".__exception_handlers")
//�жϴ������,��Ҫ�����ֳ�������ָ����λ��
void MPC5534TimeBaseHandler(void)
{
	//��TSR[DIS]
	__asm
	{
	    //3  3 3  3 4  4 4  4 4  5 5  5 5  5 6  6
	    //2  5 6  9 0  3 4  7 8  1 2  5 6  9 0  3
	    //0000 0100 0000 0000 0000 0000 0000 0000
	    //   0    4    0    0    0    0    0    0
		mftsr	r4
		//andis.	r4, r4, 0x0800
		//Ҳ��������д,ʹ��λָ��ֱ�ӽ���37λ��1
		se_bseti r4,5
		mttsr	r4
	}
	AlarmTickHandler();
}


////////////////////////////////////////////////////////////
// ����: OSCtxSw
// �汾: 1.0    COPYRIGHT (c) BFTC 2009 , All Rights Reserved
// ����: ϵͳ���õ��жϴ�����
// ����: ��
// ����: ��
// ����: void
// ˵��: EABIʹ�õ����GRP,�����VLEָ��ֻ����r0-r7
//       r0---
//       r1-----------��ջָ��
//       r2-----------��������ص�.sdata2��.sbss2ָ��,_SDA2_BASE_
//       r3-----------��������ָ��
//       r4  to r12---��������м�Ĵ���
//       r13----------��������ص�.sdata��.sbssָ��,_SDA_BASE_
//       r14 to r31---�������Ĵ�������
//
////////////////////////////////////////////////////////////
__asm void OSCtxSw(void)
{    
    nofralloc

////////////////////////////////////////////////////////////
//����ϵͳ�����ֳ�,ע��Ҫ��ָ�ʱһ��
prolog:
    stwu    r1, -0x50 (r1)      //������ջ    
    
    stw     r12, 0x4C (r1)     
    stw     r11, 0x48 (r1)
    stw     r10, 0x44 (r1) 
    stw     r9,  0x40 (r1) 
    stw     r8,  0x3C (r1) 
    stw     r7,  0x38 (r1)
    stw     r6,  0x34 (r1)
    stw     r5,  0x30 (r1)
    stw     r4,  0x2C (r1) 
    stw     r3,  0x28 (r1)      //��Ҫ������������,�ʱ��뱣��r3
    stw     r0,  0x24 (r1)      //��������Ҫ��r0,���ȱ���r0 

    //������ָ����صļĴ���,����CR,CTR,LR,XER
    //����ϵͳ���ò��漰������,�����豣��FPSCR,SPEFSCR
    mfcr    r0           
    stw     r0,  0x20 (r1)
    mfxer   r0            
    stw     r0,  0x1C (r1)
    mfctr   r0              
    stw     r0,  0x18 (r1)
    mflr    r0           
    stw     r0,  0x14 (r1)
    
////////////////////////////////////////////////////////////
//�����ں��л�,�ɰ����ں˵������л�����
    
    //ִ�������л����Ӻ���
    bl      StartupHook_SC   
    
    // Save SRR0 and SRR1 
    //mfsrr1  r0                  // Store SRR1 (must be done before enabling EE) 
    //stw     r0,  0x10 (r1)
    //mfsrr0  r0                  // Store SRR0 (must be done before enabling EE) 
    //stw     r0,  0x0C (r1)
                         

    lis     r11,Os_TCBCurr@ha                       
    lwz     r11,Os_TCBCurr@l(r11)
    
    //se_bseti r1,15
    //�˳��жϺ�����л�
    //lwz     r1, 0(r11) 
    //mtsrr0  r1
    
    /*
    //����ǰ�Ķ�ջָ�뱣�浽��ǰTCB
    stw     r1, 0(r11)    
    
    lis     r11,Os_TCBReady@ha    
    lwz     r11,Os_TCBReady@l(r11)

    lis     r12,Os_TCBCurr@ha                       
    stw     r11,Os_TCBCurr@l(r12)
    
    lis     r12,Os_TCBReady@ha                    // Get High Ready Priority
    lbz     r10,Os_TCBReady@l(r12)

    lis     r12,Os_TCBCurr@ha             
    stb     r10,Os_TCBCurr@l(r12)
    */
    
    // Ensure interrupt flag has finished clearing 
    //mbar    0

////////////////////////////////////////////////////////////
//�ָ�ϵͳ�����ֳ�
epilog:
    //�ָ���ָ����صļĴ���
    lwz     r0,  0x14 (r1)
    mtlr    r0
    lwz     r0,  0x18 (r1)
    mtctr   r0
    lwz     r0,  0x1C (r1) 
    mtxer   r0
    lwz     r0,  0x20 (r1)  
    mtcrf   0xff, r0
    
    lwz     r0,  0x24 (r1)
    lwz     r3,  0x28 (r1)
    lwz     r4,  0x2C (r1)
    lwz     r5,  0x30 (r1)
    lwz     r6,  0x34 (r1) 
    lwz     r7,  0x38 (r1) 
    lwz     r8,  0x3C (r1)  
    lwz     r9,  0x40 (r1) 
    lwz     r10, 0x44 (r1) 
    lwz     r11, 0x48 (r1)
    lwz     r12, 0x4C (r1)

    //�ָ���ջָ��
    addi    r1, r1, 0x50
    rfi                             // End of Interrupt 
}

#pragma force_active off
#pragma pop

OS_STK* OSTaskStkInit (void (*task)(void *pd), void *p_arg, OS_STK *ptos, uint16 opt)
{
    OS_STK     *stkp;                                                   /* Local: Stack pointer                                     */
    //OS_CPU_SR   cpu_msr;                                                    /* Local: Initial MSR                                       */
    //OS_CPU_SR   srr1;  
    uint32      srr1;                                                 /* Local: Initial SRR1                                      */


    (void)opt;                                                          /* 'opt' is not used, prevent warning                       */

    //cpu_msr     = CPU_SR_Rd();                                              /* get the MSB reg value                                    */
    srr1    = cpu_msr.R | 0x8000;                                             /* set MSR[EE] bit to enable interrupts                     */

    stkp    = (OS_STK *)((uint32)ptos & 0xFFFFFFF0);                    /* 16-byte align task's stack pointer (EABI)                */

                                                                        /* Leave buffer area for locals "above the stack" in ...    */
    //stkp   -=  OS_STK_RSVD_SIZE;                                        /* case the compiler prolog puts variables above the stack  */

                                                                        /* Stack Frame Initialization                               */
    *--stkp = (uint32)cpu_msr.R;                                              /* MSR                                                      */
    *--stkp = 0;                                                        /* EABI padding                                             */
    *--stkp = 0;                                                        /* EABI padding                                             */
    *--stkp = 0;                                                        /* SPEFSCR                                                  */
    *--stkp = (uint32)task;                                             /* LR                                                       */
    *--stkp = 0;                                                        /* CR                                                       */
    *--stkp = 0;                                                        /* XER                                                      */
    *--stkp = 0;                                                        /* CTR                                                      */
    *--stkp = 0;                                                        /* USPRG0                                                   */
    *--stkp = (uint32)srr1;                                             /* SRR1                                                     */
    *--stkp = (uint32)task;                                             /* SRR0                                                     */
    *--stkp = 0;                                                        /* R0                                                       */

    *--stkp = 0x31L;                                                    /* r31                                                      */
    *--stkp = 0x30L;                                                    /* r30                                                      */
    *--stkp = 0x29L;                                                    /* r29                                                      */
    *--stkp = 0x28L;                                                    /* r28                                                      */
    *--stkp = 0x27L;                                                    /* r27                                                      */
    *--stkp = 0x26L;                                                    /* r26                                                      */
    *--stkp = 0x25L;                                                    /* r25                                                      */
    *--stkp = 0x24L;                                                    /* r24                                                      */
    *--stkp = 0x23L;                                                    /* r23                                                      */
    *--stkp = 0x22L;                                                    /* r22                                                      */
    *--stkp = 0x21L;                                                    /* r21                                                      */
    *--stkp = 0x20L;                                                    /* r20                                                      */
    *--stkp = 0x19L;                                                    /* r19                                                      */
    *--stkp = 0x18L;                                                    /* r18                                                      */
    *--stkp = 0x17L;                                                    /* r17                                                      */
    *--stkp = 0x16L;                                                    /* r16                                                      */
    *--stkp = 0x15L;                                                    /* r15                                                      */
    *--stkp = 0x14L;                                                    /* r14                                                      */
    //*--stkp = (uint32)&_SDA_BASE_;                                      /* r13                                                      */
    *--stkp = 0x12L;                                                    /* r12                                                      */
    *--stkp = 0x11L;                                                    /* r11                                                      */
    *--stkp = 0x10L;                                                    /* r10                                                      */
    *--stkp = 0x9L;                                                     /* r09                                                      */
    *--stkp = 0x8L;                                                     /* r08                                                      */
    *--stkp = 0x7L;                                                     /* r07                                                      */
    *--stkp = 0x6L;                                                     /* r06                                                      */
    *--stkp = 0x5L;                                                     /* r05                                                      */
    *--stkp = 0x4L;                                                     /* r04                                                      */
    *--stkp = (uint32)p_arg;                                            /* r03                                                      */
    //*--stkp = (uint32)&_SDA2_BASE_;                                     /* r02                                                      */

    *--stkp = 0;                                                        /* BLANK for 0xA0 size                                      */
    *--stkp = (uint32)ptos;                                             /* Stack Ptr                                                */

    return(stkp);
}

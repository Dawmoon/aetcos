////////////////////////////////////////////////////////////////////////////////
//	����: CPU_Interrupt.h
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: Contains defines for utilizing the Interrupt Controller in the MPC5500. 
//        There is also the function prototypes for the common interrupt handling 
//        routines to be used on the MPC55xx (PowerPC Zen core).
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		�ƹ���	2009-04-11	��ԭIntcInterrupts.h�����ϴ����ļ�
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _CPU_INTERRUPT_H_
#define _CPU_INTERRUPT_H_

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	ISR(ISRName)	void ISRName(void)

//�жϺ���������
typedef void(*INTCInterruptFn)(void);

//���ж�ָ��,�ں��л�
#define OS_TASK_SW() asm(sc)

////////////////////////////////////////////////////////////////////////////////
//	API Declaration

#define EnableAllInterrupts()   {INTC.CPR.B.PRI = 0;asm(wrteei	1) }
//08��12��1�����,���������������ʹ��TPU�ж�
//  Ϊ�����Ч��2009��4��11��ʹ�ú꺯��

#define DisableAllInterrupts()  {asm(wrteei 0) }

void	ResumeAllInterrupts(void);

void	SuspendAllInterrupts(void);

void	ResumeOSInterrupts(void);

void	SuspendOSInterrupts(void);

extern void AlarmTickHandler(void);

//MPC5534TimeBaseHandler
void MPC5534TimeBaseHandler(void);

//�ں��л����жϴ�����
__asm void OSCtxSw(void); 

// This function will setup the PowerPC Zen core to jump to an Interrupt Service Routine
// handler. This function can be used from user_init() (no stack frame, no memory access).
__asm void INTC_InitINTCInterrupts(void);

// This function can be used to install an interrupt handler for a given
// interrupt vector. It will also set the Priority Status Register for the
// source to the one given.
// parameter handlerFn: The function to call when the interrupt occurs.
// parameter vectoryNum: The number of the INTC Interrupt Request Source we wish 
// to install the handler for.
// parameter psrPriority: The priority to set in the Interrupt Controller Priority
// Select Register.

void INTC_InstallINTCInterruptHandler(INTCInterruptFn handlerFn, unsigned short vectorNum,
                                      unsigned char psrPriority);

#pragma section RX ".__exception_handlers"

// This function is used to Handle the interrupt source by jumping to the ISR
// branch table (IACKR)
__declspec (section ".__exception_handlers") void INTC_INTCInterruptHandler(void);

#ifdef __cplusplus
}
#endif

#endif


////////////////////////////////////////////////////////////////////////////////
//	����: Os_Kernel.c
//	�汾: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	����: �ں�ʵ��
//	����: CodeWarrior for 55xx V2.3
//	�޸���ʷ�� 
//	�汾	����	  ����		���� 
//	----	-------	----------	---------------------------
//	1.0		��ҫ��	2008-09-08	�����ļ�
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//	Includes
#include "Os_Kernel.h"
#include "Os_Task.h"

extern  TCB_Type        *Os_TCBCurr;
extern  TCB_Type        *Os_TCBReady;
extern  TCB_Type        Os_TCB[];
//extern  TaskType		CurrID;

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
//extern	void	StartupHook(void);
//extern	void	ShutdownHook(StatusType Error);

AppModeType GetActiveApplicationMode(void)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//	Function implementation

////////////////////////////////////////////////////////////
//	Function name:	StartOS
//	Description:	Starts the operating system
//		Parameter:	Mode  -  Determines the operating mode of the system
//	Return value:	none
//	Function calls:	StartupHook
//					EnableAllInterrupts
//					DisableAllInterrupts
//
//	History:
//	Ver.	Person				Date		Comment
//	------	-------				--------	--------
//	0.1		Destroyer PGB Kan	2008-09-15	Creation
////////////////////////////////////////////////////////////
void	StartOS(AppModeType Mode)
{
	DisableAllInterrupts();
	
	StartupHook();
	
	EnableAllInterrupts();
	
	LED_INIT(1);
	LED_INIT(2);
	LED_INIT(3);
	LED_INIT(4);
	LED_INIT(5);
	
    //����ģʽ
    if(Mode==1)
	{
	    return;
	}
	    
	//����ģʽ
	for(;;)
	{
		//Schedule();
		//(*Os_TCB[CurrID].func)();
		Os_TCBCurr = Os_TCBReady;
		
		PreTaskHook();			
		(*Os_TCBCurr->func)();
		PostTaskHook();
	}
}

////////////////////////////////////////////////////////////
//	Function name:	ShutdownOS
//	Description:	Shutdown the operating system
//		Parameter:	Error  -  The reason why shut the system down
//	Return value:	none
//	Function calls:	ShutdownOSHook
//
//	History:
//	Ver.	Person				Date		Comment
//	------	-------				--------	--------
//	0.1		Destroyer PGB Kan	2008-09-15	Creation
////////////////////////////////////////////////////////////
void	ShutdownOS(StatusType Error)
{
	ShutdownHook(Error);
	
	for(;;)
	{
		;
	}
}


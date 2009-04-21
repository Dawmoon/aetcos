////////////////////////////////////////////////////////////////////////////////
//	名称: Os_Resource.c
//	版本: 1.0    COPYRIGHT (c) AETC 2008 , All Rights Reserved
//	描述: 资源实现
//	编译: CodeWarrior for 55xx V2.3
//	修改历史： 
//	版本	作者	  日期		描述 
//	----	-------	----------	---------------------------
//	1.0		简耀佳	2008-09-13	创建文件
//
////////////////////////////////////////////////////////////////////////////////
#include "Os_Resource.h"
#include "Os_Task.h"

////////////////////////////////////////////////////////////////////////////////
//	Resource related data
TaskType	Os_Res_Owner[OS_MAX_RESOURCE] = 
{
	INVALID_TASK
};

////////////////////////////////////////////////////////////////////////////////
//	External element declaration
//extern	TaskType	Os_Res_Owner[];
extern  TCB_Type        *Os_TCBCurr;
extern  TCB_Type        *Os_TCBReady;
extern  TCB_Type        Os_TCB[];

////////////////////////////////////////////////////////////
//	Function name:	GetResource
//	Description:	Occupy the resource
//		Parameter:	ResID	-  Resource to occupy
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	GetResource(ResourceType ResID)
{
	#ifdef	_OS_DEBUG_
		if((ResID <0) || (ResID >= OS_MAX_RESOURCE))
		{
			//Invalid resource ID
			return E_OS_ID;
		}
		
		if(Os_Res_Owner[ResID] != INVALID_TASK)
		{
			//Access argument
			return E_OS_ACCESS;
		}
	#endif
	
	Os_Res_Owner[ResID] = Os_TCBCurr->taskID;
	
	return E_OK;
}

///////////////////////////////////////////////////////////
//	Function name:	ReleaseResource
//	Description:	Release the resource
//		Parameter:	ResID	-  Resource to release
//	Return value:	Whether the operation succeeded
//	Function calls:	none
//
////////////////////////////////////////////////////////////
StatusType	ReleaseResource(ResourceType ResID)
{
	#ifdef	_OS_DEBUG_
		if((ResID <0) || (ResID >= OS_MAX_RESOURCE))
		{
			//Invalid resource ID
			return E_OS_ID;
		}
		
		if(Os_Res_Owner[ResID] == INVALID_TASK)
		{
			//Illegal release resource
			return E_OS_NOFUNC;
		}
		
		if(Os_Res_Owner[ResID] != Os_TCBCurr->taskID)
		{
			//Access argument
			return E_OS_ACCESS;
		}
	#endif
	
	Os_Res_Owner[ResID] = INVALID_TASK;
	
	return E_OK;
}
//------------------------------------------------------------------------
//  Readme.txt测试
//------------------------------------------------------------------------
This project stationery is designed to get you up and running
quickly with CodeWarrior on your MPC5534 target.

The wizard has created the following CodeWarrior target(s):

- RAM:
  This CodeWarrior target is setup to load and debug code from RAM (debug version).

- internal_FLASH:
  This CodeWarrior target is setup to debug code in internal Flash.
  The code must previously have been programmed into flash.


The targets are set up for the selected CPU and options,
but can be easily modified.

          *************
          * IMPORTANT *
          *************

If your application will run from flash memory, you should
initialize some additional registers to improve system
performance. For MPC551x devices, initialize the PFCRP0 and 
PFCRP1 registers; for other devices, initialize the BIUCR.

Please review the MPC5534 reference manual to determine 
appropriate values.

Sample code for the following language(s) is at your disposal:
- C


Other options may be available:

//------------------------------------------------------------------------
//  Getting Started
//------------------------------------------------------------------------
To build  your project, use the menu Project > Make or press F7.
This will build the selected target.

//------------------------------------------------------------------------
// Project structure
//------------------------------------------------------------------------
The project generated contains various files/groups:
- readme.txt: this file
- Sources: folder with the application source code
- Header Files: all application and runtime header files
- Startup Code: user customizable startup code 
- Lcf Files: the linker command files for the different build targets.
- Runtime: the libraries

//------------------------------------------------------------------------
//  Adding your own code
//------------------------------------------------------------------------
Once everything is working as expected, you can begin adding your own code
to the project. Keep in mind that we provide this as an example of how to
get up and running quickly with CodeWarrior. There are certainly other
ways to handle interrupts and set up your linker command file. Feel free
to modify any of the source files provided.

//------------------------------------------------------------------------
//  Additional documentation
//------------------------------------------------------------------------
Read the online documentation provided. From within the CodeWarrior IDE,
select Help > CodeWarrior Help.

//------------------------------------------------------------------------
//  Contacting Freescale
//------------------------------------------------------------------------
For bug reports, technical questions, and suggestions, please use the
forms installed in the Release_Notes folder and send them to:

cw_support@freescale.com

AETCOS 0.1 Alpha使用说明:
该版操作系统使用的任务调度内核为完全非抢占式,任务之间切换的事件较快,但任务实时性不强
(完全抢占式的也不怎么强).
调试模式的代码还未完成,故只能按照最终发布模式跑.
由于该操作系统为完全静态,所以任务和闹钟的建立比较麻烦.

任务的建立:
1.在Tasks.h中写任务所需的声明
2.在Tasks.c中按照OSEK格式用DeclareTask()声明任务
3.在Tasks.c中按照OSEK格式用TASK()写任务的实现
4.修改Os_Task_Cfg.h中Os_Tasks_Num宏的值为所有任务的总数
5.在紧跟Os_Tasks_Num宏后面的enum声明中按照优先级加入任务的名称
7.在Os_Task_Cfg.c中按优先级用_TASK()将任务添加到Os_Tasks[]数组的初始值中
8.在Os_Task_Cfg.c中按优先级用READY,WAITING,SUSPENDED初始化Os_Task_State[]数组,即初始化任务运行状态
9.在Os_Event_Cfg.h中用宏定义所需要的事件(32位)
10.在Os_Task_Cfg.c中配合Os_Task_State[]数组的初始值使用自定义的事件初始化Os_Task_Event[]数组

闹钟(Alarm)的建立:
1.在Os_Alarm_Cfg.h中修改AlarmNum宏的值为所有闹钟的总数
2.在Os_Alarm_Cfg.h中修改Timer0AlarmNm宏的值为所有使用Timer0(MPC5554时基)闹钟的总数
3.在紧跟Timer0AlarmNm宏后面的enum声明中加入闹钟的名称
4.在Alarms.h中写闹钟所需的声明
5.在Alarms.c中按照OSEK格式用DeclareAlarm()声明闹钟
6.在Alarms.c中按照OSEK格式用ALARMCALLBACK()写闹钟回调函数的实现
7.在Os_Alarm_Cfg.c中用闹钟的信息初始化AlarmInfos[]数组
	格式:
	闹钟执行模式(ALARMCALLBACKACTION,ALARMACTIVATETASK,ALARMSETTASKEVENT)
	闹钟回调函数(用_ALARMCALLBACK()声明,如果使用了的话)
	闹钟操作的任务(任务名,如果使用了的话)
	闹钟设置的事件(如果使用了的话)
	闹钟状态(RUNNING,SUSPENDED)
	闹钟循环节拍数
	闹钟当前倒数节拍
8.在Os_Alarm_Cfg.c中用闹钟所属定时器/计数器编号初始化AlarmTimer[]数组
9.在Os_Alarm_Cfg.c中用属于Timer0的闹钟名初始化Timer0Alarm[]数组

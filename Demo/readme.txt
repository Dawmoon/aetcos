//------------------------------------------------------------------------
//  Readme.txt����
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

AETCOS 0.1 Alphaʹ��˵��:
�ð����ϵͳʹ�õ���������ں�Ϊ��ȫ����ռʽ,����֮���л����¼��Ͽ�,������ʵʱ�Բ�ǿ
(��ȫ��ռʽ��Ҳ����ôǿ).
����ģʽ�Ĵ��뻹δ���,��ֻ�ܰ������շ���ģʽ��.
���ڸò���ϵͳΪ��ȫ��̬,������������ӵĽ����Ƚ��鷳.

����Ľ���:
1.��Tasks.h��д�������������
2.��Tasks.c�а���OSEK��ʽ��DeclareTask()��������
3.��Tasks.c�а���OSEK��ʽ��TASK()д�����ʵ��
4.�޸�Os_Task_Cfg.h��Os_Tasks_Num���ֵΪ�������������
5.�ڽ���Os_Tasks_Num������enum�����а������ȼ��������������
7.��Os_Task_Cfg.c�а����ȼ���_TASK()��������ӵ�Os_Tasks[]����ĳ�ʼֵ��
8.��Os_Task_Cfg.c�а����ȼ���READY,WAITING,SUSPENDED��ʼ��Os_Task_State[]����,����ʼ����������״̬
9.��Os_Event_Cfg.h���ú궨������Ҫ���¼�(32λ)
10.��Os_Task_Cfg.c�����Os_Task_State[]����ĳ�ʼֵʹ���Զ�����¼���ʼ��Os_Task_Event[]����

����(Alarm)�Ľ���:
1.��Os_Alarm_Cfg.h���޸�AlarmNum���ֵΪ�������ӵ�����
2.��Os_Alarm_Cfg.h���޸�Timer0AlarmNm���ֵΪ����ʹ��Timer0(MPC5554ʱ��)���ӵ�����
3.�ڽ���Timer0AlarmNm������enum�����м������ӵ�����
4.��Alarms.h��д�������������
5.��Alarms.c�а���OSEK��ʽ��DeclareAlarm()��������
6.��Alarms.c�а���OSEK��ʽ��ALARMCALLBACK()д���ӻص�������ʵ��
7.��Os_Alarm_Cfg.c�������ӵ���Ϣ��ʼ��AlarmInfos[]����
	��ʽ:
	����ִ��ģʽ(ALARMCALLBACKACTION,ALARMACTIVATETASK,ALARMSETTASKEVENT)
	���ӻص�����(��_ALARMCALLBACK()����,���ʹ���˵Ļ�)
	���Ӳ���������(������,���ʹ���˵Ļ�)
	�������õ��¼�(���ʹ���˵Ļ�)
	����״̬(RUNNING,SUSPENDED)
	����ѭ��������
	���ӵ�ǰ��������
8.��Os_Alarm_Cfg.c��������������ʱ��/��������ų�ʼ��AlarmTimer[]����
9.��Os_Alarm_Cfg.c��������Timer0����������ʼ��Timer0Alarm[]����

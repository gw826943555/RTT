/*
*********************************************************************************************************
*                                             uC/GUI V3.98
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
---Author-Explanation
* 
* 1.00.00 020519 JJL    First release of uC/GUI to uC/OS-II interface
* 
*
* Known problems or limitations with current version
*
*    None.
*
*
* Open issues
*
*    None
*********************************************************************************************************
*/

#include <rtthread.h>
#include "GUI_Private.H"
#include "stdio.H"

/*
*********************************************************************************************************
*                                         GLOBAL VARIABLES
*********************************************************************************************************
*/

static  rt_sem_t  	DispSem;
static  rt_sem_t  	EventSem;

static  rt_sem_t  	KeySem;
static  int        	KeyPressed;
static  char       	KeyIsInited;


/*
*********************************************************************************************************
*                                        TIMING FUNCTIONS
*
* Notes: Some timing dependent routines of uC/GUI require a GetTime and delay funtion. 
*        Default time unit (tick), normally is 1 ms.
*********************************************************************************************************
*/

int  GUI_X_GetTime (void) 
{
    return ((int)rt_tick_get());
}


void  GUI_X_Delay (int period) 
{
    rt_thread_delay(period);
}


/*
*********************************************************************************************************
*                                          GUI_X_ExecIdle()
*********************************************************************************************************
*/
void GUI_X_ExecIdle (void) 
{
    rt_thread_delay(1);
}


/*
*********************************************************************************************************
*                                    MULTITASKING INTERFACE FUNCTIONS
*
* Note(1): 1) The following routines are required only if uC/GUI is used in a true multi task environment, 
*             which means you have more than one thread using the uC/GUI API.  In this case the #define 
*             GUI_OS 1   needs to be in GUIConf.h
*********************************************************************************************************
*/

void  GUI_X_InitOS (void)
{ 
    DispSem   = rt_sem_create("DispSem",
															0,
															RT_IPC_FLAG_FIFO);
    EventSem = rt_sem_create("EventSem",
															0,
															RT_IPC_FLAG_FIFO);
		rt_sem_release(DispSem);
		rt_sem_release(EventSem);
}


void  GUI_X_Lock (void)
{ 
   rt_sem_take(DispSem, RT_WAITING_FOREVER);
}


void  GUI_X_Unlock (void)
{ 
    rt_sem_release(DispSem);
}


U32  GUI_X_GetTaskId (void) 
{ 
    return ((U32)rt_thread_self());
}

/*
*********************************************************************************************************
*                                        GUI_X_WaitEvent()
*                                        GUI_X_SignalEvent()
*********************************************************************************************************
*/


void GUI_X_WaitEvent (void) 
{
    rt_sem_take(EventSem, RT_WAITING_FOREVER);
}


void GUI_X_SignalEvent (void) 
{
    rt_sem_release(EventSem);
}

/*
*********************************************************************************************************
*                                      KEYBOARD INTERFACE FUNCTIONS
*
* Purpose: The keyboard routines are required only by some widgets.
*          If widgets are not used, they may be eliminated.
*
* Note(s): If uC/OS-II is used, characters typed into the log window will be placed	in the keyboard buffer. 
*          This is a neat feature which allows you to operate your target system without having to use or 
*          even to have a keyboard connected to it. (useful for demos !)
*********************************************************************************************************
*/

static  void  CheckInit (void) 
{
    if (KeyIsInited == RT_FALSE) {
        KeyIsInited = RT_TRUE;
        GUI_X_Init();
    }
}


void GUI_X_Init (void) 
{
    KeySem = rt_sem_create("KeySem", 0,RT_IPC_FLAG_FIFO);
		rt_sem_release(KeySem);
}


int  GUI_X_GetKey (void) 
{
    int r;


    r          = KeyPressed;
    CheckInit();
    KeyPressed = 0;
    return (r);
}


int  GUI_X_WaitKey (void) 
{
    int    r;
    CheckInit();
    if (KeyPressed == 0) {
        rt_sem_take(KeySem, RT_WAITING_FOREVER);
    }
    r          = KeyPressed;
    KeyPressed = 0;
    return (r);
}


void  GUI_X_StoreKey (int k) 
{
    KeyPressed = k;
    rt_sem_release(KeySem);
}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { ; }
void GUI_X_Warn    (const char *s) { ; }
void GUI_X_ErrorOut(const char *s) { ; }
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 

/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "includes.h"
#include "alt_ucosii_simple_error_check.h"

/* The following task is call regularly to determine if some potential system
 * integrity issues have occurred during a MicroC/OS-II system call.  If something
 * has occurred, the scheduling is turned off and the error handler is called.
 */
 

 
void alt_ucosii_check_return_code(INT8U return_code)
{
  if(return_code != OS_NO_ERR)
  {
    OSSchedLock();  /* Disable Task Switching but still service other IRQs */
    alt_ucosii_simple_error_handler(return_code);
    OSSchedUnlock(); /* Enable Task Switching */
  }
}
/*The following function is a generic error handler that doesn't actually do
 * proper error handling.  It's purpose is to simply alert the user that 
 * a MicroC/OS-II system call exited with some status other than "OK".  The 
 * current implementation terminates the program.  In a real application, there
 * should be some means to recover from errors from system calls.  This function
 * can be extended with additional inputs to produce a proper error handler that
 * controls the flow that is taken from different errors occurring at different 
 * locations in the application code.
 */

void alt_ucosii_simple_error_handler(INT8U return_code)
{
  printf("[Program Error]: See STDERR\n");
  switch (return_code) {
    case OS_PRIO_EXIST:
      fprintf(stderr, "Attempted to assign a task priority that is aready in use.\n");
      break;
    case OS_PRIO_INVALID:
      fprintf(stderr, "Specified a task priority higher than the allowed maximum.\n");
      fprintf(stderr, "Task can not be assigned a priority higher than %d\n",OS_LOWEST_PRIO);
      break;
    case OS_NO_MORE_TCB:
      fprintf(stderr, "Task Control Blocks have been exhausted\n");
      fprintf(stderr, "The current max number of task is %d\n",OS_MAX_TASKS);
      break;
    case OS_MBOX_FULL:
      fprintf(stderr, "Attempted a Post to a Mailbox that already contains a message\n");
      break;
    case OS_ERR_EVENT_TYPE:
      fprintf(stderr, "Attempted to access a resource that doesn't match the required data type\n");
      break;
    case OS_ERR_PEVENT_NULL:
      fprintf(stderr, "Attempting access a resource that is pointing to NULL\n");
      break;
    case OS_ERR_POST_NULL_PTR:
      fprintf(stderr, "Attempted to Post a NULL to a resource. \n");
      break;
    case OS_TIMEOUT:
      fprintf(stderr, "Resource not received in specified time\n");
      break;
    case OS_ERR_PEND_ISR:
      fprintf(stderr, "Attempting to pending for a resource in an ISR\n");
      break;
    case OS_TASK_DEL_IDLE:
      fprintf(stderr, "Attempted to delete the IDLE task\n");
      break;
    case OS_TASK_DEL_ERR:
      fprintf(stderr, "Attempted to delete a task that does not exist\n");
      break;
    case OS_TASK_DEL_ISR:
      fprintf(stderr, "Attempted to delete a task from an ISR\n");
      break;
    case OS_Q_FULL:
      fprintf(stderr, "Attempted to post to a full message queue\n");
      break;
    case OS_ERR_NOT_MUTEX_OWNER:
      fprintf(stderr, "Attempted to post a mutex that is not owned by the task\n");
      break;
    default:
      fprintf(stderr, "Unknown Error\n");
      break;
  }
  fprintf(stderr, "Program is terminating.\n");
  exit(0);
}

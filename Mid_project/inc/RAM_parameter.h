#ifndef RAM_H
#define RAM_H
#include "Log.h"

  /*macro*/
  #define TOP_N 5
  #define NAME_LEN    256
  #define READ_PROCESS             "/proc"
  #define READ_PROCESS_STATUS_RAM     "/proc/%d/status"
  #define READ_MEMORY_INFO        "/proc/meminfo"
  
  /*Struct*/    
  typedef struct {
      int pid;
      char name[NAME_LEN];
      unsigned long Memory_kb;
  } RAM_Process;

  /*Function user can use*/
  void RAM_INFO_CHECK();


#endif
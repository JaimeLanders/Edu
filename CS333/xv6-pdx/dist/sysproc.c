#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#ifdef PDX_XV6
#include "pdx-kernel.h"
#endif // PDX_XV6
#ifdef CS333_P2
#include "uproc.h"
#endif // CS333_P2

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      return -1;
    }
    sleep(&ticks, (struct spinlock *)0);
  }
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  xticks = ticks;
  return xticks;
}

#ifdef PDX_XV6
// Turn off the computer
int
sys_halt(void)
{
  cprintf("Shutting down ...\n");
  outw( 0x604, 0x0 | 0x2000);
  return 0;
}
#endif // PDX_XV6

#ifdef CS333_P1
int
sys_date(void)
{
  struct rtcdate *d;

  if(argptr(0, (void*)&d, sizeof(struct rtcdate)) < 0)
    return -1;
  else{
    cmostime(d);
    return 0;
  }
}
#endif // CS333_P1

#ifdef CS333_P2
uint
sys_getuid(void){
  uint uid;
  uid = getuid();
  return uid;
}

uint
sys_getgid(void){
  uint gid;
  gid = getgid();
  return gid;
}


uint
sys_getppid(void){
  uint ppid;
  ppid = getppid();
  return ppid;
}

int
sys_setuid(uint uid){
  int id;
  if (argint(0, &id) < 0)
    return -1;
  else{
    uid = id;

    if (id < 0 || id > 32767)
      return -1;
    else{
      return setuid(uid);
    }
  }
}

int
sys_setgid(uint gid){
  int id;

  if (argint(0, &id) < 0)
    return -1;
  else{
    gid = id;

    if (id < 0 || id > 32767)
      return -1;
    else{
      return setgid(gid);
    }
  }
}

int
sys_getprocs(void){

  struct uproc * table;
  int max = 0;

  if (argint(0, &max) < 0 || (argptr(1, (void*)&table, max) < 0)){
    return -1;
  }
  else{
    return getprocs(max, table);
  }
}

#endif // CS333_P2

#ifdef CS333_P4
uint
sys_getpriority(int pid){
//sys_getpriority(void){
//  cprintf("\nsys_getpriority\n"); // DEBUG
  int priority = 0;
  int id;
  if (argint(0, &id) < 0) {
    priority = -1;
  }
  else{
//    cprintf("id = %d\n", id); // DEBUG
    pid = id;
//    cprintf("pid = %d\n", pid); // DEBUG
    priority = getpriority(pid);
  }
//  cprintf("\nsys_getpriority return = %d\n", priority); // DEBUG
  return priority;
}

uint
sys_setpriority(int pid, int priority){
//  cprintf("\nsys_setpriority\n"); // DEBUG
//  int priority = 0;
  int id;
  int prio;
  int rc;
  if ((argint(0, &id) < 0) || (argint(1, &prio) < 0)) {
    return -1;
  }
  else{
//    cprintf("id = %d\n", id); // DEBUG
//    cprintf("prio = %d\n", prio); // DEBUG
    pid = id;
    rc = setpriority(pid, prio);
//    priority = setpriority(pid, prio);
  }
//  cprintf("priority return = %d\n", priority); // DEBUG
//  return priority;
//  cprintf("\nsys_setpriority rc = %d\n", rc); // DEBUG
  return rc;
}
#endif // CS333_P4

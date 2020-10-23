#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/* Depending on user value, returns:
 * 1. count of proceses in the system
 * 2. count of the total number of system calls that the current process has made so far
 * 3. number of memory pages the current process is using
 *
*/
int
sys_info(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  return info(n);
}

// Print function to demonstrate info(1) functionality
int
sys_print_proc(void)
{
  return print_proc();
}

// Growproc function to demonstrate info(3) functionality
int
sys_growproc(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  growproc(n * PGSIZE);
  return 0;
} 

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#if CS333_P2
#include "uproc.h"
#endif // CS333_P2
#if CS333_P3
//#define DEBUG // Comment to turn off
#endif // CS333_P3

static char *states[] = {
[UNUSED]    "unused",
[EMBRYO]    "embryo",
[SLEEPING]  "sleep ",
[RUNNABLE]  "runble",
[RUNNING]   "run   ",
[ZOMBIE]    "zombie"
};

#ifdef CS333_P3
#define statecount NELEM(states)
#endif // CS333_P3

#ifdef CS333_P3
struct ptrs {
    struct proc* head;
    struct proc* tail;
};
#endif // CS333_P3

static struct {
  struct spinlock lock;
  struct proc proc[NPROC];
#ifdef CS333_P3
  struct ptrs list[statecount];
#endif // CS333_P3
#ifdef CS333_P4
  struct ptrs ready[MAXPRIO + 1];
  uint PromoteAtTime;
#endif // CS333_P4
} ptable;

static struct proc *initproc;

uint nextpid = 1;
extern void forkret(void);
extern void trapret(void);
static void wakeup1(void* chan);
#ifdef CS333_P3
static void initProcessLists(void);
static void initFreeList(void);
static void assertState(struct proc *, enum procstate);
static void stateListAdd(struct ptrs*, struct proc*);
static int stateListRemove(struct ptrs*, struct proc* p);
void printListStats(void);
// prototypes
#ifdef DEBUG
static void checkProcs(const char *, const char *, int);
#endif // DEBUG
#endif // CS333_P3
#ifdef CS333_P4
static void assertPriority(struct proc *, uint);
#endif // CS333_P4

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// Must be called with interrupts disabled
int
cpuid() {
  return mycpu()-cpus;
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;

  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");

  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid) {
      return &cpus[i];
    }
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
#ifdef CS333_P3
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;
//  int found = 0;

  // Aquire ptable lock
  acquire(&ptable.lock);

  // O(1) replacement
  p = ptable.list[UNUSED].head;
  if(p == NULL){
    release(&ptable.lock);
    return 0;
  }

  // Remove process from list
  int rc = (stateListRemove(&ptable.list[p->state], p));
  if (rc != 0){
    panic("\nProcess could not be removed from UNUSED list\n");
  }else{
    // Assert that the process was in the correct state
    assertState(p, UNUSED);

    // Update the process
    p->state = EMBRYO;
    p->pid = nextpid++;
#ifdef CS333_P4
    p->priority = MAXPRIO;
    p->budget = DEFAULT_BUDGET;
#endif

    // Put on new list
    stateListAdd(&ptable.list[p->state], p);

  }
  // Release the ptable lock
  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    acquire(&ptable.lock);
    int rc = (stateListRemove(&ptable.list[p->state], p));
    if (rc != 0){
      panic("\nProcess could not be removed from EMBRYO list\n");
    }else{
      assertState(p, EMBRYO);
      p->state = UNUSED;
      stateListAdd(&ptable.list[p->state], p);
      release(&ptable.lock);
      return 0;
    }
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  p->start_ticks = ticks;
  p->cpu_ticks_total = 0;
  p->cpu_ticks_in = 0;

  return p;
}
#else
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);
  int found = 0;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED) {
      found = 1;
      break;
    }
  if (!found) {
    release(&ptable.lock);
    return 0;
  }
  p->state = EMBRYO;
  p->pid = nextpid++;
  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  #ifdef CS333_P1
    p->start_ticks = ticks;
  #endif // CS333_P1

  #ifdef CS333_P2
    p->cpu_ticks_total = 0;
    p->cpu_ticks_in = 0;
  #endif // CS333_P2

  return p;
}
#endif // CS333_P3

//PAGEBREAK: 32
// Set up first user process.
#ifdef CS333_P3
void
userinit(void)
{
  // Initialize ptable state lists
  initProcessLists();
  initFreeList();

#ifdef CS333_P4
  acquire(&ptable.lock);
  ptable.PromoteAtTime = ticks + TICKS_TO_PROMOTE;
  release(&ptable.lock);
#endif // CS333_P4

  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();

  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.

  // Acquire ptable lock
  acquire(&ptable.lock);

  // Remove process from list
  int rc = (stateListRemove(&ptable.list[p->state], p));
  if (rc != 0){
    panic("\nProcess could not be removed from EMBRYO list\n");
  }else{
    //Assert that the process was in the correct state
    assertState(p, EMBRYO); // Infinite loops

    // Update the process
    p->state = RUNNABLE;
    p->uid = 0;
    p->gid = 0;
#ifdef CS333_P4
    // Put on RUNNABLE list
    stateListAdd(&ptable.ready[p->priority], p);
#else
    stateListAdd(&ptable.list[p->state], p);
#endif // CS333_P4
  }

  // Release ptable lock
  release(&ptable.lock);

}
#else
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();

  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);
  p->state = RUNNABLE;
  release(&ptable.lock);
#ifdef CS333_P2
  p->uid = 0;
  p->gid = 0;
#endif // CS333_P2
}
#endif // CS333_P$

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
#ifdef CS333_P3
int
fork(void)
{
  int i;
  uint pid;
  struct proc *np;
  struct proc *curproc = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;

    // Acquire ptable lock
    acquire(&ptable.lock);

    // Remove process from list
    int rc = stateListRemove(&ptable.list[np->state], np);
    if(rc != 0) {
      panic("\nProcess could not be removed from EMBRYO list\n");
    } else {
      // Assert that the process was in the correct state
      assertState(np, EMBRYO);

      // Update the process
      np->state = UNUSED;

      // Put on new list
      stateListAdd(&ptable.list[np->state], np);
    }

    release(&ptable.lock);
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));
  pid = np->pid;

  // Acquire ptable lock
  acquire(&ptable.lock);

  // Remove process from list
  int rc = stateListRemove(&ptable.list[np->state], np);
  if (rc != 0){
    panic("\nProcess could not be removed from EMBRYO list\n");
  } else {
    // Assert that the process was in the correct state
    assertState(np, EMBRYO);

    // Update the process
    np->state = RUNNABLE;
    np->uid = curproc->uid;
    np->gid = curproc->gid;
#ifdef CS333_P4
    // Put on new list
    stateListAdd(&ptable.ready[np->priority], np);
#else
    stateListAdd(&ptable.list[np->state], np);
#endif // CS333_P4
  }
  // Release ptable lock
  release(&ptable.lock);

  return pid;
}
#else
int
fork(void)
{
  int i;
  uint pid;
  struct proc *np;
  struct proc *curproc = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);
  np->state = RUNNABLE;
  release(&ptable.lock);

#ifdef CS333_P2
  np->uid = curproc->uid;
  np->gid = curproc->gid;
#endif // CS333_P2

  return pid;
}
#endif // CS333_P3

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
#ifdef CS333_P3
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  // Acquire ptable lock
  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for (int i = EMBRYO; i <= ZOMBIE; i++){
    p = ptable.list[i].head;
    while (p != NULL){
      if(p->parent == curproc){
        p->parent = initproc;

        if(p->state == ZOMBIE){
          wakeup1(initproc);
        }
      }
      p = p->next;
    }
  }

  // Remove process from list
  int rc = (stateListRemove(&ptable.list[curproc->state], curproc));
  if (rc != 0)
    panic("\nCould not remove process from RUNNING list\n");
  else{
    // Assert that process wass in the correct state
    assertState(curproc, RUNNING);

    // Update the process
    curproc->state = ZOMBIE;

    //Put on new list
    stateListAdd(&ptable.list[curproc->state], curproc);

    // Jump into the scheduler, never to return.
    sched();
    panic("zombie exit");
  }
}
#else
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == curproc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}
#endif

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
#ifdef CS333_P4
int
wait(void)
{
  struct proc *p;
  int havekids;
  int priority;
  uint pid;
  struct proc *curproc = myproc();

  // Acquire ptable lock
  acquire(&ptable.lock);
  for(;;) {
    // Scan through list looking for exited children.
    havekids = 0;
    priority = 0;
    for (int i = EMBRYO; i <= ZOMBIE; i++) {
      if (i == RUNNABLE) {
        for (int j = MAXPRIO; j >= 0; --j) {
          p = ptable.ready[j].head;
          while (p != NULL) {
            if (p->parent == curproc) {
              havekids = 1;
              priority = j;
              break;
            }
            p = p->next;
          }
        }
      } else {
        p = ptable.list[i].head;
        while (p != NULL) {
          if (p->parent == curproc) {
            havekids = 1;
            break;
          }
          p = p->next;
        }
      }
      if (havekids == 1) {
        if (p->state == ZOMBIE) {
          // Found one.

          // Remove process from list
          int rc = 0;
          if (i == RUNNABLE){
            rc = (stateListRemove(&ptable.ready[p->priority], p));
            assertPriority(p, priority);
          }
          else
            rc = (stateListRemove(&ptable.list[i], p));
          if (rc != 0) {
            panic("\nProcess could not be removed from its list\n");
          }else{
            // Assert that the process was in the correct state
            assertState(p, ZOMBIE);

            // Update process
            pid = p->pid;
            kfree(p->kstack);
            p->kstack = 0;
            freevm(p->pgdir);
            p->pid = 0;
            p->parent = 0;
            p->name[0] = 0;
            p->killed = 0;
            p->state = UNUSED;

            // Put on new list
            stateListAdd(&ptable.list[p->state], p);

            // Release ptable lock
            release(&ptable.lock);

            return pid;
          }
        }
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}
#elif defined (CS333_P3)
int
wait(void)
{
  struct proc *p;
  int havekids;
  uint pid;
  struct proc *curproc = myproc();

  // Acquire ptable lock
  acquire(&ptable.lock);
  for(;;){
    // Scan through list looking for exited children.
    havekids = 0;
    for(int i = EMBRYO; i <= ZOMBIE; i++){
      for(p = ptable.list[i].head; p != NULL; p = p->next){
        if(p->parent != curproc)
          continue;
        havekids = 1;

        if(p->state == ZOMBIE){
          // Found one.

          // Remove process from list
          int rc = (stateListRemove(&ptable.list[i], p));
          if (rc != 0){
            panic("\nProcess could not be removed from its list\n");
          }else{
            // Assert that the process was in the correct state
            assertState(p, ZOMBIE);

            // Update process
            pid = p->pid;
            kfree(p->kstack);
            p->kstack = 0;
            freevm(p->pgdir);
            p->pid = 0;
            p->parent = 0;
            p->name[0] = 0;
            p->killed = 0;
            p->state = UNUSED;

            // Put on new list
            stateListAdd(&ptable.list[p->state], p);

            // Release ptable lock
            release(&ptable.lock);

            return pid;
          }
        }
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}
#else
int
wait(void)
{
  struct proc *p;
  int havekids;
  uint pid;
  struct proc *curproc = myproc();

  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}
#endif // CS333_PX

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
#ifdef CS333_P3
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
#ifdef PDX_XV6
  int idle;  // for checking if processor is idle
#endif // PDX_XV6

  for(;;){
    // Enable interrupts on this processor.
    sti();

#ifdef PDX_XV6
    idle = 1;  // assume idle unless we schedule a process
#endif // PDX_XV6

    // Acquire ptable lock
    acquire(&ptable.lock);

#ifdef CS333_P4
    if(ticks == ptable.PromoteAtTime){
      for(int i = SLEEPING; i <= RUNNING; ++i) {
        if (i == RUNNABLE){
          for (int j = MAXPRIO; j >= 0 ; --j){
            p = ptable.ready[j].head;
            while (p != NULL){
              if(p->priority < MAXPRIO){
                int  rc = (stateListRemove(&ptable.ready[p->priority], p));
                if (rc != 0) {
                  panic("\nCould not remove process from the ready list\n");
                } else {
                  // Assert that the process was in the correct state
                  assertState(p, RUNNABLE);
                  assertPriority(p, j);
                  // Update the process
                  p->priority += 1;
                  p->budget = DEFAULT_BUDGET;
                  // Put on new list
                  stateListAdd(&ptable.ready[p->priority], p);
                }
              }
              p = p->next;
            }
          }
        } else {
          p = ptable.list[i].head;
          while (p != NULL){
            if(p->priority < MAXPRIO){
              p->priority += 1;
              p->budget = DEFAULT_BUDGET;
            }
            p = p->next;
          }
        }
      }
      ptable.PromoteAtTime = ticks + TICKS_TO_PROMOTE;
    }
#endif // CS333_P4
    // Release ptable lock
    release(&ptable.lock);

    // Acquire ptable lock
    acquire(&ptable.lock);

    // Loop over runnable list looking for process to run.
#ifdef CS333_P4
    int prio = 0;
    for(int i = MAXPRIO; i >= 0; --i)
    {
      p = ptable.ready[i].head;
      if (p != NULL){
        prio = i;
        break;
      }
    }
#else
    p = ptable.list[RUNNABLE].head;
#endif // CS333_P4
    if (p != NULL){
      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
#ifdef PDX_XV6
      idle = 0;  // not idle this timeslice
#endif // PDX_XV6

      c->proc = p;
      switchuvm(p);

      // Remove the process from the list
#ifdef CS333_P4
      int rc = stateListRemove(&ptable.ready[p->priority], p);
#else
      int rc = stateListRemove(&ptable.list[p->state], p);
#endif // CS333_P4
      if (rc != 0){
        panic("Could not remove process from RUNNABLE list \n");
      } else {
        // Assert that process was the correct state
        assertState(p, RUNNABLE);
#ifdef CS333_P4
        assertPriority(p, prio);
#endif // CS333_P4

        // Update the process
        p->cpu_ticks_in = ticks;
        p->state = RUNNING;

        // Add process to the list
        stateListAdd(&ptable.list[p->state], p);

        swtch(&(c->scheduler), p->context);
        switchkvm();

        // Process is done running for now.
        // It should have changed its p->state before coming back.
        c->proc = 0;
      }
    }
    // Release ptable lock
    release(&ptable.lock);
#ifdef PDX_XV6
    // if idle, wait for next interrupt
    if (idle) {
      sti();
      hlt();
    }
#endif // PDX_XV6
  }
}
#else
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
#ifdef PDX_XV6
  int idle;  // for checking if processor is idle
#endif // PDX_XV6

  for(;;){
    // Enable interrupts on this processor.
    sti();

#ifdef PDX_XV6
    idle = 1;  // assume idle unless we schedule a process
#endif // PDX_XV6
    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
#ifdef PDX_XV6
      idle = 0;  // not idle this timeslice
#endif // PDX_XV6
#ifdef CS333_P2
      p->cpu_ticks_in = ticks;
#endif // CS333_P2
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;
      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }
    release(&ptable.lock);
#ifdef PDX_XV6
    // if idle, wait for next interrupt
    if (idle) {
      sti();
      hlt();
    }
#endif // PDX_XV6
  }
}
#endif // CS333_P3

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
#ifdef CS333_P2
  p->cpu_ticks_total += ticks - p->cpu_ticks_in;
#endif // CS333_P2
#ifdef CS333_P4
    p->budget = p->budget - (ticks - p->cpu_ticks_in);
#endif // CS333_P4
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
#ifdef CS333_P3
void
yield(void)
{
  struct proc *curproc = myproc();

  // Acquire ptable lock
  acquire(&ptable.lock);  //DOC: yieldlock

  // Remove the process from list
  int rc = stateListRemove(&ptable.list[curproc->state], curproc);
  if (rc != 0){
    panic("Could not remove process from Sleeping list\n");
  } else {
    // Assert that the process was in the correct state
    assertState(curproc, RUNNING);

    // Update the process
    curproc->state = RUNNABLE;
#ifdef CS333_P4
    if(curproc->budget <= 0) {
      if(curproc->priority > 0) {
        curproc->priority -= 1;
      }
      curproc->budget = DEFAULT_BUDGET;
    }

    // Put on new list
    stateListAdd(&ptable.ready[curproc->priority], curproc);
#else
    stateListAdd(&ptable.list[curproc->state], curproc);
#endif // CS333_P4
    sched();
  }

  // Release ptable lock
  release(&ptable.lock);
}
#else
void
yield(void)
{
  struct proc *curproc = myproc();

  acquire(&ptable.lock);  //DOC: yieldlock
  curproc->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}
#endif //CS333_P3

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
#ifdef CS333_P3
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();

  if(p == 0)
    panic("sleep");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    if (lk) release(lk);
  }

#ifdef CS333_P4
    if(p->budget <= 0) {
      if(p->priority > 0) {
        p->priority -= 1;
      }
      p->budget = DEFAULT_BUDGET;
    }
#endif // CS333_P4
  // Remove process from the list
  int rc = stateListRemove(&ptable.list[p->state], p);
  if (rc != 0){
    panic("Could not remove from RUNNING list\n");
  }else{
    // Assert that the process was in the correct state
    assertState(p, RUNNING);

    // Update the process
    // Go to sleep.
    p->chan = chan;
    p->state = SLEEPING;

    // Add process to the list
    stateListAdd(&ptable.list[p->state], p);

    sched();

    // Tidy up.
    p->chan = 0;
  }

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    if (lk) acquire(lk);
  }
}
#else
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();

  if(p == 0)
    panic("sleep");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    if (lk) release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    if (lk) acquire(lk);
  }
}
#endif // CS333_P3

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
#ifdef CS333_P3
static void
wakeup1(void *chan)
{
  struct proc *p;
  p = ptable.list[SLEEPING].head;
  while (p != NULL){
    if(p->state == SLEEPING && p->chan == chan) {

      // Remove process from list
      int rc = stateListRemove(&ptable.list[p->state], p);
      if(rc != 0){
        panic("\nCould not remove process from SLEEPING list\n");
      } else {
        // Assert that the process was in the correct state
        assertState(p, SLEEPING);

        // Update the proces
        p->state = RUNNABLE;

        // Put on new list
#ifdef CS333_P4
        stateListAdd(&ptable.ready[p->priority], p);
#else
        stateListAdd(&ptable.list[p->state], p);
#endif // CS333_P4
      }
    }
    p = p->next;
  }
}
#else
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}
#endif // CS333_P3

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
#ifdef CS333_P4
int
kill(int pid)
{
  struct proc *p;

  // Acquire ptable lock
  acquire(&ptable.lock);
  for (int i = EMBRYO; i <= ZOMBIE; i++) {
    if (i == RUNNABLE) {
      for (int j = MAXPRIO; j >= 0; --j) {
        p = ptable.ready[j].head;
        while (p != NULL){
          if(p->pid == pid) {
            p->killed = 1;

            // Release ptable lock
            release(&ptable.lock);

            return 0;
          }
          p = p->next;
        }
      }
    } else {
      p = ptable.list[i].head;
      while (p != NULL) {
        if (p->pid == pid) {
          p->killed = 1;

          // Wake process from sleep if necessary.
          if (p->state == SLEEPING) {
            // Remove process from list
            int rc = stateListRemove(&ptable.list[p->state], p);
            if (rc != 0) {
              panic("Could not remove process from SLEEPING list\n" );
            } else {
              // Assert that the process was in the correct state
              assertState(p, SLEEPING);

              //Update the process
              p->state = RUNNABLE;

              // Put on new list
              stateListAdd(&ptable.ready[p->priority], p);
            }
          }
          // Release ptable lock
          release(&ptable.lock);

          return 0;
        }
        p = p->next;
      }
    }
  }

  // Release ptable lock
  release(&ptable.lock);

  return -1;
}
#elif defined (CS333_P3)
int
kill(int pid)
{
  struct proc *p;

  // Acquire ptable lock
  acquire(&ptable.lock);
  for(int i = EMBRYO; i <= ZOMBIE; i++) {
    for(p = ptable.list[i].head; p != NULL; p = p->next){
      if(p->pid == pid){
        p->killed = 1;

        // Wake process from sleep if necessary.
        if(p->state == SLEEPING){
          // Remove process from list
          int rc = stateListRemove(&ptable.list[p->state], p);
          if (rc != 0){
            panic("Could not remove process from SLEEPING list\n" );
          } else {
            // Assert that the process was in the correct state
            assertState(p, SLEEPING);

            //Update the process
            p->state = RUNNABLE;

            // Put on new list
            stateListAdd(&ptable.list[p->state], p);
          }
        }
        // Release ptable lock
        release(&ptable.lock);

        return 0;
      }
    }
  }

  // Release ptable lock
  release(&ptable.lock);

  return -1;
}
#else
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}
#endif // CS333_PX

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.

#if defined(CS333_P1)
void
procdumpP1(struct proc *p, char *state)
{
  cprintf("%d\t", p->pid);
  if(strlen(p->name) <= 8)
    cprintf("%s\t\t", p->name);
  else
    cprintf("%s\t", p->name);
  if((ticks - p->start_ticks) % 1000 >= 100)
    cprintf("%d.%d\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  else if((ticks - p->start_ticks) % 1000 >= 10)
    cprintf("%d.%d0\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  else
    cprintf("%d.%d00\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  if (strlen(state) >= 5)
    cprintf("    %s\t", state);
  else
    cprintf("    %s\t\t", state);
  cprintf("%d\t", p->sz);
}
#endif // CS333_P1

#if defined(CS333_P2)
void
procdumpP2(struct proc *p, char *state)
{
  cprintf("%d\t", p->pid);
  if(strlen(p->name) <= 8)
    cprintf("%s\t\t", p->name);
  else
    cprintf("%s\t", p->name);
  cprintf("%d\t", p->uid);
  cprintf("%d\t", p->gid);
  if(p->parent == NULL)
    cprintf("%d\t", p->pid);
  else
    cprintf("%d\t", p->parent->pid);
  if((ticks - p->start_ticks) % 1000 >= 100)
    cprintf("%d.%d\t\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  else if((ticks - p->start_ticks) % 1000 >= 10)
    cprintf("%d.%d0\t\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  else
    cprintf("%d.%d00\t\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  if(p->cpu_ticks_total % 1000 >= 100)
    cprintf("%d.%d\t",(p->cpu_ticks_total)/1000, (p->cpu_ticks_total)%1000);
  else if(p->cpu_ticks_total % 1000 >= 10)
    cprintf("%d.%d0\t",(p->cpu_ticks_total)/1000, (p->cpu_ticks_total)%1000);
  else
    cprintf("%d.%d00\t",(p->cpu_ticks_total)/1000, (p->cpu_ticks_total)%1000);
  if (strlen(state) >= 5)
    cprintf("    %s\t", state);
  else
    cprintf("    %s\t\t", state);
  cprintf("%d\t", p->sz);
}
#endif // CS333_P2

#if defined(CS333_P4)
void
procdumpP4(struct proc *p, char *state)
{
  cprintf("%d\t", p->pid);
  if(strlen(p->name) <= 8)
    cprintf("%s\t\t", p->name);
  else
    cprintf("%s\t", p->name);
  cprintf("%d\t", p->uid);
  cprintf("%d\t", p->gid);
  if(p->parent == NULL)
    cprintf("%d\t", p->pid);
  else
    cprintf("%d\t", p->parent->pid);
  cprintf("%d\t", p->priority);
  if((ticks - p->start_ticks) % 1000 >= 100)
    cprintf("%d.%d\t\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  else if((ticks - p->start_ticks) % 1000 >= 10)
    cprintf("%d.%d0\t\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  else
    cprintf("%d.%d00\t\t",(ticks - p->start_ticks)/1000, (ticks - p->start_ticks)%1000);
  if(p->cpu_ticks_total % 1000 >= 100)
    cprintf("%d.%d\t",(p->cpu_ticks_total)/1000, (p->cpu_ticks_total)%1000);
  else if(p->cpu_ticks_total % 1000 >= 10)
    cprintf("%d.%d0\t",(p->cpu_ticks_total)/1000, (p->cpu_ticks_total)%1000);
  else
    cprintf("%d.%d00\t",(p->cpu_ticks_total)/1000, (p->cpu_ticks_total)%1000);
  if (strlen(state) >= 5)
    cprintf("    %s\t", state);
  else
    cprintf("    %s\t\t", state);
  cprintf("%d\t", p->sz);
}
#endif // CS333_P4

void
procdump(void)
{
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

#if defined(CS333_P4)
#define HEADER "\nPID\tName\t\tUID\tGID\tPPID\tPrio\tElapsed\t\tCPU\t    State\tSize \t PCs\n"
#elif defined(CS333_P2)
#define HEADER "\nPID\tName\t\tUID\tGID\tPPID\tElapsed\t\tCPU\t    State\tSize \t PCs\n"
#elif defined(CS333_P1)
#define HEADER "\nPID\tName\t\tElapsed\t    State\tSize\t PCs\n"
#else
#define HEADER "\n"
#endif // CS333_Px

  cprintf(HEADER);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
#if defined(CS333_P4)
      procdumpP4(p, state);
#elif defined(CS333_P2)
      procdumpP2(p, state);
#elif defined(CS333_P1)
      procdumpP1(p, state);
#else
    cprintf("%d\t%s\t%s\t", p->pid, p->name, state);
#endif // CS333_Px

    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
  cprintf("$ ");
}

#if defined(CS333_P2)
uint
getuid(void){
  int uid;

  acquire(&ptable.lock);
  uid = myproc()->uid;
  release(&ptable.lock);

  return uid;
}

uint
getgid(void){
  int gid;

  acquire(&ptable.lock);
  gid = myproc()->gid;
  release(&ptable.lock);

  return gid;
}

uint
getppid(void){
  int ppid;

  acquire(&ptable.lock);

  if(myproc()->pid != 1)
    ppid = myproc()->parent->pid;
  else
    ppid = myproc()->pid;

  release(&ptable.lock);

  return ppid;
}

int
setuid(uint uid){
  acquire(&ptable.lock);
  myproc()->uid = uid;
  release(&ptable.lock);

  return 0;
}

int
setgid(uint gid){
  acquire(&ptable.lock);
  myproc()->gid = gid;
  release(&ptable.lock);

  return 0;
}

int
getprocs(uint max, struct uproc* table)
{
  struct proc *p;
  int nProc = 0;
#define STRMAX 32

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC] && nProc < max; p++){
    if(p->state != EMBRYO && p->state != UNUSED && nProc < max){

      table[nProc].pid = p->pid;
      table[nProc].uid = p->uid;
      table[nProc].gid = p->gid;

      if(p->parent != NULL)
        table[nProc].ppid = p->parent->pid;
      else
        table[nProc].ppid = p->pid;

#if defined(CS333_P4)
      table[nProc].priority = p->priority;
#endif // CS333_P4

      table[nProc].elapsed_ticks = ticks - p->start_ticks;
      table[nProc].CPU_total_ticks = p->cpu_ticks_total;

      if(p->state == RUNNABLE)
        safestrcpy(table[nProc].state, "runble", STRMAX);
      else if(p->state == SLEEPING)
        safestrcpy(table[nProc].state, "sleep", STRMAX);
      else if(p->state == RUNNING)
        safestrcpy(table[nProc].state, "run", STRMAX);
      else if(p->state == ZOMBIE)
        safestrcpy(table[nProc].state, "zombie", STRMAX);
      else
        safestrcpy(table[nProc].state, "unknown", STRMAX);

      table[nProc].size = p->sz;
      safestrcpy(table[nProc].name, p->name, sizeof(p->name));

      nProc += 1;
    }
  }

  release(&ptable.lock);

  return nProc;
}
#endif // CS333_P2

#ifdef CS333_P3
// list management helper functions
static void
stateListAdd(struct ptrs* list, struct proc* p)
{
  if((*list).head == NULL){
    (*list).head = p;
    (*list).tail = p;
    p->next = NULL;
  } else{
    ((*list).tail)->next = p;
    (*list).tail = ((*list).tail)->next;
    ((*list).tail)->next = NULL;
  }
}

static int
stateListRemove(struct ptrs* list, struct proc* p)
{
  if((*list).head == NULL || (*list).tail == NULL || p == NULL){
    return -1;
  }

  struct proc* current = (*list).head;
  struct proc* previous = 0;

  if(current == p){
    (*list).head = ((*list).head)->next;
    // prevent tail remaining assigned when we've removed the only item
    // on the list
    if((*list).tail == p){
      (*list).tail = NULL;
    }
    return 0;
  }

  while(current){
    if(current == p){
      break;
    }

    previous = current;
    current = current->next;
  }

  // Process not found. return error
  if(current == NULL){
    return -1;
  }

  // Process found.
  if(current == (*list).tail){
    (*list).tail = previous;
    ((*list).tail)->next = NULL;
  } else{
    previous->next = current->next;
  }

  // Make sure p->next doesn't point into the list.
  p->next = NULL;

  return 0;
}

static void
initProcessLists()
{
  int i;

  for (i = UNUSED; i <= ZOMBIE; i++) {
    ptable.list[i].head = NULL;
    ptable.list[i].tail = NULL;
  }
#ifdef CS333_P4
  for (i = 0; i <= MAXPRIO; i++) {
    ptable.ready[i].head = NULL;
    ptable.ready[i].tail = NULL;
  }
#endif
}

static void
initFreeList(void)
{
  struct proc* p;

  for(p = ptable.proc; p < ptable.proc + NPROC; ++p){
    p->state = UNUSED;
    stateListAdd(&ptable.list[UNUSED], p);
  }
}

static void assertState(struct proc * p, enum procstate state){
  if(p->state != state){
    if(state == EMBRYO)
      panic("\nProcess state was not EMBRYO\n");
    else if(state == RUNNABLE)
      panic("\nProcess state was not RUNNABLE\n");
    else if(state == RUNNING)
      panic("\nProcess state was not RUNNING\n");
    else if(state == SLEEPING)
      panic("\nProcess state was not SLEEPING\n");
    else if(state == UNUSED)
      panic("\nProcess state was not UNUSED\n");
    else if(state == ZOMBIE)
      panic("\nProcess state was not ZOMBIE\n");
    else
      panic("\nProcess state was UNKNOWN\n");
  }
}

// Some debug code for projects 3 and 4
// Verify that all processes exist on at least one state list.
// example usage
/*
#ifdef DEBUG
  checkProcs(__FILE__, __FUNCTION__, __LINE__);
#endif // DEBUG
*/

// debug routines
#ifdef DEBUG
static int
procLookup(struct proc *p, struct proc *np)
{
  while (np != NULL) {
    if (np == p) return 1;
    np = np->next;
  }
  return 0;
}

static int
findProc(struct proc *p)
{
  if (procLookup(p, ptable.list[UNUSED].head)   != 0) return 1;
  if (procLookup(p, ptable.list[EMBRYO].head)   != 0) return 1;
  if (procLookup(p, ptable.list[RUNNING].head)  != 0) return 1;
  if (procLookup(p, ptable.list[SLEEPING].head) != 0) return 1;
  if (procLookup(p, ptable.list[ZOMBIE].head)   != 0) return 1;
#ifdef CS333_P4
  for (int i=0; i<=MAXPRIO; i++) // P4
    if (procLookup(p, ptable.ready[i].head) != 0) return 1;
#endif // CS333_P4
  return 0; // not found
}

static void
checkProcs(const char *file, const char *func, int line)
{
  int found;
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    found = findProc(p);
    if (found) continue;
    cprintf("checkprocs error. Called from %s, %s, @ %d\n", file, func, line);
    panic("Process array and lists inconsistent\n");
  }
}

#endif // DEBUG

// from MM's xv6 P3 implementation. Linked to control-l in
// console.c
void
printListStats(void)
{
  int i, count, total = 0;
  struct proc *p;

  acquire(&ptable.lock);
  for (i=UNUSED; i<=ZOMBIE; i++) {
    count = 0;
    p = ptable.list[i].head;
    if (p != NULL){
      while (p != NULL) {
        count++;
        p = p->next;
      }
    }
    cprintf("\n%s list has ", states[i]);
    if (count < 10) cprintf(" ");  // line up columns
    cprintf("%d processes", count);
    total += count;
  }
  release(&ptable.lock);
  cprintf("\nTotal on lists is: %d. NPROC = %d. %s",
      total, NPROC, (total == NPROC) ? "Congratulations!" : "Bummer");
  cprintf("\n$ ");  // simulate shell prompt
  return;
}

void
ctrlf(void){
  struct proc * p;
  int nProc = 0;

  for(p = ptable.list[UNUSED].head; p != NULL; p = p->next){
    nProc += 1;
  }

  cprintf("\nFree List Size: %d processes \n", nProc);
  cprintf("\n$ ");  // simulate shell prompt
  return;
}

void
ctrlr(void){
  struct proc * p;

  cprintf("\nReady List Processes:\n");
#ifdef CS333_P4
  for(int i = MAXPRIO; i >= 0; --i){
    p = ptable.ready[i].head;
    while (p != NULL){
      if(p->next != NULL)
        cprintf("(%d, %d) -> ", p->pid, p->budget);
      else
        cprintf("(%d, %d)\n", p->pid, p->budget);
      p = p->next;
    }
  }
#else
  for(p = ptable.list[RUNNABLE].head; p != NULL; p = p->next){
    if(p->next != NULL)
      cprintf("%d -> ", p->pid);
    else
      cprintf("%d\n", p->pid);
  }
#endif
  cprintf("\n$ ");  // simulate shell prompt
  return;
}

void
ctrls(void){
  struct proc * p;

  cprintf("\nSleep List Processes:\n");
  for(p = ptable.list[SLEEPING].head; p != NULL; p = p->next){
    if(p->next != NULL)
      cprintf("%d -> ", p->pid);
    else
      cprintf("%d\n", p->pid);
  }
  cprintf("\n$ ");  // simulate shell prompt
  return;
}

void
ctrlz(void){
  struct proc * p;

  cprintf("\nZombie List Processes:\n");
  for(p = ptable.list[ZOMBIE].head; p != NULL; p = p->next){
    if(p->next != NULL){
      if(p->parent != NULL)
        cprintf("(%d, %d) -> ", p->pid, p->parent->pid);
      else
        cprintf("(%d, %d) -> ", p->pid, p->pid);
    } else {
      if(p->parent != NULL)
        cprintf("(%d, %d)\n", p->pid, p->parent->pid);
      else
        cprintf("(%d, %d)\n", p->pid, p->pid);
    }
  }
  cprintf("\n$ ");  // simulate shell prompt
  return;
}
#endif // CS333_P3

#ifdef CS333_P4
int
getpriority(int pid){
  struct proc * p;
  int priority = -1;
  int found = 0;
  acquire(&ptable.lock);
  for(int i = SLEEPING; i <= ZOMBIE; ++i){
    if(i == RUNNABLE){
      for(int j = MAXPRIO; j >= 0; --j){
        p = ptable.ready[j].head;
        while (p != NULL) {
          if(p->pid == pid){
            priority = p->priority;
            found = 1;
          }
          p = p->next;
        }
      }
    } else {
      p = ptable.list[i].head;
      while (p != NULL) {
        if(p->pid == pid){
          priority = p->priority;
          found = 1;
        }
        p = p->next;
      }
    }
  }
  release(&ptable.lock);

  if(found == 1)
    return priority;
  else
    return -1;
}

int
setpriority(int pid, int priority){
  struct proc * p;
  int found = 0;
  if(priority >= 0 && priority <= MAXPRIO){
    // Acquire ptable lock
    acquire(&ptable.lock);
    for(int i = SLEEPING; i <= ZOMBIE; ++i){
      if(i == RUNNABLE){
        for(int j = MAXPRIO; j >= 0; --j){
          p = ptable.ready[j].head;
          while (p != NULL) {
            if(p->pid == pid){
              if(p->priority != priority){
                // Remove the process from the list
                int  rc = (stateListRemove(&ptable.ready[p->priority], p));
                if (rc != 0) {
                  panic("\nCould not remove process from the ready list\n");
                } else {
                  // Assert that the process was in the correct state
                  assertState(p, RUNNABLE);
                  assertPriority(p, j);
                  // Update the process
                  p->priority = priority;
                  p->budget = DEFAULT_BUDGET;
                  // Put on new list
                  stateListAdd(&ptable.ready[p->priority], p);
                }
                found = 1;
              }
            }
            p = p->next;
          }
        }
      } else {
        p = ptable.list[i].head;
        while (p != NULL) {
          if(p->pid == pid){
            if(p->priority != priority){
              p->priority = priority;
              p->budget = DEFAULT_BUDGET;
            }
            found = 1;
          }
          p = p->next;
        }
      }
    }
    // Release ptable lock
    release(&ptable.lock);
  }

  if(found == 1){
    return 0;
  }
  else{
    return -1;
  }
}

static void assertPriority(struct proc * p, uint priority){
  if(p->priority != priority)
      panic("\nProcess did not have correct priority \n");
}

#endif // CS333_P4

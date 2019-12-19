#ifdef CS333_P2

#include "types.h"
#include "user.h"
#include "uproc.h"

int
ps (int max, struct uproc * temp)
{
  int nProc = 0;

  nProc = getprocs(max, temp);
//  int nProc = 0; // Test for no processes
//  int nProc = -1; // Test for errors

  if(nProc < 0)
    printf(2, "An error occured trying to return processes, exiting \n");
  else if (nProc == 0)
    printf(2, "No processes found, exiting\n");
  else{

#ifdef CS333_P4
    printf(2, "\nPID\tName\t\tUID\tGID\tPPID\tPrio\tElapsed\t\tCPU\t    State\tSize\n");
#else
    printf(2, "\nPID\tName\t\tUID\tGID\tPPID\tElapsed\t\tCPU\t    State\tSize\n");
#endif // CS333_P4

    for (int i = 0; i < nProc; i++)
    {
      printf(2, "%d\t", temp[i].pid);

      if(strlen(temp[i].name) <= 8)
        printf(2, "%s\t\t", temp[i].name);
      else
        printf(2, "%s\t", temp[i].name);

      printf(2, "%d\t", temp[i].uid);
      printf(2, "%d\t", temp[i].gid);
      printf(2, "%d\t", temp[i].ppid);
#ifdef CS333_P4
      printf(2, "%d\t", temp[i].priority);
#endif // CS333_P4

      if(temp[i].elapsed_ticks % 1000 >= 100)
        printf(2, "%d.%d\t\t",(temp[i].elapsed_ticks)/1000, (temp[i].elapsed_ticks)%1000);
      else if(temp[i].elapsed_ticks % 1000 >= 10)
        printf(2, "%d.%d0\t\t",(temp[i].elapsed_ticks)/1000, (temp[i].elapsed_ticks)%1000);
      else
        printf(2, "%d.%d00\t\t",(temp[i].elapsed_ticks)/1000, (temp[i].elapsed_ticks)%1000);

      if(temp[i].CPU_total_ticks % 1000 >= 100)
        printf(2, "%d.%d\t",(temp[i].CPU_total_ticks)/1000, (temp[i].CPU_total_ticks)%1000);
      else if(temp[i].CPU_total_ticks % 1000 >= 10)
        printf(2, "%d.%d0\t",(temp[i].CPU_total_ticks)/1000, (temp[i].CPU_total_ticks)%1000);
      else
        printf(2, "%d.%d00\t",(temp[i].CPU_total_ticks)/1000, (temp[i].CPU_total_ticks)%1000);

      if (strlen(temp[i].state) >= 5)
        printf(2, "    %s\t", temp[i].state);
      else
        printf(2, "    %s\t\t", temp[i].state);

      printf(2, "%d\t\n", temp[i].size);

    }
    printf(2, "\n");
  }

  return nProc;
}

int
getprocstest(int max, struct uproc* temp)
{
  int ret = 0;
  int success = 0;
  int nProcs = 0;

  printf(1, "\nTesting getproc()\n");

  printf(1, "Filling ptable up to 64 processes\n");

  ret = fork(); // Borrowed from p2-test
  if (ret == 0){
    while((ret = fork()) == 0);
    if(ret > 0){
      wait();
      exit();
    }

    printf(1, "\nRunning ps with max of 1\n");
    nProcs = ps(1, temp);
    if(nProcs == 1)
      printf(1, "Test passed\n");
    else{
      printf(1, "Test failed\n");
      success = -1;
    }

    printf(1, "\nRunning ps with max of 16\n");
    nProcs = ps(16, temp);
    if(nProcs == 16)
      printf(1, "Test passed\n");
    else{
      printf(1, "Test failed\n");
      success = -1;
    }

    printf(1, "\nRunning ps with max of 64\n");
    nProcs = ps(64, temp);
    if(nProcs == 64)
      printf(1, "Test passed\n");
    else{
      printf(1, "Test failed\n");
      success = -1;
    }

    printf(1, "\nRunning ps with max of 72\n");
    nProcs = ps(72, temp);
    if(nProcs == 64)
      printf(1, "Test passed\n");
    else{
      printf(1, "Test failed\n");
      success = -1;
    }
    if (success == 0)
      printf(1, "\ngetprocs Test Passed \n");
    else
      printf(1, "\ngetprocs Test Failed \n");

    printf(1, "\nPress Ctrl-p to compare outputs in the next 2 seconds...\n");
    sleep(5000); // Used to compare to Ctrl-p
    printf(1, "Done waiting\n");

    exit();
  }
  wait();

  return success;
}

int
main(void)
{
//  int max = 1; // Test
//  int max = 16; // Test
//  int max = 64; // Test
  int max = 72; // Default value, don't change unless testing
//  int max = 1024; // Test

  struct uproc * temp;

//  temp = malloc(sizeof(struct uproc)); // Test for invalid array
  temp = malloc(sizeof(struct uproc) * max);
  if (!temp)
    printf(1, "\nThere was an error creating the table, exiting...\n");
  else{

//    getprocstest(max, temp); // Uncomment to test getprocs()
    ps(max, temp);

    free(temp);
  }

  exit();
}

#endif // CS333_P2

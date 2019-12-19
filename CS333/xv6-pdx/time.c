#ifdef CS333_P2
#include "time.h"

int
main(int argc, char * argv[])
{
  int time = uptime();
  int pid = 0;

  if (argc > 1){
    pid = fork();

    if (pid < 0){
      printf(2, "\nError trying to fork, exiting \n");
    }
    else {
      if (pid > 0){
        wait();
      }
      else {
        if (exec(argv[1], argv + 1)){
          exit();
        }
      }
    }
  }

  time = uptime() - time;

  if (time % 1000 >= 100)
    printf(2, "%s ran in %d.%d seconds \n", argv[1], time / 1000, time % 1000);
  else if (time % 1000 >= 10)
    printf(2, "%s ran in %d.%d0 seconds \n", argv[1], time / 1000, time % 1000);
  else
    printf(2, "%s ran in %d.%d00 seconds \n", argv[1], time / 1000, time % 1000);

  exit();
}

#endif

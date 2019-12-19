#ifdef CS333_P2

#include "types.h"
#include "user.h"

static void
testuid(uint id)
{
//  printf(2, "\ntestuid\n");

  uint uid;

  uid = getuid();
  printf(2, "Current UID is: %d\n", uid);
  printf(2, "Setting UID to %d\n", id);
  if (setuid(id) < 0)
    printf(2,"UID is not valid\n");
  else{
    uid = getuid();
    printf(2, "Current UID is: %d\n", uid);
  }
}

static void
testgid(uint id)
{
//  printf(2, "\ntestgid\n");

  uint gid;

  gid = getgid();
  printf(2, "Current GID is: %d\n", gid);
  printf(2, "Setting GID to %d\n", id);
  if (setgid(id) < 0)
    printf(2,"GID is not valid\n");
  else{
    gid = getgid();
    printf(2, "Current GID is: %d\n", gid);
  }
}

static void
testppid(void)
{
  printf(2, "\ntestppid\n");

  uint ppid;

  ppid = getppid();
  printf(2, "My parrent process is: %d\n", ppid);
  printf(2, "Done!\n");
}

static int
testid(void)
{
  uint id = 100;

  printf(2, "\nTesting uid within range:\n");
  testuid(id);

  printf(2, "\nTesting UID less than 0:\n");
  id = -1;
  testuid(id);

  printf(2, "\nTesting UID greater than 32767:\n");
  id = 32768;
  testuid(id);
  printf(2, "\nDone testing UID\n");

  printf(2, "\nTesting GID within range:\n");
  id = 100;
  testgid(id);

  printf(2, "\nTesting GID less than 0:\n");
  id = -1;
  testgid(id);

  printf(2, "\nTesting GID greater than 32767:\n");
  id = 32768;
  testgid(id);
  printf(2, "\nDone testing GID\n");

  printf(2, "\nTesting PPID:\n");
  testppid();
  printf(2, "\nDone testing PPID\n");

  return 0;
}

int
main(void)
{
  printf(2, "\nWelcome to testid\n");
  testid();

  printf(2, "\nAll tests finished\n");

  exit();
}
#endif // CS333_P1

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>


static const pid_t ignored_pid;
static const caddr_t ignored_ptr;
static const int no_continue_signal = 0;

static void setup_inferior(const char *path, char *const argv[]) {
  printf(" ptrace(%i, %i, %i, %i), returning -1\n", PT_TRACE_ME, NULL, NULL, 0);
  printf("setup_inferior");
  ptrace(PT_TRACE_ME, ignored_pid, ignored_ptr, 0);
  execv(path, argv);
}

static void attach_to_inferior(pid_t pid) {
  while(1) {
    int status;
    waitpid(pid, &status, 0);

    if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
      printf("Inferior stoped on SIGTRAP - continuing...\n");
      ptrace(PT_CONTINUE, pid, ignored_ptr, no_continue_signal);
    } else if(WIFEXITED(status)) {
      printf("Inferior exited - debugger terminating...\n");
      exit(0);
    }
  }
}

void dbg_inferior_exec(const char *path, char *const argv[]) {
  pid_t result;
  
  do {
    result = fork();

    switch (result)
    {
    case 0:
      setup_inferior(path, argv);
      break;
    case -1:
      break;
    default:
      attach_to_inferior(result);
      break;
    }
  } while(result == -1 && errno == EAGAIN);
}
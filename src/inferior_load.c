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
  ptrace(PT_TRACE_ME, ignored_pid, ignored_ptr, 0);
  if (execv(path, argv) < 0) {
    perror("execv error");
  }
}

static void attach_to_inferior(pid_t pid) {
  while(1) {
    int status;
    waitpid(pid, &status, 0);

    if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
      printf("Inferior stoped on SIGTRAP - continuing...\n");
      ptrace(PT_CONTINUE, pid, 1, 0);
    } else if(WIFEXITED(status)) {
      printf("Inferior exited - debugger terminating...\n");
      return;
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
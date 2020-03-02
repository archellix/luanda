#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>


static const pid_t ignored_pid;
static const void *ignored_ptr;
static const *no_continue_signal = 0;

static void setup_inferior(const char *path, char *const argv[]) {
  ptrace(PT_TRACE_ME, ignored_pid, ignored_ptr, ignored_ptr);
  execv(path, argv);
}

static void attach_to_inferior(pid_t pid) {
  while(1) {
    int status;
    printf("%d\n", pid);
    waitpid(pid, &status, 0);

    if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
      printf("Inferior stopedon SIGTRAP - continuing...\n");
      ptrace(PT_CONTINUE, pid, ignored_ptr, no_continue_signal);
    } else if(WIFEXITED(status)) {
      printf("Inferior exited - debugger terminating...");
      exit(0);
    }
  }
}

void dbg_inferior_exec(const char *path, char *const argv[]) {
  pid_t result;

  do {
    result = fork();
    printf("result %d\n", result);
    switch (result)
    {
    case 0: // inferior
      setup_inferior(path, argv);
      break;
    case -1: // error
      break;
    default: //debugger
      attach_to_inferior(result);
      break;
    }
  } while(result == -1 && errno == EAGAIN);
}
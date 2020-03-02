#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ptrace.h>


static const pid_t ignored_pid;
static const void *ignored_ptr;

static void setup_inferior(const char *path, char *const argv[]) {
  ptrace(PT_TRACE_ME, ignored_pid, ignored_ptr, ignored_ptr);
  execv(path, argv);
}

static void attach_to_inferior(pid_t pid) {
  // todo waiting inferior
  while(1) {

  }
}

void dbg_inferior_exec(const char *path, char *const argv[]) {
  pid_t result;

  do {
    result = fork();
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
#include <luanda.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <mach/exception_types.h>

static luanda_breakpoint_callback_t g_callback;

void luanda_breakpoint_set_callback(luanda_breakpoint_callback_t callback) {
  g_callback = callback;
}

luanda_breakpoint_t luanda_inferior_set_breakpoint(luanda_inferior_t inferior, char *location) {
  const void *target_address = (void *) 0x000000000040079d;
  const void *int3_opcode = (void *) 0xCC;
  pid_t inferior_pid = inferior;

  ptrace(PT_ATTACHEXC, inferior_pid, int3_opcode, target_address);
}
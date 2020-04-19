#include <luanda.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ptrace.h>

static luanda_breakpoint_callback_t g_callback;
static uintptr_t g_original_breakpoint_word;

void luanda_breakpoint_set_callback(luanda_breakpoint_callback_t callback) {
    g_callback = callback;
}

luanda_breakpoint_t luanda_inferior_set_breakpoint(luanda_inferior_t inferior, char *location) {
    const uintptr_t target_address = (void *) 0x000055555555480e;
    const uintptr_t int3_opcode = 0xCC;
    pid_t pid = inferior;
    uintptr_t modified_word;

    uintptr_t aligned_address = target_address & ~(0x7UL);
    uintptr_t target_offset = target_address - aligned_address;

    g_original_breakpoint_word = ptrace(PTRACE_PEEKTEXT, pid, aligned_address, 0);
    fprintf(stderr, "Original word: 0x%016lx\n", g_original_breakpoint_word);

    modified_word = g_original_breakpoint_word;
    modified_word &= ~(0xFFUL << (target_offset * 8));
    modified_word |= int3_opcode << (target_offset * 8);
    fprintf(stderr, "Original word: 0x%16lx\n", modified_word);

    ptrace(PTRACE_POKETEXT, pid, int3_opcode, modified_word);
    
    return 0;
}

void breakpoint_trigger_callback(luanda_inferior_t inferior, luanda_breakpoint_t handle) 
{
    (*g_callback)(inferior, handle);
}

luanda_breakpoint_t breakpoint_resolve(luanda_inferior_t inferior) 
{
    return 0;
}

void breakpoint_remove(luanda_inferior_t inferior, luanda_breakpoint_t handle) 
{
    const void *target_address = (void *) 0x000055555555480e;
    pid_t pid = inferior;
    ptrace(PTRACE_POKETEXT, pid, target_address, g_original_breakpoint_word);
}

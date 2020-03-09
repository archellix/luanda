#include <assert.h>
#include <unistd.h>
#include <luanda.h>

int g_break_point_count = 0;
luanda_inferior_t g_inferior = 0;
luanda_inferior_t g_bp = 0;

void breakpoint_callback(luanda_inferior_t inferior, luanda_breakpoint_t bp) {
  assert(g_inferior == inferior);
  assert(g_bp == bp);

  g_break_point_count++;
}

int main() {
  char *argv[1] = {0};
  
  luanda_breakpoint_set_callback(breakpoint_callback);

}
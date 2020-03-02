#include <stdio.h>
#include "luandra-debugger.h"

int main() {
  char *argv[1] = { 0 };
  dbg_inferior_exec("./a.out", argv);
}

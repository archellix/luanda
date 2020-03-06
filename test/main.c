#include <stdio.h>
#include "inferior_load.h"

int main() {
  char *argv[1] = { 0 };
  dbg_inferior_exec("bin/test", argv);
}

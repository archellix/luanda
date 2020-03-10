#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <luanda.h>

int capturefd(int fd) {
  char name[] = "test_exec_XXXXXX";
  int captured = mkstemp(name);
  if (dup2(captured, fd) == -1) {
    perror("dup2: ");
  }
  unlink(name);
  return captured;
}

void verify_text(int fd, char *text) {
  int i;
  char buf[4097] = {0};
  lseek(fd, 0, SEEK_SET);
  read(fd, buf, 4096);

  char *p = buf;
  for (i = 0; i < 2 && p < buf + 4096; i++) {
    fprintf(stderr, "Compare with: %s\n", p);
    if (strcmp(p, text) == 0) return;
    p += strlen(buf) + 1;
  }

  assert(!"verify_text could not find the specified text");
}

int main() {
  char *argv[1] = {0};

  int captured = capturefd(STDOUT_FILENO);

  luanda_inferior_t inferior = luanda_inferior_exec("./inferiors/hello", argv);
  luanda_inferior_continue(inferior);

  verify_text(captured, "Hi my majesty!\n");
}
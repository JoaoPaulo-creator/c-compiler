#include "compiler.h"
#include <stdio.h>

int main() {
  int res = compile_file("./test.c", "./test", 0);

  if (res == COMPILER_FILE_COMPILED_OK) {
    printf("Compilou certinho caraio\n");
  } else if (res == COMPILER_FAILED_WITH_ERRORS) {
    printf("Deu ruim na compilação\n");
  } else {
    printf("Sei lá o que ta rolando, tio\n");
  }

  printf("Compilou certinho caraio\n");

  printf("Hello world\n");
  return 2;
}

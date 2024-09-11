
// filename: o nome do arquivo
// outfilename: o nome do arquivo de saida. Ex.: -o filenameExample
// flags: ainda vou saber
#include "compiler.h"

int compile_file(const char *filename, const char *out_filename, int flags) {
  struct compile_process *process =
      compile_process_create(filename, out_filename, flags);
  if (!process) {
    return COMPILER_FAILED_WITH_ERRORS;
  }

  // performa a analise lexica

  // performa o parsing

  // performa o code generation

  return COMPILER_FILE_COMPILED_OK;
}


// filename: o nome do arquivo
// outfilename: o nome do arquivo de saida. Ex.: -o filenameExample
// flags: ainda vou saber
#include "compiler.h"

struct lex_process_functions compile_lex_functions = {
    .next_char = compile_process_next_char,
    .peek_char = compile_process_peek_char,
    .push_char = compile_process_push_char,
};

int compile_file(const char *filename, const char *out_filename, int flags) {
  struct compile_process *process =
      compile_process_create(filename, out_filename, flags);
  if (!process) {
    return COMPILER_FAILED_WITH_ERRORS;
  }

  // performa a analise lexica
  struct lex_process *lex_process =
      lex_process_create(process, &compile_lex_functions, NULL);
  if (!lex_process) {
    return COMPILER_FAILED_WITH_ERRORS;
  }

  if (lex(lex_process) != LEXICAL_ANALYSIS_ALL_OK) {
    return COMPILER_FAILED_WITH_ERRORS;
  }

  // performa o parsing

  // performa o code generation

  return COMPILER_FILE_COMPILED_OK;
}

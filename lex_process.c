#include "compiler.h"
#include "helpers/vector.h"
#include <stdlib.h>

struct lex_process *lex_processCreate(struct compile_process *compiler,
                                    struct lex_process_functions *functions,
                                    void *private) {

  struct lex_process *process = calloc(1, sizeof(struct lex_process));
  process->function = functions;
  process->tokenVec = vector_create(sizeof(struct token));
  process->compiler = compiler;
  process->private = private;
  process->pos.line = 1;
  process->pos.col = 1;

  return process;
}

void lex_processFree(struct lex_process *process) {
  vector_free(process->tokenVec);
  free(process);
}

void *lex_processPrivate(struct lex_process *process) { return process->private; }

struct vector *lex_processTokens(struct lex_process *process) {
  return process->tokenVec;
}

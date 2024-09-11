// cprocess == compile  process

#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>

struct compile_process *
compile_processCreate(const char *filename, const char *filenameOut, int flags) {

  FILE *file = fopen(filename, "r");
  if (!file) {
    return NULL;
  }

  FILE *outFile = NULL;
  if (filenameOut) {
    outFile = fopen(filenameOut, "w");
    if (!outFile) {
      return NULL;
    }
  }

  struct compile_process *process = calloc(1, sizeof(struct compile_process));
  process->flags = flags;
  process->cfile.fp = file;
  process->ofile = outFile;

  return process;
}

char compile_processNextChar(struct lex_process* lex_process) {
  struct compile_process *compiler = lex_process->compiler;
  compiler->pos.col += 1;
  char c = getc(compiler->cfile.fp);

  /*
   * se eu não estiver errado,
   * será feito uma leitura de uma linha inteira,
   * coluna a coluna. Se o proximo caracter for igual
   * a uma nova linha, então eu incremento a linha e a coluna.
   * Dessa forma, inicio a iteração de cada caracter.
   * */
  if (c == '\n') {
    compiler->pos.line += 1;
    compiler->pos.col += 1;
  }

  return c;
}

char compile_processPeekChar(struct lex_process* lex_process) {
	struct compile_process* compiler = lex_process->compiler;
	char c = getc(compiler->cfile.fp);
	ungetc(c, compiler->cfile.fp);
	return c;
}

void compilerProcessPushChar(struct lex_process* lex_process, char c) {
	struct compile_process* compiler = lex_process->compiler;
	ungetc(c, compiler->cfile.fp);
}



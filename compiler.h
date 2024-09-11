/*
 * esse header vai conter todos os prototipos
 * que serão aceesado por todo o compilador
 *
 * */

#ifndef PEACHCOMPILER_H
#define PEACHCOMPILER_H

#include <stdbool.h>
#include <stdio.h>

enum {
  COMPILER_FILE_COMPILED_OK,
  COMPILER_FAILED_WITH_ERRORS,
};

enum {
  TOKEN_TYPE_IDENTIFIER,
  TOKEN_TYPE_KEYWORD,
  TOKEN_TYPE_OPERATOR,
  TOKEN_TYPE_SYMBOL,
  TOKEN_TYPE_NUMBER,
  TOKEN_TYPE_STRING,
  TOKEN_TYPE_COMMENT,
  TOKEN_TYPE_NEWLINE,
};

// vai checar em qual linha e coluna, o token está
struct pos {
  int line;
  int col;
  const char *fileName; // indica qual arquivo está sendo verificado/checado
};

struct token {
  int type;
  int flags;

  union {
    char cval;
    const char *sval;
    unsigned int inum;
    unsigned long lnum;
    unsigned long long llnum;
    void *any;
  };

  // true, se houver whitespaces entre o token atual, e o proximo token
  bool whitespace;
  // qualquer coisa entre parenteses
  const char *betweenBrackets;
};

struct lex_process;
typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lex_process *process);
typedef char (*LEX_PROCESS_PEEK_CHAR)(struct lex_process *process);
typedef char (*LEX_PROCESS_PUSH_CHAR)(struct lex_process *process, char c);

struct lex_process_functions {
  LEX_PROCESS_NEXT_CHAR nextChar;
  LEX_PROCESS_PEEK_CHAR peekChar;
  LEX_PROCESS_PUSH_CHAR pushChar;
};

struct lex_process {
  struct pos pos;
  struct vector *tokenVec;
  struct compile_process *compiler;

  int currentExpressionCount;
  struct buffer *parenthesesBuffer;
  struct lex_process_functions *function;

  // esse membro será o dado privado, que o lexer não vai entender/compreender
  // mas quem estiver usando o lexer, vai conseguir compreender
  void *private;
};

struct compile_process {
  // flags recebe flags (quem diria), para indicar como o arquivo deve ser
  // compilado
  int flags;

  struct pos pos;
  struct compile_process_input_file {
    FILE *fp;
    const char *absPath; // caminho absoluto
  } cfile;

  FILE *ofile; // output file
};

int compile_file(const char *filename, const char *filenameOut, int flags);
struct compile_process *
compile_process_create(const char *filename, const char *filenameOut, int flags);

#endif

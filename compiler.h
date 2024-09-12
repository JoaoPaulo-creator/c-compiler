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

enum {
  LEXICAL_ANALYSIS_ALL_OK,
  LEXICAL_ANALYSIS_INPUT_ERROR,
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
typedef void (*LEX_PROCESS_PUSH_CHAR)(struct lex_process *process, char c);

struct lex_process_functions {
  LEX_PROCESS_NEXT_CHAR next_char;
  LEX_PROCESS_PEEK_CHAR peek_char;
  LEX_PROCESS_PUSH_CHAR push_char;
};

struct lex_process {
  struct pos pos;
  struct vector *token_vec;
  struct compile_process *compiler;

  int current_expression_count;
  struct buffer *parentheses_buffer;
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
    const char *abs_path; // caminho absoluto
  } cfile;

  FILE *ofile; // output file
};

int compile_file(const char *filename, const char *out_filename, int flags);
struct compile_process *compile_process_create(const char *filename,
                                               const char *filename_out,
                                               int flags);

char compile_process_next_char(struct lex_process *lex_process);
char compile_process_peek_char(struct lex_process *lex_process);
void compile_process_push_char(struct lex_process *lex_process, char c);

struct lex_process *lex_process_create(struct compile_process *compiler,
                                       struct lex_process_functions *functions,
                                       void *private);

void lex_process_free(struct lex_process *process);
void *lex_process_private(struct lex_process *process);
struct vector *lex_process_tokens(struct lex_process *process);
int lex(struct lex_process *process);

#endif

/*
 * esse header vai conter todos os prototipos
 * que serão aceesado por todo o compilador
 *
 * */


#ifndef PEACHCOMPILER_H
#define PEACHCOMPILER_H

#include <stdio.h>
#include <stdbool.h>

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
	const char* fileName; // indica qual arquivo está sendo verificado/checado
};


struct token {
	int type;
	int flags;

	union {
		char cval;
		const char* sval;
		unsigned int inum;
		unsigned long lnum;
		unsigned long long llnum;
		void* any;
	};


	//true, se houver whitespaces entre o token atual, e o proximo token
	bool whitespace;
	// qualquer coisa entre parenteses
	const char* betweenBrackets;
};


struct compileProcess{
	// flags recebe flags (quem diria), para indicar como o arquivo deve ser compilado
	int flags;

	struct compileProcessInputFile {
		FILE* fp;
		const char* absPath; // caminho absoluto
	} cfile;

	FILE* ofile; // output file
};

int compileFile(const char* filename, const char* filenameOut, int flags); 
struct compileProcess *compileProcessCreate(const char* filename, const char* filenameOut, int flags);

#endif


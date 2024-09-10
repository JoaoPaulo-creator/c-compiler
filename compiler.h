/*
 * esse header vai conter todos os prototipos
 * que serão aceesado por todo o compilador
 *
 * */


#ifndef PEACHCOMPILER_H
#define PEACHCOMPILER_H

#include <stdio.h>

enum {
	COMPILER_FILE_COMPILED_OK,
	COMPILER_FAILED_WITH_ERRORS,
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


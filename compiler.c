
//filename: o nome do arquivo
//outfilename: o nome do arquivo de saida. Ex.: -o filenameExample
//flags: ainda vou saber
#include "compiler.h"

int compileFile(const char* filename, const char* outfilename, int flags) {
	struct compileProcess* process = compileProcessCreate(filename, outfilename, flags);
	if (!process) {
		return COMPILER_FAILED_WITH_ERRORS;
	}


	// performa a analise lexica
	
	// performa o parsing
	
	// performa o code generation


	

	return COMPILER_FILE_COMPILED_OK;
}

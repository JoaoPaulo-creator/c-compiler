// cprocess == compile  process

#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

struct compileProcess *compileProcessCreate(const char* filename, const char* filenameOut, int flags){

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


	struct compileProcess* process = calloc(1, sizeof(struct compileProcess));
	process->flags = flags;
	process->cfile.fp = file;
	process->ofile = outFile;

	return process;
} 


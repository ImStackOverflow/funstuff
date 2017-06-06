#include <stdlib.h>
#include "utilities.c"

static void error(const char message[], char function[]){
	printf("%s in %s\n", message, function);
	exit(1);
}

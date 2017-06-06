#include <stdlib.h>
#include "utilities.h"

void error(char message[], const char function[]){
	printf("%s in %s\n", message, function);
	exit(1);
}

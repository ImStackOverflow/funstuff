#include "adjWgtVec.h"

static void error(const char message[], char function[]);

AdjWgt adjWgtTop(AdjWgtVec myVec){
	if(!myVec) error("null pointer", __func__);
	return *myVec;
}

AdjWgt adjWgtData(AdjWgtVec myVec, int i){
	
	
}

static void error(const char message[], char function[]){
	printf("%s in %s\n", message, function);
	exit(1);
}

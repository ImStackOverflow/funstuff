typedef struct IntVecNode * IntVec{
	int *data;
	int sz;
	int capacity;
}

int intTop(IntVec myVec){
	if (myVec)
	{
		int *penis = myVec.data;
	penis += sz;
	return *penis;
	}
	else error("there was a null pointer in intTop");
	
}

int intData(IntVec myVec, int i){
	if (myVec)
	{
			int *penis = myVec.data;
	penis += i;
	return *penis;
	}
	else error("there was a null pointer in intData");

}

int intSize(IntVec myVec){
	if (myVec)
	{
		return *myVec.sz;
	}
	else error("there was a null pointer in intSize");
	
}
int intCapacity(IntVec myVec){
	if (myVec)
	{
		return *myVec.capacity;
	}
	else error("there was a null pointer in intCapacity");
	
}

IntVec intMakeEmptyVec(void){
	IntVecNode penis;
	IntVec ass 
}

void error(string n){
	printf("%s\n",n);
	exit(1);
}
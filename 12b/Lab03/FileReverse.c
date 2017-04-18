#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fuckup 1
#define good 0

char* reverse(char word[256]);

int main(int argc, char* argv[]){
	FILE* in;
	FILE* out;

	char word[256]; /* char array to store words from input file */
	/* check command line for correct number of arguments */ 
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(fuckup); 
	}
	/* open input file for reading */ 
	in = fopen(argv[1], "r");
	if( in==NULL ){
	printf("Unable to read from file %s\n", argv[1]);
	exit(fuckup); 
	}
	/* open output file for writing */ 
	out = fopen(argv[2], "w");
	if( out==NULL ){
	printf("Unable to write to file %s\n", argv[2]);
	exit(fuckup); 
	}
/* read words from input file, print on separate lines to output file*/ 
	while(fscanf(in, " %s", word) != EOF ){
		reverse(word);
		printf("%s\n", word);	
		fprintf(out, "%s\n", word);
	}
		
		

/* close input and output files */ 
fclose(in);
fclose(out);
return(good); 

}

char* reverse(char word[256]){
	int i = 0;
	int j = 0;
	char hold;
	while(word[++j]!='\0');
	for (int i = 0; i < j;)
	{
		hold = word[i];
		word[i++] = word[--j];
		word[j] = hold;/* code */
	}
	return word;
	
}
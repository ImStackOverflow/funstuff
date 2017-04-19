#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

#define debug 1

void extract_chars(char *s, char *a, char *d, char *p, char *w);
int getit(char* see);

int main(int argc, char* argv[]){
	printf("in function %s/n", __func__);
	FILE* in;
	FILE* out;

	out = fopen(argv[2], "w"); //get output file
	if( out==NULL ){
	printf("Unable to write to file %s\n", argv[2]);
	exit(EXIT_FAILURE); }

	in = fopen(argv[1], "r");//get input file
	if( in==NULL ){
	printf("Unable to read from file %s\n", argv[1]);
	exit(EXIT_FAILURE); }

	int size = 100;
	int* kno = &size;
	char* line = calloc(size,sizeof(char));
	int g = 0;
	getline(&line,kno,in);
	int i = 1;
	int j = 0;

	while (g != -1){
	fprintf(out, "The contents of line %d is \n", i);
	char* a = calloc(size,sizeof(char));
	char* d = calloc(size,sizeof(char));
	char* p = calloc(size,sizeof(char));
	char* w = calloc(size,sizeof(char));
	extract_chars(line, a, d, p, w);
	j = getit(a);
	if(j>1) fprintf(out, "%d alphabetic characters: %s\n", j,a);
	else fprintf(out, "%d alphabetic character: %s\n", j,a);

	j = getit(d);
	if(j>1) fprintf(out, "%d digits: %s\n",j, d);
	else fprintf(out, "%d digit: %s\n",j, d);

	j = getit(p);
	if(j>1) fprintf(out, "%d punctuation characters: %s\n", j, p);
	else fprintf(out, "%d punctuation character: %s\n", j, p);

	j = getit(w);
	if(j>1) fprintf(out, "%d whitespace chracters: %s\n\n\n",j, w);
	else fprintf(out, "%d whitespace chracter: %s\n\n\n",j, w);
	
	free(a);
	free(d);
	free(p);
	free(w);
	g = getline(&line,kno,in);
	i++;
	}
	free(line);
	fclose(in);
	fclose(out);

}
int getit(char* see){
	int i = 0;
	while(*see!='\0'){
		i++;
		see++;
	}
	return i;
}

void extract_chars(char *s, char *a, char *d, char *p, char *w){
	int k = 0;
	int i = 0;
	while(*s != '\n') {
		k = *s;
		if(isalpha(k)) {			
			*a = *s;
			a++;
		} 
		else if (isdigit(k)) {
			*d = *s;
			d++;
		}
		else if (ispunct(k)) {
			*p = *s;
			p++;
		} 
		else if (isspace(k)){
			*w = *s;
			w++;
		}
		++s;
		i++;
	}
	*a = '\0';
	*d = '\0';
	*p = '\0';
	*w = '\0';
}

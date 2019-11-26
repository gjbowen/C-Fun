#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "color.c"
#include "file.c"


int main(void)
{
	printlnRed("START");

	struct File f = File("program.txt");
	
	printf("File Name: %s\n",f.fileName);
	printf("Number of rows: %d\n",f.rows);
	
	int i;
	for(i=0;i<f.rows;++i){
		printf("%s\n", f.contents[i]);
	}
	printlnRed("END");
	return 0;
}
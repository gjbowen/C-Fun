#include "file.c"

int main(int argc, char *argv[])
{	
	char file_name[50];
	if(argc<2) strcpy(file_name,"program.txt");
	else strcpy(file_name,argv[1]);

	File f = file(file_name,'R');
	char* line=get_line(&f);
	while(line){
		printf("LINE-%s",line);
		line=get_line(&f);
	}


	return 0;
}

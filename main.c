#include "file.c"

int main(int argc, char *argv[])
{	
	char file_name[50];
	if(argc<2) strcpy(file_name,"program.txt");
	else strcpy(file_name,argv[1]);

	File f = file(file_name);
	// char* line = get_line(f);
	//read_file(&f);
	//print_file(&f);

	return 0;
}

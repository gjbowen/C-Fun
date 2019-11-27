#include "file.c"
#include "color.c"

int main(int argc, char *argv[])
{	
	File f = file("output.txt","a");
	write_line(&f,"THIS WILL BE LINE ONE.");
	write_line(&f,"this is another line..");
	close_file(&f);
	printlnGreen("DONE\n");
	return 0;
}
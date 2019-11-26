struct File 
{ 
   	char fileName[50];
	int rows;
	char** contents;
}; 

void resizeContents(struct File *f){
    /*  Allocate number of rows  */
    f->contents = malloc(f->rows * sizeof(char*));
};

void setContents(struct File *f){
	FILE *stream = fopen(f->fileName,"r");

	char *line=NULL;
	size_t len,read;
	int i=0;
	while ((read = getline(&line, &len, stream)) != -1)
	{
	    if(strchr(line, '\n'))
	    	--read;
	    /*  Allocate column for each name  */
		f->contents[i] = malloc(read * sizeof(char));
		int j;
		for(j=0;j<read;++j)
			f->contents[i][j] = line[j];
	    
		++i;
	}

	fclose(stream);
	free(stream);
	free(line);
};

void setDimensions(struct File *f){

	FILE *stream = fopen(f->fileName,"r");

	char *line=NULL;
	int rows=0;
	size_t len,lineLength;
	
	while ((lineLength = getline(&line, &len, stream)) != -1)
		++rows;

	fclose(stream);
	free(line);
	free(stream);

	f->rows=rows;
};

void setFileName(struct File *f,char* fileName){
	strcpy(f->fileName , fileName);
};

struct File File(char* fileName){
	struct File f;
	
	setFileName(&f,fileName);

	setDimensions(&f);

	resizeContents(&f);

	setContents(&f);
	
	return f;
};
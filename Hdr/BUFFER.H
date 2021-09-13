void saveimg(int,int, int, int, char *);
void repaint(int, int, char *);
void saveimg(int l,int t, int r, int b, char *fname)
{
	int StoreFile;
	FILE *fp;
	long size;
	char *scr;

	size = imagesize(l,t,r,b);
	scr =(char *)malloc(size);
	getimage(l,t,r,b,scr);

	fp=fopen(fname,"wb+");// Creating the file
	fclose(fp);

	StoreFile = open(fname, O_CREAT | O_BINARY | O_WRONLY);
	if (StoreFile == -1)
	{
		close(StoreFile);
	}
	else
	{
		_write(StoreFile,scr,size);
		close(StoreFile);
	}
	free(scr);
	close(StoreFile);
}
void repaint(int l,int t, char *fl)
{
	char *scr;
	int size;
	int OpenFile;
	if ((OpenFile =open(fl, O_RDONLY | O_BINARY)) == -1)
	{
		close(OpenFile);
		free(scr);
		return;
	}
	size=filelength(OpenFile);
	scr=(char *)malloc(size);
	if (read(OpenFile, scr, size) == -1)
	{
		close(OpenFile);
		free(scr);
		return;
	}
	putimage(l,t,scr,0);
	free(scr);
	close(OpenFile);
	unlink(fl);
}

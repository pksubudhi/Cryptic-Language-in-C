void d2b(unsigned char,char *);
unsigned char b2d(char *);
void d2b(unsigned char x, char *b)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		b[i]=48;
	}
	b[i]='\0';
	i=0;
	while(x>0)
	{
		b[i]=(x%2)+48;
		x=x/2;
		i++;
	}
	strrev(b);
}
unsigned char b2d(char *p)
{
	int i;
	unsigned char n=0;
	int j=0;
	for(i=strlen(p)-1;i>=0;i--,j++)
	{
		if(p[i]=='1')
		{
			n=n+pow(2,j);
		}
	}
	return n;
}
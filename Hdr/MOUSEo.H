#include<dos.h>

union REGS in, out;

initmouse()
{
	in.x.ax=0;
	int86(0x33,&in,&out);
	return;
}
showmouse()
{
	in.x.ax=1;
	int86(0x33,&in,&out);
	return;
}
hidemouse()
{
	in.x.ax=2;
	int86(0x33,&in,&out);
	return;
}
getpos(int *btn,int *x, int *y)
{
	in.x.ax=3;
	int86(0x33,&in,&out);
	*btn=out.x.bx;
	*x=out.x.cx;
	*y=out.x.dx;
	return;
}
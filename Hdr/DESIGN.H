void desktop(int col)
{
	setfillstyle(1,col);
	bar(0,0,639,479);
}
void button(int l, int t, int w, int h, int st, char *cap)
{
	int lcol, rcol;

	if(st==1)
	{
		lcol=15;
		rcol=8;
	}
	else
	{
		lcol=8;
		rcol=15;
	}
	setfillstyle(1,7);
	bar(l,t,l+w,t+h);
	setcolor(lcol);
	line(l,t,l+w,t);
	line(l,t,l,t+h);

	setcolor(rcol);
	line(l+1,t+h-1,l+w-1,t+h-1);
	line(l+w-1,t+1,l+w-1,t+h-1);

	line(l,t+h,l+w,t+h);
	line(l+w,t,l+w,t+h);

	setcolor(1);
	settextstyle(2,0,4);
	outtextxy(l+(w-textwidth(cap))/2,t+(h-textheight(cap))/2,cap);

}
void form(int l, int t, int w, int h, char *cap)
{
	button(l,t,w,h,1,"");

	setfillstyle(1,4);
	bar(l+1,t+1,l+w-2,t+16);

	setcolor(15);
	outtextxy(l+(w-textwidth(cap))/2,t,cap);

	// Designing cross button
	button(l+w-20,t+3,12,12,1,"");
	setcolor(4);
	settextstyle(2,0,4);
	outtextxy(l+w-17,t+2,"x");
}
void font(int l, int t, int fc)
{
	int i;
	char s[5];
	button(l,t,40,55,1,"");
	setfillstyle(1,7);
	bar(l,t+13,l+40,t+55);
	setcolor(8);
	line(l,t+13,l+40,t+13);

	rectangle(l,t+15,l+40,t+55);
	for(i=1;i<=7;i++)
	{
		line(l+(i*5),t+15,l+(i*5),t+55);
	}
	for(i=1;i<=7;i++)
	{
		line(l,t+15+(i*5),l+40,t+15+(i*5) );
	}
	setcolor(1);
	settextstyle(2,0,4);
	sprintf(s,"%c(%c)",fc+65,fc+97);
	outtextxy(l+2,t,s);
}
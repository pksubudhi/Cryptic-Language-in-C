void box(int l,int t,int w,int h)
{
	setfillstyle(1,7);
	bar(l,t,l+w,t+h);
	setcolor(15);
	line(l,t,l+w,t);
	line(l,t,l,t+h);
	setcolor(8);
	line(l+w,t,l+w,t+h);
	line(l,t+h,l+w,t+h);
      //setcolor(1);
	//settextstyle(2,0,4);
       //outtextxy(l+((w-textwidth(s))/2),t+((h-textheight(s))/2),s);
}

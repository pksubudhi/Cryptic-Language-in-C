void button(int,int,int,int,int,char,char *,int);
void dform(int ,int , int , int , char *);
void hlpbox(int ,int , int , int , int);
void form(int ,int , int , int , char *);
int msgbox(int , int , char *, char *);
void label(int , int , char *, int , int , int );
int inbox(int , int , char *, char *, char *, int );
int pwbox(int , int , char *, char *, char *, int );
void SetCur(int , int , int );
void textbox(int , int , int );
void textedit(int , int , int , int );
void showtips(int, int, char *);
void showtips(int l, int t, char *s)
{
	int wd=0,ht=15,ln=1;
	char wrd[15];
	int wleft=l+2, wtop=t+2,i=0,j=0;
	int mx,my,mb,pmx,pmy;
	int ptime,ctime;
	settextstyle(2,0,4);
	wd=textwidth(s);
	ln=(wd/150)+1;
	if(wd>150)
	{
		wd=150;
		ht=ln*15;
	}
	hidemouse();
	saveimg(l,t,l+wd+5,t+ht+5,"sys\\__ttip.img");
	setfillstyle(1,8);
	bar(l+wd,t+5,l+wd+3,t+ht+3);
	bar(l+5,t+ht,l+wd+3,t+ht+3);
	setfillstyle(1,14);
	bar(l,t,l+wd,t+ht);
	setcolor(6);
	rectangle(l,t,l+wd,t+ht);
	setcolor(1);

	while(s[i]!='\0')
	{
		j=0;
		while( (s[j]!=' ') && (s[i]!='\0'))
		{
			wrd[j++]=s[i++];
		}
		wrd[j]='\0';
		if(wleft+textwidth(wrd)<(l+150))
		{
			outtextxy(wleft,wtop,wrd);
			wleft=wleft+textwidth(wrd);
		}
		else
		{
			wtop=wtop+15;
			wleft=l+2;
			outtextxy(wleft,wtop,wrd);
			wleft=wleft+textwidth(wrd);
		}
	}
	showmouse();
}
void textedit(int l, int t, int w, int h)
{
	setfillstyle(1,15);
	bar(l,t,l+w,t+h);
	setcolor(7);
	rectangle(l,t,l+w-1,t+h-1);
	line(l,t,l+w,t);
	line(l,t,l,t+h);

	setcolor(8);
	line(l+1,t+1,l+w,t+1);
	line(l+1,t+1,l+1,t+h);

	setcolor(0);
	line(l+2,t+2,l+w-1,t+2);
	line(l+2,t+2,l+2,t+h-1);
}
void textbox(int l, int t, int w)
{
	setfillstyle(1,15);
	bar(l,t,l+w,t+16);

	setcolor(8);
	line(l,t,l+w,t);
	line(l,t,l,t+16);

	setcolor(0);
	line(l+1,t+1,l+w-1,t+1);
	line(l+1,t+1,l+1,t+15);

	setcolor(7);
	line(l+1,t+15,l+w-1,t+15);
	line(l+w-1,t+1,l+w-1,t+15);
}
void label(int l, int t, char *cap, int fn, int fs, int fc)
{
	setcolor(fc);
	settextstyle(fn,0,fs);
	outtextxy(l,t,cap);
}
int inbox(int l, int t, char *cap, char *prompt, char *ostr, int mc)
{
	char tmp_fl[13];
	char ch;
	int cc=0;
	struct time t1;
	union REGS iin, iout;
	int cPos;
	int mb, mx, my;
	saveimg(l,t,l+250,t+100,"image\\__ibim.img");

	hidemouse();
	form(l,t,250,100,cap);

	label(l+50,t+25,prompt,2,4,5);
	textbox(l+50,t+40,150);
	button(l+60,t+70,60,20,1,'e',"Cancel",1);
	button(l+130,t+70,60,20,1,'e',"Ok",1);

	setcolor(0);
	rectangle(l+130-1,t+70-1,l+190,t+90);

	tmp_fl[cc]='\0';
	cPos=l+53;

	SetCur(cPos,t+42,0);
	showmouse();
	while(1)
	{
		if(kbhit())
		{
			iin.h.ah=0;
			int86(22,&iin,&iout);
			ch=iout.h.al;
			if( ((ch>=65) && (ch<=90)) || ((ch>=97)&&(ch<=122)) )
			{
				if(cc<mc-1)
				{
					hidemouse();
					tmp_fl[cc++]=ch;
					tmp_fl[cc]='\0';
					SetCur(cPos,t+42,15);
					label(l+53,t+42,tmp_fl,2,4,0);
					cPos=l+53+textwidth(tmp_fl)+1;
					SetCur(cPos,t+42,0);
					showmouse();
				}
			}
		}
		if(ch==BS)
		{
			if(cc>0)
			{
				hidemouse();
				SetCur(cPos,t+42,15);
				cc--;
				tmp_fl[cc]='\0';
				textbox(l+50,t+40,150);
				label(l+53,t+42,tmp_fl,2,4,0);
				cPos=l+53+textwidth(tmp_fl)+1;
				SetCur(cPos,t+42,0);
				showmouse();
			}
			ch=0;
		}

		if(ch==ESC)
		{
			hidemouse();
			repaint(l,t,"image\\__ibim.img");
			return 0;
		}
		if(ch==ENTER)
		{
			hidemouse();
			if(strlen(tmp_fl)>0)
			{
				strcpy(ostr,tmp_fl);
			}
			repaint(l,t,"image\\__ibim.img");
			return strlen(tmp_fl);
		}
		getpos(&mb,&mx,&my);
		if(mb==1)
		{
			hidemouse();
			// if Close button revoked
			if( (mx>=(l+236)) && (mx<=(l+247)) && (my>=(t+3)) && (my<=(t+14)) )
			{
				repaint(l,t,"image\\__ibim.img");
				return 0;
			}
			// if cancel button revoked
			if( (mx>=(l+60)) && (mx<=(l+120)) && (my>=(t+70)) && (my<=(t+90)) )
			{
				button(l+60,t+70,60,20,0,'e',"Cancel",1);
				delay(20);
				button(l+60,t+70,60,20,1,'e',"Cancel",1);
				repaint(l,t,"image\\__ibim.img");
				return 0;
			}
			// if ok button revoked
			if( (mx>=(l+130)) && (mx<=(l+190)) && (my>=(t+70)) && (my<=(t+90)) )
			{
				button(l+130,t+70,60,20,0,'e',"Ok",1);
				delay(20);
				button(l+130,t+70,60,20,1,'e',"Ok",1);
				if(strlen(tmp_fl)>0)
				{
					strcpy(ostr,tmp_fl);
				}
				repaint(l,t,"image\\__ibim.img");
				return strlen(tmp_fl);
			}

		}
		gettime(&t1);
		if((t1.ti_hund/25)%2==0)
		{
			SetCur(cPos,t+42,15);
		}
		else
		{
			SetCur(cPos,t+42,0);
		}
		showmouse();
	}
}

int pwbox(int l, int t, char *cap, char *prompt, char *ostr, int mc)
{
	char tmp_fl[13];
	char pw_str[13];
	char ch;
	int cc=0;
	struct time t1;
	union REGS iin, iout;
	int cPos;
	int mb, mx, my;
	saveimg(l,t,l+250,t+100,"image\\__ibim.img");

	hidemouse();
	form(l,t,250,100,cap);

	label(l+50,t+25,prompt,2,4,5);
	textbox(l+50,t+40,150);
	button(l+60,t+70,60,20,1,'e',"Cancel",1);
	button(l+130,t+70,60,20,1,'e',"Ok",1);

	setcolor(0);
	rectangle(l+130-1,t+70-1,l+190,t+90);

	tmp_fl[cc]='\0';
	pw_str[cc]='\0';
	cPos=l+53;

	SetCur(cPos,t+42,0);
	showmouse();
	while(1)
	{
		if(kbhit())
		{
			iin.h.ah=0;
			int86(22,&iin,&iout);
			ch=iout.h.al;
			if( ((ch>=65) && (ch<=90)) || ((ch>=97)&&(ch<=122)) )
			{
				if(cc<mc-1)
				{
					hidemouse();
					tmp_fl[cc]=ch;
					pw_str[cc++]='*';
					tmp_fl[cc]='\0';
					pw_str[cc]='\0';
					SetCur(cPos,t+42,15);
					label(l+53,t+42,pw_str,2,4,0);
					cPos=l+53+textwidth(pw_str)+1;
					SetCur(cPos,t+42,0);
					showmouse();
				}
			}
		}
		if(ch==BS)
		{
			if(cc>0)
			{
				hidemouse();
				SetCur(cPos,t+42,15);
				cc--;
				tmp_fl[cc]='\0';
				pw_str[cc]='\0';
				textbox(l+50,t+40,150);
				label(l+53,t+42,pw_str,2,4,0);
				cPos=l+53+textwidth(tmp_fl)+1;
				SetCur(cPos,t+42,0);
				showmouse();
			}
			ch=0;
		}
		if(ch==ESC)
		{
			hidemouse();
			repaint(l,t,"image\\__ibim.img");
			return 0;
		}
		if(ch==ENTER)
		{
			hidemouse();
			if(strlen(tmp_fl)>0)
			{
				strcpy(ostr,tmp_fl);
			}
			repaint(l,t,"image\\__ibim.img");
			return strlen(tmp_fl);
		}
		getpos(&mb,&mx,&my);
		if(mb==1)
		{
			hidemouse();
			// if Close button revoked
			if( (mx>=(l+236)) && (mx<=(l+247)) && (my>=(t+3)) && (my<=(t+14)) )
			{
				repaint(l,t,"image\\__ibim.img");
				return 0;
			}
			// if cancel button revoked
			if( (mx>=(l+60)) && (mx<=(l+120)) && (my>=(t+70)) && (my<=(t+90)) )
			{
				button(l+60,t+70,60,20,0,'e',"Cancel",1);
				delay(20);
				button(l+60,t+70,60,20,1,'e',"Cancel",1);
				repaint(l,t,"image\\__ibim.img");
				return 0;
			}
			// if ok button revoked
			if( (mx>=(l+130)) && (mx<=(l+190)) && (my>=(t+70)) && (my<=(t+90)) )
			{
				button(l+130,t+70,60,20,0,'e',"Ok",1);
				delay(20);
				button(l+130,t+70,60,20,1,'e',"Ok",1);
				if(strlen(tmp_fl)>0)
				{
					strcpy(ostr,tmp_fl);
				}
				repaint(l,t,"image\\__ibim.img");
				return strlen(tmp_fl);
			}

		}
		gettime(&t1);
		if((t1.ti_hund/25)%2==0)
		{
			SetCur(cPos,t+42,15);
		}
		else
		{
			SetCur(cPos,t+42,0);
		}
		showmouse();
	}
}


int msgbox(int l, int t, char *cap, char *prompt)
{
	union REGS iin, iout;
	int mb, mx, my;
	int cPos;
	char ch;
	saveimg(l,t,l+250,t+100,"image\\__mgim.im");
	hidemouse();
	form(l,t,250,100,cap);
	label(l+(250-textwidth(prompt))/2,t+35,prompt,2,4,5);
	button(l+100,t+70,60,20,1,'e',"Ok",1);
	setcolor(0);
	rectangle(l+100-1,t+70-1,l+160,t+90);
	showmouse();
	while(1)
	{
		if(kbhit())
		{
			iin.h.ah=0;
			int86(0x16,&iin,&iout);
			ch=iout.h.al;
		}
		if(ch==ESC)
		{
			hidemouse();
			repaint(l,t,"image\\__mgim.im");
			return 0;
		}
		if(ch==ENTER)
		{
			hidemouse();
			repaint(l,t,"image\\__mgim.im");
			return 1;
		}
		getpos(&mb,&mx,&my);
		if(mb==1)
		{
			hidemouse();
			// if Close button revoked
			if( (mx>=(l+236)) && (mx<=(l+247)) && (my>=(t+3)) && (my<=(t+14)) )
			{
				repaint(l,t,"image\\__mgim.im");
				return 0;
			}
			// if ok button revoked
			if( (mx>=(l+100)) && (mx<=(l+160)) && (my>=(t+70)) && (my<=(t+90)) )
			{
				button(l+130,t+70,60,20,0,'e',"Ok",1);
				delay(20);
				button(l+130,t+70,60,20,1,'e',"Ok",1);
				repaint(l,t,"image\\__mgim.im");
				return 1;
			}
		}
		showmouse();
	}
}
void SetCur(int l, int t, int c)
{

	setcolor(c);
	line(l,t,l,t+10);
}

void button(int l,int t,int w,int h,int fl,char mode,char *s,int col)
{
	int lcol, rcol;
	if(fl==1)
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
	line(l+w,t,l+w,t+h);
	line(l,t+h,l+w,t+h);
	if(mode=='e')
	{
		setcolor(1);
	}
	else
	{
		setcolor(8);
	}
	setcolor(col);
	settextstyle(2,0,4);
	outtextxy(l+((w-textwidth(s))/2),t+((h-textheight(s))/2),s);

}
void dform(int l,int t, int w, int h, char *cap)
{

	int sl, st;
	sl=l+4;
	st=t+4;
	// Shadow
	setcolor(8);
	setfillstyle(1,8);
	pieslice(sl+3,st+3,0,360,3);
	pieslice(sl+3,st+h-3,0,360,3);
	pieslice(sl+w-3,st+3,0,360,3);
	pieslice(sl+w-3,st+h-3,0,360,3);
	bar(sl+3,st+3,sl+w-3,st+h-3);
	bar(sl,st+3,sl+3,st+h-3);
	bar(sl+3,st,sl+w-3,st+3);
	bar(sl+3,st+h-3,sl+w-3,st+h);
	bar(sl+w-3,st+3, sl+w,st+h-3);

	setcolor(15);
	setfillstyle(1,15);
	pieslice(l+3,t+3,0,360,3);
	pieslice(l+3,t+h-3,0,360,3);
	pieslice(l+w-3,t+3,0,360,3);
	pieslice(l+w-3,t+h-3,0,360,3);
	bar(l+3,t+3,l+w-3,t+h-3);
	bar(l,t+3,l+3,t+h-3);
	bar(l+3,t,l+w-3,t+3);
	bar(l+3,t+h-3,l+w-3,t+h);
	bar(l+w-3,t+3, l+w,t+h-3);

	setcolor(9);
	arc(l+3,t+3,90,180,3);
	arc(l+3,t+h-3,180,270,3);
	arc(l+w-3,t+3,0,90,3);
	arc(l+w-3,t+h-3,270,360,3);

	line(l,t+3,l,t+h-3);
	line(l+3, t, l+w-3, t);
	line(l+w, t+3, l+w, t+h-3);
	line(l+3, t+h, l+w-3, t+h);

	setcolor(1);
	settextstyle(0,0,1);
	outtextxy(l+5,t+3,cap);

	// Close Button
	setcolor(7);
	setfillstyle(1,7);
	pieslice(l+w-8,t+8,0,360,5);
	setcolor(4);
	settextstyle(2,0,4);
	outtextxy(l+w-10,t+1,"x");
}
void hlpbox(int l,int t, int w, int h, int hcode)
{
	int sl, st;
	int i=0,j;
	union REGS hin, hout;
	char ch=0;
	int GlowFl=0;
	int mb, mx, my;

	FILE *hlp;
	char tmp_str[20];
	int hLeft, hTop;
	struct hlp_hdr hl;

	//tmp_str[1]='\0';
	sl=l;
	st=t;

	hidemouse();
	saveimg(l,t,l+w,t+h,"image\\__him.im");
	setcolor(0);
	setfillstyle(1,0);

	pieslice(sl+5,st+5,0,360,5);
	pieslice(sl+5,st+h-5,0,360,5);
	pieslice(sl+w-5,st+5,0,360,5);
	pieslice(sl+w-5,st+h-5,0,360,5);

	bar(sl+5,st+5,sl+w-5,st+h-5);
	bar(l+8,t,l+w-8,t+8);
	bar(l,t+8,l+8,t+h-8);
	bar(l+8,t+h-8,l+w-8,t+h);
	bar(l+w-8,t+8,l+w,t+h-8);

	setcolor(14);
	arc(l+6,t+6,90,180,3);
	arc(l+6,t+h-6,180,270,3);
	arc(l+w-6,t+6,0,90,3);
	arc(l+w-6,t+h-6,270,360,3);

	line(l+2,t+7,l+2,t+h-7);
	line(l+7, t+2, l+w-7, t+2);
	line(l+w-2, t+7, l+w-2, t+h-7);
	line(l+7, t+h-2, l+w-7, t+h-2);

	// Close Button
	setcolor(4);
	setfillstyle(1,4);
	pieslice(l+w-9,t+9,0,360,5);
	setcolor(15);
	settextstyle(2,0,4);
	outtextxy(l+w-11,t+2,"x");
	if(hcode>0)
	{
		hLeft=l+4;
		hTop=t+15;
		hlp=fopen("help\\_mhelp.hl","rb");
		while(fread(&hl,sizeof(hl),1,hlp)!=NULL)
		{
			if(hl.hlp_code==hcode)
			{
				break;
			}
		}
		fclose(hlp);
		i=0;
		while(hl.hlp_det[i]!='\0')
		{
			if(hl.hlp_det[i]==' ')
			{
				tmp_str[0]=hl.hlp_det[i];
				tmp_str[1]='\0';
				i++;
			}
			else
			{
				j=0;
				while((hl.hlp_det[i]!=' ')&&(hl.hlp_det[i]!='\0'))
				{
					tmp_str[j]=hl.hlp_det[i];
					j++;
					i++;
				}
				tmp_str[j]='\0';
			}
			if(hLeft<(l+w-textwidth(tmp_str)))
			{
				label(hLeft,hTop,tmp_str,2,4,11);
				hLeft=hLeft+textwidth(tmp_str);
			}
			else
			{
				hTop=hTop+15;
				hLeft=l+4;
				if(tmp_str[0]!=' ')
				{
				label(hLeft,hTop,tmp_str,2,4,11);
				hLeft=hLeft+textwidth(tmp_str);
				}
			}
			i++;
		}
		fclose(hlp);
	}
	showmouse();
	while(1)
	{
		getpos(&mb,&mx,&my);
		if( (mx>=(l+w-15)) && (mx<=(l+w-4)) && (my>=(t+4)) && (my<=(t+15)) )
		{
			if( GlowFl == 0 )
			{
				hidemouse();
				setcolor(12);
				setfillstyle(1,12);
				pieslice(l+w-9,t+9,0,360,5);
				setcolor(15);
				settextstyle(2,0,4);
				outtextxy(l+w-11,t+2,"x");
				showmouse();
				GlowFl=1;
			}
		}
		else
		{
			if(GlowFl==1)
			{
				hidemouse();
				setcolor(4);
				setfillstyle(1,4);
				pieslice(l+w-9,t+9,0,360,5);
				setcolor(15);
				settextstyle(2,0,4);
				outtextxy(l+w-11,t+2,"x");
				showmouse();
				GlowFl=0;
			}
		}
		if(mb==1)
		{
			if( (mx>=(l+w-15)) && (mx<=(l+w-4)) && (my>=(t+4)) && (my<=(t+15)) )
			{
				hidemouse();
				repaint(l,t,"image\\__him.im");
				showmouse();
				return;
			}
		}
		if(kbhit())
		{
			hin.h.ah=0;
			int86(0x16,&hin,&hout);
			ch=hout.h.al;
		}
		if(ch==ESC)
		{
			hidemouse();
			repaint(l,t,"image\\__him.im");
			showmouse();
			return;
		}
		showmouse();
	}

}
void form(int l,int t, int w, int h, char *cap)
{
	setfillstyle(1,7);
	bar(l,t,l+w,t+h);
	setcolor(15);
	line(l,t,l+w,t);
	line(l,t,l,t+h);
	setcolor(8);
	line(l+w,t,l+w,t+h);
	line(l,t+h,l+w,t+h);
	setfillstyle(1,4);
	bar(l+1,t+1,l+w-1,t+16);
	setcolor(12);
	rectangle(l+1,t+1,l+w-1,t+16);
	setcolor(8);
	settextstyle(2,0,4);
	outtextxy(l+1+((w-textwidth(cap))/2),t+1,cap);
	setcolor(8);
	settextstyle(2,0,4);
	outtextxy(l+1+((w-textwidth(cap))/2),t+1,cap);
	setcolor(15);
	settextstyle(2,0,4);
	outtextxy(l+((w-textwidth(cap))/2),t,cap);
	button(l+w-14,t+3,11,11,1,'e',"",4);
	setcolor(4);
	settextstyle(2,0,4);
	outtextxy(l+w-10,t+1,"x");
}
void frame(int l, int t, int w, int h, int fl)
{

	int lcol,tcol;
	if(fl==0)
	{
		lcol=8;
		tcol=15;
	}
	else
	{
		lcol=15;
		tcol=8;
	}
	setcolor(tcol);
	rectangle(l, t, l+w, t+h);
	setcolor(lcol);
	rectangle(l-1, t-1, l+w-1, t+h-1);

}
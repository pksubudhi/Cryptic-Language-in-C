#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<io.h>
#include<fcntl.h>
#include<math.h>



#include "hdr\hlp_meta.h"
#include "hdr\keyconst.h"
#include "hdr\mouse.h"
#include "hdr\buffer.h"
#include "hdr\util.h"
#include "hdr\ctrl.h"

typedef struct
{
	char fCode;
	unsigned char fVal[8];
}FONT;

void lang_crea();
void _edit(char *);
void _encrypt();
void _decrypt();
void _help();

void SetFocus(int,int);
void desktop(int);

void font(int,int,int);
void block(int,int,int,int);
void plotf(int , int , int );
void set_font();
void save_font(char *);
void show_prev();
int chk_font();
void plotfnt(int , int , FONT );
char chr_code(FONT );
#define bCount 6
#define fCol 1


FONT f[26];     // Font Set

int dCol=3;
int tLeft[26], tTop[26];     //font left and top
union REGS in,out;
int EnFlg=-1;

int bLeft=20;    //button entity
int bWidth=150;
int bHight=40;

int bTop[bCount]={100,150,200,250,300,350};
char bCap[bCount][20]={"Language Creation","Editor","Encryption","Decreption","Help","Quit"};
char tTip[bCount][50]={
		"Click Here to create new cryptic language",
		"A Text editor to create textdocuments",
		"Encrypt the text document",
		"Decrypt the encrypted document",
		"Detail Description about Crylan 2.0",
		"Exit" };
int mBtn=-1, pBtn=-1;
int mPos=-1, pPos=-1;

void main()
{
	int mb,mx,my;

	int gd=DETECT,gm;
	int i;
	char ch;
	char scan;
	int CurBtn=-1;
	int SelBtn=0;
	int PrevBtn=-1;
	char str[9];
	int tl,tt;
	clrscr();
	initgraph(&gd,&gm,"gra");
	desktop(dCol);
	setcolor(1);
	settextstyle(4,0,6);
	outtextxy(100,20,"The Cryptic Editor");
	frame(bLeft-4,bTop[0]-4,bWidth+8,298,1);
	for(i=0;i<bCount;i++)
	{
		button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);

	}
	SetFocus(SelBtn,PrevBtn);

	initmouse();
	mouseshape(4,0,0);
	showmouse();

	while(1)
	{
		getpos(&mb,&mx,&my);
		for(i=0;i<bCount;i++)
		{
			if( (mx>=bLeft) && (mx<=(bLeft+bWidth)) && (my>=bTop[i]) && (my<=(bTop[i]+bHight)) )
			{
				mBtn=i;
				break;
			}
		}
		if(i==bCount)
		{
			mBtn=-1;
		}
		if( (mBtn>=0) && (mBtn!=pBtn) )
		{
			hidemouse();
			if(pBtn>=0)
			{
				hidemouse();
				repaint(tl,tt,"sys\\__ttip.img");
				button(bLeft,bTop[pBtn],bWidth,bHight,1,'e',bCap[pBtn],1);

				showmouse();
			}
			button(bLeft,bTop[mBtn],bWidth,bHight,1,'e',bCap[mBtn],4);
			tl=mx;
			tt=my;
			hidemouse();
			saveimg(tl,tt,tl+150,tt+50,"sys\\__ttip.img");
			showtips(tl,tt,tTip[mBtn]);
			pBtn=mBtn;
			showmouse();
		}
		else
		{
			if((pBtn>=0) && (mBtn!=pBtn) )
			{
				hidemouse();
				repaint(tl,tt,"sys\\__ttip.img");
				button(bLeft,bTop[pBtn],bWidth,bHight,1,'e',bCap[pBtn],1);

				showmouse();
				pBtn=mBtn;
			}

			showmouse();
		}


		if(mb==1)
		{
			for(i=0;i<bCount;i++)
			{
				if( (mx>=bLeft) && (mx<=(bLeft+bWidth)) && (my>=bTop[i]) && (my<=(bTop[i]+bHight)) )
				{
					hidemouse();
					PrevBtn=SelBtn;
					CurBtn=i;
					SelBtn=i;
					repaint(tl,tt,"sys\\__ttip.img");
					button(bLeft,bTop[i],bWidth,bHight,0,'e',bCap[i],1);
					delay(20);
					button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);
					SetFocus(SelBtn,PrevBtn);
					showmouse();
				}
			}
		}
		if(kbhit())
		{
			in.h.ah=0;
			int86(0x16,&in,&out);
			ch=out.h.al;
			scan=out.h.ah;
			switch(ch)
			{
			case 0:
				if(scan==72) // Up arrow
				{
					PrevBtn=SelBtn;
					if(CurBtn>0)
					{
						CurBtn=CurBtn-1;
						SelBtn=CurBtn;
					}
					else
					{
						CurBtn=bCount-1;
						SelBtn=bCount-1;
					}
					SetFocus(SelBtn,PrevBtn);
				}
				else
				{
					if(scan==80) // Dn arrow
					{
						PrevBtn=SelBtn;
						if(CurBtn<bCount-1)
						{
							CurBtn=CurBtn+1;
							SelBtn=CurBtn;
						}
						else
						{
							CurBtn=0;
							SelBtn=0;
						}
						SetFocus(SelBtn,PrevBtn);
					}
				}
				scan=-1;
				ch=-1;
				break;
			case ESC:
				closegraph();
				exit(1);
				break;
			case TAB:
				break;
			case ENTER:
				break;
			case F1:
			hidemouse();
			hlpbox(420,150,200,100,3);
			showmouse();
			scan=0;
			break;
		}
		}
		else
		{
		if(mb==1)
		{
		switch(CurBtn)
		{
			case 0:
				CurBtn=-1;
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'d',bCap[i],1);
				}
				showmouse();
				lang_crea();
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);
				}
				showmouse();
				break;
			case 1:
				CurBtn=-1;
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'d',bCap[i],1);
				}
				showmouse();
				EnFlg=-1;
				_edit("");
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);
				}
				showmouse();
				break;
			case 2:
				CurBtn=-1;
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'d',bCap[i],1);
				}
				showmouse();
				_encrypt();
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);
				}
				showmouse();
				break;
			case 3:
				CurBtn=-1;
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'d',bCap[i],1);
				}
				showmouse();
				_decrypt();
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);
				}
				showmouse();
				break;
			case 4:
				CurBtn=-1;
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'d',bCap[i],1);
				}
				showmouse();
				_help();
				hidemouse();
				for(i=0;i<bCount;i++)
				{
					button(bLeft,bTop[i],bWidth,bHight,1,'e',bCap[i],1);
				}
				showmouse();
				break;
			case 5:
				closegraph();
				exit(1);
				break;
		}
		}
		}
	}
}
void _edit(char *FileName)
{
	struct time t1;
	int fLeft=190,fTop=100,fWidth=420,fHight=300;
	int mb,my,mx,pmx,pmy;

	int cLeft, cTop;
	char ch=0,scan=0;

	int i,j;
	int fbTop=368;
	int fbLeft[3]={465,400,530};
	char fbCap[3][20]={"Encrypt","Cancel","Save"};
	int fcCtrl;
	char f_path[30];
	char _fname[13];
	char str[2];

	FILE *_tfile;   // Temporary file
	FILE *_dfile;   // Final Document
	FONT tmp_font;
	struct ffblk fb;
	// Font file header
	struct ff_head
	{
		char t[10];
		char sig[3];
		int cnt;
		int sz;
	}ffl_hd;
	// Encrypt file Header
	struct FileHeader
	{
		char t[10];
		char sig[3];
		char pw[9];
		int cnt;
	}efl_hd;
	efl_hd.cnt=0;
	strcpy(efl_hd.t,"Crylan.2");    // Owner

	_fname[0]='\0';
	_tfile=fopen("sys\\_tfile.txt","wb");
	str[1]='\0';
	hidemouse();
	saveimg(fLeft,100,319,400,"image\\_edi1.in");
	saveimg(320,100,419,400,"image\\_edi2.in");
	saveimg(420,100,519,400,"image\\_edi3.in");
	saveimg(520,100,620,400,"image\\_edi4.in");

	// Drawing the form
	form(fLeft,fTop,fWidth,fHight,"Text Editor");
	textedit(fLeft+20,fTop+20,fWidth-40,fHight-60);
	// Putting controls to the form
	/*for(i=0;i<3;i++)
	{
		button(fbLeft[i],fbTop,60,25,1,'e',fbCap[i]);
	}*/
	button(fbLeft[1],fbTop,60,25,1,'e',fbCap[1],1);
	if(EnFlg==-1)
	{
		button(fbLeft[0],fbTop,60,25,1,'e',fbCap[0],1);
	}
	else
	{
		if(EnFlg==1)
		{
			button(fbLeft[0],fbTop,60,25,1,'e',"Decrypt",1);
		}
		else
		{
			button(fbLeft[0],fbTop,60,25,1,'e',fbCap[0],1);
		}
		fcCtrl=0;
	}
	if(EnFlg==-1)
	{
		button(fbLeft[2],fbTop,60,25,1,'e',fbCap[2],1);
		fcCtrl=2;
	}
	setcolor(0);
	rectangle(fbLeft[fcCtrl]-1,fbTop-1,fbLeft[fcCtrl]+61,fbTop+26);
	// Loading the file
	if(strlen(FileName)>0)
	{
		cLeft=fLeft+24;
		cTop=fTop+24;
		if(EnFlg==1)
		{
			strcpy(f_path,"Docu\\En\\");
			strcat(f_path,FileName);
			strcat(f_path,".ef");
			if(findfirst(f_path,&fb,0)==0)
			{
				_tfile=fopen(f_path,"rb");
				fread(&efl_hd,sizeof(efl_hd),1,_tfile);
				hidemouse();
				// Skipping language (Embedded)
				for(i=0;i<26;i++)
				{
					fread(&tmp_font,sizeof(tmp_font),1,_tfile);
				}
				while(fread(&tmp_font,sizeof(tmp_font),1,_tfile)!=NULL)
				{
					SetCur(cLeft,cTop,15);
					if(tmp_font.fCode<=1)
					{
						plotfnt(cLeft,cTop,tmp_font);

					}
					else
					{
						sprintf(str,"%c",tmp_font.fCode);
						label(cLeft,cTop,str,2,4,1);
					}
					if(cLeft<(fLeft+fWidth-30))
					{
						cLeft=cLeft+10;
					}
					else
					{
						cLeft=fLeft+24;
						cTop=cTop+15;
					}
					SetCur(cLeft,cTop,0);
				}
				showmouse();
				button(fbLeft[0],fbTop,60,25,1,'e',"Decrypt",1);
			}
			else
			{
				msgbox(200,150,f_path,"Above File you want to load is not found.");
				button(fbLeft[0],fbTop,60,25,1,'d',"Decrypt",1);
			}
		}
		else if(EnFlg==0)
		{

			strcpy(f_path,"Docu\\Dn\\");
			strcat(f_path,FileName);
			strcat(f_path,".df");
			if(findfirst(f_path,&fb,0)==0)
			{
				_tfile=fopen(f_path,"rb");
				while((ch=getc(_tfile))!=EOF)
				{
					SetCur(cLeft,cTop,15);
					str[0]=ch;
					str[1]='\0';
					label(cLeft,cTop,str,2,4,1);
					if(cLeft<(fLeft+fWidth-30))
					{
						cLeft=cLeft+textwidth(str);
					}
					else
					{
						cLeft=fLeft+24;
						cTop=cTop+15;
					}
					SetCur(cLeft,cTop,0);
					efl_hd.cnt++;
				}
				button(fbLeft[0],fbTop,60,25,1,'e',fbCap[0],1);
			}
			else
			{
				msgbox(200,200,f_path,"Above File you want to load is not found.");
				button(fbLeft[0],fbTop,60,25,1,'d',fbCap[0],1);
			}
		}
	}
	else
	{
		cLeft=fLeft+24;
		cTop=fTop+24;
	}
	SetCur(cLeft,cTop,0);
	showmouse();
	while(1)
	{
		getpos(&mb,&mx,&my);

		if(mb==1)
		{
			// Close Button
			if( (mx>=(fLeft+fWidth-14)) && (mx<=(fLeft+fWidth-3))&&(my>=(fTop+3))&&(my<=(fTop+14)))
			{
				hidemouse();
				repaint(fLeft,100,"image\\_edi1.in");
				repaint(320,100,"image\\_edi2.in");
				repaint(420,100,"image\\_edi3.in");
				repaint(520,100,"image\\_edi4.in");
				showmouse();
				return;
			}
			// Cancel Button.
			if( (mx>=fbLeft[1]) && (mx<=(fbLeft[1]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)))
			{
				hidemouse();
				button(fbLeft[1],fbTop,60,25,0,'e',fbCap[1],1);
				delay(40);
				button(fbLeft[1],fbTop,60,25,1,'e',fbCap[1],1);
				repaint(fLeft,100,"image\\_edi1.in");
				repaint(320,100,"image\\_edi2.in");
				repaint(420,100,"image\\_edi3.in");
				repaint(520,100,"image\\_edi4.in");
				showmouse();
				return;
			}
			// Save Button
			if( (mx>=fbLeft[2]) && (mx<=(fbLeft[2]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)))
			{
				hidemouse();
				button(fbLeft[2],fbTop,60,25,0,'e',fbCap[1],1);
				delay(40);
				button(fbLeft[2],fbTop,60,25,1,'e',fbCap[1],1);
				if(inbox(100,100,"Saving Document.","Type File Name",_fname,8))
				{
					f_path[0]='\0';
					strcpy(f_path,"docu\\dn\\");
					strcat(f_path,_fname);
					strcat(f_path,".df");

					if(findfirst(f_path,&fb,0)!=0)
					{
						fclose(_tfile);
						_tfile=fopen("sys\\_tfile.txt","rb");
						_dfile=fopen(f_path,"wb");
						while((ch=getc(_tfile))!=EOF)
						{
							putc(ch,_dfile);
						}
						fclose(_tfile);
						fclose(_dfile);
						//unlink("\\_tfile.txt");
					}
					else
					{
						msgbox(100,100,"Invalid or Duplicate File","File already exists");
					}

				}
				else
				{

				}
				repaint(fLeft,100,"image\\_edi1.in");
				repaint(320,100,"image\\_edi2.in");
				repaint(420,100,"image\\_edi3.in");
				repaint(520,100,"image\\_edi4.in");
				showmouse();
				return;
			}
			// Encrypt Button
			if((EnFlg==0))
			{
			if( (mx>=fbLeft[0]) && (mx<=(fbLeft[0]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)) && ((EnFlg==0) || (EnFlg==-1)) )
			{
				hidemouse();
				button(fbLeft[0],fbTop,60,25,0,'e',fbCap[0],1);
				delay(40);
				button(fbLeft[0],fbTop,60,25,1,'e',fbCap[0],1);
				if(inbox(100,100,"Encrypting Document.","Type Language File Name",_fname,8))
				{
					if(strlen(_fname)>0)
					{
						f_path[0]='\0';
						strcpy(f_path,"Lang\\");
						strcat(f_path,_fname);
						strcat(f_path,".lng");
						if(findfirst(f_path,&fb,0)==0)
						{
							_dfile=fopen(f_path,"rb");
							i=0;
							fread(&ffl_hd,sizeof(ffl_hd),1,_dfile);
							while(fread(&tmp_font,sizeof(tmp_font),1,_dfile)!=NULL)
							{
								f[i]=tmp_font;
								i++;
							}
							fclose(_dfile);
						if(pwbox(100,100,"File Protection.","Type Password",_fname,8))
						{
							// Creating path for encrypted file
							strcpy(efl_hd.sig,"EF");        // Signature
							//Encrypting password
							for(i=0;_fname[i]!='\0';i++)
							{
								_fname[i]=_fname[i]+(123+i);
							}
							strcpy(efl_hd.pw,_fname);
							strcpy(f_path,"Docu\\En\\");
							strcat(f_path,FileName);
							strcat(f_path,".ef");
							_dfile=fopen(f_path,"wb");
							// Writing File Header
							fwrite(&efl_hd,sizeof(efl_hd),1,_dfile);
							// Writing the associated Language
							for(i=0;i<26;i++)
							{
								fwrite(&f[i],sizeof(f[i]),1,_dfile);
							}
							rewind(_tfile);
							while((ch=getc(_tfile))!=EOF)
							{

								if( (ch>=65) && (ch<=90) )
								{
									tmp_font=f[ch-65];
									tmp_font.fCode=1;
								}
								else
								{
									if( (ch>=97) && (ch<=122) )
									{
										tmp_font=f[ch-97];
										tmp_font.fCode=0;
									}
									else
									{
										tmp_font.fCode=ch;
										for(i=0;i<8;i++)
										{
											tmp_font.fVal[i]=0;
										}
									}
								}
								fwrite(&tmp_font,sizeof(tmp_font),1,_dfile);
							}
							hidemouse();
							fclose(_tfile);
							fclose(_dfile);
							repaint(fLeft,100,"image\\_edi1.in");
							repaint(320,100,"image\\_edi2.in");
							repaint(420,100,"image\\_edi3.in");
							repaint(520,100,"image\\_edi4.in");
							showmouse();
							return;
						}
					}
					else
					{
					msgbox(100,100,"Error! File not found","Language File not found");
					}
					}
					else
					{
						msgbox(100,100,"Error! Empty File Name","Language File not found");
					}
				}
				else
				{
					msgbox(100,100,"No or Empty Language","Process Aborted");
				}


			}
			EnFlg=-1;
			}
			// Decrypt Button
			if(EnFlg==1)
			{
			if( (mx>=fbLeft[0]) && (mx<=(fbLeft[0]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)) && (EnFlg==1))
			{
				hidemouse();
				button(fbLeft[0],fbTop,60,25,0,'e',fbCap[0],1);
				delay(40);
				button(fbLeft[0],fbTop,60,25,1,'e',fbCap[0],1);
				if(pwbox(100,100,"File is password protected.","Type Password",_fname,8))
				{
					if(strlen(_fname)>0)
					{
						rewind(_tfile);
						// Extracting the File Header
						fread(&efl_hd,sizeof(efl_hd),1,_tfile);
						//Decrypting password
						for(i=0;efl_hd.pw[i]!='\0';i++)
						{
							efl_hd.pw[i]=efl_hd.pw[i]-(123+i);
						}
						if(strcmp(_fname,efl_hd.pw)==0)
						{

							strcpy(f_path,"Docu\\Dn\\");
							strcat(f_path,FileName);
							strcat(f_path,".df");
							_dfile=fopen(f_path,"wb");

							// Getting the Language associated
							for(i=0;i<26;i++)
							{
								fread(&tmp_font,sizeof(tmp_font),1,_tfile);
								f[i]=tmp_font;
							}
							while(fread(&tmp_font,sizeof(tmp_font),1,_tfile)!=NULL)
							{
								fputc(chr_code(tmp_font),_dfile);
							}
							msgbox(100,100,"Acknowledgement","Decrementation Over");
							fclose(_tfile);
							fclose(_dfile);
						}
						else
						{
							msgbox(100,100,"Password mis typed?","The typed passwor does not match");
						}
					}
					else
					{
						msgbox(100,100,"Empty Password","Password not yet typed.");
					}
				}

			}
			EnFlg=-1;
			}

		}
		if(kbhit())
		{
			in.h.ah=0;
			int86(0x16,&in,&out);
			ch=out.h.al;
			scan=out.h.ah;
		}
		if(ch==ESC)
		{
			hidemouse();
			repaint(fLeft,100,"image\\_edi1.in");
			repaint(320,100,"image\\_edi2.in");
			repaint(420,100,"image\\_edi3.in");
			repaint(520,100,"image\\_edi4.in");
			showmouse();
			ch=0;
			return;
		}
		if(scan==F1)
		{
			hidemouse();
			hlpbox(420,150,200,100,4);
			showmouse();
			scan=0;
		}

		if(ch==ENTER)
		{
			SetCur(cLeft,cTop,15);
			cLeft=fLeft+24;
			cTop=cTop+15;
			SetCur(cLeft,cTop,15);
			fputc(ch,_tfile);
			ch=0;
		}
		if(ch==BS)
		{
			// Galat he
			SetCur(cLeft,cTop,15);
			if(cLeft>fLeft+24)
			{
				cLeft=cLeft-textwidth(str);
			}
			else
			{
				cLeft=fLeft+fWidth-30;
				cTop=cTop-15;
			}
			label(cLeft,cTop,str,2,4,15);
			SetCur(cLeft,cTop,15);
			ch=0;
		}
		else
		{

			if(isprint(ch) && (EnFlg==-1))
			{
				SetCur(cLeft,cTop,15);
				str[0]=ch;
				str[1]='\0';
				label(cLeft,cTop,str,2,4,1);
				if(cLeft<(fLeft+fWidth-30))
				{
					cLeft=cLeft+textwidth(str);
				}
				else
				{
					cLeft=fLeft+24;
					cTop=cTop+15;
				}
				SetCur(cLeft,cTop,0);
				fputc(ch,_tfile);
				ch=0;
			}
		}
		gettime(&t1);
		if((t1.ti_hund/25)%2==0)
		{
			SetCur(cLeft,cTop,15);
		}
		else
		{
			SetCur(cLeft,cTop,0);
		}
		showmouse();
	}
}
void _encrypt()
{
	char f_name[9];
	f_name[0]='\0';
	hidemouse();
	inbox(200,150,"To Encrypt a file.","Type the file name",f_name,8);
	showmouse();
	if(strlen(f_name)>0)
	{
		EnFlg=0;
		_edit(f_name);
		showmouse();
		//return;
	}
	else
	{
		hidemouse();
		msgbox(200,150,"Empty or Invalid File Name","May be file name not typed ..");
		showmouse();
		//return;

	}
	showmouse();
}
void _decrypt()
{
	char f_name[9];
	f_name[0]='\0';
	hidemouse();
	inbox(200,150,"To Decrypt a file.","Type the file name",f_name,8);
	showmouse();
	if(strlen(f_name)>0)
	{
		EnFlg=1;
		_edit(f_name);
		showmouse();
		//return;
	}
	else
	{
		hidemouse();
		msgbox(200,150,"Empty or Invalid File Name","May be file name not typed ..");
		showmouse();
		//return;
	}
	showmouse();
}
char chr_code(FONT tf)
{
	int i,j,n;
	if(tf.fCode>1)
	{
		return tf.fCode;
	}
	else
	{
		for(i=0;i<26;i++)
		{
			n=0;
			for(j=0;j<8;j++)
			{
				if(f[i].fVal[j]==tf.fVal[j])
				{
					n++;
				}
			}
			if(n==8)
			{
				if(tf.fCode==1)
				{
					return i+65;
				}
				else
				{
					return i+97;
				}
			}
		}
		return tf.fCode;
	}
}
void _help()
{
}
void lang_crea()
{
	int fLeft=190,fTop=100,fWidth=420,fHight=300;
	int mb,my,mx,pmx,pmy;
	char ch;
	char scan;
	int i,j;
	int fbTop=350;
	int fbLeft[3]={310,470,535};
	char fbCap[3][20]={"Preview","Cancel","Save"};
	int fcCtrl=2;
	char f_name[9];
	int ret_val;
	struct ffblk fb;
	char dup_file[30];

	f_name[0]='\0';
	hidemouse();
	saveimg(fLeft,100,319,400,"image\\_fimg1.in");
	saveimg(320,100,419,400,"image\\_fimg2.in");
	saveimg(420,100,519,400,"image\\_fimg3.in");
	saveimg(520,100,620,400,"image\\_fimg4.in");

	// Drawing the form
	form(fLeft,fTop,fWidth,fHight,"Language Creation");
	// Putting controls to the form
	for(i=0;i<3;i++)
	{
		button(fbLeft[i],fbTop,60,25,1,'e',fbCap[i],1);
	}
	setcolor(0);
	rectangle(fbLeft[fcCtrl]-1,fbTop-1,fbLeft[fcCtrl]+61,fbTop+26);
	// Refreshing the font set
	for(i=0;i<26;i++)
	{
		for(j=0;j<8;j++)
		{
			f[i].fVal[j]=0;
		}
	}
	for(i=0;i<=25;i++)
	{
		if( (i%8) == 0)
		{
			tLeft[i]=fLeft+15;
			if(i==0)
			{
				tTop[i]=fTop+25;
			}
			else
			{
				tTop[i]=tTop[i-1]+65;
			}
		}
		else
		{
			tLeft[i]=tLeft[i-1]+50;
			tTop[i]=tTop[i-1];
		}
		font(tLeft[i],tTop[i],i);
	}
	showmouse();
	while(1)
	{
		getpos(&mb,&mx,&my);

		if(mb==1)
		{
			if( (mx>=(fLeft+fWidth-14)) && (mx<=(fLeft+fWidth-3))&&(my>=(fTop+3))&&(my<=(fTop+14)))
			{
				hidemouse();
				repaint(fLeft,100,"image\\_fimg1.in");
				repaint(320,100,"image\\_fimg2.in");
				repaint(420,100,"image\\_fimg3.in");
				repaint(520,100,"image\\_fimg4.in");
				showmouse();
				return;
			}
			// Cancel Button.
			if( (mx>=fbLeft[1]) && (mx<=(fbLeft[1]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)))
			{
				hidemouse();
				button(fbLeft[1],fbTop,60,25,0,'e',fbCap[1],1);
				delay(40);
				button(fbLeft[1],fbTop,60,25,1,'e',fbCap[1],1);
				repaint(fLeft,100,"image\\_fimg1.in");
				repaint(320,100,"image\\_fimg2.in");
				repaint(420,100,"image\\_fimg3.in");
				repaint(520,100,"image\\_fimg4.in");
				showmouse();
				return;
			}
			// Preview Button
			if( (mx>=fbLeft[0]) && (mx<=(fbLeft[0]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)))
			{
				hidemouse();
				button(fbLeft[0],fbTop,60,25,0,'e',fbCap[0],1);
				delay(40);
				button(fbLeft[0],fbTop,60,25,1,'e',fbCap[0],1);
				set_font();

				show_prev();
				delay(120);
				showmouse();
			}
			// Save Button
			if( (mx>=fbLeft[2]) && (mx<=(fbLeft[2]+60)) &&(my>=(fbTop)) && (my<=(fbTop+25)))
			{
				hidemouse();
				button(fbLeft[2],fbTop,60,25,0,'e',fbCap[2],1);
				delay(40);
				button(fbLeft[2],fbTop,60,25,1,'e',fbCap[2],1);
				set_font();

				saveimg(200,150,500,210,"image\\__msgbar.im");
				button(200,150,300,60,1,'e',"Please Wait! Checking Integrity..",1);


				ret_val=chk_font();
				delay(120);

				repaint(200,150,"image\\__msgbar.im");
				if(ret_val==1)
				{
					inbox(200,150,"To save the Language..","Type File Name..",f_name,8);
					if(strlen(f_name)>0)
					{
						strcpy(dup_file,"lang\\");
						strcat(dup_file,f_name);
						strcat(dup_file,".lng");
						if(findfirst(dup_file,&fb,0)==0)
						{
							msgbox(200,150,"File Name already exists.","Language can not be overwitten..");
						}
						else
						{

							save_font(f_name);
							repaint(fLeft,100,"image\\_fimg1.in");
							repaint(320,100,"image\\_fimg2.in");
							repaint(420,100,"image\\_fimg3.in");
							repaint(520,100,"image\\_fimg4.in");
							showmouse();
							return;
						}
					}
					else
					{
						msgbox(200,150,"Empty file name or Aborted","Language not saved..");
					}
					showmouse();
				}
				else
				{
					if(ret_val==0)
					{
						msgbox(200,150,"Incomplete Language ","One or more font(s) not defined..");
					}
					else
					{
						msgbox(200,150,"Duplicate Font..,","One or more font(s) has similarity");
					}
				}
				showmouse();
				mb=0;
			}
			// Identifying Ticking selected block.
			for(i=0;i<=25;i++)
			{

				if( (mx>=tLeft[i]) && (mx<(tLeft[i]+40)) && (my>=tTop[i]+15) && (my<(tTop[i]+55)) )
				{
					if( (pmx!=mx) || (pmy!=my) )
					{
						block(mx,my,i,1);
						pmx=mx;pmy=my;
						break;
					}
				}
			}
		}
		if(mb==2)
		{
			for(i=0;i<=25;i++)
			{
				if( (mx>=tLeft[i]) && (mx<(tLeft[i]+40)) && (my>=tTop[i]+15) && (my<(tTop[i]+55)) )
				{
					if( (pmx!=mx) || (pmy!=my) )
					{
						block(mx,my,i,0);
						pmx=mx;pmy=my;
						break;
					}
				}
			}
		}

		if(kbhit())
		{
			in.h.ah=0;
			int86(0x16,&in,&out);
			ch=out.h.al;
			scan=out.h.ah;
		}
		if(ch==ESC)
		{
			hidemouse();
			repaint(fLeft,100,"image\\_fimg1.in");
			repaint(320,100,"image\\_fimg2.in");
			repaint(420,100,"image\\_fimg3.in");
			repaint(520,100,"image\\_fimg4.in");
			showmouse();
			ch=0;
			return;
		}
		if(ch==ENTER)
		{
			set_font();
			//chk_font();
		}
		if(scan==F1)
		{
			hidemouse();
			hlpbox(400,150,200,100,1);
			showmouse();
			scan=0;
		}

	}
}
void plotf(int l, int t, int c)
{
	int i,j;
	char bstr[9];
	int pLeft,pTop;
	pLeft=l;
	pTop=t;
	for(i=0;i<8;i++)
	{
		d2b(f[c].fVal[i],bstr);
		for(j=0;j<8;j++)
		{
			if(bstr[j]=='1')
			{
				putpixel(pLeft,pTop,1);
			}
			pLeft++;
		}
		pTop++;
		pLeft=l;
	}
}
void plotfnt(int l, int t, FONT c)
{
	int i,j;
	char bstr[9];
	int pLeft,pTop;
	pLeft=l;
	pTop=t;
	for(i=0;i<8;i++)
	{
		d2b(c.fVal[i],bstr);
		for(j=0;j<8;j++)
		{
			if(bstr[j]=='1')
			{
				putpixel(pLeft,pTop,1);
			}
			pLeft++;
		}
		pTop++;
		pLeft=l;
	}
}
void show_prev()
{
	int fLeft=200, fTop=200, fWidth=250, fHeight=150;
	int mb, mx, my;
	union REGS pi, po;
	int GlowFl=0;
	char ch;
	int i;
	int aLeft, aTop, nLeft,nTop;
	char str[6];
	hidemouse();
	saveimg(fLeft,fTop,fLeft+fWidth+5,fTop+fHeight+5,"image\\__prev.im");
	dform(fLeft,fTop,fWidth,fHeight,"Font Preview..");
	setcolor(9);
	rectangle(fLeft+5,fTop+20,fLeft+fWidth-5,fTop+fHeight-10);
	for(i=1;i<=8;i++)
	{
		line(fLeft+(i*30)+5,fTop+20,fLeft+(i*30)+5,fTop+fHeight-10);
	}
	for(i=1;i<=8;i++)
	{
		line(fLeft+5,fTop+(i*15)+20,fLeft+fWidth-5,fTop+(i*15)+20);
	}
	aLeft=fLeft+10;
	nLeft=fLeft+10;
	aTop=fTop+20;
	nTop=aTop+20;
	for(i=0;i<=25;i++)
	{
		sprintf(str,"%c",i+65);
		settextstyle(2,0,4);
		setcolor(5);
		if(i==0)
		{
			outtextxy(aLeft,aTop,str);
			plotf(nLeft,nTop,i);
		}
		else
		{
			if(i%8==0)
			{
				aTop=aTop+30;
				aLeft=fLeft+10;
				nLeft=fLeft+10;
				nTop=aTop+20;

			}
			else
			{
				aLeft=aLeft+30;
				nLeft=nLeft+30;
			}

			outtextxy(aLeft,aTop,str);
			plotf(nLeft,nTop,i);
		}
	}
	showmouse();
	while(1)
	{
		getpos(&mb,&mx,&my);
		if( (mx>=(fLeft+fWidth-14)) && (mx<=(fLeft+fWidth-3)) && (my>=(fTop+3)) && (my<=(fTop+14)) )
		{
			if( GlowFl == 0 )
			{
				hidemouse();
				setcolor(8);
				setfillstyle(1,8);
				pieslice(fLeft+fWidth-8,fTop+8,0,360,5);
				setcolor(15);
				settextstyle(2,0,4);
				outtextxy(fLeft+fWidth-10,fTop+1,"x");
				showmouse();
				GlowFl=1;
			}
		}
		else
		{
			if(GlowFl==1)
			{
				hidemouse();
				setcolor(7);
				setfillstyle(1,7);
				pieslice(fLeft+fWidth-8,fTop+8,0,360,5);
				setcolor(4);
				settextstyle(2,0,4);
				outtextxy(fLeft+fWidth-10,fTop+1,"x");
				showmouse();
				GlowFl=0;
			}
		}
		if(mb==1)
		{
			if( (mx>=(fLeft+fWidth-14)) && (mx<=(fLeft+fWidth-3)) && (my>=(fTop+3)) && (my<=(fTop+14)) )
			{
				hidemouse();
				repaint(fLeft,fTop,"image\\__prev.im");
				showmouse();
				return;
			}
		}
		if(kbhit())
		{
			pi.h.ah=0;
			int86(0x16,&pi, &po);
			ch=po.h.al;
		}
		if(ch==27)
		{
			hidemouse();
			repaint(fLeft,fTop,"image\\__prev.im");
			showmouse();
			return;
		}
		showmouse();
	}
}
void save_font(char *fn)
{
	// Font file header
	struct ff_head
	{
		char t[10];
		char sig[3];
		int cnt;
		int sz;
	}fl_hd;

	FILE *ft;
	int i;
	char fname[30];

	strcpy(fname,"lang\\");
	strcat(fname,fn);
	strcat(fname,".lng");

	ft=fopen(fname,"wb");

	if(ft==NULL)
	{
		msgbox(200,150,"Error: File operation.","Unable to save file");
		return;
	}

	//Setting file header
	strcpy(fl_hd.t,"Crylan.2");    // Owner
	strcpy(fl_hd.sig,"LN");        // Signature
	fl_hd.cnt=26;                  // Count
	fl_hd.sz=8;                    // Size of font
	fwrite(&fl_hd,sizeof(fl_hd),1,ft);
	for(i=0;i<26;i++)  //
	{
		fwrite(&f[i],sizeof(f[i]),1,ft);
	}
	fclose(ft);
	msgbox(200,150,"Acknowledgement.","Language Saved...");
}
int chk_font()
{
	int i,j,k;
	int n;
	// Checking Completeness
	for(i=0;i<26;i++)
	{
		n=0;
		for(j=0;j<8;j++)
		{
			n = n + f[i].fVal[j];

		}
		if(n==0)
		{
			return 0;
		}
	}
	// Duplicate checking
	for(i=0;i<26;i++)
	{
		for(j=0;j<26;j++)
		{
			if(i!=j)
			{
				n=0;
				for(k=0;k<8;k++)
				{
					if( f[i].fVal[k] == f[j].fVal[k] )
					{
						n++;
					}
				}
				if(n==8)
				{
					return -1;
				}
			}
		}
	}
	return 1;
}

void set_font()
{

	char bStr[9];
	int i,j,k;
	bStr[8]='\0';
	for(i=0;i<26;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<8;k++)
			{
				if(getpixel(tLeft[i]+(k*5)+2,tTop[i]+15+(j*5)+2)==fCol)
				{
					bStr[k]='1';
				}
				else
				{
					bStr[k]='0';
				}
			}
			f[i].fVal[j]=b2d(bStr);
		}
		f[i].fCode=i;
	}

}
void block(int x, int y, int fc, int fl)
{
	int bl,bt;
	int col;
	if(fl==1)
	{
		col=fCol;
	}
	else
	{
		col=7;
	}

	bl = tLeft[fc] + ((x-tLeft[fc])/5)*5;
	bt = tTop[fc] + 15 + ((y-(tTop[fc]+15))/5)*5;
	hidemouse();
	setfillstyle(1,col);
	bar(bl+1,bt+1,bl+4,bt+4);
	showmouse();
}
void font(int fl, int ft, int fc)
{
	int i;
	char s[5];
	sprintf(s,"%c(%c)",fc+65,fc+97);
	button(fl,ft,40,13,1,'e',s,1);

	frame(fl-2,ft-2,46,60,1);
	setcolor(9);

	rectangle(fl,ft+15,fl+40,ft+55);
	for(i=1;i<=7;i++)
	{
		line(fl+(i*5),ft+15,fl+(i*5),ft+55);
		line(fl,ft+(i*5)+15,fl+40,ft+(i*5)+15);
	}
}
void desktop(int n)
{
	setfillstyle(1,n);
	bar(0,0,639,479);
}
void SetFocus(int s, int p)
{
	if(p>=0)
	{
		setcolor(dCol);
		rectangle(bLeft-1,bTop[p]-1,bLeft+bWidth+1,bTop[p]+bHight+1);
	}
	setcolor(0);
	rectangle(bLeft-1,bTop[s]-1,bLeft+bWidth+1,bTop[s]+bHight+1);
}

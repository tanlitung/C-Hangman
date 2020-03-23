/*=====================================================================================

					HANGMAN

---------------------------------------------------------------------------------------

 Author 1:  TAN LI TUNG
 Author 2:  TEOH LYNN JING

 ---------------------------------------------------------------------------------------

***Change the path of the "data.txt" and "words.txt" in line 450,491,773 before use.***

=====================================================================================*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#include "gfx.h"

void header();
void keyboard();
void rack();
void head();
void body();
void hand();
void leg();
void base();
void hang();
void level_keyboard();
char read_level();
char read_input();
void home_page();
int read_home();
int quit();

int main()
{
/*-----------------------------------------------------------------------------------*/
/*---------------------------------Variable Declaration------------------------------*/
/*-----------------------------------------------------------------------------------*/
	int max=100;
	char word[max];
	char c=' ';
	int count=0;
	int i=0;
	int wordlength=0;
	int match=0;
	int correct=0;
	int rand1=0;
	int rand2=0;
	int level=0;
	int opt;
	int mode;
	int x,y;
	int game_played;
	int highest_score;
	int line=0;
	int score=0;
	char copy[max];
	char data[max];
	char highest[max];
	char game[max];
	char scored[max];
	
	FILE *fptr;
	
	srand(time(NULL));
	gfx_open(900,900,"Hangman");//open gfx window
	gfx_clear_color(15,128,234);

/*-----------------------------------------------------------------------------------*/
/*---------------------------------------Game Start----------------------------------*/
/*-----------------------------------------------------------------------------------*/
	
	while (1)//infinite loop so that game will loop until quit is hit
	{	
		gfx_clear();//clear screen
		header();
		home_page();
		mode=0;
		while (mode<1 || mode>4)
		{
			mode=read_home();
		}
		
		opt=5;//make sure the game wont quit itself

/*-----------------------------------------------------------------------------------*/
/*---------------------------------Human vs Human------------------------------------*/
/*-----------------------------------------------------------------------------------*/
		
		if (mode==1)
		{
			printf("/*-----------------------------------------------------------------------------------*/\n");
			printf("/*---------------------------------Human vs Human------------------------------------*/\n");
			printf("/*-----------------------------------------------------------------------------------*/\n");

			while (opt!=0)//human vs human
			{
				opt=5;
				for (i=0;i<=max;i++)//clear word array
				{
					word[i]=' ';
				}
				
				gfx_clear();//display a hangman
				header();
				rack();
				head();
				hand();
				leg();
				body();
				base();
				gfx_color(255,255,255);
				gfx_text("Enter a word to be guessed",300,250);//end of display hangman
				
				i=0;
				c=' ';
				while (c!='\r')
				{
					gfx_color(15,128,234);
					gfx_fillrectangle(200,300,700,50);
					gfx_color(255,255,255);
					gfx_text(word,375,300);
					keyboard();
					c=read_input();
					if (c>='a' && c<='z')
					{
						c=c-32;
						word[i]=c;
						i++;
					}
					
					else if (c>='A' && c<='Z')
					{
						word[i]=c;
						i++;
					}
					
					else if (c=='\r' || c==' ')
					{
						word[i]=c;
						i++;
					}
					
					else if (c=='\b')
					{
						word[i-1]=' ';
						i--;
						
					}
					else
					{}
				}
				
				printf("/*-----------------------------------------------------------------------------------*/\n");
				printf("/*---------------------------------End of Input--------------------------------------*/\n");
				printf("/*-----------------------------------------------------------------------------------*/\n");


/*-----------------------------------------------------------------------------------*/
/*---------------------------------Calculate Word Length-----------------------------*/
/*-----------------------------------------------------------------------------------*/

				wordlength=0;
				for(i=0;i<=max;i++)
				{
					if (word[i]!='\r')
					{
						wordlength++;
					}
					else
					{
						break;
					}
				}
				
				printf("\n\nWord Length = %d\n\n",wordlength);
				
				for (i=0;i<max;i++)//clear copy
				{
					copy[i]=' ';
				}
				strcpy(copy, word);
				for (i=wordlength;i<max;i++)
				{
					word[i]=' ';
					copy[i]=' ';
				}
				
				for (i=0;i<wordlength;i++)
				{
					if (copy[i]!=' ')
					{
						copy[i]='_';
					}
				}
				
				printf("Word is %s\n\n",word);
				printf("Copy is %s\n\n",copy);
				
/*-----------------------------------------------------------------------------------*/
/*---------------------------------Generate Random Number----------------------------*/
/*-----------------------------------------------------------------------------------*/

				rand1=rand()%wordlength;
				
				for(i=0;i<5;i++)
				{
					rand2=rand()%wordlength;
					if (rand2!=rand1)
					{
						break;
					}
				}
				
				printf("\n\nRandom numer 1 is %d\n",rand1);
				printf("Random numer 2 is %d\n\n",rand2);
/*-----------------------------------------------------------------------------------*/
/*-------------------------------------Select Level----------------------------------*/
/*-----------------------------------------------------------------------------------*/

				printf("/*-----------------------------------------------------------------------------------*/\n");
				printf("/*-------------------------------------Select Level----------------------------------*/\n");
				printf("/*-----------------------------------------------------------------------------------*/\n");

				gfx_clear();
				header();
				level_keyboard();
				level=0;
				while (level<49 || level>51)
				{
					level=read_level();
					switch (level)
					{
						case 49:printf("level=1\n");
							break;
						case 50:printf("level=2\n");
							break;
						case 51:printf("level=3\n");
							break;
						default: break;
					}
				}
				
				if (level==49)
				{
					for (i=0;i<wordlength;i++)
					{
						if (i==rand1 || i==rand2)
						{
							copy[i]=word[i];
						}
					}
				}
				
				
				if (level==50)
				{
					for (i=0;i<wordlength;i++)
					{
						if (i==rand1)
						{
							copy[i]=word[i];
						}
					}
				}
				
				printf("\n\nWord is %s\n\n",word);
				printf("Copy is %s\n\n",copy);
				

/*-----------------------------------------------------------------------------------*/
/*---------------------------------------Player--------------------------------------*/
/*-----------------------------------------------------------------------------------*/
				x=450-((wordlength/2)*12);
				printf("x=%d\n",x);
				gfx_clear();
				header();
				gfx_color(255,255,255);
				gfx_text("Guess the word !!!",325,250);
				gfx_text(copy,x,300);
				keyboard();
				count=0;
				while (count<6)
				{
					correct=0;
					for(i=0;i<wordlength;i++)
					{
						if (copy[i]==word[i])
						{
							correct++;
						}
					}
					
					if(correct==wordlength)
					{
						break;
					}
					
					gfx_color(15,128,234);
					gfx_fillrectangle(100,300,800,50);
					gfx_color(255,255,255);
					gfx_text(copy,x,300);
					
					printf("%s\n",copy);
					
					switch (count)
						{
							case 1:	rack();
								base();
								break;
							case 2:	{
								rack();
								base();
								head();
								break;
								}
							case 3:	{
								rack();
								head();
								body();
								base();
								break;
								}
							case 4:	{
								rack();
								head();
								hand();
								body();
								base();
								break;
								}
							case 5:	{
								rack();
								head();
								hand();
								leg();
								body();
								base();
								break;
								}
							default : break;
						}//end switch case
						
					c=read_input();
					
					if (c>='a' && c<='z')
					{
						c=c-32;
						match=0;
						
						for(i=0;i<wordlength;i++)
						{
							if(c==word[i])
							{
								match=1;
								copy[i]=c;
							}
						}
					}
					
					
					else if (c>='A' && c<='Z')
					{
						match=0;
						
						for(i=0;i<wordlength;i++)
						{
							if(c==word[i])
							{
								match=1;
								copy[i]=c;
							}
						}
					}
					
					else 
					{
						match=1;
					}
					
					
					if (match==0)
					{
						count++;
					}
				}//end of while
				
				gfx_clear();
				
				if (correct==wordlength)
				{
					header();
					gfx_color(255,255,255);
					gfx_text("Congratulations !!!",315,400);
				}	
				else
				{
					header();
					gfx_color(255,255,255);	
					gfx_text("The word is",x-145,280);
					gfx_text(word,x,280);
					hang();
				}
				
				while (opt<0 || opt>1)
				{
					opt=quit();
				}
				printf("option = %d\n", opt);
				gfx_clear();
			}

		printf("/*-----------------------------------------------------------------------------------*/\n");
		printf("/*---------------------------------End of Human vs Human-----------------------------*/\n");
		printf("/*-----------------------------------------------------------------------------------*/\n");
				
		}//end of human vs human

/*-----------------------------------------------------------------------------------*/
/*---------------------------------Human vs Computer---------------------------------*/
/*-----------------------------------------------------------------------------------*/
		
		else if (mode==2)
		{	
			score=0;
			printf("/*-----------------------------------------------------------------------------------*/\n");
			printf("/*-------------------------------------Human vs Computer-----------------------------*/\n");
			printf("/*-----------------------------------------------------------------------------------*/\n");
			while (opt!=0)//human vs computer
			{
				opt=5;
				for (i=0;i<max;i++)//clear array
				{
					copy[i]=' ';
					word[i]=' ';
				}
/*-----------------------------------------------------------------------------------*/
/*---------------------------------------Read data-----------------------------------*/
/*-----------------------------------------------------------------------------------*/

				printf("\n\n\n\n/*-----------------------------------------------------------------------------------*/\n");
				printf("/*---------------------------------------Read data-----------------------------------*/\n");
				printf("/*-----------------------------------------------------------------------------------*/\n");
			
				if ((fptr = fopen("/hangman/data.txt","r"))==NULL)//chage the path of the "data.txt" file
				{
					exit(1);
				}
				i=0;
				while(fgets(data,sizeof(data),fptr))
				{
					i++;
					if (i==1)
					{
						game_played=atoi(data);
						printf("Game played= %d\n",game_played);
					}
					
					else if (i==2)
					{
						highest_score=atoi(data);
						printf("Highest score= %d\n",highest_score);
					}
					
					else 
					{
						break;
					}
				}
				fclose(fptr);

/*-----------------------------------------------------------------------------------*/
/*---------------------------------Read a Radom Word---------------------------------*/
/*-----------------------------------------------------------------------------------*/

				printf("\n\n\n\n/*-----------------------------------------------------------------------------------*/\n");
				printf("/*---------------------------------Read a Radom Word---------------------------------*/\n");
				printf("/*-----------------------------------------------------------------------------------*/\n");
				
				line =0;
				while (line<1 || line >48)
				{
					line=rand()%48;
				}
				
				if ((fptr = fopen("/hangman/words.txt","r"))==NULL)//chage the path of the "words.txt" file
				{
					exit(1);
				}
				

				while(fgets(data,sizeof(data),fptr))
				{
					i++;
					if (i==line)
					{
						printf("Word in file is %s\n",data);
						strcpy(word,data);
						printf("Word copied is %s\n",word);
						strcpy(copy,data);
						printf("Copy is %s\n\n\n",word);
					}
				}
				fclose(fptr);
				
				wordlength=0;
				gfx_clear();
				header;
				i=0;
				while (word[i]!='\n')
				{
					wordlength++;
					i++;
				}
				
				for (i=0;i<wordlength;i++)
				{
					if (copy[i]!=' ')
					{
						copy[i]='_';
					}
				}
				
				printf("Word is %s\n",word);
				printf("Copy is %s\n\n\n",word);

/*-----------------------------------------------------------------------------------*/
/*---------------------------------Generate Random Number----------------------------*/
/*-----------------------------------------------------------------------------------*/

				rand1=rand()%wordlength;
				
				for(i=0;i<5;i++)
				{
					rand2=rand()%wordlength;
					if (rand2!=rand1)
					{
						break;
					}
				}
				
				printf("\n\nRandom numer 1 is %d\n",rand1);
				printf("Random numer 2 is %d\n\n",rand2);
				
/*-----------------------------------------------------------------------------------*/
/*------------------------------------Select Level-----------------------------------*/
/*-----------------------------------------------------------------------------------*/

				printf("/*-----------------------------------------------------------------------------------*/\n");
				printf("/*-------------------------------------Select Level----------------------------------*/\n");
				printf("/*-----------------------------------------------------------------------------------*/\n");
				
				gfx_clear();
				header();
				level_keyboard();
				level=0;
				while (level<49 || level>51)
				{
					level=read_level();
					switch (level)
					{
						case 49:printf("level=1\n");
							break;
						case 50:printf("level=2\n");
							break;
						case 51:printf("level=3\n");
							break;
						default: break;
					}
				}
				
				if (level==49)
				{
					for (i=0;i<wordlength;i++)
					{
						if (i==rand1 || i==rand2)
						{
							copy[i]=word[i];
						}
					}
				}
				
				
				if (level==50)
				{
					for (i=0;i<wordlength;i++)
					{
						if (i==rand1)
						{
							copy[i]=word[i];
						}
					}
				}

/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------Player------------------------------------*/
/*-----------------------------------------------------------------------------------*/
	
				gfx_clear();
				header();
				x=450-((wordlength/2)*12);
				gfx_text(copy,x,320);
				printf("%s\n",copy);
				keyboard();
				count=0;
				while (count<6)
				{
					correct=0;
					for(i=0;i<wordlength;i++)
					{
						if (copy[i]==word[i])
						{
							correct++;
						}
					}
					
					if(correct==wordlength)
					{
						break;
					}
					gfx_color(15,128,234);
					gfx_fillrectangle(10,210,890,140);
					
					gfx_color(255,255,255);
					gfx_text("Highest Score ",50,240);
					sprintf(highest,"%d",highest_score);
					gfx_text(highest,220,240);
					gfx_rectangle(30,220,250,65);
					
					gfx_text("Your Score ",370,240);
					sprintf(scored,"%d",score);
					gfx_text(scored,520,240);
					gfx_rectangle(350,220,210,65);
					
					gfx_text("Game Played ",655,240);
					sprintf(game,"%d",game_played);
					gfx_text(game,800,240);
					gfx_rectangle(630,220,230,65);
				
					gfx_color(15,128,234);
					gfx_fillrectangle(200,300,700,50);
					gfx_color(255,255,255);
					gfx_text(copy,x,320);
					
					printf("%s\n",copy);
					
					switch (count)
						{
							case 1:	rack();
								base();
								break;
							case 2:	{
								rack();
								base();
								head();
								break;
								}
							case 3:	{
								rack();
								head();
								body();
								base();
								break;
								}
							case 4:	{
								rack();
								head();
								hand();
								body();
								base();
								break;
								}
							case 5:	{
								rack();
								head();
								hand();
								leg();
								body();
								base();
								break;
								}
							default : break;
						}//end switch case
						
					c=read_input();
					
					if (c>='a' && c<='z')
					{
						c=c-32;
						match=0;
						
						for(i=0;i<wordlength;i++)
						{
							if(c==word[i])
							{
								match=1;
								copy[i]=c;
							}
						}
					}
					
					
					else if (c>='A' && c<='Z')
					{
						match=0;
						
						for(i=0;i<wordlength;i++)
						{
							if(c==word[i])
							{
								match=1;
								copy[i]=c;
							}
						}
					}
					
					else 
					{
						match=1;
					}
					
					
					if (match==0)
					{
						count++;
					}

					
				}//end of while
				
				gfx_clear();
				gfx_color(255,255,255);
				if (correct==wordlength)
				{
					header();
					gfx_color(255,255,255);
					gfx_text("Congratulations !!!",315,400);
					score+=(level-48);
					
					gfx_text("Your Score ",370,240);
					sprintf(scored,"%d",score);
					gfx_text(scored,520,240);
					gfx_rectangle(350,220,210,65);
					
					if (score>highest_score)
					{
						highest_score=score;
					}
					printf("score= %d\n",score);
				}	
				else
				{
					header();
					gfx_color(255,255,255);	
					gfx_text("The word is",x-145,280);
					gfx_text(word,x,280);
					hang();
					
					gfx_color(255,255,255);
					gfx_text("Your Score 0",380,220);
					gfx_rectangle(350,200,210,65);
				}
				
				game_played++;
				printf("Game played=%d\n",game_played);
				printf("Highest score=%d\n",highest_score);
					
				if ((fptr = fopen("/hangman/data.txt","w"))==NULL)//chage the path of the "data.txt" file
				{
					exit(1);
				}
					
				for(i=1;i<=2;i++)
				{
					if (i==1)
					{
						fprintf(fptr,"%d\n",game_played);
					}
						
					if (i==2)
					{
						fprintf(fptr,"%d\n",highest_score);
					}
				}
					
				fclose(fptr);
				
				while (opt<0 || opt>1)
				{
					opt=quit();
				}
				printf("option = %d\n", opt);
				gfx_clear();
			}
		
		printf("/*-----------------------------------------------------------------------------------*/\n");
		printf("/*-------------------------------End of Human vs Computer----------------------------*/\n");
		printf("/*-----------------------------------------------------------------------------------*/\n");
		
		}//end of human vs computer

/*-----------------------------------------------------------------------------------*/
/*----------------------------------------Rules--------------------------------------*/
/*-----------------------------------------------------------------------------------*/

		else if (mode==3)
		{
			printf("/*-----------------------------------------------------------------------------------*/\n");
			printf("/*----------------------------------------Rules--------------------------------------*/\n");
			printf("/*-----------------------------------------------------------------------------------*/\n");
			
			gfx_clear();
			header();
			gfx_color(255,255,255);
			
			gfx_text("One of the player will enter the word to be guessed. ", 100, 300);
			gfx_text("The other player will guess the word.", 100, 350);
			gfx_text("The computer will prepare the words to be guessed.", 100, 520);
			gfx_text("Select a level and guess the word.", 100, 570);
			gfx_text("One mark for 1 one correct word in level 1.", 100, 620);
			gfx_text("Two mark for 1 one correct word in level 2.", 100, 670);
			gfx_text("Three mark for 1 one correct word in level 3.", 100, 720);
			gfx_text("Press any key to continue", 100, 810);
			gfx_fillrectangle(90,225,230,50);
			gfx_fillrectangle(90,445,230,50);
			gfx_color(0,0,0);
			gfx_text("Human vs Human", 125, 240);
			gfx_text("Human vs Computer", 105, 460);
			gfx_wait();
			
		
		}

/*-----------------------------------------------------------------------------------*/
/*------------------------------------------Quit-------------------------------------*/
/*-----------------------------------------------------------------------------------*/

		else
		{
			printf("/*-----------------------------------------------------------------------------------*/\n");
			printf("/*----------------------------------------Quit---------------------------------------*/\n");
			printf("/*-----------------------------------------------------------------------------------*/\n");
			break;
		}
	}
	
	return 0;
}// end of main
































































/*-----------------------------User Defined Functions-------------------------------*/
void home_page()
{
	int y;
	header();
	for (y=400;y<=700;y+=100)
	{
		gfx_color(255,255,255);
		gfx_fillrectangle(300,y,300,50);
	}
	
	gfx_color(0,0,0);
	
	gfx_fillcircle(450,250,50);
	gfx_fillrectangle(420,290,60,10);
	gfx_fillrectangle(445,250,10,80);
	gfx_fillrectangle(420,330,60,10);
	gfx_fillrectangle(420,340,10,20);
	gfx_fillrectangle(470,340,10,20);
	
	gfx_text("Human VS Human",365,415);
	gfx_text("Human VS Computer",360,515);
	gfx_text("Help",430,615);
	gfx_text("Quit",430,715);
}

int read_home()
{
	char c;
	int mode;
	c=gfx_wait();
		if (c==0x01||c==0x02||c==0x03)//mouse input
		{
			if (gfx_xpos()>=300 && gfx_xpos()<=600)
			{
				 if (gfx_ypos()>=400 && gfx_ypos()<=450)
				 {
				 	printf("Human vs Human\n");
				 	mode=1;
				 }
				 
				 else if (gfx_ypos()>=500 && gfx_ypos()<=550)
				 {
				 	printf("Human vs Computer\n");
				 	mode=2;
				 }
				 
				 else if (gfx_ypos()>=600 && gfx_ypos()<=650)
				 {
				 	printf("Help\n");
				 	mode=3;
				 }
				 
				  else if (gfx_ypos()>=700 && gfx_ypos()<=750)
				 {
				 	printf("Quit\n");
				 	mode=4;
				 }
				 
				 else
				 {
				 	mode=0;
				 }
			}
		}
		
		else
		{
			mode=0;
		}//keyboard input
		
	return mode;
}

void header()
{
	gfx_color(255,255,255);
	gfx_fillrectangle(170,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(190,80,20,35);
	gfx_fillrectangle(190,135,20,35);
	
	gfx_color(255,255,255);
	gfx_fillrectangle(250,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(270,100,20,20);
	gfx_fillrectangle(270,140,20,30);
	
	gfx_color(255,255,255);
	gfx_fillrectangle(330,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(350,100,20,70);
	
	gfx_color(255,255,255);
	gfx_fillrectangle(410,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(430,100,20,50);
	gfx_fillrectangle(450,100,20,30);
	
	gfx_color(255,255,255);
	gfx_fillrectangle(490,80,60,90);
	gfx_fillrectangle(530,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(510,100,20,70);
	gfx_fillrectangle(550,100,20,70);
	
	gfx_color(255,255,255);
	gfx_fillrectangle(610,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(630,100,20,20);
	gfx_fillrectangle(630,140,20,30);
	
	gfx_color(255,255,255);
	gfx_fillrectangle(690,80,60,90);
	gfx_color(15,128,234);
	gfx_fillrectangle(710,100,20,70);
}

void keyboard()
{
	int y,i,x;
	gfx_color(255,255,255);
	y=392;
	for(i=1;i<=4;i++)
	{
		for(x=400;x<=800;x+=80)
		{
			gfx_fillrectangle(x,y, 40,40);
		}
		y+=80;
	}
	
	y=712;
	for(x=400;x<=480;x+=80)
	{
		gfx_fillrectangle(x,y, 40,40);
	}
	
	for(x=560;x<=720;x+=160)
	{
		gfx_fillrectangle(x,y, 120,40);
	}
		
	gfx_color(0,0,0);
	gfx_text("A",415,400);
	gfx_text("B",495,400);
	gfx_text("C",575,400);
	gfx_text("D",655,400);
	gfx_text("E",735,400);
	gfx_text("F",815,400);

	gfx_text("G",415,480);
	gfx_text("H",495,480);
	gfx_text("I",575,480);
	gfx_text("J",655,480);
	gfx_text("K",735,480);
	gfx_text("L",815,480);
	
	gfx_text("M",415,560);
	gfx_text("N",495,560);
	gfx_text("O",575,560);
	gfx_text("P",655,560);
	gfx_text("Q",735,560);
	gfx_text("R",815,560);
	
	gfx_text("S",415,640);
	gfx_text("T",495,640);
	gfx_text("U",575,640);
	gfx_text("V",655,640);
	gfx_text("W",735,640);
	gfx_text("X",815,640);
	
	gfx_text("Y",415,720);
	gfx_text("Z",495,720);
	
	gfx_text("SPACE",590,720);
	gfx_text("ENTER",750,720);
}

void rack()
{
	gfx_color(255,255,255);
	gfx_fillrectangle(100,392,200,400);
	gfx_color(15,128,234);
	gfx_fillrectangle(120,412,200,400);
}

void head()
{
	gfx_color(255,255,255);//white
	gfx_fillcircle(250,500,100);
}	

void body()
{
	gfx_color(255,255,255);
	gfx_fillrectangle(250,550,5,120);
}

void hand()
{
	gfx_color(255,255,255);
	gfx_fillcircle(250,620,150);
	gfx_color(15,128,234);
	gfx_fillcircle(250,625,150);
}

void leg()
{
	gfx_color(255,255,255);
	gfx_fillcircle(250,745,150);
	gfx_color(15,128,234);
	gfx_fillcircle(250,750,150);
}

void base()
{
	gfx_color(255,255,255);
	gfx_fillrectangle(100,792,200,20);
}

void hang()
{
	gfx_color(255,255,255);
	gfx_fillrectangle(300,342,200,400);
	gfx_color(15,128,234);
	gfx_fillrectangle(320,362,200,400);
	gfx_color(255,255,255);//white
	gfx_fillcircle(450,450,100);
	gfx_color(255,255,255);
	gfx_fillcircle(450,570,150);
	gfx_color(15,128,234);
	gfx_fillcircle(450,575,150);
	gfx_color(255,255,255);
	gfx_fillcircle(450,695,150);
	gfx_color(15,128,234);
	gfx_fillcircle(450,700,150);
	gfx_color(255,255,255);
	gfx_fillrectangle(450,500,5,120);
	gfx_color(255,255,255);
	gfx_fillrectangle(300,742,200,20);
	gfx_color(255,255,255);
	gfx_fillrectangle(450,347,5,60);
	gfx_color(0,0,0);
	gfx_text("X",425,425);
	gfx_text("X",470,425);
}

char read_input()
{
	char c;
	c=gfx_wait();
		if (c==0x01||c==0x02||c==0x03)//mouse input
		{
		
			if (gfx_xpos()>=560 && gfx_xpos()<=680)//space
			{
				if (gfx_ypos()>=712 && gfx_ypos()<=752)
				 {
				 	printf("Space\n");
				 	c=' ';
				 }
				 
				 
			}//end of space
			
			else if (gfx_xpos()>=720 && gfx_xpos()<=840)//enter
			{
				if (gfx_ypos()>=712 && gfx_ypos()<=752)
				 {
				 	printf("Enter\n");
				 	c='\r';
				 }
				 
				 
			}//end of enter
			
			else if (gfx_xpos()>=400 && gfx_xpos()<=440)//first col
			{
				 if (gfx_ypos()>=392 && gfx_ypos()<=432)
				 {
				 	printf("A\n");
				 	c='A';
				 }
				 
				 else if (gfx_ypos()>=472 && gfx_ypos()<=512)
				 {
				 	printf("G\n");
				 	c='G';
				 }
				 
				 else if (gfx_ypos()>=552 && gfx_ypos()<=592)
				 {
				 	printf("M\n");
				 	c='M';
				 }
				 
				 else if (gfx_ypos()>=632 && gfx_ypos()<=672)
				 {
				 	printf("S\n");
				 	c='S';
				 }
				 
				 else if (gfx_ypos()>=712 && gfx_ypos()<=752)
				 {
				 	printf("Y\n");
				 	c='Y';
				 }
				 
				 
			}//end of if xpos = first col
			
			else if (gfx_xpos()>=480 && gfx_xpos()<=520)//second col
			{
				 if (gfx_ypos()>=392 && gfx_ypos()<=432)
				 {
				 	printf("B\n");
				 	c='B';
				 }
				 
				 else if (gfx_ypos()>=472 && gfx_ypos()<=512)
				 {
				 	printf("H\n");
				 	c='H';
				 }
				 
				 else if (gfx_ypos()>=552 && gfx_ypos()<=592)
				 {
				 	printf("N\n");
				 	c='N';
				 }
				 
				 else if (gfx_ypos()>=632 && gfx_ypos()<=672)
				 {
				 	printf("T\n");
				 	c='T';
				 }
				 
				 else if (gfx_ypos()>=712 && gfx_ypos()<=752)
				 {
				 	printf("Z\n");
				 	c='Z';
				 }
				 
				
			}//end of if xpos = second col
			
			if (gfx_xpos()>=560 && gfx_xpos()<=600)//third
			{
				 if (gfx_ypos()>=392 && gfx_ypos()<=432)
				 {
				 	printf("C\n");
				 	c='C';
				 }
				 
				 else if (gfx_ypos()>=472 && gfx_ypos()<=512)
				 {
				 	printf("I\n");
				 	c='I';
				 }
				 
				 else if (gfx_ypos()>=552 && gfx_ypos()<=592)
				 {
				 	printf("O\n");
				 	c='O';
				 }
				 
				 else if (gfx_ypos()>=632 && gfx_ypos()<=672)
				 {
				 	printf("U\n");
				 	c='U';
				 }
				 
				 
			}//end of if xpos = third col
			
			else if (gfx_xpos()>=640 && gfx_xpos()<=680)//forth col
			{
				 if (gfx_ypos()>=392 && gfx_ypos()<=432)
				 {
				 	printf("D\n");
				 	c='D';
				 }
				 
				 else if (gfx_ypos()>=472 && gfx_ypos()<=512)
				 {
				 	printf("J\n");
				 	c='J';
				 }
				 
				 else if (gfx_ypos()>=552 && gfx_ypos()<=592)
				 {
				 	printf("P\n");
				 	c='P';
				 }
				 
				 else if (gfx_ypos()>=632 && gfx_ypos()<=672)
				 {
				 	printf("V\n");
				 	c='V';
				 }
				 
				 
			}//end of if xpos = forth col
			
			if (gfx_xpos()>=720 && gfx_xpos()<=760)//fifth col
			{
				 if (gfx_ypos()>=392 && gfx_ypos()<=432)
				 {
				 	printf("E\n");
				 	c='E';
				 }
				 
				 else if (gfx_ypos()>=472 && gfx_ypos()<=512)
				 {
				 	printf("K\n");
				 	c='K';
				 }
				 
				 else if (gfx_ypos()>=552 && gfx_ypos()<=592)
				 {
				 	printf("Q\n");
				 	c='Q';
				 }
				 
				 else if (gfx_ypos()>=632 && gfx_ypos()<=672)
				 {
				 	printf("W\n");
				 	c='W';
				 }
				 
				 
			}//end of if xpos = fifth col
			
			else if (gfx_xpos()>=800 && gfx_xpos()<=840)//sixth col
			{
				 if (gfx_ypos()>=392 && gfx_ypos()<=432)
				 {
				 	printf("F\n");
				 	c='F';
				 }
				 
				 else if (gfx_ypos()>=472 && gfx_ypos()<=512)
				 {
				 	printf("L\n");
				 	c='L';
				 }
				 
				 else if (gfx_ypos()>=552 && gfx_ypos()<=592)
				 {
				 	printf("R\n");
				 	c='R';
				 }
				 
				 else if (gfx_ypos()>=632 && gfx_ypos()<=672)
				 {
				 	printf("X\n");
				 	c='X';
				 }
				 
				 
			}//end of if xpos = sixth col
			
			
			
		}//end of mouse input
		
		else//keyboard input
		{
			printf("%c\n",c);
		}

	
	return c;
}

void level_keyboard()
{
	int x,y;
	void header();
	gfx_color(255,255,255);
	gfx_text("Select a level",370,250);
	
	y=350;
	for(x=250;x<=570;x+=160)
	{
		gfx_color(255,255,255);
		gfx_fillrectangle(x,y, 80,80);
		
	}
	
	gfx_color(0,0,0);
	gfx_text("1",285,380);
	gfx_text("2",445,380);
	gfx_text("3",605,380);
}

char read_level()
{
	char c;
	c=gfx_wait();
		if (c==0x01||c==0x02||c==0x03)//mouse input
		{
			if (gfx_ypos()>=350 && gfx_ypos()<=430)
			{
				 if (gfx_xpos()>=250 && gfx_xpos()<=330)
				 {
				 	printf("1\n");
				 	c=49;
				 }
				 
				 else if (gfx_xpos()>=410&& gfx_xpos()<=490)
				 {
				 	printf("2\n");
				 	c=50;
				 }
				 
				 else if (gfx_xpos()>=570 && gfx_xpos()<=650)
				 {
				 	printf("3\n");
				 	c=51;
				 }
				 
				 else{}
			}
			else{}
		}
		
			
		else//keyboard input
		{}
		
	return c;
}

int quit()
{
	int opt=5;
	char c;
	gfx_color(255,255,255);
	gfx_fillrectangle(200,800,200,50);
	gfx_fillrectangle(500,800,200,50);
	
	gfx_color(0,0,0);
	gfx_text("Replay",265,815);
	gfx_text("Home",570,815);
	
	c=gfx_wait();
		if (c==0x01||c==0x02||c==0x03)//mouse input
		{
			if (gfx_ypos()>=800 && gfx_ypos()<=850)
			{
				 if (gfx_xpos()>=200 && gfx_xpos()<=400)
				 {
				 	printf("Replay\n");
				 	opt=1;
				 }
				 
				 else if (gfx_xpos()>=500 && gfx_xpos()<=700)
				 {
				 	printf("Home\n");
				 	opt=0;
				 }
				 
				 else{}
			}//end of if xpos = first col
			
			else{}
		}
			
		else//keyboard input
		{}
		
	return opt;
}
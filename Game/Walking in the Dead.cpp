//Author: Azizur Rahman & Asif Haider
//Created: Sunday, 15-09-2019

# include "iGraphics.h"


#define screenWidth 1280
#define screenHeight 600

#define Max_Zombie_1 15
#define Max_Zombie_2 30
#define Max_Zombie_3 50




int level_1=0, level_2=0, level_3=0;

int player_x, player_y;
int player_speed=25, zombie_speed[50]= {0}, ammo_speed=50;

int max_zombie=0;
int zombie_x[50]= {0}, zombie_y[50]= {0},zombie_timer[50]= {0};
int zombie_set[50]= {0},zombie_start=0;

int pl_right=1, pl_left=0, pl_up=0, pl_down=0;

int ammo_x[1000], ammo_y[1000], ammo_radius[1000]= {0}, ammo_direction[1000]= {0}, ammo_set[1000]= {0}, count_ammo=0;
int player_direction=0; // 1= right, 2= left, 3= up, 4= down


int p_move=1;
int kills=8;
char scr[100];
char health[100]="Player Health";

int zombie_life=1, p_health=150,hs_height[5]= {420,360,300,240,180};

int length=0;
int Game_start=1, Menu_start=0;

//Xbow information for level 3;
int xbow_x=1150, xbow_y=300;
int xbowBullet_x[500], xbowBullet_y[500];
int xbow_set=0, xbowBullet_set[500]= {0}, xbowBullet_start=0, xbow_Bullet=0, xbow_health=150;
int xbowBullet_timer[500]= {0}, xb_timer=0, xb_speed=55;

int x_sound=1;
int health_kit=0, health_kit_x, health_kit_y, kit_done=0, health_increase=60;


//For link ups

int load=1, menu=0, level_break=0, next_level=0, level_on=0,in_game=0;
int game_over=0, p_dead=0, g_complete=0, g_over_pic=0, g_complete_pic=0;
int how_to_play = 0, credit = 0;
int high_score=0;



//High Score variables
int GScore=0, see_score=0, go_next=0, is_high=0, concate=0;
char show_score[40]="Your score is: ";
char HS[100], HighScore[50]="High Score: ";

typedef struct
{
    int ranks;
    char name[50];
    int score;

} highscore;

highscore Score[6];

int ShowRender=0;
FILE *fp;
int flag=0;
int renderbox_x=540, renderbox_y=300, renderbox_dx=200, renderbox_dy=40;
char InputName[100];
int len=0;
char str1[150]="please click inside the box to enter your name and press Page_down on completing entering your name!";
int ch, kh, sortScore;
char sortName[50];

void menusound(){
    if(menu)PlaySound("got.wav",NULL,SND_ASYNC | SND_LOOP);
    else PlaySound(NULL,NULL,SND_ASYNC);
}

void drawRender()
{
    if(flag == 0)
    {
        iSetColor(255, 255, 255);
        iRectangle(renderbox_x, renderbox_y, renderbox_dx, renderbox_dy);
    }
    if(flag == 1)
    {
        iSetColor(255, 0, 0);
        iRectangle(renderbox_x, renderbox_y, renderbox_dx, renderbox_dy);
        iSetColor(255, 255, 255);
        iText(renderbox_x+20, renderbox_y+10, InputName, GLUT_BITMAP_HELVETICA_18);
    }

    iSetColor(255, 255, 0);
    iText(500, 580, "CONGRATULATIONS! YOU ARE ONE OF THE TOP SCORERS!", GLUT_BITMAP_9_BY_15);
    iSetColor(255, 255, 0);

    iText(renderbox_x, renderbox_y-30,"Please enter your name!", GLUT_BITMAP_9_BY_15);

    iSetColor(255, 255, 255);
    iText(renderbox_x,15,"Press ENTER to continue!", GLUT_BITMAP_9_BY_15);
}

void sortHighScore()
{
    for(ch=0; ch<=4; ch++)
        {
            for(kh=ch; kh<=5; kh++)
            {
                if(Score[ch].score < Score[kh].score)
                {

                    sortScore=Score[kh].score;
                    Score[kh].score=Score[ch].score;
                    Score[ch].score=sortScore;


                    strcpy(sortName,Score[kh].name);
                    strcpy(Score[kh].name,Score[ch].name);
                    strcpy(Score[ch].name,sortName);



                }
            }
        }
}

void ShowScore()
{
    itoa(GScore,scr,10);
    if(concate==0)
    {
        strcat(show_score,scr);
        concate=1;
    }

    iSetColor(255,255,255);
    iText(580,300,show_score,GLUT_BITMAP_TIMES_ROMAN_24);

}



void highscoreread()
{
    FILE *fp=fopen("game_score.txt","r");
    char s[100],b[100];
    for(int i=0; i<5; i++)
    {
        fscanf(fp,"%d %s %d",&Score[i].ranks,Score[i].name,&Score[i].score);
        char s[10],b[10];
        itoa(Score[i].ranks,s,10);
        itoa(Score[i].score,b,10);
        iSetColor(255,255,255);
        iText(400,hs_height[i],s,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(500,hs_height[i],Score[i].name,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(800,hs_height[i],b,GLUT_BITMAP_TIMES_ROMAN_24);

    }
}

void NewGame()
{
    menu=0;
    next_level=1;
    game_over=0;
    g_over_pic=0;
    g_complete_pic=0;
    p_health=150;
    GScore=0;
    kills=0;
    p_dead=0;
    health_kit=0;
    player_x=screenWidth/2;
    player_y=screenHeight/2;
}

void GameOver()
{
    if(p_health<=0)
    {
        p_dead=1;
    }
    else if(kills==Max_Zombie_3 && xbow_health<=0)
    {
        g_complete=1;
    }
}

void drawLoading()
{
    iSetColor(255, 0, 0);
    iFilledRectangle(20,20, length, 20);
}



void drawBullet(int a, int b)
{
    iSetColor(51, 84, 255);
    iFilledCircle(a,b,4);
}


void drawPHealth(int a)
{
    iSetColor(255,255,255);
    iRectangle(49,509, 152, 22 );
    iSetColor(231, 76, 60  );
    iFilledRectangle(50,510,p_health, 20);
}

void drawXbowHealth()
{
    iSetColor(231, 76, 60);
    iFilledRectangle(1000, xbow_y, xbow_health, 10);
}

void drawXbowBullet(int x, int y)
{
    iSetColor(0,0,0);
    iFilledCircle(x,y, 4);
}

void Loading()
{
    if(length<=1200)
    {
        length+=10;
    }

    else
    {
        load=0;
        menu=1;
        menusound();
    }

}



void Game_Level_1()
{
    int i;
    in_game=1;
    p_health=150;
    max_zombie=Max_Zombie_1;
    zombie_start=0;
    kills=0;
    xbow_set=0;

    for(i=0; i<max_zombie; i++)
    {
       if(i%4==0)
        {
            zombie_x[i]=rand()%1200+1200;
            zombie_y[i]=rand()%400+600;
        }
        else if(i%4==1)
        {
            zombie_x[i]=rand()%10-120;
            zombie_y[i]=rand()%5-100;
        }
        else if(i%4==2)
        {
            zombie_x[i]=rand()%100-200;
            zombie_y[i]=rand()%400+600;
        }
        else
        {
            zombie_x[i]=rand()%1200+1200;
            zombie_y[i]=rand()%5-100;
        }
        zombie_set[i]=0;
        zombie_timer[i]=(i+1)*8;
        zombie_speed[i]=rand()%5+3;
    }
}


void Game_Level_2()
{
    int i;
    xbow_set=1;
    p_health=150;
    max_zombie=Max_Zombie_2;
    zombie_start=0;
    kills=0;

    for(i=0; i<max_zombie; i++)
    {
        if(i%4==0)
        {
            zombie_x[i]=rand()%1200+1200;
            zombie_y[i]=rand()%400+600;
        }
        else if(i%4==1)
        {
            zombie_x[i]=rand()%10-120;
            zombie_y[i]=rand()%5-100;
        }
        else if(i%4==2)
        {
            zombie_x[i]=rand()%100-200;
            zombie_y[i]=rand()%400+600;
        }
        else
        {
            zombie_x[i]=rand()%1200+1200;
            zombie_y[i]=rand()%5-100;
        }
        zombie_set[i]=0;
        zombie_timer[i]=(i+1)*10;
        zombie_speed[i]=rand()%6+2;
    }
}

void Game_Level_3()
{
    int i;
    in_game=1;
    if(!xbow_set)
    {
        xbow_set=1;

    }
    xbow_health=200;
    max_zombie=Max_Zombie_3;
    p_health=150;
    zombie_start=0;
    kills=0;
    //xbow_set=1;

    for(i=0; i<max_zombie; i++)
    {
        if(i%4==0)
        {
            zombie_x[i]=rand()%1200+1200;
            zombie_y[i]=rand()%400+600;
        }
        else if(i%4==1)
        {
            zombie_x[i]=rand()%10-120;
            zombie_y[i]=rand()%5-100;
        }
        else if(i%4==2)
        {
            zombie_x[i]=rand()%100-200;
            zombie_y[i]=rand()%400+600;
        }
        else
        {
            zombie_x[i]=rand()%1200+1200;
            zombie_y[i]=rand()%5-100;
        }
        zombie_set[i]=0;
        zombie_timer[i]=(i+1)*15;
        zombie_speed[i]=rand()%6+2;
    }
}

void XB_Bullet()
{
    if(xbow_set)
    {


        xb_timer+=2;


        if(xbow_y<player_y-20)
        {
            if(xbow_y<=580)
                xbow_y+=(player_speed-4);
        }

        if(xbow_y>player_y-20)
        {
            if(xbow_y>=40)
            {
                xbow_y-=(player_speed-4);
            }
            if(xbow_y>3 && xbow_y<40)
            {
                xbow_y-=2;
            }
        }


        int i,a;
        for(i=0; i<xbow_Bullet; i++)
        {
            if(xbowBullet_set[i]==1)
            {
                xbowBullet_x[i]-=xb_speed;

                if(xbowBullet_set[i]!=-1)
                {
                    for(a=0; a<xbow_Bullet; a++)
                    {
                        if( xbowBullet_set[a] && xbowBullet_x[a]>=player_x-10 && xbowBullet_x[a]<player_x+60 && xbowBullet_y[a]>=player_y-10 && xbowBullet_y[a]<player_y+60)
                        {
                            p_health-=5;
                            if(p_health<=0)
                            {
                                p_dead=1;
                            }
                            xbowBullet_set[a]=-1;
                            xbowBullet_x[a]=0;
                            xbowBullet_y[a]=0;
                        }
                    }
                }
            }
        }


    }



}

void Collision()
{
    int a;
    for(a=0; a<max_zombie; a++)
    {
        if(zombie_set[a] && zombie_x[a]>=player_x-45 && zombie_x[a]<=player_x+45 && zombie_y[a]>=player_y-45 && zombie_y[a]<=player_y+45 )
        {
            p_health-=2;

            if(player_x>30 && player_x<screenWidth-100 && player_y>30 && player_y<screenHeight-50)
            {


                if(zombie_x[a]<=player_x)
                {
                    player_x+=30;
                    zombie_x[a]-=50;
                }
                else if(zombie_x[a]>player_x)
                {
                    player_x-=30;
                    zombie_x[a]+=50;
                }
                else if(zombie_y[a]<=player_y)
                {
                    player_y+=30;
                    zombie_y[a]-=50;
                }
                else if(zombie_y[a]>player_y)
                {
                    player_y-=30;
                    zombie_y[a]+=50;
                }
            }

        }
    }

    if(player_x>=xbow_x-40)
    {
        player_x-=10;
    }

    if(p_health<=0)
    {
        p_dead=1;
    }
}

void moveAmmo()
{
    int a,z;
    for(a=0; a<count_ammo; a++)
    {
        if(ammo_direction[a]==1)
        {
            ammo_x[a]+=ammo_speed;
        }
        else if(ammo_direction[a]==2)
        {
            ammo_x[a]-=ammo_speed;
        }
        else if(ammo_direction[a]==3)
        {
            ammo_y[a]+=ammo_speed;
        }
        else
        {
            ammo_y[a]-=ammo_speed;
        }

        if(ammo_set[a]!=-1)
        {

            for(z=0; z<max_zombie; z++)
            {
                if( zombie_set[z] && ammo_x[a]>=zombie_x[z] && ammo_x[a]<= zombie_x[z]+45 && ammo_y[a]>=zombie_y[z] && ammo_y[a]<=zombie_y[z]+45)
                {
                    zombie_set[z]=0;
                    ammo_set[a]=-1;
                    a++;
                    kills++;
                    GScore+=2;
                }

            }

            for(z=0; z<xbow_Bullet; z++)
            {
                if(xbow_set && ammo_x[a]>=xbow_x && ammo_y[a]>=xbow_y+30 && ammo_y[a]<xbow_y+120 )
                {
                    xbow_health-=2;
                    GScore+=3;
                    ammo_set[a]=-1;
                    a++;

                    if(xbow_health<=0)
                    {
                        xbow_set=0;
                        GScore+=20;
                    }
                }

            }
        }

    }

}

void MoveZombie()
{
    int i;
    for (i=0; i<max_zombie; i++)
    {
        if(zombie_x[i]>=0 && zombie_x[i]<=screenWidth && zombie_y[i]>=0 && zombie_y[i]<=screenHeight)
        {
            if(zombie_x[i]<player_x && zombie_x[i]<screenWidth-50)
            {
                zombie_x[i]+=zombie_speed[i];
            }

            if(zombie_x[i]>player_x && zombie_x[i]>30)
            {
                zombie_x[i]-=zombie_speed[i];

            }

            if(zombie_y[i]<player_y && zombie_y[i]<screenHeight-50)
            {
                zombie_y[i]+=zombie_speed[i];
            }

            if(zombie_y[i]>player_y && zombie_y[i]>30)
            {
                zombie_y[i]-=zombie_speed[i];
            }
        }
        else
        {
            if(zombie_x[i]<0)
            {
                zombie_x[i]+=5;
            }
            if(zombie_x[i]>screenWidth)
            {
                zombie_x[i]-=5;
            }
            if(zombie_y[i]<0)
            {
                zombie_y[i]+=5;
            }
            if(zombie_y[i]>screenHeight)
            {
                zombie_y[i]-=5;
            }
        }

    }

    int j;

    for(i=0; i<max_zombie; i++)
    {


        for(j=0; j<max_zombie; j++)
        {
            if(zombie_x[i]<=player_x-200 || zombie_x[i]>=player_x+245 || zombie_y[j]<=player_y-200 || zombie_y[i]>=player_y+245)
            {

                if(i!=j && zombie_set[i] && zombie_set[j] && zombie_x[i]>=zombie_x[j]-45 && zombie_x[i]<=zombie_x[j]+45 && zombie_y[i]>=zombie_y[j]-45 && zombie_y[i]<=zombie_y[j]+45 )
                {

                    if(zombie_x[i]>=zombie_x[j])
                        zombie_x[i]+=10;
                    else if(zombie_x[i]<zombie_x[j])
                        zombie_x[i]-=10;
                    else if(zombie_y[i]>=zombie_y[j])
                        zombie_y[i]+=10;
                    else if(zombie_y[i]<zombie_y[j])
                        zombie_y[i]-=10;
                }
            }
        }
    }
}

void Zombie_start()

{
    zombie_start++;
}

void HealthAmmo()
{
    if(p_health<=50)
    {
        health_kit=1;
    }

    if(health_kit && player_x>=health_kit_x && player_x<health_kit_x+60 && player_y>=health_kit_y && player_y<health_kit_y+60)
    {
        p_health+=health_increase;
        health_kit=0;
    }

}

void mainmenu()

{
    iShowBMP(0, 0, "main_menu.bmp");

}




void iDraw()
{

    iClear();

    if(load)
    {
        iShowBMP(0,0, "Gamecover.bmp");
        drawLoading();
        Loading();

    }

    else if(!next_level && menu)
    {
        mainmenu();
        if (how_to_play)
        {
            iShowBMP(0,0,"how_to_play.bmp");
        }
        if (credit)
        {
            iShowBMP(0,0,"credit.bmp");
        }
        if (high_score)
        {
            iShowBMP(0,0,"high_score.bmp");
            highscoreread();
        }

    }


    else if(!game_over)

    {
        if(next_level==1)
        {
            Game_Level_1();
            next_level=0;
            level_1=1;
        }

        else if(next_level==2)
        {
            Game_Level_2();
            next_level=0;
            level_1=0;
            level_2=1;

        }

        else if(next_level==3)
        {
            Game_Level_3();
            next_level=0;
            level_2=0;
            level_3=1;
        }

        int i, done[500]= {0};

        if(!game_over)
        {
            GameOver();
            if(p_dead==1)
            {
                level_3=0;
                g_over_pic=1;
                game_over=1;
            }
            else if(g_complete==1)
            {
                level_3=0;
                count_ammo=0;
                g_complete_pic=1;
                game_over=1;
            }

        }



        if((level_1 && kills==Max_Zombie_1) || (level_2 && kills==Max_Zombie_2))
        {

            level_break=1;
            if(kills==Max_Zombie_1)
                iShowBMP(0,0, "level_one_pass.bmp");
            else if(kills==Max_Zombie_2)
                iShowBMP(0,0, "level_2_pass.bmp");
        }

        if(level_break)
        {
            if(level_on)
            {
                if(kills==Max_Zombie_1)
                {
                    next_level=2;
                }
                else if(kills==Max_Zombie_2)
                {
                    next_level=3;
                }

                level_on=0;
                level_break=0;
            }
        }

        if(!level_break)
        {
            if(level_1==1)
                iShowBMP(0,0, "final_bg.bmp");

            else if(level_2==1)
            {
                iShowBMP(0,0, "bg_2.bmp");
            }
            else if(level_3==1)
            {
                iShowBMP(0,0, "bg_3.bmp");
            }

            drawPHealth(p_health);
            itoa(GScore,scr,10);
            //iText(100,550, health);
            iSetColor(255,255,255);
            iText(380, 510, scr, GLUT_BITMAP_TIMES_ROMAN_24);

            if(health_kit)
            {
                if(!kit_done)
                {
                    health_kit_x=rand()%1000+100;
                    health_kit_y=rand()%400+100;
                    kit_done=1;
                }

                iShowBMP2(health_kit_x,health_kit_y, "health_kit.bmp", 0);

            }

            else
            {
                kit_done=0;
            }

            if(xbow_set) //Xbow & Xbow Bullet
            {

                drawXbowHealth();
                iShowBMP2(xbow_x, xbow_y, "xbow.bmp", 0);

                if(xb_timer%20==0)
                {
                    xbow_Bullet++;
                }

                for(i=0; i<xbow_Bullet; i++)
                {
                    if(xbowBullet_set[i]==0 && xbowBullet_timer[i]==xb_timer)
                    {
                        xbowBullet_set[i]=1;
                        if(!done[i])
                        {
                            xbowBullet_x[i]=xbow_x-20;
                            xbowBullet_y[i]=xbow_y+50;
                            done[i]=1;
                        }

                    }

                    if(xbowBullet_set[i]!=-1)
                        drawXbowBullet(xbowBullet_x[i], xbowBullet_y[i]);

                }
            }




            if(pl_right)
            {
                player_direction=1;
                iShowBMP2(player_x, player_y, "pl1_right.bmp",0);
            }

            if(pl_left)
            {
                player_direction=2;
                iShowBMP2(player_x, player_y, "pl1_left.bmp", 0);

            }

            if(pl_up)
            {
                player_direction=3;
                iShowBMP2(player_x, player_y, "pl1_up.bmp", 0);

            }

            if(pl_down)
            {
                player_direction=4;
                iShowBMP2(player_x, player_y, "pl1_down.bmp", 0);

            }
            //player_boundary(player_x,player_y);

            for(i=0; i<count_ammo; i++) //For ammo according to player's position
            {
                if(ammo_set[i]==0 && ammo_set[i]!=-1)
                {
                    ammo_direction[i]=player_direction;
                    ammo_set[i]=1;

                    if(ammo_direction[i]==1)
                    {
                        ammo_x[i]=player_x+45;
                        ammo_y[i]=player_y+20;
                    }

                    else if(ammo_direction[i]==2)
                    {
                        ammo_x[i]=player_x;
                        ammo_y[i]=player_y+26;
                    }

                    else if(ammo_direction[i]==3)
                    {
                        ammo_x[i]=player_x+26;
                        ammo_y[i]=player_y+45;
                    }
                    else
                    {
                        ammo_x[i]=player_x+20;
                        ammo_y[i]=player_y;
                    }

                }

                if(ammo_set[i]!=-1)
                {
                    drawBullet(ammo_x[i], ammo_y[i]);

                }

            }

            for (i=0; i<max_zombie; i++)
            {
                if (zombie_start==zombie_timer[i] || zombie_set[i]==1)
                {
                    zombie_set[i]=1;
                    if(zombie_x[i]<player_x)
                    {

                        iShowBMP2(zombie_x[i], zombie_y[i], "zm_right.bmp", 0);
                    }

                    else if(zombie_x[i]>player_x)
                    {
                        iShowBMP2(zombie_x[i], zombie_y[i], "zm_left.bmp",0);
                    }

                    else if(zombie_y[i]<player_y)
                    {
                        iShowBMP2(zombie_x[i], zombie_y[i], "zm_up.bmp", 0);
                    }

                    else if(zombie_y[i]>player_y)
                    {
                        iShowBMP2(zombie_x[i], zombie_y[i], "zm_down.bmp", 0);
                    }
                    // zombie_boundary(zombie_x[i],zombie_y[i]);
                }
            }

        }

    }

    else if(game_over)
    {
//        if(game_over)
//        {
        if(g_over_pic)
        {
            iShowBMP(0,0, "Game_over.bmp");
            // ShowScore();
        }

        else if(g_complete_pic)
        {
            iShowBMP(0,0, "game_complete.bmp");
            //ShowScore();
        }

        else if(see_score)
        {
            iShowBMP(0,0, "final_score.bmp");
            ShowScore();
        }

        else if(go_next)
        {
            g_over_pic=0;
            g_complete_pic=0;

            for(ch=0; ch<5; ch++)
            {

                if(GScore>=Score[ch].score) // comparing the current scores with the
                    //scores stored so that it can be defined
                {
                    //that render box will be shown or not
                    ShowRender=1;
                    break;
                }

            }

            if(ShowRender==1)
            {
                iShowBMP(0,0, "congrats.bmp");
                drawRender();
            }

            else if ( ShowRender==0)  //renderBox will not be seen and gamne will exit

            {
                menu=1;
                menusound();
            }

        }
//        }
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (mx>=925 && mx<=1200 && my>=455 && my<=500)
        {
            if(menu)
            {
                NewGame();
                menu=0;
                menusound();
            }
        }
        if (mx>=910 && mx<=1215 && my>=385 && my<=430)
        {
            if (!how_to_play)
            {
                //menu=1;
                how_to_play=1;
                //howtoplay();
            }
        }
        if (mx>=960 && mx<=1170 && my>=260 && my<=305)
        {
            if (!credit)
            {
                credit=1;
            }
        }
        if (mx>=1090 && mx<=1250 && my>=15 && my<=55)
        {
            exit(0);
        }
        if (mx>=920 && mx<=1205 && my>=320 && my<=365)
        {
            if(!high_score)
            {
                high_score=1;
            }
        }



        if(mx>= renderbox_x && mx<= (renderbox_x + renderbox_dx) && my>= renderbox_y && my<= (renderbox_y+renderbox_dy ) && ShowRender==1)
        {
            flag=1;
        }
        //place your codes here
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(flag == 1)
    {
        if(key == '\b')
        {
            if(len<=0)
                len = 0;
            else
                len--;
            InputName[len]='\0';

        }
        else if(key!=' ' && key!=13)
        {
            InputName[len]=key;
            len++;
            InputName[len]='\0';
        }

    }

    if(key==13 && flag==1)
    {
        if(len==0)
        {
            strcpy(InputName,"Unknown");

        }
        Score[5].score=GScore;
        strcpy(Score[5].name,InputName);

//        for(ch=0; ch<=4; ch++)
//        {
//            for(kh=ch; kh<=5; kh++)
//            {
//                if(Score[ch].score < Score[kh].score)
//                {
//
//                    sortScore=Score[kh].score;
//                    Score[kh].score=Score[ch].score;
//                    Score[ch].score=sortScore;
//
//
//                    strcpy(sortName,Score[kh].name);
//                    strcpy(Score[kh].name,Score[ch].name);
//                    strcpy(Score[ch].name,sortName);
//
//
//
//                }
//            }
//        }

        sortHighScore();

        fp=fopen("game_score.txt","w");

        for(ch=0; ch<5; ch++)
        {
            fprintf(fp,"%d            %s            %d\n",Score[ch].ranks,Score[ch].name,Score[ch].score);
        }

        fclose(fp);

        menu=1;
    }



    if(key == 'x' || key=='X')
    {
        //do something with 'x'
        exit(0);
    }

    if(key==' ')
    {
        if(!level_break && !menu && !p_dead && !g_complete_pic)
        {
            count_ammo++;
            PlaySound("shot.wav", NULL,SND_ASYNC);
        }
        else
        {

        }

    }


    if(key=='f' || key=='F')
    {
        level_on=1;
        iResumeTimer(4);
    }

    if(key=='n' || key=='N')
    {
        if(!ShowRender)
        {
            go_next=0;
            g_over_pic=0;
            g_complete_pic=0;
            see_score=1;
            ShowScore();
        }
    }

    if(key=='m' || key=='M')
    {
        go_next=1;
        see_score=0;
        menusound();
    }

    if(key==13)
    {
        if(ShowRender)
        {
            menu=1;
            menusound();
            mainmenu();
            ShowRender=0;
        }
    }

    if (key=='a' || key=='A')
    {

        if(!ShowRender)
        {

            if (how_to_play)
            {
                how_to_play=0;
                menu = 1;
                mainmenu();


            }
            if (credit)
            {
                credit=0;
                menu = 1;
                mainmenu();
            }
            if (high_score)
            {
                high_score=0;
                menu=1;
                mainmenu();
            }
            if(game_over)
            {
                game_over=0;
                menu=1;
                menusound();
                mainmenu();
            }
        }
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

    if(p_move)
    {

        if(key == GLUT_KEY_LEFT)
        {

            pl_right=0;
            pl_down=0;
            pl_left=1;
            pl_up=0;

            if(player_x>30)
                player_x-=player_speed;

        }
        if(key == GLUT_KEY_RIGHT)
        {
            pl_right=1;
            pl_down=0;
            pl_left=0;
            pl_up=0;

            if(player_x<screenWidth-100)
                player_x+=player_speed;

        }
        if(key == GLUT_KEY_UP)
        {
            pl_right=0;
            pl_down=0;
            pl_left=0;
            pl_up=1;

            if(player_y<screenHeight-50)
                player_y+=player_speed;


        }
        if(key == GLUT_KEY_DOWN)
        {
            pl_right=0;
            pl_down=1;
            pl_left=0;
            pl_up=0;

            if(player_y>30)
                player_y-=player_speed;

        }
    }

}





int main()
{
    player_x=screenWidth/2;
    player_y=screenHeight/2;

    int timer=20;

    for(int a=0; a<500; a++)
    {
        xbowBullet_timer[a]+=timer;
        timer+=20;
    }

    iSetTimer(40, moveAmmo);
    iSetTimer(40, MoveZombie);
    iSetTimer(40, Collision);
    iSetTimer (40,Zombie_start);
    iSetTimer(40, XB_Bullet);
    iSetTimer(40, HealthAmmo);
    iPauseTimer(4);

    highscoreread();

    fclose(fp);

    iInitialize(screenWidth, screenHeight, "WALKING IN THE DEAD");
    return 0;
}


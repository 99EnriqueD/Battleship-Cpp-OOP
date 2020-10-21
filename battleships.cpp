/*
Battleships
Version 1.0
Written by:  Shivam Shekhar
*/
#include<stdio.h>
#include<iostream>
#include<time.h>

using namespace std;

void delay(clock_t a)
{
    clock_t start;
    start  = clock();
    while(clock()-start<a)
    {

    }
}
int main()
{
    //A:Aircraft carrier
    //B:Battleship
    //D:destroyer
    //C:corvette
    int i,j,k=0,x,y,chk=0,win=0,uposa[5][2],uposb[4][2],uposd[3][2],uposc[2][2],a=0,b=0,c=0,d=0,probab,diff;
    char gridu[10][10],griduv[10][10],gridc[10][10],gridcv[10][10],orin[2],tempstr[10],str[20]="Battleships V1.0",str1[50]="Written By: Shivam Shekhar",ch;
   for(i=0;i<10;i++)
    {
        printf("\n");
    }
    for(i=0;i<30;i++)
    {
        printf(" ");
    }
    for(i=0;str[i]!='\0';i++)
    {
        printf("%c",str[i]);
        delay(60);
    }
    printf("\n");
    for(i=0;i<30;i++)
    {
        printf(" ");
    }
    for(i=0;str1[i]!='\0';i++)
    {
        printf("%c",str1[i]);
        delay(60);
    }
    delay(1500);
    system("cls");
    for(;;)
    {
        system("cls");
        for(i=0;i<10;i++)
            printf("\n");
        for(i=0;i<30;i++)
            printf(" ");
        printf("1.Play Battleships\n");
        for(i=0;i<30;i++)
            printf(" ");
        printf("2.Rules\n");
        ch=getch();
        if(ch==49)
            break;
        if(ch==50)
        {
            system("cls");
            printf("Get ready, for a war has been declared. Its time for some naval warfare.\n");
            printf("1.You have to defeat your opponent by destroying all his war ships before he destroys yours.\n");
            printf("2.They battlefield is a 10x10 grid where you place your ships\n");
            printf("3.You can place your ships by entering its orientation, i.e horizontal or vertical. For horizontal orientation, type 'h' in the orientation option and type 'v' for vertical\n");
            printf("4.And its x y coordinates(both separated by a space) where x is the row number and y is the column number\n");
            printf("4.You have a fleet of 4 battle ships: aircraft carrier(5 units long), battleship(4 units long), destroyer(3 units long) and corvette(2 units long)\n");
            printf("5.After placing your ships, you can attack the enemy area. To attack a specific area, enter its x y coordinate(separated by a space)\n");
            printf("6.If your attack hits the enemy ship, it will be denoted by an 'H'. And you get an extra turn\n");
            printf("7.If your attack misses, it will be denoted by a '*' and your turn ends\n");
            printf("press enter to continue.........");
            fflush(stdin);
            gets(tempstr);
            continue;
        }
    }
    system("cls");
    for(i=0;i<10;i++)
        printf("\n");
    for(i=0;i<30;i++)
    printf(" ");
    printf("Select the difficulty level:\n");
    for(i=0;i<30;i++)
    printf(" ");
    printf("1.easy\n");
    for(i=0;i<30;i++)
    printf(" ");
    printf("2.medium\n");
    for(i=0;i<30;i++)
    printf(" ");
    printf("3.hard\n");
    ch=getch();
    if(ch==49)
        diff=9;
    if(ch==50)
        diff=8;
    if(ch==51)
        diff=6;
    system("cls");
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            gridc[i][j]='.';
            gridu[i][j]='.';
            gridcv[i][j]='.';
        }
    }
    for(i=0;i<10;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==0)
        {
            printf("  ");
            for(j=0;j<10;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=0;j<10;j++)
            printf("%c ",gridu[i][j]);
        printf("\n");
    }
   /*Aircraft carrier*/
    for(;;)
    {
        printf("Aircraft Carrier:\n");
        printf("Orientation: ");
        scanf("%s",&orin);
        printf("x and y coordinates: ");
        scanf("%d %d",&x,&y);
        if(strcmp(orin,"h")==0)
        {
            if(y>5 || y<0 || x>9 || x<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
            else
            {
                for(i=y;i<y+5;i++)
                {
                    gridu[x][i]='A';
                    uposa[k][0]=x;
                    uposa[k][1]=i;
                    k++;
                }
                break;
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>5 || x<0 || y>9 || y<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
             else
            {
                for(i=x;i<x+5;i++)
                {
                    gridu[i][y]='A';
                    uposa[k][0]=i;
                    uposa[k][1]=y;
                    k++;
                }
                break;
            }
        }
    }
    k=0;
    system("cls");
    for(i=0;i<10;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==0)
        {
            printf("  ");
            for(j=0;j<10;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=0;j<10;j++)
            printf("%c ",gridu[i][j]);
        printf("\n");
    }
    /*B:Battleship*/
    for(;;)
    {
        chk=0;
        printf("Battleship:\n");
        printf("Orientation: ");
        scanf("%s",&orin);
        printf("x and y coordinates: ");
        scanf("%d %d",&x,&y);
        if(strcmp(orin,"h")==0)
        {
            if(y>6 || y<0 || x>9 || x<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
            else
            {

                for(i=y;i<y+4;i++)
                {
                    if(gridu[x][i]!='.')
                    {
                        printf("Can't place the ship. try again\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+4;i++)
                    {
                        gridu[x][i]='B';
                        uposb[k][0]=x;
                        uposb[k][1]=i;
                        k++;
                    }
                    break;
                }
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>6 || x<0 || y>9 || y<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
             else
            {
                 for(i=x;i<x+4;i++)
                {
                    if(gridu[i][y]!='.')
                    {
                        printf("Can't place the ship. try again\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                   for(i=x;i<x+4;i++)
                    {
                        gridu[i][y]='B';
                        uposb[k][0]=i;
                        uposb[k][1]=y;
                        k++;
                    }
                    break;
                }
            }
        }
    }
    k=0;
    system("cls");
    for(i=0;i<10;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==0)
        {
            printf("  ");
            for(j=0;j<10;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=0;j<10;j++)
            printf("%c ",gridu[i][j]);
        printf("\n");
    }
    /*Destroyer*/
    for(;;)
    {
        chk=0;
        printf("Destroyer:\n");
        printf("Orientation: ");
        scanf("%s",&orin);
        printf("x and y coordinates: ");
        scanf("%d %d",&x,&y);
        if(strcmp(orin,"h")==0)
        {
            if(y>7 || y<0 || x>9 || x<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
            else
            {
                for(i=y;i<y+3;i++)
                {
                    if(gridu[x][i]!='.')
                    {
                        printf("Can't place the ship. try again\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+3;i++)
                    {
                        gridu[x][i]='D';
                        uposd[k][0]=x;
                        uposd[k][1]=i;
                        k++;
                    }
                    break;
                }
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>7 || x<0 || y>9 || y<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
             else
            {
                 for(i=x;i<x+3;i++)
                {
                    if(gridu[i][y]!='.')
                    {
                        printf("Can't place the ship. try again\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+3;i++)
                    {
                        gridu[i][y]='D';
                        uposd[k][0]=i;
                        uposd[k][1]=y;
                        k++;
                    }
                    break;
                }
            }
        }
    }
    k=0;
    system("cls");
    for(i=0;i<10;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==0)
        {
            printf("  ");
            for(j=0;j<10;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=0;j<10;j++)
            printf("%c ",gridu[i][j]);
        printf("\n");
    }
    /*Corvette*/
    for(;;)
    {
        chk=0;
        printf("Corvette:\n");
        printf("Orientation: ");
        scanf("%s",&orin);
        printf("x and y coordinates: ");
        scanf("%d %d",&x,&y);
        if(strcmp(orin,"h")==0)
        {
            if(y>8 || y<0 || x>9 || x<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
            else
            {
                for(i=y;i<y+2;i++)
                {
                    if(gridu[x][i]!='.')
                    {
                        printf("Can't place the ship. try again\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+2;i++)
                    {
                        gridu[x][i]='C';
                        uposc[k][0]=x;
                        uposc[k][1]=i;
                        k++;
                    }
                    break;
                }
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>8 || x<0 || y>9 || y<0)
            {
                printf("Can't place the ship. try again\n");
                continue;
            }
             else
            {
                 for(i=x;i<x+2;i++)
                {
                    if(gridu[i][y]!='.')
                    {
                        printf("Can't place the ship. try again\n");
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+2;i++)
                    {
                        gridu[i][y]='C';
                        uposc[k][0]=i;
                        uposc[k][1]=y;
                        k++;
                    }
                    break;
                }
            }
        }
    }
    system("cls");
    for(i=0;i<10;i++)
    {
        for(j=0;j<30;j++)
            printf(" ");
        if(i==0)
        {
            printf("  ");
            for(j=0;j<10;j++)
            printf("%d ",j);
            printf("\n");
            for(j=0;j<30;j++)
            printf(" ");
        }
        printf("%d ",i);
        for(j=0;j<10;j++)
            printf("%c ",gridu[i][j]);
        printf("\n");
    }
    printf("Press enter to continue......");
    fflush(stdin);
    gets(tempstr);
    srand(time(NULL));
    /*Aircraft carrier cpu*/
    for(;;)
    {
        if(rand()%2 == 1)
            strcpy(orin,"h");
        else strcpy(orin,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orin,"h")==0)
        {
            if(y>5 || y<0 || x>9 || x<0)
            {
                continue;
            }
            else
            {
                for(i=y;i<y+5;i++)
                    gridc[x][i]='A';
                break;
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>5 || x<0 || y>9 || y<0)
            {
                continue;
            }
             else
            {
                for(i=x;i<x+5;i++)
                    gridc[i][y]='A';
                break;
            }
        }
    }
    /*B:Battleship cpu*/
    for(;;)
    {
        chk=0;
        if(rand()%2 == 1)
            strcpy(orin,"h");
        else strcpy(orin,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orin,"h")==0)
        {
            if(y>6 || y<0 || x>9 || x<0)
                continue;
            else
            {
                for(i=y;i<y+4;i++)
                {
                    if(gridc[x][i]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+4;i++)
                        gridc[x][i]='B';
                    break;
                }
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>6 || x<0 || y>9 || y<0)
            {
                continue;
            }
             else
            {
                 for(i=x;i<x+4;i++)
                {
                    if(gridc[i][y]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+4;i++)
                        gridc[i][y]='B';
                    break;
                }
            }
        }
    }
    /*Destroyer cpu*/
    for(;;)
    {
        chk=0;
        if(rand()%2 == 1)
            strcpy(orin,"h");
        else strcpy(orin,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orin,"h")==0)
        {
            if(y>7 || y<0 || x>9 || x<0)
            {
               continue;
            }
            else
            {
                for(i=y;i<y+3;i++)
                {
                    if(gridc[x][i]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+3;i++)
                        gridc[x][i]='D';
                    break;
                }
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>7 || x<0 || y>9 || y<0)
            {
                continue;
            }
             else
            {
                 for(i=x;i<x+3;i++)
                {
                    if(gridc[i][y]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+3;i++)
                        gridc[i][y]='D';
                    break;
                }
            }
        }
    }
    /*Corvette cpu*/
    for(;;)
    {
        chk=0;
        if(rand()%2 == 1)
            strcpy(orin,"h");
        else strcpy(orin,"v");
        x=rand()%10;
        y=rand()%10;
        if(strcmp(orin,"h")==0)
        {
            if(y>8 || y<0 || x>9 || x<0)
            {
                continue;
            }
            else
            {
                for(i=y;i<y+2;i++)
                {
                    if(gridc[x][i]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=y;i<y+2;i++)
                        gridc[x][i]='C';
                    break;
                }
            }
        }
        if(strcmp(orin,"v")==0)
        {
            if(x>8 || x<0 || y>9 || y<0)
            {
                continue;
            }
             else
            {
                 for(i=x;i<x+2;i++)
                {
                    if(gridc[i][y]!='.')
                    {
                        chk=1;
                        break;
                    }
                }
                if(chk==1)
                    continue;
                else
                {
                    for(i=x;i<x+2;i++)
                        gridc[i][y]='C';
                    break;
                }
            }
        }
    }
   /* system("cls");
    for(i=0;i<10;i++)
    {
        if(i==0)
        {
            printf("  ");
            for(j=0;j<10;j++)
            printf("%d ",j);
            printf("\n");
        }
        printf("%d ",i);
        for(j=0;j<10;j++)
            printf("%c ",gridc[i][j]);
        printf("\n");
    }    printf("Press enter to continue......");
    fflush(stdin);
    gets(tempstr);*/
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
            griduv[i][j]=gridu[i][j];
    }
    for(;;)
    {
        system("cls");
        for(i=0;i<10;i++)
        {
            for(j=0;j<30;j++)
            printf(" ");
            if(i==0)
            {
                printf("  ");
                for(j=0;j<10;j++)
                printf("%d ",j);
                printf("\n");
                for(j=0;j<30;j++)
                printf(" ");
            }
            printf("%d ",i);
            for(j=0;j<10;j++)
                printf("%c ",gridcv[i][j]);
            printf("\n");
        }
        printf("\n");
        for(i=0;i<10;i++)
        {
            for(j=0;j<30;j++)
            printf(" ");
            if(i==0)
            {
                printf("  ");
                for(j=0;j<10;j++)
                printf("%d ",j);
                printf("\n");
                for(j=0;j<30;j++)
                printf(" ");
            }
            printf("%d ",i);
            for(j=0;j<10;j++)
                printf("%c ",griduv[i][j]);
            printf("\n");
        }
        for(;;)
        {
            printf("Enter x and y: ");
            scanf("%d %d", &x,&y);
            if(x>9 || x<0 || y>9 || y<0 || gridcv[x][y]=='H' || gridcv[x][y]=='*')
            {
                printf("Invalid input. Try again\n");
                continue;
            }
            else
            {
                if(gridc[x][y]=='A' || gridc[x][y]=='B'||gridc[x][y]=='C'||gridc[x][y]=='D')
                {
                    if(gridcv[x][y]!='H')
                    {
                        gridcv[x][y]='H';
                        system("cls");
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==0)
                            {
                                printf("  ");
                                for(j=0;j<10;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=0;j<10;j++)
                                printf("%c ",gridcv[i][j]);
                            printf("\n");
                        }
                        printf("\n");
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==0)
                            {
                                printf("  ");
                                for(j=0;j<10;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=0;j<10;j++)
                                printf("%c ",griduv[i][j]);
                            printf("\n");
                        }
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<10;j++)
                            {
                                if(gridcv[i][j]=='H')
                                    win++;
                            }
                        }
                        if(win==14)
                        {
                            printf("\nYou win!\n");
                            break;
                        }
                        win=0;
                        continue;
                    }
                    else
                    {
                        printf("Invalid Input. Try again\n");
                        continue;
                    }
                }
                else
                {
                    gridcv[x][y]='*';
                    break;
                }
            }
        }
        for(;;)
        {
            probab=rand()%diff;
            if(probab==diff-3&& a<5)
            {
                x=uposa[a][0];
                y=uposa[a][1];
                a++;
            }
            else if(probab==diff-2 && b<4)
            {
                x=uposb[b][0];
                y=uposb[b][1];
                b++;
            }
            else if(probab==diff-5 && d<3)
            {
                x=uposd[d][0];
                y=uposd[d][1];
                d++;
            }
            else if(probab==diff-6 && c<2)
            {
                x=uposc[c][0];
                y=uposc[c][1];
                c++;
            }
            else
            {
                x=rand()%10;
                y=rand()%10;
            }
            if(x>9 || x<0 || y>9 || y<0 || griduv[x][y]=='H' || griduv[x][y]=='*')
            {
                continue;
            }
            else
            {
                if(gridu[x][y]=='A' || gridu[x][y]=='B'||gridu[x][y]=='C'||gridu[x][y]=='D')
                {
                    if(griduv[x][y]!='H')
                    {
                        griduv[x][y]='H';
                        system("cls");
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==0)
                            {
                                printf("  ");
                                for(j=0;j<10;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=0;j<10;j++)
                                printf("%c ",gridcv[i][j]);
                            printf("\n");
                        }
                        printf("\n");
                        for(i=0;i<10;i++)
                        {
                            for(j=0;j<30;j++)
                            printf(" ");
                            if(i==0)
                            {
                                printf("  ");
                                for(j=0;j<10;j++)
                                    printf("%d ",j);
                                printf("\n");
                                for(j=0;j<30;j++)
                                printf(" ");
                            }
                            printf("%d ",i);
                            for(j=0;j<10;j++)
                                printf("%c ",griduv[i][j]);
                            printf("\n");
                        }
                        delay(1000);
                        continue;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    griduv[x][y]='*';
                    break;
                }
            }

        }
        for(i=0;i<10;i++)
        {
            for(j=0;j<10;j++)
            {
                if(gridcv[i][j]=='H')
                    win++;
            }
        }
        if(win==14)
        {
            printf("\nYou win!\n");
            break;
        }
        win=0;
        for(i=0;i<10;i++)
        {
            for(j=0;j<10;j++)
            {
                if(griduv[i][j]=='H')
                    win++;
            }
        }
        if(win==14)
        {
            printf("\nYou lose!\n");
            break;
        }
        win=0;
    }
    return 0;
}
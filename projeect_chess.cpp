#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>

//Since the direction key is a special character,
//two values are input, and the first number returns 224 for all the direction keys first.
//Then judge the direction like 75 77

#define LEFT 75 
#define RIGHT 77
#define DOWN 80
#define UP 72
#define Select 13

#define pawn 1
#define rock 2
#define knight 3
#define bishop 4
#define queen 5
#define king 6

//typedef PickedPieces PP

int x = 1;
int y = 1;
int x_max = 8;
int y_max = 8;

int arrX = 2;
int arrY = 2;

int save_x;
int save_y;

int color = 0;

int cnt = 0;

int PickedPieces[2] = {0 , 0}; // x = [0], y = [1]

int xy_save(int x, int y) //Coordinates previously pointed at 
{
	save_x = x;
	save_y = y;
}

int first = 0;

int BoardControl(int x, int y);
void EraseOutline(int mode);

// 1 pawn 2 rock 3 knight 4 bishop 5 queen 6 king
int currentTurn = 1;
int base_board[8][8] = {
        {2,3,4,5,6,4,3,2},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
};



struct Location
{
    int arrX;
	int arrY;
};

char blackWhite[8][8] = {
        {'O','X','O','O','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','O','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','O','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'}
};

int moves[8][8];

int pick;

void gotoxy(int x, int y) {
    //x, y set coordinates
    COORD pos = { x,y };
    //console cursor move
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int Pawn(void)
{
	int move = 0;
	
	if(y == 2 || y == 7)
	{	
		 
	}
	else
	{
		
	}
}

void ChessPieces()
{
	gotoxy(0, (y_max * 2) + 4);
	printf("                ");
	gotoxy(0, (y_max * 2) + 4);
	switch(base_board[y - 1][x - 1])
	{	
		case 1:
			printf("1 pawn Æù\n");
			// Pawn();
			break;
			
		case 2:
			printf("2 rock ·è\n");
			break;
		
		case 3:
			printf("3 knight ³ªÀÌÆ®\n");
			break;
		
		case 4:				
			printf("4 bishop ºñ¼ó\n");
			break;
		
		case 5:	
			printf("5 queen Äý\n");
			break;
			
		case 6:	
			printf("6 king Å·\n");
			break;		
	}
}

int KeyControl()
{
	char input = getch(); //Because getchar uses a buffer, getch is used, and it is not displayed like getchar and getche.
	
	if(input == ' ' || input == '\r') // Confirm the input of the space bar, and since getch comes in \r after enter, put \r to check if enter is entered
		return Select;
	else if((input == 'A' || input == 'a') || input == LEFT)
		return LEFT;
		
	else if((input == 'D' || input == 'd') || input == RIGHT)
		return RIGHT;
		
	else if((input == 'W' || input == 'w') || input == UP)
		return UP;
		
	else if((input == 'S' || input == 's') || input == DOWN)
		return DOWN;
}
 
int Rules(void)
{
	printf("\t\tGame Rules\n\n\n");
	printf("Use the arrow keys and W, A, S, D to move.\n");
	
	printf("Press enter to exit to menu\n");
	while(1)
	{
		if(getch() == Select)
			break;
	}
	
	return 0;	
} 
 
void title(void) 
{
	system("cls");
	gotoxy(20, 5);
	printf("¡á¡áChess Game¡á¡á\n");
	
	
	gotoxy(20 - 3, 12);
	printf("-> Start Game");
	gotoxy(20, 13);
	printf("Game Rules");
	gotoxy(20, 14);
	printf("Exit Game");
	
	gotoxy(20, 15);
	printf("Test Case");
} 
 
int MenuDraw()
{
	int menu_y = 12, menu_x = 20;
		
	while(1)
	{	
		gotoxy(menu_x,16);
		printf("Select : %d", menu_y);
	
		char c = KeyControl();
		switch (c) {
		    case DOWN:
		        if (menu_y != 16)
		        {
		        	gotoxy(menu_x - 3, menu_y++);
		            printf("  ");
		            gotoxy(menu_x - 3, menu_y);
		            printf("->");
				}
		        break;
		
		    case UP:
		        if(menu_y != 12)
		        {
		        	gotoxy(menu_x - 3, menu_y--);
		            printf("  ");
		            gotoxy(menu_x - 3, menu_y);
		            printf("->");
				}
		        break;
		    
		    case Select:
		    	if(menu_y == 12)
		    		return 0;
				
				else if(menu_y == 13)
					return 1;
				
				else if(menu_y == 14)
					return 2;
				else
					return 3;		
		}
	}	
}

void EraseOutline(void) 
{
	for(int i = 0; i <= 4; i++) // Delete previously taken coordinate contours 
	{
		if(x != 1)
		{
			gotoxy(save_x - i, save_y); // 9
			printf(" ");
			
			gotoxy(save_x - i, save_y - 1);// 11
			printf(" ");
			
			gotoxy(save_x - i, save_y + 1); // 8
			printf(" ");
		}
	
		gotoxy(save_x, save_y - 1); // 12
		printf(" ");
		
		gotoxy(save_x + i, save_y + 1); // 6
		printf(" ");
		
		if(x != 8)
		{
			gotoxy(save_x + i, save_y - 1); //2
			printf(" ");
			
			gotoxy(save_x + i, save_y); // 3
			printf(" ");
			
			gotoxy(save_x, save_y + 1); // 5
			printf(" ");
		}
	}
}

int BoardControl(int x, int y) //Editing
{
	// A 1 == xy 2 2
	
	if(x != 1) // Coordinate outline currently being taken
	{
		gotoxy(arrX - 2, arrY); // 9
		printf("¡á");
	
		gotoxy(arrX - 2, arrY - 1);// 11
		printf("¡á");
		
		gotoxy(arrX - 2, arrY + 1); // 8
		printf("¡á");
	}
	
	gotoxy(arrX, arrY - 1); // 12
	printf("¡á");

	gotoxy(arrX, arrY + 1); // 6
	printf("¡á");
	
	if(x != 8)
	{
		gotoxy(arrX + 2, arrY - 1); //2
		printf("¡á");
		
		gotoxy(arrX + 2, arrY); // 3
		printf("¡á");
		
		gotoxy(arrX + 2, arrY + 1); // 4
		printf("¡á");
	}
	
	if(base_board[y - 1][x - 1] == pawn && cnt)
	{
		if(y == 2 || y == 7)
		{
			for(int i = 0; i <= 4; i += 2)	
			{
				if(x != 1) // Coordinate outline currently being taken
				{
					gotoxy(arrX - 2, arrY + i); // 9
					printf("¡á");
					
					gotoxy(arrX - 2, arrY + i - 1);// 11
					printf("¡á");
					
					gotoxy(arrX - 2, arrY + i + 1); // 8
					printf("¡á");
				}
				
				gotoxy(arrX, arrY + i - 1); // 12
				printf("¡á");
				
				gotoxy(arrX, arrY + i + 1); // 6
				printf("¡á");
				
				if(x != 8)
				{
					gotoxy(arrX + 2, arrY + i - 1); //2
					printf("¡á");
					
					gotoxy(arrX + 2, arrY + i); // 3
					printf("¡á");
					
					gotoxy(arrX + 2, arrY + i + 1); // 4
					printf("¡á");
				}
			}
		}
	}
	
	xy_save(arrX, arrY);
}

int BoardControl1(void)
{
    // A 1 == xy 2 2

    for(int i = 0; i <= 4; i++) // Delete previously taken coordinate contours
    {
        if(x != 1)
        {
            gotoxy(save_x - i, save_y); // 9
            printf(" ");

            gotoxy(save_x - i, save_y - 1);// 11
            printf(" ");

            gotoxy(save_x - i, save_y + 1); // 8
            printf(" ");
        }

        gotoxy(save_x, save_y - 1); // 12
        printf(" ");

        gotoxy(save_x + i, save_y + 1); // 6
        printf(" ");

        if(x != 8)
        {
            gotoxy(save_x + i, save_y - 1); //2½Ã
            printf(" ");

            gotoxy(save_x + i, save_y); // 3½Ã
            printf(" ");

            gotoxy(save_x, save_y + 1); // 5½Ã
            printf(" ");
        }
    }

    if(x != 1) // Coordinate outline currently being taken
	{
		gotoxy(arrX - 2, arrY); // 9
		printf("¡á");
		
		gotoxy(arrX - 2, arrY - 1);// 11
		printf("¡á");
		
		gotoxy(arrX - 2, arrY + 1); // 8
		printf("¡á");
	}
	
	gotoxy(arrX, arrY - 1); // 12
	printf("¡á");
	
	gotoxy(arrX, arrY + 1); // 6
	printf("¡á");
	
	if(x != 8)
	{
		gotoxy(arrX + 2, arrY - 1); //2
		printf("¡á");
		
		gotoxy(arrX + 2, arrY); // 3
		printf("¡á");
		
		gotoxy(arrX + 2, arrY + 1); // 4
		printf("¡á");
	}

    xy_save(arrX, arrY);
}
  
void Game(void)
{		
	while(1) {
		
		/*
		gotoxy(0, y_max + 2);
		printf("%20d ÃÊ \n", clock() / 1000);
		Sleep(1000);*/ 
		
		gotoxy(0, 0); //gotoxy test
		printf("J");
		
		int k = 2;
		int l = 2;
		
		char c;
		
		gotoxy(0, (y_max * 2) + 3);
		printf("ÇöÀç ÁÂÇ¥ : %c%d\n", 64 + x, 9 - y); //Output chess checkerboard coordinates 
		
		ChessPieces(); // Chess piece check function 
		
		gotoxy(0,21);
		printf("½ÇÁ¦ ¹è¿­ ÁÂÇ¥ : %d %d", x, y); //array coordinates 
		
		//EraseOutline();
		//BoardControl(arrX, arrY); //Current tile outline
		BoardControl1(); //Current tile outline

		gotoxy(0,22);
        printf("      ");
		gotoxy(0,22);
        printf("%d %d", arrX, arrY); //Coordinates in the console
		
		for(int i = 1; i <= 8; i++) // outer coordinates 
		{
			gotoxy(0,l);
			printf("%d", 9 - i);
			
			gotoxy(32,l);
			printf("%d", 9 - i);
			
			gotoxy(k,0);
			printf("%c", 64 + i);
			
			gotoxy(k,18);
			printf("%c", 64 + i);
			
			k += 4;
			l += 2;
		}
		
		for(int i = 0; i <= 31; i++) //chess board outline 
		{
			if(i <= 16)
			{
				gotoxy(1,i);
				printf("|");
				
				gotoxy(31,i);
				printf("|");
			}
			
			gotoxy(i,1);
			printf("-");
			
			gotoxy(i,17);
			printf("-");
			k += 4;
			l += 2;
		}
	
		k = 2;
		l = 2;
		
		for(int i = 0; i < 8; i++) //chess board and pieces setting
		{
			for(int j = 0; j < 8; j++)
			{
	    		gotoxy(k, l);
	    		if(base_board[i][j]) 
	    			printf("%d", base_board[i][j]);
	    		else
	    			printf("%c", blackWhite[i][j]);
	    		k += 4;
	    	}
	    	k = 2;
	    	l += 2;
		}
		
        c = KeyControl(); // Move the chessboard and select pieces
        switch (c) {
            case LEFT:
                if (x != 1)
                {
                	gotoxy(x--, y);
                	arrX -= 4;
				}
                break;

            case RIGHT:
                if (x != x_max)
                {
                	gotoxy(x++, y);
                	arrX += 4;
				}
                break;

            case DOWN:
                if (y != y_max)
                {
					gotoxy(x, y++);	
					arrY += 2;
				}
                break;

            case UP:
                if(y != 1)
            	{
            		gotoxy(x, y--);
            		arrY -= 2;
				}
                break;
            case Select:
            	if(base_board[y - 1][x - 1])
				{
					gotoxy(0,23);
        			printf("                      ");
        			gotoxy(0,23);
					printf("naneun byeongsin");
					cnt++;
					ChessPieces();
					PickedPieces[0] = x;
					PickedPieces[1] = y;
					
				}
				else 
				{
					cnt = 0;
					gotoxy(0,23);
					printf("                      ");
					gotoxy(0,23);
					printf("pick the pieces");
				}
            	break;
                
        }
        
        
	}
} 
 
int main(void)
{	
	while(1)
	{
		title();
		int menu_code = MenuDraw();
		if(menu_code == 0)
		{
			system("cls");
		    Game();
		}
		else if(menu_code == 1)
		{
			system("cls");
			Rules();
		}
		else if(menu_code == 2)
		{
			return 0;
		}
		else if(menu_code == 3)
		{
			return 0;
		} 
		
		system("cls");
	}
	
    return 0;
}

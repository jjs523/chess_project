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
#define ESC 27

#define pawn 1
#define rock 2
#define knight 3
#define bishop 4
#define queen 5
#define king 6

int x = 0;
int y = 0;
int x_max = 7;
int y_max = 7;

int arrX = 2;
int arrY = 2;

int cnt = 0;

int PickedPieces[2] = {0 , 0}; // x = [0], y = [1]

int temp = 0;

int turn = 0;

struct xy_save
{
	int save_x;
	int save_y;
} Erase, Next, Cursor;

void gotoxy(int x, int y);
int BoardControl(int x, int y);
void EraseOutline(int mode);
int KeyControl();
void control(void);
void Selected_Pieces(int xx, int yy);
int promotion();

// 1 pawn 2 rook 3 knight 4 bishop 5 queen 6 king
int currentTurn = 1;
int base_board[8][8] = {
        {12,13,14,15,16,14,13,12},
        {11,11,11,11,11,11,11,11},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,6,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
};

struct Pieces
{
    char Pawn[8];
	char Rook[2];
	char Knight[2];
	char Bishop[2];
	char Queen;
	char King;
};

struct Board
{
	int board[8][8];
	int turn;
	
	struct Board *next;
	
} board, save;

void addFirst(struct Node* target, int data)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->next = target->next;
    newNode->data = data;
    target->next = newNode;
}

struct Node* findNode(struct Node* node, int data)
{
    while (!(node->next == NULL))
    {
        if (node->next->data == data)
        {
            data = node->next->data;
			node = node -> next;
          	return data, node;
            break;
        } 
        else
            node = node->next;
    }
}

char blackWhite[8][8] = {
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'}
};

void gotoxy(int x, int y) {
    //x, y set coordinates
    COORD pos = { x,y };
    //console cursor move
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void WhereToGo(void)	//배열좌표에서 +를 해야 밑으로 내려가며 -가 위쪽 플레이어 기준 위로 가는 것 
{
	Next.save_x = x;
	Next.save_y = y;

	gotoxy(36,0);	
	printf("                                             ");	
	gotoxy(36,2);	
	printf("                                             ");	
		
	gotoxy(36,0);	
	printf("처음으로 찍은 값 X : %d Y : %d data = %d", PickedPieces[1], PickedPieces[0], base_board[PickedPieces[1]][PickedPieces[0]]);
	gotoxy(36,2);	
	printf("마지막으로 찍은 값 X : %d Y : %d data = %d", Next.save_y, Next.save_x, base_board[Next.save_y][Next.save_x]);
	
	Selected_Pieces(PickedPieces[0], PickedPieces[1]);
}

void time(void)
{
	gotoxy(20, 20);
	int seconde =  clock() / 1000;
	int minit = 0;
	if(seconde > 60)
	{
		minit++;
		seconde = 0;
	}
		
	
	printf("%10d 분%d 초\n", minit, seconde);
	//Sleep(1000);
}

void move(void)
{	
	gotoxy(36,8);
	printf("       ");
	if(base_board[Next.save_y][Next.save_x])
	{
		base_board[Next.save_y][Next.save_x] = base_board[PickedPieces[1]][PickedPieces[0]];
		base_board[PickedPieces[1]][PickedPieces[0]] = 0;			
		gotoxy(36,8);
		printf("attack");
	}
	
	else
	{
		temp = base_board[Next.save_y][Next.save_x];
		base_board[Next.save_y][Next.save_x] = base_board[PickedPieces[1]][PickedPieces[0]];
		base_board[PickedPieces[1]][PickedPieces[0]] = temp;		
		gotoxy(36,8);
		printf("move");
	}
	cnt = 0 ;
	turn++;
	
	
	
	
}

int Pawn(void)//배열좌표에서 +를 해야 밑으로 내려가며 -가 위쪽 플레이어 기준 위로 가는 것  x - 는 왼쪽  
{	
	if(turn % 2 == 0) //white  
	{
		if(PickedPieces[1] == 6) // 최대 2두칸 이동 가능한 상항 
		{	
			if(!(base_board[PickedPieces[1] - 1][PickedPieces[0]])) // 앞 2칸에 기물이 있는지 없는지 확인  
			{
				if(PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] == Next.save_x) // 1
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("한칸으로 들어감");
					move();	
				}
				
				if(!(base_board[PickedPieces[1] - 2][PickedPieces[0]])) 
				{
				 	if(PickedPieces[1] - 2 == Next.save_y && PickedPieces[0] == Next.save_x) // 2
					{
						gotoxy(36,11);
						printf("                               ");
						gotoxy(36,11);	
						printf("두칸으로 들어감");
						move();	
					}
				}
			}
			if((base_board[PickedPieces[1] - 1][PickedPieces[0] + 1]) || (base_board[PickedPieces[1] - 1][PickedPieces[0] - 1])) // 적 말이 왔을 때 공격 모션 
			{
				
				gotoxy(50,20);
				printf("%d", (PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] - 1 == Next.save_x) && base_board[Next.save_y][Next.save_x]);
				gotoxy(52,20);
				printf("%d", (PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] + 1 == Next.save_x) && base_board[Next.save_y][Next.save_x]);
				
				
				if((PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] - 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("왼쪽 위으로 들어감");
					move();	
				}
				if((PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] + 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("오른쪽 위으로 들어감!!");
					move();	
				}
			}
			else
			{
				gotoxy(36,11);
				printf("                               ");
				gotoxy(36,11);
				printf("이동할 위치를 다시 찍어 주세요.") ;
			}	
		}
		else 
		{
			if(!(base_board[PickedPieces[1] - 1][PickedPieces[0]]))//앞에 말이 있으면 못 움직임
			{
				if(PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] == Next.save_x) 
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("한칸으로 들어감");
					move();	
				}
			}
			if((base_board[PickedPieces[1] - 1][PickedPieces[0] + 1]) || (base_board[PickedPieces[1] - 1][PickedPieces[0] - 1])) // 적 말이 왔을 때 공격 모션 
			{
				if((PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] - 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("왼쪽 위으로 들어감");
					move();	
				}
				if((PickedPieces[1] - 1 == Next.save_y && PickedPieces[0] + 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("오른쪽 위으로 들어감!");
					move();	
				}
			}
			else
			{
				gotoxy(36,11);
				printf("                               ");
				gotoxy(36,11);
				printf("이동할 위치를 다시 찍어 주세요.") ;
				
			}
		}
		
	}
	else//black
	{	
		if(PickedPieces[1] == 1) //2칸 이동 가 능  
		{	
			if(!(base_board[PickedPieces[1] + 1][PickedPieces[0]])) // 앞 2칸에 기물이 있는지 없는지 확인  
			{
				if(PickedPieces[1] + 1 == Next.save_y && PickedPieces[0] == Next.save_x)
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("한칸이동");
					move();	
				}
				
				if(!(base_board[PickedPieces[1] + 2][PickedPieces[0]]))
				{
					if(PickedPieces[1] + 2 == Next.save_y && PickedPieces[0] == Next.save_x)
					{	
						gotoxy(36,11);
						printf("                               ");
						gotoxy(36,11);	
						printf("두칸이동");
						move();	
					}
				}
			 	
			if((base_board[PickedPieces[1] + 1][PickedPieces[0] + 1]) || (base_board[PickedPieces[1] + 1][PickedPieces[0] - 1])) // 적 말이 왔을 때 공격 모션 
			{
				if((PickedPieces[1] + 1 == Next.save_y && PickedPieces[0] - 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("왼쪽 밑으로 들어감??");
					move();	
				}
				if((PickedPieces[1] + 1 == Next.save_y && PickedPieces[0] + 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("오른쪽 밑으로 들어감!!");
					move();	
				}
			}
			}
			else
			{
				gotoxy(36,11);
				printf("                               ");
				gotoxy(36,11);
				printf("이동할 위치를 다시 찍어 주세요.") ;
				
			}
				
		}
		else
		{
			if(!(base_board[PickedPieces[1] + 1][PickedPieces[0]]))
			{
				if(PickedPieces[1] + 1 == Next.save_y && PickedPieces[0] == Next.save_x)
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("한칸이동");
					move();	
				}
			}
			if((base_board[PickedPieces[1] + 1][PickedPieces[0] + 1]) || (base_board[PickedPieces[1] + 1][PickedPieces[0] - 1])) // 적 말이 왔을 때 공격 모션 
			{
				if((PickedPieces[1] + 1 == Next.save_y && PickedPieces[0] - 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("왼쪽 밑으로 들어감");
					move();	
				}
				if((PickedPieces[1] + 1 == Next.save_y && PickedPieces[0] + 1 == Next.save_x) && base_board[Next.save_y][Next.save_x])
				{	
					gotoxy(36,11);
					printf("                               ");
					gotoxy(36,11);	
					printf("오른쪽 밑으로 들어감!");
					move();	
				}
			}
			else
			{
				gotoxy(36,11);
				printf("                               ");
				gotoxy(36,11);
				printf("Please reset the location to move to.") ;
				
			}
		}
		
	}
	
	if((y == 0 || y == 7) && ((base_board[y][x] == 1) || (base_board[y][x] == 11))) 
	{
		//cnt is changed and the player's turn is passed, so set the chess piece settings in reverse
		
		if(turn % 2 == 0) //b 
			base_board[y][x] = (10 + promotion());
			
		else //w
			base_board[y][x] = promotion();	
		
		//erase promotion comment
		gotoxy(36,13);
		printf("                              ");
		gotoxy(36,14);
		printf("                              ");
		gotoxy(36,15);
		printf("                              ");
		gotoxy(36,16);
		printf("                              ");
		gotoxy(36,17);
		printf("                              ");
	}
}

int promotion()
{	
	Cursor.save_x = x;
	Cursor.save_y = y;
	
	int select = 14, selectx = 34;
	gotoxy(34,14);
	printf(">");
	
	while(1)
	{
		gotoxy(36,13);
		printf("Which chess piece would you like to turn into?");
		gotoxy(36,14);
		printf("Rook 2");
		gotoxy(36,15);
		printf("Knight 3");
		gotoxy(36,16);
		printf("Bishop 4");
		gotoxy(36,17);
		printf("Queen 5");
		
		char c = KeyControl();
		switch (c) {
		    case DOWN:
		        if (select != 17)
		        {
		        	gotoxy(selectx, select++);
		            printf(" ");
		            gotoxy(selectx, select);
		            printf(">");
				}
		        break;
		
		    case UP:
		        if(select != 14)
		        {
		        	gotoxy(selectx, select--);
		            printf(" ");
		            gotoxy(selectx, select);
		            printf(">");
				}
		        break;
		    
		    case Select:
		    	if(select == 14)
		    		return 2;
				
				else if(select == 15)
					return 3;
				
				else if(select == 16)
					return 4;
					
				else if(select == 17)
					return 5;		
				break;		
		}
	}
}

void Rook(void)
{
	int emty = 0;

	float yy = 0; //현재 비숍 위치와 이동할 위치의 거리차이 y 변수  
	float xx = 0; //현재 비숍 위치와 이동할 위치의 거리차이 x 변수 
	
	yy = abs(Next.save_y - PickedPieces[1]); //현재 비숍 위치와 이동할 위치의 거리차이 x
	xx = abs(Next.save_x - PickedPieces[0]); //현재 비숍 위치와 이동할 위치의 거리차이 y
	
	gotoxy(50,25);								//잠시 체크용  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	if(Next.save_x == PickedPieces[0]) // up down 
	{
		
		if(Next.save_y < PickedPieces[1]) //up
		{
			for(int i = 1; i <= yy; i++) //위 빈공간 확인 반복문
			{
				if(base_board[PickedPieces[1] - i][PickedPieces[0]])
					emty++;
			}
		}
		else //down
		{
			for(int i = 1; i <= yy ; i++) //밑 빈공간 확인 반복문 
			{
				if(base_board[PickedPieces[1] + i][PickedPieces[0]])
					emty++;
			}
		}
		
		//이동 가능한가에 대한 판단 
		if(!(emty)) // 아무것도 없을때 
			move();
		else if(emty == 1 && ((xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // 흰 
			move();
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
			move();
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // 흰 
			move();
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
			move(); 
	}
	
	else if(Next.save_y == PickedPieces[1]) // left right
	{
		if(Next.save_x < PickedPieces[0]) //left
		{
			for(int i = 1; i <= xx ; i++) //왼쪽 빈공간 확인 반복문 
			{				
				if(base_board[PickedPieces[1]][PickedPieces[0] - i])
					emty++;			
			}
		}
		else //right 
		{
			for(int i = 1; i <= xx ; i++) //오른쪽 빈공간 확인 반복문 
			{
				if(base_board[PickedPieces[1]][PickedPieces[0] + i])
					emty++;	
			}
		}
		
		//이동 가능한가에 대한 판단 
		if(!(emty)) // 아무것도 없을때 
			move();
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] > 7)))) // 흰 
			move();
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
			move();
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //흰 
			move();
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // 검
			move(); 

			
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}

}

void Knight(void)
{
	int emty = 0; //이동할 위치사이의 기물존재 확인을 위한 변수  
	int cntline = 0;
	
	gotoxy(50,27);
	printf("   ");
	
	//기울기를 사용하여 이동 
	
	float yy = 0; //현재 비숍 위치와 이동할 위치의 거리차이 y 변수  
	float xx = 0; //현재 비숍 위치와 이동할 위치의 거리차이 x 변수 
	
	yy = abs(Next.save_y - PickedPieces[1]); //현재 비숍 위치와 이동할 위치의 거리차이 x
	xx = abs(Next.save_x - PickedPieces[0]); //현재 비숍 위치와 이동할 위치의 거리차이 y
	
	gotoxy(50,25);								//잠시 체크용  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	if(yy == 2 && xx == 1 || yy == 1 && xx == 2)
	{
		if((turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7) || !(base_board[Next.save_y][Next.save_x]))
			move();
					
		else if((turn % 2 == 1 && base_board[Next.save_y][Next.save_x] < 7) || !(base_board[Next.save_y][Next.save_x]))
			move();
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}
}

void Bishop(void)
{
	int emty = 0; //이동할 위치사이의 기물존재 확인을 위한 변수  
	int cntline = 0;
	
	gotoxy(50,27);
	printf("   ");
	
	//기울기를 통한 대각선 이동 
	
	float yy = 0; //현재 비숍 위치와 이동할 위치의 거리차이 y 변수  
	float xx = 0; //현재 비숍 위치와 이동할 위치의 거리차이 x 변수 
	
	yy = abs(Next.save_y - PickedPieces[1]); //현재 비숍 위치와 이동할 위치의 거리차이 x
	xx = abs(Next.save_x - PickedPieces[0]); //현재 비숍 위치와 이동할 위치의 거리차이 y
	
	gotoxy(50,25);								//잠시 체크용  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	float inclination = yy / xx; 

	if(inclination == 1)
	{
		gotoxy(50,26);
		printf("                      ");
		gotoxy(50,26);
		printf("inclination : %2.f",inclination);
		
		if(Next.save_y > PickedPieces[1]) // down 
		{
			if(Next.save_x < PickedPieces[0]) //left
			{
				for(int i = 1; i <= yy ; i++) //왼쪽 밑 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //오른쪽 밑 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			
			//이동 가능한가에 대한 판단 
			if(!(emty)) // 아무것도 없을때 
				move();
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // 흰 
				move();
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //흰 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // 검
				move(); 
		}
		else // up
		{
			if(Next.save_x < PickedPieces[0]) //left
			{
				for(int i = 1; i <= yy ; i++) //왼쪽 위 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //오른쪽 위 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;
				}
			}
			
			//이동 가능한가에 대한 판단
			if(!(emty)) // 아무것도 없을때 
				move();
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // 흰 
				move();
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //흰 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // 검
				move(); 
		}
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}

	cntline = 0;
}

void Queen(void)
{
	int emty = 0; //이동할 위치사이의 기물존재 확인을 위한 변수  
	int cntline = 0;
	
	gotoxy(50,27);
	printf("   ");
	
	//기울기를 통한 대각선 이동 
	
	float yy = 0; //현재 비숍 위치와 이동할 위치의 거리차이 y 변수  
	float xx = 0; //현재 비숍 위치와 이동할 위치의 거리차이 x 변수 
	
	yy = abs(Next.save_y - PickedPieces[1]); //현재 비숍 위치와 이동할 위치의 거리차이 x
	xx = abs(Next.save_x - PickedPieces[0]); //현재 비숍 위치와 이동할 위치의 거리차이 y
	
	gotoxy(50,25);								//잠시 체크용  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	float inclination = yy / xx; 

	if(inclination == 1)
	{
		gotoxy(50,26);
		printf("                      ");
		gotoxy(50,26);
		printf("inclination : %2.f",inclination);
		
		if(Next.save_y > PickedPieces[1]) // down 
		{
			if(Next.save_x < PickedPieces[0]) //left
			{
				for(int i = 1; i <= yy ; i++) //왼쪽 밑 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //오른쪽 밑 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			
			//이동 가능한가에 대한 판단 
			if(!(emty)) // 아무것도 없을때 
				move();
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // 흰 
				move();
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //흰 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // 검
				move(); 
		}
		else // up
		{
			if(Next.save_x < PickedPieces[0]) //left
			{
				for(int i = 1; i <= yy ; i++) //왼쪽 위 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //오른쪽 위 대각선 빈공간 확인 반복문 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;		
				}
			}
			
			//이동 가능한가에 대한 판단
			if(!(emty)) // 아무것도 없을때 
				move();
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // 흰 
				move();
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //흰 
				move();
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // 검
				move(); 
		}
	}
	else if(Next.save_x == PickedPieces[0]) // up down 
	{
		
		if(Next.save_y < PickedPieces[1]) //up
		{
			for(int i = 1; i <= yy; i++) //위 빈공간 확인 반복문
			{
				if(base_board[PickedPieces[1] - i][PickedPieces[0]])
					emty++;
			}
		}
		else //down
		{
			for(int i = 1; i <= yy ; i++) //밑 빈공간 확인 반복문 
			{
				if(base_board[PickedPieces[1] + i][PickedPieces[0]])
					emty++;
			}
		}
		
		//이동 가능한가에 대한 판단 
		if(!(emty)) // 아무것도 없을때 
			move();
		else if(emty == 1 && ((xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // 흰 
			move();
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
			move();
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // 흰 
			move();
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
			move(); 
	}
	
	else if(Next.save_y == PickedPieces[1]) // left right
	{
		if(Next.save_x < PickedPieces[0]) //left
		{
			for(int i = 1; i <= xx ; i++) //왼쪽 빈공간 확인 반복문 
			{				
				if(base_board[PickedPieces[1]][PickedPieces[0] - i])
					emty++;			
			}
		}
		else //right 
		{
			for(int i = 1; i <= xx ; i++) //오른쪽 빈공간 확인 반복문 
			{
				if(base_board[PickedPieces[1]][PickedPieces[0] + i])
					emty++;	
			}
		}
		
		//이동 가능한가에 대한 판단 
		if(!(emty)) // 아무것도 없을때 
			move();
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] > 7)))) // 흰 
			move();
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //검 
			move();
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //흰 
			move();
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // 검
			move(); 	
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}
}

void King(void)
{
	int emty = 0; //이동할 위치사이의 기물존재 확인을 위한 변수  
	int cntline = 0;
	
	gotoxy(50,27);
	printf("   ");
	
	float yy = 0; //현재 비숍 위치와 이동할 위치의 거리차이 y 변수  
	float xx = 0; //현재 비숍 위치와 이동할 위치의 거리차이 x 변수 
	
	yy = abs(Next.save_y - PickedPieces[1]); //현재 비숍 위치와 이동할 위치의 거리차이 x
	xx = abs(Next.save_x - PickedPieces[0]); //현재 비숍 위치와 이동할 위치의 거리차이 y
	
	gotoxy(50,25);								//잠시 체크용  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	if((yy == 1 && xx == 1) || ((yy == 1 && xx == 0) || (yy == 0 && xx == 1)))
	{
		if((turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7) || !(base_board[Next.save_y][Next.save_x]))
			move();
					
		else if((turn % 2 == 1 && base_board[Next.save_y][Next.save_x] < 7) || !(base_board[Next.save_y][Next.save_x]))
			move();
	}
}

void Selected_Pieces(int xx, int yy)
{
	gotoxy(0, (y_max * 2) + 6);
	printf("                ");
	gotoxy(0, (y_max * 2) + 6);
	switch(base_board[yy][xx])
	{	
		case 1:
		case 11:
			
			printf("1 pawn\n");
			Pawn();
			break;
		
		case 2:
		case 12:
			printf("2 rock\n");
			Rook();
			break;
		
		case 3:
		case 13:
			printf("3 knight\n");
			Knight();
			break;
		
		case 4:
		case 14:				
			printf("4 bishop\n");
			Bishop();
			break;
		
		case 5:
		case 15:	
			printf("5 queen\n");
			Queen();
			break;
			
		case 6:
		case 16:	
			printf("6 king\n");
			King();
			break;		
	}
}

void control(void)
{
	char c;
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
	    	
	    	break;
	}
}

void ChessPieces(void)
{
	gotoxy(0, (y_max * 2) + 6);
	printf("                ");
	gotoxy(0, (y_max * 2) + 6);
	switch(base_board[y][x])
	{	
		case 1:
		case 11:
			
			printf("1 pawn\n");
			break;
		
		case 2:
		case 12:
			printf("2 rock\n");
			break;
		
		case 3:
		case 13:
			printf("3 knight\n");
			break;
		
		case 4:
		case 14:				
			printf("4 bishop\n");
			break;
		
		case 5:
		case 15:	
			printf("5 queen\n");
			break;
			
		case 6:
		case 16:	
			printf("6 king\n");
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
	else if(input == ESC)
		return ESC;
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
	printf("#################################################################################################\n");
	printf("#                                                                                               #\n");
	printf("#                                                                                               #\n");
	printf("#                                                                                               #\n");
	printf("#                                                                                               #\n");
	printf("#           ##     # #     ###      ##      ##              ##      #      # #     ###          #\n");
	printf("#   	   #       # #     #       #       #               #       # #     # #     #            #\n");
	printf("#          #       ###     ###      #       #              # #     ###     ###     ###          #\n");
	printf("#          #       # #     #         #       #             # #     # #     # #     #            #\n");
	printf("#           ##     # #     ###     ##      ##               ##     # #     # #     ###          #\n");
	printf("\t\t\t\t\t\tChess Game\t\n");

	
	gotoxy(48 - 3, 12);
	printf("-> Start Game");
	
	gotoxy(48, 13);
	printf("Game Rules");
	
	gotoxy(48, 14);
	printf("Exit Game");

	gotoxy(48, 15);
	printf("Test Case");
} 
 
int MenuDraw()
{
	int menu_y = 12, menu_x = 48;
		
	while(1)
	{	
		gotoxy(menu_x,16);
		printf("Select : %d", menu_y - 11);
	
		char c = KeyControl();
		switch (c) {
		    case DOWN:
		        if (menu_y != 15)
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
				else if(menu_y == 15)
					return 3;		
				break;		
		}
	}	
}

void EraseOutline(void) 
{
	for(int i = 0; i <= 4; i++) // Delete previously taken coordinate contours 
	{
		
		if(x != 0)
		{
			gotoxy(Erase.save_x - i, Erase.save_y); // 9
			printf(" ");
			
			gotoxy(Erase.save_x - i, Erase.save_y - 1);// 11
			printf(" ");
			
			gotoxy(Erase.save_x - i, Erase.save_y + 1); // 8
			printf(" ");
		}
	
		gotoxy(Erase.save_x, Erase.save_y - 1); // 12
		printf(" ");
		
		gotoxy(Erase.save_x + i, Erase.save_y + 1); // 6
		printf(" ");
		
		if(x != 7)
		{
			gotoxy(Erase.save_x + i, Erase.save_y - 1); //2
			printf(" ");
			
			gotoxy(Erase.save_x + i, Erase.save_y); // 3
			printf(" ");
			
			gotoxy(Erase.save_x, Erase.save_y + 1); // 5
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
		printf("■");
	
		gotoxy(arrX - 2, arrY - 1);// 11
		printf("■");
		
		gotoxy(arrX - 2, arrY + 1); // 8
		printf("■");
	}
	
	gotoxy(arrX, arrY - 1); // 12
	printf("■");

	gotoxy(arrX, arrY + 1); // 6
	printf("■");
	
	if(x != 8)
	{
		gotoxy(arrX + 2, arrY - 1); //2
		printf("■");
		
		gotoxy(arrX + 2, arrY); // 3
		printf("■");
		
		gotoxy(arrX + 2, arrY + 1); // 4
		printf("■");
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
					printf("■");
					
					gotoxy(arrX - 2, arrY + i - 1);// 11
					printf("■");
					
					gotoxy(arrX - 2, arrY + i + 1); // 8
					printf("■");
				}
				
				gotoxy(arrX, arrY + i - 1); // 12
				printf("■");
				
				gotoxy(arrX, arrY + i + 1); // 6
				printf("■");
				
				if(x != 8)
				{
					gotoxy(arrX + 2, arrY + i - 1); //2
					printf("■");
					
					gotoxy(arrX + 2, arrY + i); // 3
					printf("■");
					
					gotoxy(arrX + 2, arrY + i + 1); // 4
					printf("■");
				}
			}
		}
	}
	
	Erase.save_x = arrX;
	Erase.save_y = arrY;
}

int BoardControl1(void)
{
    // A 1 == xy 2 2

	EraseOutline();

    if(x != 0) // Coordinate outline currently being taken
	{
		gotoxy(arrX - 2, arrY); // 9
		printf("■");
		
		gotoxy(arrX - 2, arrY - 1);// 11
		printf("■");
		
		gotoxy(arrX - 2, arrY + 1); // 8
		printf("■");
	}
	
	gotoxy(arrX, arrY - 1); // 12
	printf("■");
	
	gotoxy(arrX, arrY + 1); // 6
	printf("■");
	
	if(x != 7)
	{
		gotoxy(arrX + 2, arrY - 1); //2
		printf("■");
		
		gotoxy(arrX + 2, arrY); // 3
		printf("■");
		
		gotoxy(arrX + 2, arrY + 1); // 4
		printf("■");
	}
	
	Erase.save_x = arrX;
	Erase.save_y = arrY;
}
  
int Game()
{	
	
	struct Pieces Black_Pieces;
	struct Pieces White_Pieces;
	
	for(int i = 0; i < 8; i++)
		Black_Pieces.Pawn[i] = 'P';
	
	for(int i = 0; i < 2; i++)		
		Black_Pieces.Rook[i] = 'R';
	
	for(int i = 0; i < 2; i++)		
		Black_Pieces.Knight[i] = 'N';
	
	for(int i = 0; i < 2; i++)		
		Black_Pieces.Bishop[i] = 'B';
	
	Black_Pieces.Queen = 'Q';
	Black_Pieces.King = 'K';
	
	for(int i = 0; i < 8; i++)
		White_Pieces.Pawn[i] = 'p';
	
	for(int i = 0; i < 2; i++)	
		White_Pieces.Rook[i] = 'r';
	
	for(int i = 0; i < 2; i++)
		White_Pieces.Knight[i] = 'n';
	
	for(int i = 0; i < 2; i++)	
		White_Pieces.Bishop[i] = 'b';
	
	White_Pieces.Queen = 'q';
	White_Pieces.King = 'k';
	
	while(1)
	{
		gotoxy(0, 0); //gotoxy test
		printf("J");
		
		int k = 2;
		int l = 2;
		
		char c;
		
		if(turn % 2 == 0) 
		{
			gotoxy(36,4);
			printf("White faction user's turn %d", turn);
		}
		else 
		{
			gotoxy(36,4);
			printf("Black faction user's turn %d", turn );
		}
		
		
		gotoxy(0, (y_max * 2) + 5);
		printf("current coordinates : %c%d\n", 65 + x, 8 - y); //Output chess checkerboard coordinates 
		
		ChessPieces(); // Chess piece check function 
		
		
		gotoxy(0,21);
		printf("                                                                     ");
		gotoxy(0,21);
		printf("real array coordinates and values : %d %d %d", y, x, base_board[y][x]); //array coordinates 
		
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
	    		{
					if(base_board[i][j] - 10 > 0)
					{
	    				switch(base_board[i][j] - 10)
	    				{
	    					case 1:
	    						printf("%c", Black_Pieces.Pawn[j]);
	    						break;
	    						
	    					case 2:
								printf("%c", Black_Pieces.Rook[0]);
								break;
							
							case 3:
								printf("%c", Black_Pieces.Knight[0]);
								break;
							
							case 4:
								printf("%c", Black_Pieces.Bishop[0]);
								break;
								
							case 5:
								printf("%c", Black_Pieces.Queen);
								break;
							
							case 6:
								printf("%c", Black_Pieces.King);
								break;	
						}	
					}
					
					else
					{
						switch(base_board[i][j])
	    				{
	    					case 1:
	    						printf("%c", White_Pieces.Pawn[j]);
	    						break;
	    						
	    					case 2:
								printf("%c", White_Pieces.Rook[0]);
								break;
							
							case 3:
								printf("%c", White_Pieces.Knight[0]);
								break;
							
							case 4:
								printf("%c", White_Pieces.Bishop[0]);
								break;
								
							case 5:
								printf("%c", White_Pieces.Queen);
								break;
							
							case 6:
								printf("%c", White_Pieces.King);
								break;	
						}
					}
	    		}
	    		else
	    		{
					if(blackWhite[i][j] == 'X')	 
	    				printf("□");
	    			else
	    				printf("■");
				}
	    			
	    		k += 4;
	    	}
	    	k = 2;
	    	l += 2;
		}
		
		gotoxy(36,0);	
		printf("처음으로 찍은 값 X : %d Y : %d data = %d", PickedPieces[1], PickedPieces[0], base_board[PickedPieces[1]][PickedPieces[0]]);
		gotoxy(36,2);	
		printf("마지막으로 찍은 값 X : %d Y : %d data = %d", Next.save_y, Next.save_x, base_board[Next.save_y][Next.save_x]);
		
		
		c = KeyControl(); // Move the chessboard and select pieces
		switch (c) {
		    case LEFT:
		        if (x != 0)
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
		        if(y != 0)
		    	{
		    		gotoxy(x, y--);
		    		arrY -= 2;
				}
		        break;
			
			case ESC:
				return 0;
				break;
		        
		    case Select:
		    	if(base_board[y][x])
				{
					gotoxy(0,23);
					printf("                                     ");
					gotoxy(36,6);
					printf(" 							         ");

					if(cnt)//기물 -> 기물 
					{
						if(PickedPieces[0] == x && PickedPieces[1] == y)
						{
							cnt--;
							gotoxy(36,6);
							printf("                                  ");
							gotoxy(36,6);
							printf("선택 취소");
						}
						else
						{
							gotoxy(0,23);
							printf("                                   ");
							gotoxy(0,23);
							printf("공격할 기물을 선택하셨습니다.");
							WhereToGo();
							//Selected_Pieces();	
						}
					}
					
					else
					{
						gotoxy(36,11);
						printf("                               ");
						if(turn % 2 == 0 && base_board[y][x] > 7)
						{
							gotoxy(36,6);
							printf(" 							 ");
							gotoxy(36,6);
							printf("흰색 기물을 선택해 주십시오.");
						}
						else if(turn % 2 == 1 && base_board[y][x] <= 6) 
						{
							gotoxy(36,6);
							printf(" 							 ");
							gotoxy(36,6);
							printf("흑색 기물을 선택해 주십시오.");
						}
						else
						{
							PickedPieces[0] = x;
							PickedPieces[1] = y;
							cnt++;
							gotoxy(36,6);
							printf("                                  ");
							gotoxy(36,6);
							printf("첫번째 선택");
						}
					}
				}
				else 
				{
					if(cnt)
					{	
						gotoxy(36,6);
						printf(" 							       				  ");
						gotoxy(36,6);
						printf("두번째 선택");
						gotoxy(0,25);
						printf("                      ");
						gotoxy(0,25);
						printf("%d %d", x, y);
						WhereToGo();
					}
					else
					{
						gotoxy(36,11);
						printf("                               ");
						cnt = 0;
						gotoxy(0,23);
						printf("기물을 선택해 주세요. pick the pieces");
					}

				}
		    	break; 
		}
	}
} 
 
 void list(void)
 {
 	save.Board = base_board;
 	
 	board* head = (board*)malloc(sizeof(board));
 	head -> next = NULL;
 	
 	board*  = (board*)malloc(sizeof(board));
 	
 }
 
void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
 
int main(void)
{	
	while(1)
	{	
		CursorView();
		title();
		switch(MenuDraw())
		{
			case 0:
				system("cls");
		    	Game();
				break;
				
			case 1:
				system("cls");
				Rules();	
				break;
				
			case 2:
				return 0;
				break;
			
			case 3:	
				break;
				
			case 4:
				break;	
		}
		system("cls");
	}
}

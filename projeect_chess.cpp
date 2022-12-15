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

int x = 0; // ������ġ�� ���� ���� 
int y = 0; // ������ġ�� ���� ���� 
int x_max = 7; //���� �ִ�ũ�� ���� 
int y_max = 7; //���� �ִ�ũ�� ���� 
 
int arrX = 2; //�ܼ�â���� �迭0 0 ��ġ 
int arrY = 2; //�ܼ�â���� �迭0 0 ��ġ

int cnt = 0; // �⹰ ���ð� �⹰ ���� ��Ҹ� ���� ī��Ʈ ���� 

int PickedPieces[2] = {0 , 0}; // x = [0], y = [1] // ���ʷ� ������ �⹰ ��ġ �迭 

int temp = 0; // �⹰ ��ġ ���� ���� 

int turn = 0; // �÷��̾� �� ���� 

///////////��� ŷ, ������ ŷ ��ǥ ���� ���� 

int Bking_x;
int Bking_y;
int Wking_x;
int Wking_y;

struct xy_save // ���� ��ǥ�� �����ϱ����� ����ü 
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
int Selected_Pieces_chk(int xx, int yy);
int promotion();
// 11 pawn 22 rook 33 knight 44 bishop 55 queen 66 king 	Black Pieces
// 1 pawn 2 rook 3 knight 4 bishop 5 queen 6 king 			White Pieces
int currentTurn = 1;
int base_board[8][8] = {
        {12,13,14,15,16,14,13,12},
        {11,11,11,11,11,11,11,11},
        {0,0,0,3,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
}; // �� �⹰�� ��ġ ������ �̵��� �� �⹰�� �ش��ϴ� ���ڵ� �̵�

int chk_board[8][8] = {0,};

struct Pieces //�⹰ ����ü 
{
    char Pawn[8];
	char Rook[2];
	char Knight[2];
	char Bishop[2];
	char Queen;
	char King;
	
	int total;
} Black_Pieces, White_Pieces;

char blackWhite[8][8] = {
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'},
        {'O','X','O','X','O','X','O','X'},
        {'X','O','X','O','X','O','X','O'}
}; // Ư�� ��ȣ ����� ����ϴ� üũ���� 

/*********************** gotoxy�� ����� ������ �ִ� ������ �ڵ����� ������ ��µȰ� �������� �ʱ� ������***********************/
void gotoxy(int x, int y) // �ܼ� ��ǥ �̵� �Լ� 
{
    //x, y set coordinates ��ǥ ���� 
    COORD pos = { x,y }; //��ġ ���� ����ü 
    //console cursor move Ŀ���̵�  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //Ŀ���� ��ġ �̵� �Լ� 
}

void Pieces_Set(void) // �⹰ �� ������ ����ü�� �⹰�� �´� ���� ���� 
{
	for(int i = 0; i < 8; i++)
	{
		Black_Pieces.Pawn[i] = 'P';
		Black_Pieces.total++; 
	}
		
	for(int i = 0; i < 2; i++)		
	{
		Black_Pieces.Rook[i] = 'R';
		Black_Pieces.total++;
	}
		
	for(int i = 0; i < 2; i++)
	{
		Black_Pieces.Knight[i] = 'N';
		Black_Pieces.total++;
	}
		
	for(int i = 0; i < 2; i++)		
	{
		Black_Pieces.Bishop[i] = 'B';
		Black_Pieces.total++;
	}
		
	Black_Pieces.Queen = 'Q';
	Black_Pieces.King = 'K';
	
	Black_Pieces.total += 2 ;
	
	for(int i = 0; i < 8; i++)
	{
		White_Pieces.Pawn[i] = 'p';
		White_Pieces.total++; 
	}
	
	for(int i = 0; i < 2; i++)
	{
		White_Pieces.Rook[i] = 'r';
		White_Pieces.total++;
	}
	
	for(int i = 0; i < 2; i++)
	{
		White_Pieces.Knight[i] = 'n';
		White_Pieces.total++;
	}
	
	for(int i = 0; i < 2; i++)	
	{
		White_Pieces.Bishop[i] = 'b';
		White_Pieces.total++;
	}
	
	White_Pieces.Queen = 'q';
	White_Pieces.King = 'k';

	White_Pieces.total += 2;
} 

void Where_To_Go(void)	//������ �⹰�� �Լ��� �̵�
{
	Next.save_x = x; //�ι�°�� ������ ��ġ�� ��ǥ ���� 
	Next.save_y = y; 

	gotoxy(36,0);	
	printf("                                             ");	
	gotoxy(36,2);	
	printf("                                             ");	
		
	gotoxy(36,0);	
	printf("ó������ ���� �� X : %d Y : %d data = %d", PickedPieces[1], PickedPieces[0], base_board[PickedPieces[1]][PickedPieces[0]]); // �ֿܼ��� ������ Ȯ���� ���� ǥ�� 
	gotoxy(36,2);	
	printf("���������� ���� �� X : %d Y : %d data = %d", Next.save_y, Next.save_x, base_board[Next.save_y][Next.save_x]);
	
	Selected_Pieces(PickedPieces[0], PickedPieces[1]); //ó�� ���� �⹰�� �Լ��� �̵� 
}

void time(void) // ���� ������ �귯�� �ð� Ȯ�� 
{
	gotoxy(20, 20);
	int seconde =  clock() / 1000;
	int minit = 0;
	if(seconde > 60)
	{
		minit++;
		seconde = 0;
	}
		
	
	printf("%10d ��%d ��\n", minit, seconde);
	//Sleep(1000);
}

int Check_Mate() //ü������Ʈ �Լ� �׽�Ʈ �� 
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			chk_board[i][j] = base_board[i][j];
	
	memcpy(chk_board, base_board, sizeof(int) * 5);
	
	Next.save_y = Bking_y;
	Next.save_x = Bking_x;
	
	for(int i = 0; i < 8; i++)
	{
		PickedPieces[1] = i;
		for(int j = 0; j < 8; j++)
		{
			PickedPieces[0] = j;
			
			if(Selected_Pieces_chk(i, j))
			{
				gotoxy(0,25);
		        printf("                ");
				gotoxy(0,25);
		        printf("Cheak Mate! %d %d", i, j);
		        return 1;
			}
		}
	}
	
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			base_board[i][j] = chk_board[i][j];
	
}

void move(void) // ü�� �� �̵� �Լ� 
{	
	if(base_board[Next.save_y][Next.save_x])
	{
		base_board[Next.save_y][Next.save_x] = base_board[PickedPieces[1]][PickedPieces[0]];
		base_board[PickedPieces[1]][PickedPieces[0]] = 0;
		if(base_board[Next.save_y][Next.save_x] > 10)
			Black_Pieces.total--;
		else
			White_Pieces.total--;
	}
	
	else
	{
		temp = base_board[Next.save_y][Next.save_x];
		base_board[Next.save_y][Next.save_x] = base_board[PickedPieces[1]][PickedPieces[0]];
		base_board[PickedPieces[1]][PickedPieces[0]] = temp;
	}
	
	cnt = 0 ; //�⹰ ���ð� �⹰ ���� ��Ҹ� ���� ī��Ʈ ���� �ʱ�ȭ 
	turn++; //�⹰ �̵� �� �� ������ ���� �� ����ڰ� ������ �� �ֵ����Ѵ� 
}

int Pawn(void) // �� �Լ�  
{	
	float yy = 0; //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� y ����  
	float xx = 0; //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� x ���� 
	
	yy = abs(Next.save_y - PickedPieces[1]); //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� x
	xx = abs(Next.save_x - PickedPieces[0]); //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� y
	
	gotoxy(50,25);								//��� üũ��  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	if((PickedPieces[1] == 6 && base_board[PickedPieces[1]][PickedPieces[0]] == 1) || (PickedPieces[1] == 1 && base_board[PickedPieces[1]][PickedPieces[0]] == 11)) 
	{
		if((yy == 2 && xx == 0) || (yy == 1 && xx == 0))
		{
			if((turn % 2 == 0 && (!(base_board[Next.save_y][Next.save_x]) && Next.save_y < PickedPieces[1]))) //��� �� 
			{
				move(); 
			}
			else if((turn % 2 == 1 && (!(base_board[Next.save_y][Next.save_x]) && Next.save_y > PickedPieces[1]))) //������ �� 
			{
				move();
			}
		}
		else if((yy == 1 && xx == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7 && Next.save_y < PickedPieces[1]))) //��� �� 
		{
			move();
		}
		else if((yy == 1 && xx == 1) && (turn % 2 == 1 && ((base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1) &&Next.save_y > PickedPieces[1]))) //������ �� 
		{
			move();
		}
	}
	else
	{
		if(yy == 1 && xx == 0)
		{
			if((turn % 2 == 0 && (!(base_board[Next.save_y][Next.save_x]) && Next.save_y < PickedPieces[1]))) //��� �� 
			{
				move(); 
			}
			else if((turn % 2 == 1 && (!(base_board[Next.save_y][Next.save_x]) && Next.save_y > PickedPieces[1]))) //������ �� 
			{
				move();
			}
		}
		else if((yy == 1 && xx == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7 && Next.save_y < PickedPieces[1]))) //��� �� 
		{
			move(); 
		}
		else if((yy == 1 && xx == 1) && (turn % 2 == 1 && ((base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1) &&Next.save_y > PickedPieces[1]))) //������ �� 
		{
			move();
		}
	}
	
	if((y == 0 || y == 7) && ((base_board[y][x] == 1) || (base_board[y][x] == 11))) //������ �� �Ʒ��� ������ �� �ٸ� ŷ ���� �ٸ� �⹰�� ��ȯ�� ���� ���� 
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

int promotion() // ���� �ٸ� �⹰�� �ٲٴ� �Լ� 
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
		
		char c = KeyControl(); //�ܼ� ��ǥ�� �����ϱ⿡ �ٸ� ���� �Լ��� ���� �� �� 
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

int Rook(void) // �� �Լ� 
{
	int emty = 0;

	float yy = 0; //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� y ����  
	float xx = 0; //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� x ���� 
	
	yy = abs(Next.save_y - PickedPieces[1]); //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� x
	xx = abs(Next.save_x - PickedPieces[0]); //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� y
	
	gotoxy(50,25);								//��� üũ��  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	if(Next.save_x == PickedPieces[0]) // up down 
	{
		
		if(Next.save_y < PickedPieces[1]) //up
		{
			for(int i = 1; i <= yy; i++) //�� ����� Ȯ�� �ݺ���
			{
				if(base_board[PickedPieces[1] - i][PickedPieces[0]])
					emty++;
			}
		}
		else //down
		{
			for(int i = 1; i <= yy ; i++) //�� ����� Ȯ�� �ݺ��� 
			{
				if(base_board[PickedPieces[1] + i][PickedPieces[0]])
					emty++;
			}
		}
		
		//�̵� �����Ѱ��� ���� �Ǵ� 
		if(!(emty)) // �ƹ��͵� ������ 
			move();
		else if(emty == 1 && ((xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // �� 
			move();
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
			move();
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // �� 
			move();
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
			move(); 
	}
	
	else if(Next.save_y == PickedPieces[1]) // left right
	{
		if(Next.save_x < PickedPieces[0]) //left
		{
			for(int i = 1; i <= xx ; i++) //���� ����� Ȯ�� �ݺ��� 
			{				
				if(base_board[PickedPieces[1]][PickedPieces[0] - i])
					emty++;			
			}
		}
		else //right 
		{
			for(int i = 1; i <= xx ; i++) //������ ����� Ȯ�� �ݺ��� 
			{
				if(base_board[PickedPieces[1]][PickedPieces[0] + i])
					emty++;	
			}
		}
		
		//�̵� �����Ѱ��� ���� �Ǵ� 
		if(!(emty)) // �ƹ��͵� ������ 
		{
			move();
			return 1;
		}
			
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] > 7)))) // �� 
		{
			move();
			return 1;
		}
		
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
		{
			move();
			return 1;
		}
				
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //�� 
		{
			move();
			return 1;
		}
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // ��
		{
			move();
			return 1;
		}			
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}
}

int Knight(void) // ����Ʈ �Լ� 
{
	int emty = 0; //�̵��� ��ġ������ �⹰���� Ȯ���� ���� ����  
	
	gotoxy(50,27);
	printf("   ");
	
	float yy = 0; //���� ����Ʈ ��ġ�� �̵��� ��ġ�� �Ÿ����� y ����  
	float xx = 0; //���� ����Ʈ ��ġ�� �̵��� ��ġ�� �Ÿ����� x ���� 
	
	yy = abs(Next.save_y - PickedPieces[1]); //���� ����Ʈ ��ġ�� �̵��� ��ġ�� �Ÿ����� x
	xx = abs(Next.save_x - PickedPieces[0]); //���� ����Ʈ ��ġ�� �̵��� ��ġ�� �Ÿ����� y
	
	gotoxy(50,25);								//��� üũ��  
	printf("                             ");
	gotoxy(50,25);
	printf("yy : %2.f xx : %2.f", yy, xx);
	
	if(yy == 2 && xx == 1 || yy == 1 && xx == 2)
	{
		if((turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7) || !(base_board[Next.save_y][Next.save_x]))		// ��� �ϋ� ����ְų� �������� �ش��ϴ� �⹰���� �Ǵ� ���� 
		{
			move();
			return 1;
		}
					
		else if((turn % 2 == 1 && base_board[Next.save_y][Next.save_x] < 7) || !(base_board[Next.save_y][Next.save_x]))	// ������ �ϋ� ����ְų� ����� �ش��ϴ� �⹰���� �Ǵ� ���� 
		{
			move();
			return 1;
		}
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}
}

int Bishop(void) // ��� �Լ� 
{
	int emty = 0; //�̵��� ��ġ������ �⹰���� Ȯ���� ���� ����  
	int cntline = 0;
	
	gotoxy(50,27);
	printf("   ");
	
	//���⸦ ���� �밢�� �̵� 
	
	float yy = 0; //���� ��� ��ġ�� �̵��� ��ġ�� �Ÿ����� y ����  
	float xx = 0; //���� ��� ��ġ�� �̵��� ��ġ�� �Ÿ����� x ���� 
	
	yy = abs(Next.save_y - PickedPieces[1]); //���� ��� ��ġ�� �̵��� ��ġ�� �Ÿ����� x
	xx = abs(Next.save_x - PickedPieces[0]); //���� ��� ��ġ�� �̵��� ��ġ�� �Ÿ����� y
	
	gotoxy(50,25);								//��� üũ��  
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
				for(int i = 1; i <= yy ; i++) //���� �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //������ �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			
			//�̵� �����Ѱ��� ���� �Ǵ� 
			if(!(emty)) // �ƹ��͵� ������ 
			{
				move();
				return 1;
			}
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // ��
			{
				move();
				return 1;
			}
			
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //��
			{
				move();
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //�� 
			{
				move();
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // ��
			{
				move(); 
				return 1;
			}
		}
		else // up
		{
			if(Next.save_x < PickedPieces[0]) //left
			{
				for(int i = 1; i <= yy ; i++) //���� �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //������ �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;
				}
			}
			
			//�̵� �����Ѱ��� ���� �Ǵ�
			if(!(emty)) // �ƹ��͵� ������ 
			{
				move(); 
				return 1;
			}
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // �� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //�� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // ��
			{
				move(); 
				return 1;
			}
		}
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}

	cntline = 0;
}

int Queen(void) // �� �Լ� 
{
	
	// ���� �������� ���� �� ��ģ�Ͱ� ����. 
	
	int emty = 0; //�̵��� ��ġ������ �⹰���� Ȯ���� ���� ����  
	
	int cntline = 0; 
	//���⸦ ���� �밢�� �̵� 
	
	float yy = 0; //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� y ����  
	float xx = 0; //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� x ���� 
	
	yy = abs(Next.save_y - PickedPieces[1]); //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� x
	xx = abs(Next.save_x - PickedPieces[0]); //���� �� ��ġ�� �̵��� ��ġ�� �Ÿ����� y
	
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
				for(int i = 1; i <= yy ; i++) //���� �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //������ �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] + i][j])
						emty++;
				}
			}
			
			//�̵� �����Ѱ��� ���� �Ǵ� 
			if(!(emty)) // �ƹ��͵� ������ 
			{
				move(); 
				return 1;
			}
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // �� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //�� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // ��
			{
				move(); 
				return 1;
			}
		}
		else // up
		{
			if(Next.save_x < PickedPieces[0]) //left
			{
				for(int i = 1; i <= yy ; i++) //���� �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] - cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;
				}
			}
			else //right 
			{
				for(int i = 1; i <= yy ; i++) //������ �� �밢�� ����� Ȯ�� �ݺ��� 
				{
					cntline++;
					int j = PickedPieces[0] + cntline;
					
					if(base_board[PickedPieces[1] - i][j])
						emty++;		
				}
			}
			
			//�̵� �����Ѱ��� ���� �Ǵ�
			if(!(emty)) // �ƹ��͵� ������ 
			{
				move(); 
				return 1;
			}
			
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) // �� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //�� 
			{
				move(); 
				return 1;
			}
				
			else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // ��
			{
				move(); 
				return 1;
			}
		}
	}
	else if(Next.save_x == PickedPieces[0]) // up down 
	{
		
		if(Next.save_y < PickedPieces[1]) //up
		{
			for(int i = 1; i <= yy; i++) //�� ����� Ȯ�� �ݺ���
			{
				if(base_board[PickedPieces[1] - i][PickedPieces[0]])
					emty++;
			}
		}
		else //down
		{
			for(int i = 1; i <= yy ; i++) //�� ����� Ȯ�� �ݺ��� 
			{
				if(base_board[PickedPieces[1] + i][PickedPieces[0]])
					emty++;
			}
		}
		
		//�̵� �����Ѱ��� ���� �Ǵ� 
		if(!(emty)) // �ƹ��͵� ������ 
		{
			move();
			return 1;
		}
		
		else if(emty == 1 && ((xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // �� 
		{
			move();
			return 1;
		}
		
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
		{
			move();
			return 1;
		}
		
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7))) // �� 
		{
			move();
			return 1;
		}
		
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
		{
			move();
			return 1;
		}
	}
	
	else if(Next.save_y == PickedPieces[1]) // left right
	{
		if(Next.save_x < PickedPieces[0]) //left
		{
			for(int i = 1; i <= xx ; i++) //���� ����� Ȯ�� �ݺ��� 
			{				
				if(base_board[PickedPieces[1]][PickedPieces[0] - i])
					emty++;			
			}
		}
		else //right 
		{
			for(int i = 1; i <= xx ; i++) //������ ����� Ȯ�� �ݺ��� 
			{
				if(base_board[PickedPieces[1]][PickedPieces[0] + i])
					emty++;	
			}
		}
		
		//�̵� �����Ѱ��� ���� �Ǵ� 
		if(!(emty)) // �ƹ��͵� ������ 
		{
			move();
			return 1;
		}
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] > 7)))) // �� 
		{
			move();
			return 1;
		}
			
		else if(emty == 1 && (xx == 1 && yy == 1 && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) //�� 
		{
			move();
			return 1;
		}
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 0 && (base_board[Next.save_y][Next.save_x] > 7)))) //�� 
		{
			move();
			return 1;
		}
			
		else if(emty == 1 && (!(xx == 1 && yy == 1) && (turn % 2 == 1 && (base_board[Next.save_y][Next.save_x] < 7 && base_board[Next.save_y][Next.save_x] >= 1)))) // ��
		{
			move();
			return 1;
		}
	}
	else
	{
		gotoxy(50,26);
		printf("                      ");
	}
}

int King(void) // ŷ �Լ� 
{
	int emty = 0; //�̵��� ��ġ������ �⹰���� Ȯ���� ���� ����  
	
	float yy = 0; //���� ŷ ��ġ�� �̵��� ��ġ�� �Ÿ����� y ����  
	float xx = 0; //���� ŷ ��ġ�� �̵��� ��ġ�� �Ÿ����� x ���� 
	
	yy = abs(Next.save_y - PickedPieces[1]); //���� ŷ ��ġ�� �̵��� ��ġ�� �Ÿ����� x
	xx = abs(Next.save_x - PickedPieces[0]); //���� ŷ ��ġ�� �̵��� ��ġ�� �Ÿ����� y
	
	if((yy == 1 && xx == 1) || ((yy == 1 && xx == 0) || (yy == 0 && xx == 1)))
	{
		if((turn % 2 == 0 && base_board[Next.save_y][Next.save_x] > 7) || !(base_board[Next.save_y][Next.save_x])) //�� �⹰�� ��� 
		{
			move();
			Wking_x = Next.save_x;
			Wking_y = Next.save_y;
			gotoxy(0,24);
	        printf("                ");
			gotoxy(0,24);
	        printf("W King %d %d", Wking_y, Wking_x);
	        return 1;
		}
			
					
		else if((turn % 2 == 1 && base_board[Next.save_y][Next.save_x] < 7) || !(base_board[Next.save_y][Next.save_x])) //���� �⹰�� ��� 
		{
			move();
			Bking_x = Next.save_x;
			Bking_y = Next.save_y;
			gotoxy(0,23);
	        printf("                ");
			gotoxy(0,23);
	        printf("B King %d %d", Bking_y, Bking_x);
	        return 1;
		}
	}
}

void Selected_Pieces(int xx, int yy) // �⹰ ���� �� �ش� �⹰�� �Լ��� �̾��ִ� �Լ� 
{
	gotoxy(0, (y_max * 2) + 6);
	printf("                ");
	gotoxy(0, (y_max * 2) + 6);
	switch(base_board[yy][xx])
	{	
		case 1:
		case 11:	//11�̳� 12�� �ִ� ������ �������� ����� ���� �ϱ� ���ؼ��̴�. 
			
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

int Selected_Pieces_chk(int xx, int yy) //�׽�Ʈ 
{
	gotoxy(0, (y_max * 2) + 6);
	printf("                ");
	gotoxy(0, (y_max * 2) + 6);
	switch(base_board[yy][xx])
	{	
		case 1:
		case 11:
			
			printf("1 pawn\n");
			if(Pawn())
				return 1;
			break;
		
		case 2:
		case 12:
			printf("2 rock\n");
			if(Rook())
				return 1;
			break;
		
		case 3:
		case 13:
			printf("3 knight\n");
			if(Knight())
				return 1;
			break;
		
		case 4:
		case 14:				
			printf("4 bishop\n");
			if(Bishop())
				return 1;
			break;
		
		case 5:
		case 15:	
			printf("5 queen\n");
			if(Queen())
				return 1;
			break;
			
		case 6:
		case 16:	
			printf("6 king\n");
			if(King())
				return 1;
			break;		
	}
}

void control(void) // ����Ű ���� �Լ� 
{
	char c;
	c = KeyControl(); // Move the chessboard and select pieces
	switch (c) {
	    case LEFT:	// LEFT 75�� ���� �Ͽ� ����Ͽ��� ���� ����Ű�� Ư���� ��ȣ�� 2���� ���� ������ ���� ���ڸ��� ���� ����Ѵ�. 
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

void ChessPieces(void) // �ش� ��ġ�� �ִ� �⹰ ǥ�� �Լ� 
{
	gotoxy(0, (y_max * 2) + 6);
	printf("                ");
	gotoxy(0, (y_max * 2) + 6);
	switch(base_board[y][x])
	{	
		case 1:
		case 11:			//11�̳� 12�� �ִ� ������ �������� ����� ���� �ϱ� ���ؼ��̴�. 
			
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

int KeyControl() // ����Ű�� WASD���� �� Ű �Է� �Լ� 
{
	char input = getch();	//Because getchar uses a buffer, getch is used, and it is not displayed like getchar and getche.
							//getchar�� ���۸� ����ϱ� ������ getch�� ����ϸ� getchar, getcheó�� ǥ�õ��� �ʴ´�.
	if(input == ' ' || input == '\r')	// Confirm the input of the space bar, and since getch comes in \r after enter, put \r to check if enter is entered 
		return Select;					// �����̽����� �Է��� Ȯ���� ���� getch�� enter �ڿ� \r�� �����Ƿ� enter�� �ԷµǾ����� Ȯ���ϱ� ���� \r�� �Է��Ѵ�.
	else if((input == 'A' || input == 'a') || input == LEFT) // �빮�� �ҹ��� ����Ű�� �̵� ���� �ϵ��� �ִ� �����̸� 
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
 
int Rules(void) // ��Ģ ǥ�� �Լ� 
{
	printf("\t\tGame Rules\n\n\n");
	printf("Use the arrow keys and W, A, S, D to move.\n");
	
	printf("Press enter to exit to menu\n");
	
	while(1) // ���� �Է� ������ ȭ�� ǥ�� 
	{
		if(getch() == Select)
			break;
	}
	
	return 0;	
} 
 
void title(void) // �޴� ȭ�� ǥ�� �Լ� 
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

int draw_show() // ���ºν� �ߴ� ȭ�� ��� �Լ� 
{
	printf("																		");
	printf("					______                        						");
	printf("					|  _  \                       						");
	printf("					| | | | _ __   __ _ __      __						");
	printf("					| | | || '__| / _` |\ \ /\ / /						");
	printf("					| |/ / | |   | (_| | \ V  V / 						");
	printf("					|___/  |_|    \__,_|  \_/\_/  						");
	printf("                              											");
                              
	return 0;
}
 
int MenuDraw() // �޴����� �� ǥ�� �� ���� �Լ� 
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

void EraseOutline(void) // üũ���忡�� ������ �� �� ���� ��ġ�� ���� ������ ����� 
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

int BoardControl(int x, int y) //�׽�Ʈ �� 
{
	if(x != 1) // Coordinate outline currently being taken
	{
		gotoxy(arrX - 2, arrY); // 9
		printf("��");
	
		gotoxy(arrX - 2, arrY - 1);// 11
		printf("��");
		
		gotoxy(arrX - 2, arrY + 1); // 8
		printf("��");
	}
	
	gotoxy(arrX, arrY - 1); // 12
	printf("��");

	gotoxy(arrX, arrY + 1); // 6
	printf("��");
	
	if(x != 8)
	{
		gotoxy(arrX + 2, arrY - 1); //2
		printf("��");
		
		gotoxy(arrX + 2, arrY); // 3
		printf("��");
		
		gotoxy(arrX + 2, arrY + 1); // 4
		printf("��");
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
					printf("��");
					
					gotoxy(arrX - 2, arrY + i - 1);// 11
					printf("��");
					
					gotoxy(arrX - 2, arrY + i + 1); // 8
					printf("��");
				}
				
				gotoxy(arrX, arrY + i - 1); // 12
				printf("��");
				
				gotoxy(arrX, arrY + i + 1); // 6
				printf("��");
				
				if(x != 8)
				{
					gotoxy(arrX + 2, arrY + i - 1); //2
					printf("��");
					
					gotoxy(arrX + 2, arrY + i); // 3
					printf("��");
					
					gotoxy(arrX + 2, arrY + i + 1); // 4
					printf("��");
				}
			}
		}
	}
	
	Erase.save_x = arrX;
	Erase.save_y = arrY;
}

int BoardControl1(void) // üũ���忡�� ������ �� ���� ������ ǥ�� �Լ� 
{
    // A 1 == xy 2 2

	EraseOutline();

    if(x != 0) // Coordinate outline currently being taken
	{
		gotoxy(arrX - 2, arrY); // 9
		printf("��");
		
		gotoxy(arrX - 2, arrY - 1);// 11
		printf("��");
		
		gotoxy(arrX - 2, arrY + 1); // 8
		printf("��");
	}
	
	gotoxy(arrX, arrY - 1); // 12
	printf("��");
	
	gotoxy(arrX, arrY + 1); // 6
	printf("��");
	
	if(x != 7)
	{
		gotoxy(arrX + 2, arrY - 1); //2
		printf("��");
		
		gotoxy(arrX + 2, arrY); // 3
		printf("��");
		
		gotoxy(arrX + 2, arrY + 1); // 4
		printf("��");
	}
	
	Erase.save_x = arrX;
	Erase.save_y = arrY;
}
  
int winloss_check() // üũ �Լ� �׽�Ʈ 
{
	if(Black_Pieces.total <= 3 && White_Pieces.total <= 3)
	{
		system("cls");
		draw_show();
		return 1;
	}
	else
	{
		return 0;
	}
}
  
int Game()
{	
	Pieces_Set();

	while(1)
	{
		if(winloss_check())
			return 0;
		
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
								Bking_y = i;
								Bking_x = j;
								gotoxy(0,23);
						        printf("                ");
								gotoxy(0,23);
						        printf("B King %d %d", Bking_y, Bking_x);
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
								Wking_y = i;
								Wking_x = j;
								gotoxy(0,24);
						        printf("                ");
								gotoxy(0,24);
						        printf("W King %d %d", Wking_y, Wking_x);
								break;	
						}
					}
	    		}
	    		else
	    		{
					if(blackWhite[i][j] == 'X')	 
	    				printf("��");
	    			else
	    				printf("��");
				}
	    			
	    		k += 4;
	    	}
	    	k = 2;
	    	l += 2;
		}
		
		gotoxy(36,0);	
		printf("ó������ ���� �� X : %d Y : %d data = %d", PickedPieces[1], PickedPieces[0], base_board[PickedPieces[1]][PickedPieces[0]]);
		gotoxy(36,2);	
		printf("���������� ���� �� X : %d Y : %d data = %d", Next.save_y, Next.save_x, base_board[Next.save_y][Next.save_x]);
		
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

					if(cnt)//�⹰ -> �⹰ 
					{
						if(PickedPieces[0] == x && PickedPieces[1] == y)
						{
							cnt--;
							gotoxy(36,6);
							printf("                                  ");
							gotoxy(36,6);
							printf("���� ���");
						}
						else
						{
							gotoxy(0,23);
							printf("                                   ");
							gotoxy(0,23);
							printf("������ �⹰�� �����ϼ̽��ϴ�.");
							Where_To_Go();	
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
							printf("��� �⹰�� ������ �ֽʽÿ�.");
						}
						else if(turn % 2 == 1 && base_board[y][x] <= 6) 
						{
							gotoxy(36,6);
							printf(" 							 ");
							gotoxy(36,6);
							printf("��� �⹰�� ������ �ֽʽÿ�.");
						}
						else
						{
							PickedPieces[0] = x;
							PickedPieces[1] = y;
							cnt++;
							gotoxy(36,6);
							printf("                                  ");
							gotoxy(36,6);
							printf("ù��° ����");
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
						printf("�ι�° ����");
						Where_To_Go();
					}
					else
					{
						gotoxy(36,11);
						printf("                               ");
						cnt = 0;
						gotoxy(0,23);
						printf("�⹰�� ������ �ּ���. pick the pieces");
					}

				}
		    	break; 
		}
	}
} 
 
void CursorView() //Ŀ�� ���ֱ� // ��α׿��� ������ 
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
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

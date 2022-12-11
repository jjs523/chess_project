#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>


#define LEFT 75 //방향키는 특수문자라 값이 두개가 입력되며 첫번째 수는 방향키 모두 224를 먼저 반환한다 그 후 들어오는 값 으로 방향키 판별 75,77,80,72
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

int xy_save(int x, int y) //이전에 가리키고있던 좌표 
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
    //x, y 좌표 설정
    COORD pos = { x,y };
    //커서 이동
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
			printf("1 pawn 폰\n");
			// Pawn();
			break;
			
		case 2:
			printf("2 rock 룩\n");
			break;
		
		case 3:
			printf("3 knight 나이트\n");
			break;
		
		case 4:				
			printf("4 bishop 비숍\n");
			break;
		
		case 5:	
			printf("5 queen 퀸\n");
			break;
			
		case 6:	
			printf("6 king 킹\n");
			break;		
	}
}

int KeyControl()
{
	char input = getch(); //getchar은 버퍼를 사용하기에 getch를 사용 또한 getchar, getche처럼 화면표시하지 않음 
	
	if(input == ' ' || input == '\r') // 스페이스바 입력 확인과 getch는 엔터 후 \r이 들어오기에 \r을 넣어 확인 
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
void vovoid(void) //메모 저장  
{
		
	/*
	typedef struct Node
	{
	    int board[8][8] = {
	    {2,3,4,5,6,4,3,2},
	    {1,1,1,1,1,1,1,1},
	    {0,0,0,0,0,0,0,0},
	    {0,0,0,0,0,0,0,0},
	    {0,0,0,0,0,0,0,0},
	    {0,0,0,0,0,0,0,0},
	    {1,1,1,1,1,1,1,1},
	    {2,3,4,5,6,4,3,2}
	};
	    struct Node *next;
	}Node;
	
	typedef struct Queue
	{
	    Node *front;
	    Node *rear;
	    int count;
	}Queue;
	
	void InitQueue(Queue*queue);
	int IsEmpty(Queue*queue);
	void Enqueue(Queue*queue, int data);
	int Dequeue(Queue*queue);
	void InitQueue(Queue*queue){
	    queue -> front = queue -> rear = NULL;
	    queue -> count = 0;
	}
	
	int IsEmpty(Queue*queue)
	{
	    return !queue -> count;
	}
	
	void Enqueue(Queue*queue, int data)
	{
	    Node *now = (Node*)malloc(sizeof(Node));
	    now -> data = data;
	    now -> next = NULL;
	
	    if(IsEmpty(queue))
	    {
	        queue -> front = now;
	    }
	
	    else
	    {
	        queue -> rear -> next = now;
	
	    }
	
	    queue -> rear = now;
	    queue -> count++;
	}
	
	int Dequeue(Queue*queue)
	{
	    int re = 0;
	    Node *now;
	
	    if(IsEmpty(queue))
	    {
	        printf("Queue is empty.\n");
	        return re;
	    }
	
	    now = queue -> front;
	    re = now -> data;
	    queue -> front = now -> next;
	    printf("(%d) is dequeued.\n", re);
	    free(now);
	    queue -> count--;
	    return re;
	}
	 */
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 /*
	int select = 0;
	int num = 0;
	int cnt = 0;
	Queue queue;
	InitQueue(&queue);
	
	while(1)
	{
	    printf("Select menu [(1) enqueue (2) dequeue (3) exit program] : ");
	    scanf("%d", &select);
	
	    switch(select)
	    {
	        case 1:
	            printf("Input number : ");
	            scanf("%d", &num);
	            if(queue.count == 5)
	                printf("Queue is full. (%d) is not enqueued.\n", num);
	            else
	                Enqueue(&queue, num);
	            break;
	
	        case 2:
	            for(int j = 0; j < 1; j++)
	                Dequeue(&queue);
	            break;
	
	        case 3:
	            cnt++;
	            break;
	
	    }
	    if(cnt)
	        break;
	}
	*/
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
	printf("■■Chess Game■■\n");
	
	
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
	for(int i = 0; i <= 4; i++) // 이전에 찍고 있는 좌표 윤곽선 삭제 
	{
		if(x != 1)
		{
			gotoxy(save_x - i, save_y); // 9시 
			printf(" ");
			
			gotoxy(save_x - i, save_y - 1);// 11시 
			printf(" ");
			
			gotoxy(save_x - i, save_y + 1); // 8시 
			printf(" ");
		}
		
		gotoxy(save_x, save_y - 1); // 12시 
		printf(" ");
		
		gotoxy(save_x + i, save_y + 1); // 6시 
		printf(" ");
		
		if(x != 8)
		{
			gotoxy(save_x + i, save_y - 1); //2시 
			printf(" ");
			
			gotoxy(save_x + i, save_y); // 3시 
			printf(" ");
			
			gotoxy(save_x, save_y + 1); // 5시 
			printf(" ");
		}
	}
}

int BoardControl(int x, int y)
{
	// A 1 == xy 2 2
	
	if(x != 1) // 현재에 찍고 있는 좌표 윤곽선
	{
		gotoxy(arrX - 2, arrY); // 9시 
		printf("■");
		
		gotoxy(arrX - 2, arrY - 1);// 11시 
		printf("■");
		
		gotoxy(arrX - 2, arrY + 1); // 8시 
		printf("■");
	}
	
	gotoxy(arrX, arrY - 1); // 12시 
	printf("■");
	
	gotoxy(arrX, arrY + 1); // 6시 
	printf("■");
	
	if(x != 8)
	{
		gotoxy(arrX + 2, arrY - 1); //2시 
		printf("■");
		
		gotoxy(arrX + 2, arrY); // 3시 
		printf("■");
		
		gotoxy(arrX + 2, arrY + 1); // 4시 
		printf("■");
	}
	
	if(base_board[y - 1][x - 1] == pawn && cnt)
	{
		if(y == 2 || y == 7)
		{
			for(int i = 0; i <= 4; i += 2)	
			{
				if(x != 1) // 현재에 찍고 있는 좌표 윤곽선
				{
					gotoxy(arrX - 2, arrY + i); // 9시 
					printf("■");
					
					gotoxy(arrX - 2, arrY + i - 1);// 11시 
					printf("■");
					
					gotoxy(arrX - 2, arrY + i + 1); // 8시 
					printf("■");
				}
				
				gotoxy(arrX, arrY + i - 1); // 12시 
				printf("■");
				
				gotoxy(arrX, arrY + i + 1); // 6시 
				printf("■");
				
				if(x != 8)
				{
					gotoxy(arrX + 2, arrY + i - 1); //2시 
					printf("■");
					
					gotoxy(arrX + 2, arrY + i); // 3시 
					printf("■");
					
					gotoxy(arrX + 2, arrY + i + 1); // 4시 
					printf("■");
				}
			}
		}
	}
	
	xy_save(arrX, arrY);
}

int BoardControl1(void)
{
    // A 1 == xy 2 2

    for(int i = 0; i <= 4; i++) // 이전에 찍고 있는 좌표 윤곽선 삭제
    {
        if(x != 1)
        {
            gotoxy(save_x - i, save_y); // 9시
            printf(" ");

            gotoxy(save_x - i, save_y - 1);// 11시
            printf(" ");

            gotoxy(save_x - i, save_y + 1); // 8시
            printf(" ");
        }

        gotoxy(save_x, save_y - 1); // 12시
        printf(" ");

        gotoxy(save_x + i, save_y + 1); // 6시
        printf(" ");

        if(x != 8)
        {
            gotoxy(save_x + i, save_y - 1); //2시
            printf(" ");

            gotoxy(save_x + i, save_y); // 3시
            printf(" ");

            gotoxy(save_x, save_y + 1); // 5시
            printf(" ");
        }
    }

    if(x != 1) // 현재에 찍고 있는 좌표 윤곽선
	{
		gotoxy(arrX - 2, arrY); // 9시 
		printf("■");
		
		gotoxy(arrX - 2, arrY - 1);// 11시 
		printf("■");
		
		gotoxy(arrX - 2, arrY + 1); // 8시 
		printf("■");
	}
	
	gotoxy(arrX, arrY - 1); // 12시 
	printf("■");
	
	gotoxy(arrX, arrY + 1); // 6시 
	printf("■");
	
	if(x != 8)
	{
		gotoxy(arrX + 2, arrY - 1); //2시 
		printf("■");
		
		gotoxy(arrX + 2, arrY); // 3시 
		printf("■");
		
		gotoxy(arrX + 2, arrY + 1); // 4시 
		printf("■");
	}

    xy_save(arrX, arrY);
}
  
void Game(void)
{		
	while(1) {
		
		/*
		gotoxy(0, y_max + 2);
		printf("%20d 초 \n", clock() / 1000);
		Sleep(1000);*/ //시간 
		
		gotoxy(0, 0); //gotoxy test
		printf("J");
		
		int k = 2;
		int l = 2;
		
		char c;
		
		for(int i = 0; i < 6; i++)
		{
			gotoxy(36, i);
			
		}
		
		
		
		gotoxy(0, (y_max * 2) + 3);
		printf("현재 좌표 : %c%d\n", 64 + x, 9 - y); // 체스보드 좌표 
		
		ChessPieces(); // 기물확인 함수 
		
		gotoxy(0,21);
		printf("실제 배열 좌표 : %d %d", x, y); //실제 배열 좌표 
		
		//EraseOutline();
		//BoardControl(arrX, arrY); //현재 위치한 타일 윤곽선
		BoardControl1();

		gotoxy(0,22);
        printf("      "); // 실제 배열 좌표
		gotoxy(0,22);
        printf("%d %d", arrX, arrY); // 실제 배열 좌표
		
		for(int i = 1; i <= 8; i++) // 바깥좌표 표시 
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
		
		for(int i = 0; i <= 31; i++) // 체스보드 외곽선 
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
		
		for(int i = 0; i < 8; i++) //체스보드 및 체스기물 
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
		
        c = KeyControl(); // 체스보드 기물 선택 
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
            case Select: // 선택 
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
					printf("pick the gimul");
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

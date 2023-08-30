#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

//��ʼ���׳�
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

//��ӡ�׳�
void DisplayBoard(char board[ROWS][COLS], int row, int col) 
{
	printf("-------------------ɨ��----------------------\n");
	for (int j = 0; j <= col; j++)
	{
		printf("%d ", j);
	}
		printf("\n");
	for (int i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (int j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------------------------\n");
}

//����
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		//��������׵�����
		int x = rand() % row + 1;//1~9
		int y = rand() % col + 1;//1~9

		if (board[x][y] == '0') {
			board[x][y]='1';
			count--;
		}
	}
}
//�����
void MarkMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("����������Ҫ���λ�õ�����->");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)    //�жϸ������Ƿ�Ϸ�
		{
			if (board[x][y] == '*')        //�жϸ������Ƿ��Ų�
			{
				board[x][y] = '!';
				break;
			}
			else
			{
				printf("��λ�ò��ܱ���ǣ�����������!\n");
			}
		}
		else
		{
			printf("�����������������!\n");
		}
	}
}


//��¼�׵ĸ���
int get_mine_count(char board[ROWS][COLS],int x,int y)
{
	//ͳ�Ƹ�������Χ���׸���
	int sum = 0;
	for (int i = x-1; i <=x+1; i++)
	{
		for (int j = y-1; j <=y+1; j++)
		{
			if (board[i][j]=='1')
			{
				sum++;
			}
			
		}
	}
		return (sum);
	//����Ӧ������ʾ��ֵ��count;
//----------------------------------------------
	//ͨ�������ַ���ʾ�ף���'1'�������ף�'1'=49,'0'=48��ͳ�Ʒ�Χ�ڵ������ַ����ܺ� - ����*'0'= �׵ĸ���
	/*return (  board[x-1][y]
			+ board[x - 1][y - 1]
			+ board[x][y - 1]
			+ board[x + 1][y - 1]
			+ board[x + 1][y]
			+ board[x + 1][y + 1]
			+ board[x][y + 1]
			+ board[x - 1][y + 1]- 8*'0');*/
	//����Ӧ������ʾ��ֵ��count + '0';
			
}
//�ݹ鱬ըʽչ��һƬ
void ExplosionSpread(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y, int* pw)
{
	if (x >= 1 && x <= row && y >= 1 && y <= col)  //�ж������Ƿ�Ϊ�Ų鷶Χ��
	{
		int num = get_mine_count(mine, x, y);   //��ȡ������Χ�׵ĸ���
		if (num == 0)
		{
			(*pw)++;
			show[x][y] = ' ';   //�����������Χû���ף��ͰѸ������óɿո񣬲�����Χ�˸�����չ��
			int i = 0;
			int j = 0;
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (show[i][j] == '*')    //���Ƶݹ���������ֹ�Ѿ��Ų���������ٴεݹ飬�Ӷ�������ݹ�
						ExplosionSpread(mine, show, row, col, i, j, pw);
				}
			}
		}
		else
		{
			(*pw)++;
			show[x][y] = num + '0';
		}
	}
}

//����
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	char mark = 0;//���ڽ����Ƿ���Ҫ�����

	int win = 0;////��������Ƿ�ȡ��ʤ��
	int *pw = &win;

	while (1)
	{
		printf("�������Ų������:");
		scanf("%d%d", &x, &y);
		if (x>=1 && x<=row && y>=1 && y<=col)
		{
			if (mine[x][y]=='1')
			{
				printf("���ź��㱻ը����\n");
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else
			{
				if (show[x][y]!='*')
				{
					printf("�������ѱ��Ų飬����������!\n");
					continue;  //ֱ�ӽ�����һ��ѭ��
				}
				else
				{
					ExplosionSpread(mine, show, row, col, x, y, pw);  //��ըչ��һƬ
					system("cls");  //�����Ļ
					DisplayBoard(show, ROW, COL);  //��ӡ����


					printf("��Ҫ����׵�λ��������y/Y,�����밴�����->");
					while ((mark = getchar()) != '\n');  //��������

					scanf("%c", &mark);
					if (mark == 'Y' || mark == 'y')
					{
						MarkMine(show, row, col);   //�����
						system("cls");
						DisplayBoard(show, row, col);
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			printf("�Ƿ����꣬����������\n");
		}
	}
	//
	int count = get_mine_count(mine, x, y);
	if (win == count)
	{
		system("cls");//�����Ļ
		printf("��ϲ�㣬���׳ɹ�!\n");
		DisplayBoard(show, row, col);
		return;
	}
}
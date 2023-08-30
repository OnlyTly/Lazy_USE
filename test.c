#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu()
{
	printf("****************   һ����ɨ��  ****************\n");
	printf("****************     1.Play    ****************\n");
	printf("****************     0.Exit    ****************\n");
	printf("***********************************************\n");

}

void Game()
{
	char mine[ROWS][COLS] = {0};					//��Ų��õ��� ����'1';
	char show[ROWS][COLS] = { 0 };					//����Ų�����׵���Ϣ����Χ�׵ĸ����������죬�����ʺ�

	//��ʼ�����������Ϊָ��������
	//mine ������û�в����׵�ʱ�� ����'0'
	InitBoard(mine, ROWS, COLS,'0');

	//show ������û�в����׵�ʱ�� ����'*'
	InitBoard(show, ROWS, COLS,'*');

	//��ӡ���׵��׳�
	//DisplayBoard(mine, ROW, COL);

	//����
	SetMine(mine,ROW,COL);
	DisplayBoard(show, ROW, COL);

	//�Ų���
	FindMine(mine,show,ROW,COL);

}

int main()
{
	int inpute = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();//��ӡ�˵�
		printf("��ѡ��:");
		scanf("%d", &inpute);
		switch (inpute)
		{
		case 1:
			Game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�������ѡ��1/0��\n");
			break;
		}
	} while (inpute);
}
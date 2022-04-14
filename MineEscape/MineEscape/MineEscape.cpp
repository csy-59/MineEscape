// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	char gameMap[10][10];
	int gameEscape[2];
	int gamePlayerPosition[2] = { 0, 0 };
	char gameKey;

	// ���� ����, gameEscape ����
	// x��
	srand(time(NULL));
	gameEscape[0] = rand();
	srand(time(NULL));
	gameEscape[0] += rand();
	gameEscape[0] %= 10;

	// y��
	srand(time(NULL));
	gameEscape[1] = rand();
	srand(time(NULL));
	gameEscape[1] += rand();
	gameEscape[1] %= 10;

	// gameEscape = {0, 0} ����
	while (gameEscape[0] == 0 && gameEscape[1] == 0)
	{
		gameEscape[0] = rand();
		gameEscape[0] %= 10;
		gameEscape[1] = rand();
		gameEscape[1] %= 10;
	}

	// gameMap �ʱ�ȭ
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			gameMap[j][i] = '#';
		}
	}

	// Ż������(gameEscape) ǥ��
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	// �÷��̾� ��ġ(gamePlayerPosition) ǥ��
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// �ʱ�ȭ�� ǥ��
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			cout << gameMap[i][j];
		}
		cout << endl;
	}

	// �̵� �� ȭ�� ����
	while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1])
	{
		gameKey = _getch();

		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = '#';
		// ��ҹ��� ������ �ν�
		if (gameKey >= 97 && gameKey <= 122) // ASCII code a = 97, z = 122
		{
			gameKey -= 32;
		}
		bool errPosition = 0;
		
		// �÷��̾� ��ġ ���� (switch��)
		switch (gameKey)
		{
		case 'W':
			gamePlayerPosition[1] -= 1;
			break;
		case 'A':
			gamePlayerPosition[0] -= 1;
			break;
		case 'S':
			gamePlayerPosition[1] += 1;
			break;
		case 'D':
			gamePlayerPosition[0] += 1;
			break;
		default:
			errPosition = 1;
			break;
		}

		// �̵� �Ѱ� (if��)
		if (gamePlayerPosition[0] > 9)
		{
			gamePlayerPosition[0] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[0] < 0)
		{
			gamePlayerPosition[0] += 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] > 9)
		{
			gamePlayerPosition[1] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] < 0)
		{
			gamePlayerPosition[1] += 1;
			errPosition = 1;
		}

		// �÷��̾� ��ġ ���ε�
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// ȭ�� ����
		system("cls");

		// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;

		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}
		// �̵� �Ѱ� ���
		errPosition == 1 ? cout << "�̵� �Ұ�" << endl : cout << gameKey << endl;
	}

	cout << "Ż�⿡ �����߽��ϴ�." << endl;
}
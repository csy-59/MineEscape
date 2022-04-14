// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{	
	//// ���� ���̵� ���� // map // sight
	//int gameLevel[3] = {1, 2, 3};
	//int inputGameLevel;
	//cin >> inputGameLevel;

	char gameMap[20][20]; // map
	int gameEscape[2];
	int gamePlayerPosition[2] = { 1, 1 };
	char gameKey;

	// ���� ����, gameEscape ����
	// x��
	srand(time(NULL));
	gameEscape[0] = rand();
	srand(time(NULL));
	gameEscape[0] += rand();
	gameEscape[0] %= 20; // map

	// y��
	srand(time(NULL));
	gameEscape[1] = rand();
	srand(time(NULL));
	gameEscape[1] += rand();
	gameEscape[1] %= 20; // map

	// gameEscape = {0, 0} ����
	while (gameEscape[0] == 0 || gameEscape[1] == 0 || gameEscape[0] == 19 || gameEscape[1] == 19 || (gameEscape[0] == 1 && gameEscape[1] == 1))
	{
		gameEscape[0] = rand();
		gameEscape[0] %= 20; // map
		gameEscape[1] = rand();
		gameEscape[1] %= 20; // map
	}

	// gameMap �ʱ�ȭ
	for (int j = 0; j < 20; j++) // map
	{
		for (int i = 0; i < 20; i++) // map
		{
			(i == 0 || j == 0 || i == 19 || j == 19) ? gameMap[j][i] = '*' : gameMap[j][i] = '/';
		}
	}

	// Ż������(gameEscape) ����
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	// �÷��̾� ��ġ(gamePlayerPosition) ����
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// �÷��̾� �ʱ� �þ� ����
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
		}
	}

	// �ʱ�ȭ�� ǥ��
	for (int j = 0; j < 20; j++) // map
	{
		for (int i = 0; i < 20; i++) // map
		{
			cout << gameMap[i][j];
		}
		cout << endl;
	}

	// �̵� �� ȭ�� ����
	while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1])
	{
		gameKey = _getch();

		//�ʱ�ȭ
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = ' ';
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == ' ')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = '/';
			}
		}
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
		if (gamePlayerPosition[0] > 18) // map
		{
			gamePlayerPosition[0] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[0] < 1)
		{
			gamePlayerPosition[0] += 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] > 18) // map
		{
			gamePlayerPosition[1] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] < 1) // map
		{
			gamePlayerPosition[1] += 1;
			errPosition = 1;
		}

		// �÷��̾� ��ġ ���ε�
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// �÷��̾� �þ� ���� // sight
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}

		// ȭ�� ����
		system("cls");

		// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;

		for (int j = 0; j < 20; j++) // map
		{
			for (int i = 0; i < 20; i++) // map
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
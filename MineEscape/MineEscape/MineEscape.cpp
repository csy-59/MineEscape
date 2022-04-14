// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{	
	
	int inputMapLevel, inputSightLevel;
	cin >> inputMapLevel >> inputSightLevel;
	int gameMapSize;
	char gameMap[42][42] = { ' ' };
	int gameSight;
	int gameEscape[2];
	int gamePlayerPosition[2] = { 1, 1 };
	char gameKey;

	// ���� ���̵� ���� // map // sight
	switch (inputMapLevel)
	{
	case 1:
		gameMapSize = 20; // map
		break;
	case 2:
		gameMapSize = 30; // map
		break;
	case 3:
		gameMapSize = 40; // map
		break;
	}

	switch (inputSightLevel)
	{
	case 1:
		gameSight = 3; // sight
		break;
	case 2:
		gameSight = 2; // sight
		break;
	case 3:
		gameSight = 1; // sight
		break;
	}

	//// ���� ����, gameEscape ����
	//// x��
	//srand(time(NULL));
	//gameEscape[0] = rand();
	//srand(time(NULL));
	//gameEscape[0] += rand();
	//gameEscape[0] %= gameMapSize; // map

	//// y��
	//srand(time(NULL));
	//gameEscape[1] = rand();
	//srand(time(NULL));
	//gameEscape[1] += rand();
	//gameEscape[1] %= gameMapSize; // map

	//// gameEscape = {0, 0} ����
	//while (gameEscape[0] == 0 || gameEscape[1] == 0 || gameEscape[0] == 19 || gameEscape[1] == 19 || (gameEscape[0] == 1 && gameEscape[1] == 1))
	//{
	//	gameEscape[0] = rand();
	//	gameEscape[0] %= gameMapSize; // map
	//	gameEscape[1] = rand();
	//	gameEscape[1] %= gameMapSize; // map
	//}

	//Ż�� ��ġ ����
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		srand(time(NULL));
		gameEscape[1] = rand() % gameMapSize + 1;
	} while (gameEscape[0] == 1 && gameEscape[1] == 1);

	// gameMap �ʱ�ȭ
	for (int j = 0; j < gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < gameMapSize + 2; i++) // map
		{
			(i == 0 || j == 0 || i == gameMapSize + 1 || j == gameMapSize + 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '/'; // map
		}
	}

	// Ż������(gameEscape) ����
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	// �÷��̾� ��ġ(gamePlayerPosition) ����
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// �÷��̾� �ʱ� �þ� ����
	for (int i = -1 * gameSight; i < gameSight + 1; i++) {				// sight
		for (int j = -1 * gameSight; j < gameSight + 1; j++) {			// sight
			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
		}
	}

	// �̵� �� ȭ�� ���� 
	do
	{
		// ȭ�� ǥ��
		for (int j = 0; j < gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}
		gameKey = _getch();
		// �ʱ�ȭ
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = ' ';
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {								// sight
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {							// sight
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == ' ')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = '/';
			}
		}
		// ��ҹ��� ������ �ν�
		if (gameKey >= 97 && gameKey <= 122) // ASCII code a = 97, z = 122
		{
			gameKey -= 32;
		}
		bool errPosition = 0; // �̵��Ұ� ���� ǥ�ÿ�
		
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
		if (gamePlayerPosition[0] > gameMapSize) // map
		{
			gamePlayerPosition[0] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[0] < 1)
		{
			gamePlayerPosition[0] += 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] > gameMapSize) // map
		{
			gamePlayerPosition[1] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] < 1)
		{
			gamePlayerPosition[1] += 1;
			errPosition = 1;
		}

		// �÷��̾� ��ġ ���ε�
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// �÷��̾� �þ� ���� // sight
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}

		// ȭ�� ����
		system("cls");

		// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;
		// �̵� �Ѱ� ���
		errPosition == 1 ? cout << "�̵� �Ұ�" << endl : cout << gameKey << endl;
	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);

	cout << "Ż�⿡ �����߽��ϴ�." << endl;
}
// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{	
	// ���� ���̵� ���� // map // sight
	int gameLevel[3] = {1, 2, 3};
	int inputGameLevel;
	char gameMap[20][20]{}; // map

	//cin >> inputGameLevel;

	//switch (inputGameLevel)
	//{
	//case 1:
	//	char gameMap[20][20]; // map
	//	int gameMapSize = 20;
	//	int gameSight = 3; // sight
	//	break;
	//case 2:
	//	char gameMap[20][20]; // map
	//	int gameMapSize = 20;
	//	int gameSight = 3; // sight
	//	break;
	//case 3:
	//	char gameMap[20][20]; // map
	//	int gameMapSize = 20;
	//	int gameSight = 3; // sight
	//	break;
	//}

	
	int gameEscape[2];
	int gamePlayerPosition[2] = { 1, 1 };
	char gameKey;
	int stamina = 10; // ����Ƚ�� �߰�
	bool gameOver = false;

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
	while (!gameOver)
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
			--stamina;
			break;
		case 'A':
			gamePlayerPosition[0] -= 1;
			--stamina;

			break;
		case 'S':
			gamePlayerPosition[1] += 1;
			--stamina;

			break;
		case 'D':
			gamePlayerPosition[0] += 1;
			--stamina;

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
		//gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]
		
		//���� ���� �ݺ���
		if (gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] == gameMap[gameEscape[0]][gameEscape[1]])
		{
			gameOver = true;
		}
		// �̵� �Ѱ� ���
		errPosition == 1 ? cout << "�̵� �Ұ�" << endl : cout << gameKey << endl;
		cout << "����Ƚ��" << stamina << endl;
		if (stamina == 0)
		{
			gameOver = true;
			cout << "Ż�⿡ ���� �߽��ϴ�." << endl;
		}
	}
	cout << "��������" << endl;
}
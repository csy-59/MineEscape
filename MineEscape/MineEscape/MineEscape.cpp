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
	int gameItem[2][4];
	int gameItemCount = 4;
	int gamePlayerChance = 20;
	char wellLocation = '#';

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






	//Ż�� ��ġ ����
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		srand(time(NULL));
		gameEscape[1] = rand() % gameMapSize + 1;
	} while (gameEscape[0] == 1 && gameEscape[1] == 1);

	//������ ��ġ ����
	for (int i = 0; i < gameItemCount; i++) {
		do {
			gameItem[0][i] = rand() % gameMapSize + 1;
			gameItem[1][i] = rand() % gameMapSize + 1;
		} while (gameItem[0][i] == 1 && gameItem[1][i] == 1);
	}

	


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

	for (int i = 0; i < gameItemCount; i++) {
		gameMap[gameItem[0][i]][gameItem[1][i]] = 'I';
	}


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

		bool errPosition = 0; // �̵��Ұ� ���� ǥ�ÿ�

		// �÷��̾� ��ġ ���� (switch��)
		switch (gameKey)
		{
		case 'W':
		case 'w':
			gamePlayerPosition[1] -= 1;
			gamePlayerChance--;
			break;
		case 'A':
		case 'a':
			gamePlayerPosition[0] -= 1;
			gamePlayerChance--;
			break;
		case 'S':
		case 's':
			gamePlayerPosition[1] += 1;
			gamePlayerChance--;
			break;
		case 'D':
		case 'd':
			gamePlayerPosition[0] += 1;
			gamePlayerChance--;
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



		// �÷��̾� �þ� ���� // sight
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}
		//�칰 ��ġ ����
		gameMap[gameMapSize/2][gameMapSize/2] = wellLocation;
		// �÷��̾� ��ġ ���ε�
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';
		for (int i = 0; i < gameItemCount; i++)
			if (gamePlayerPosition[0] == gameItem[0][i] && gamePlayerPosition[1] == gameItem[1][i]) {
				gameSight+=2;
			}
		if (gamePlayerPosition[0] == gameMap[gameMapSize / 2][gameMapSize / 2] && gamePlayerPosition[1] == [gameMapSize / 2][gameMapSize / 2]) {
			gamePlayerChance = 20;
		}
		

				// ȭ�� ����
				system("cls");

		// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;
		// �̵� �Ѱ� ���
		errPosition == 1 ? cout << "�̵� �Ұ�" << endl : cout << gameKey << "\t" << gamePlayerChance << endl;
		
	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);

	cout << "Ż�⿡ �����߽��ϴ�." << endl;
}
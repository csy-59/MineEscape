// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{

	char gameMap[42][42] = { '/' }; //��
	int gameMapSize; //�� ũ��
	int gameSight; //�þ� ũ��

	int gameEscape[2];	//�ⱸ ��ġ
	int gamePlayerPosition[2] = { 1, 1 }; //�÷��̾� ��ġ
	char gameKey; //�Է�Ű
	int inputGameLevel; //���̵� �Է�

	int gamesTalactiteCount; //������ ����
	int gamesTalactitePosition[5][2]; //������ ��ġ �迭

	int gameJewelryCount; //���� ����
	int gameJewelryPosition[7][2]; // ���� ��ġ �迭
	int gameJewelryScore[7]; // ���� ��ġ �迭


	// ���� ���̵� ���� // map // sight
	cout << "=================" << endl;
	cout << ">> MINE ESCAPE <<" << endl;
	cout << "=================" << endl;
	do {
		cout << "���̵� �Է�(1~3): ";
		cin >> inputGameLevel;

		switch (inputGameLevel)
		{
		case 1:
			gameMapSize = 20;
			gamesTalactiteCount = 13;
			gameJewelryCount = 5;
			gameSight = 3; // sight
			break;
		case 2:
			gameMapSize = 30;
			gamesTalactiteCount = 20;
			gameJewelryCount = 6;
			gameSight = 3; // sight
			break;
		case 3:
			gameMapSize = 40;
			gamesTalactiteCount = 34;
			gameJewelryCount = 7;
			gameSight = 3; // sight
			break;
		default:
			cout << "�߸��� �Է�" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "�ε���..." << endl;

	// ���� ����, gameEscape(Ż�ⱸ) ����
	//// x��
	//srand(time(NULL));
	//gameEscape[0] = rand();
	//srand(time(NULL));
	//gameEscape[0] += rand();
	//gameEscape[0] %= gameMapSize; // map
	//
	//// y��
	//srand(time(NULL));
	//gameEscape[1] = rand();
	//srand(time(NULL));
	//gameEscape[1] += rand();
	//gameEscape[1] %= 20; // map
	//
	//// gameEscape = {0, 0} ����
	//while (gameEscape[0] == 0 || gameEscape[1] == 0 || gameEscape[0] == 19 || gameEscape[1] == 19 || (gameEscape[0] == 1 && gameEscape[1] == 1))
	//{
	//	gameEscape[0] = rand();
	//	gameEscape[0] %= 20; // map
	//	gameEscape[1] = rand();
	//	gameEscape[1] %= 20; // map
	//}

	//Ż�� ��ġ ����
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		srand(time(NULL));
		gameEscape[1] = rand() % gameMapSize + 1;
	} while (gameEscape[0] == 1 && gameEscape[1] == 1);

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

	// gameMap �ʱ�ȭ
	for (int j = 0; j < gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < gameMapSize + 2; i++) // map
		{
			(i == 0 || j == 0 || i == gameMapSize - 1 || j == gameMapSize - 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '/';
		}
	}

	//������ ��ġ
	for (int i = 0; i < gamesTalactiteCount; i++) {
		do {
			srand(time(NULL));
			gamesTalactitePosition[i][0] = rand() % gameMapSize + 1;
			srand(time(NULL));
			gamesTalactitePosition[i][1] = rand() % gameMapSize + 1;
		} while ((gamesTalactitePosition[i][0] == 1 && gamesTalactitePosition[i][1] == 1) ||
			(gamesTalactitePosition[i][0] == gameEscape[0] && gamesTalactitePosition[i][1] == gameEscape[1]));
		//�������� ��ġ�� �÷��̾�/Ż�� ��ġ/��/�ٸ� ������/�þ� ��ġ�� �ƴ� ��� ���� �Ϸ�.

		//������ �������� �ڸ���� ���������� ����
		gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] = 'T';
	}



	//���� ��ġ

	//ȸ�� �칰 ��ġ

	system("cls");

	do {
		// �ʱ�ȭ�� ǥ��
		for (int j = 0; j < gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}

		gameKey = _getch();

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
		if (gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] == 'T' || errPosition == 1)
			cout << "�̵� �Ұ�" << endl;
		else
			cout << gameKey << endl;


	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);


	// �̵� �� ȭ�� ����
	//while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1])
	//{
	//	gameKey = _getch();
	//
	//	//�ʱ�ȭ
	//	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = ' ';
	//	for (int i = -1; i < 2; i++) {
	//		for (int j = -1; j < 2; j++) {
	//			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == ' ')
	//				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = '/';
	//		}
	//	}
	//	// ��ҹ��� ������ �ν�
	//	if (gameKey >= 97 && gameKey <= 122) // ASCII code a = 97, z = 122
	//	{
	//		gameKey -= 32;
	//	}
	//	bool errPosition = 0;
	//	
	//	// �÷��̾� ��ġ ���� (switch��)
	//	switch (gameKey)
	//	{
	//	case 'W':
	//		gamePlayerPosition[1] -= 1;
	//		break;
	//	case 'A':
	//		gamePlayerPosition[0] -= 1;
	//		break;
	//	case 'S':
	//		gamePlayerPosition[1] += 1;
	//		break;
	//	case 'D':
	//		gamePlayerPosition[0] += 1;
	//		break;
	//	default:
	//		errPosition = 1;
	//		break;
	//	}
	//
	//	// �̵� �Ѱ� (if��)
	//	if (gamePlayerPosition[0] > 18) // map
	//	{
	//		gamePlayerPosition[0] -= 1;
	//		errPosition = 1;
	//	}
	//	else if (gamePlayerPosition[0] < 1)
	//	{
	//		gamePlayerPosition[0] += 1;
	//		errPosition = 1;
	//	}
	//	else if (gamePlayerPosition[1] > 18) // map
	//	{
	//		gamePlayerPosition[1] -= 1;
	//		errPosition = 1;
	//	}
	//	else if (gamePlayerPosition[1] < 1) // map
	//	{
	//		gamePlayerPosition[1] += 1;
	//		errPosition = 1;
	//	}
	//
	//	// �÷��̾� ��ġ ���ε�
	//	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';
	//
	//	// �÷��̾� �þ� ���� // sight
	//	for (int i = -1; i < 2; i++) {
	//		for (int j = -1; j < 2; j++) {
	//			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
	//				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
	//		}
	//	}
	//
	//	// ȭ�� ����
	//	system("cls");
	//
	//	// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;
	//
	//	for (int j = 0; j < 20; j++) // map
	//	{
	//		for (int i = 0; i < 20; i++) // map
	//		{
	//			cout << gameMap[i][j];
	//		}
	//		cout << endl;
	//	}
	//
	//	// �̵� �Ѱ� ���
	//	if (gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] == 'T' || errPosition == 1)
	//		cout << "�̵� �Ұ�" << endl;
	//	else
	//		cout << gameKey << endl;
	//}

	cout << "Ż�⿡ �����߽��ϴ�." << endl;
}
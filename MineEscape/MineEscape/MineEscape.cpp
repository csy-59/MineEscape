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

	int gameJewelryBasicSocre[3] = { 100,200,300 };//���� �⺻ ����(���⼭ �������� ����)

	int score = 0;
	int walk = 0;

	
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
			gamesTalactiteCount = 4;
			gameJewelryCount = 5;
			gameSight = 5; // sight
			break;
		case 2:
			gameMapSize = 30;
			gamesTalactiteCount = 5;
			gameJewelryCount = 6;
			gameSight = 4; // sight
			break;
		case 3:
			gameMapSize = 40;
			gamesTalactiteCount = 7;
			gameJewelryCount = 7;
			gameSight = 3; // sight
			break;
		default:
			cout << "�߸��� �Է�" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "�ε���..." << endl;

	// gameMap �ʱ�ȭ
	for (int j = 0; j < gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < gameMapSize + 2; i++) // map
		{
			(i == 0 || j == 0 || i == gameMapSize + 1 || j == gameMapSize + 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '/'; // map
		}
	}


	// �÷��̾� ��ġ(gamePlayerPosition) ����
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// �÷��̾� �þ� ���� // sight
	for (int i = -1 * gameSight; i < gameSight + 1; i++) {
		for (int j = -1 * gameSight; j < gameSight + 1; j++) {
			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
		}
	}

	//Ż�� ��ġ ����
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		gameEscape[1] = rand() % gameMapSize + 1;
	} while (gameEscape[0] == 1 && gameEscape[1] == 1);

	// Ż������(gameEscape) ����
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	//������ ��ġ
	for (int i = 0; i < gamesTalactiteCount;i++) {
		bool isStalactitePossible = true;
		do {
			isStalactitePossible = true;
			srand(time(NULL));
			gamesTalactitePosition[i][0] = rand() % gameMapSize + 1;
			gamesTalactitePosition[i][1] = rand() % gameMapSize + 1;

			//�÷��̾� �ʱ���ġ �Ǻ�
			if ((gamesTalactitePosition[i][0] == 1 && gamesTalactitePosition[i][1] == 1))
				isStalactitePossible = false;

			//Ż�� ��ġ �Ǻ�
			if (gamesTalactitePosition[i][1] == gameEscape[1] && gamesTalactitePosition[i][0] == gameEscape[0])
				isStalactitePossible = false;

			for (int j = 0;j < i;j++) {
				if (gamesTalactitePosition[j][0] == gamesTalactitePosition[i][0] &&
					gamesTalactitePosition[j][1] == gamesTalactitePosition[i][1]) {
					//���� ������ ��ġ�� ��ģ�ٸ�
					isStalactitePossible = false;
					break;
				}
			}
		} while (!isStalactitePossible);
		//�������� ��ġ�� �÷��̾�/Ż�� ��ġ/��/�ٸ� ������/�þ� ��ġ�� �ƴ� ��� ���� �Ϸ�.

		//������ �������� �ڸ���� ���������� ����
		gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] = 'T';
	}

	//���� ��ġ
	for (int i = 0; i < gameJewelryCount;i++) {
		
		bool isJewelryPossible = true;
		
		do {
			isJewelryPossible = true;

			srand(time(NULL));
			gameJewelryPosition[i][0] = rand() % gameMapSize + 1;
			gameJewelryPosition[i][1] = rand() % gameMapSize + 1;

			if ((gameJewelryPosition[i][0] == 1 && gameJewelryPosition[i][1] == 1))
				isJewelryPossible = false;

			if ((gameJewelryPosition[i][1] == gameEscape[1] && gameJewelryPosition[i][0] == gameEscape[0]))
				isJewelryPossible = false;

			for (int j = 0;j < gamesTalactiteCount;j++) {
				if (gameJewelryPosition[i][0] == gamesTalactitePosition[j][0] &&
					gameJewelryPosition[i][1] == gamesTalactitePosition[j][1]) {
					//���� ������ ��ġ�� ��ģ�ٸ�
					isJewelryPossible = false;
					break;
				}
			}

			for (int j = 0;j < i;j++) {
				if (gameJewelryPosition[j][0] == gameJewelryPosition[i][0] &&
					gameJewelryPosition[j][1] == gameJewelryPosition[i][1]) {
					//���� ���� ��ġ�� ��ģ�ٸ�
					isJewelryPossible = false;
					break;
				}
			}
		} while (!isJewelryPossible);
		//������ ��ġ�� �÷��̾�/Ż�� ��ġ/��/�ٸ� ������/�þ� ��ġ�� �ƴ� ��� ���� �Ϸ�.

		//������ ������ �ڸ���� �������� ����
		gameMap[gameJewelryPosition[i][0]][gameJewelryPosition[i][1]] = 'J';

		//���� ���� ����
		srand(time(NULL));
		gameJewelryScore[i] = gameJewelryBasicSocre[rand() % 3];

	}

	//ȸ�� �칰 ��ġ


	system("cls");
	// �̵� �� ȭ�� ���� 
	do
	{
	//cout << gameEscape[0] << " " << gameEscape[1] << endl;
	//cout << gamePlayerPosition[0] << " " << gamePlayerPosition[1] << endl;
		// ȭ�� ǥ��
		for (int j = 0; j < gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}

		//�ϴ� ���ھ�, ���׹̳� ǥ��
		cout << "score: " << score << endl;
		cout << "walk: " << walk << endl;

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
			//��
			errPosition = gamePlayerPosition[1] <= 1;
			
			if (!errPosition) {
				//������ ����
				for (int j = 0;j < gamesTalactiteCount;j++) {
					if ((gamePlayerPosition[1] - 1) == gamesTalactitePosition[j][1] &&
						gamePlayerPosition[0] == gamesTalactitePosition[j][0]) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				gamePlayerPosition[1] -= 1;
				walk++;
			}
			break;
		case 'A':
		case 'a':
			//��
			errPosition = gamePlayerPosition[0] <= 1;

			if (!errPosition) {
				//������ ����
				for (int j = 0;j < gamesTalactiteCount;j++) {
					if (gamePlayerPosition[1] == gamesTalactitePosition[j][1] &&
						(gamePlayerPosition[0] - 1) == gamesTalactitePosition[j][0]) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				gamePlayerPosition[0] -= 1;
				walk++;
			}
			break;
		case 'S':
		case 's':
			//��
			errPosition = gamePlayerPosition[1] >= gameMapSize;

			if (!errPosition) {
				//������ ����
				for (int j = 0;j < gamesTalactiteCount;j++) {
					if ((gamePlayerPosition[1] + 1) == gamesTalactitePosition[j][1] &&
						gamePlayerPosition[0] == gamesTalactitePosition[j][0]) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}
			if (!errPosition) {
				gamePlayerPosition[1] += 1;
				walk++;
			}
			break;
		case 'D':
		case 'd':
			//��
			errPosition = gamePlayerPosition[0] >= gameMapSize;

			if (!errPosition) {
				//������ ����
				for (int j = 0;j < gamesTalactiteCount;j++) {
					if (gamePlayerPosition[1] == gamesTalactitePosition[j][1] &&
						(gamePlayerPosition[0] + 1) == gamesTalactitePosition[j][0]) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				gamePlayerPosition[0] += 1;
				walk++;
			}
			break;
		default:
			errPosition = 1;
			break;
		}

		//���� ���� ����
		for (int j = 0;j < gameJewelryCount;j++) {
			if (gamePlayerPosition[1] == gameJewelryPosition[j][1] &&
				gamePlayerPosition[0] == gameJewelryPosition[j][0]) {
				//���� ���� ��ġ�� ��ģ�ٸ� ������ ���� ȹ��
				score += gameJewelryScore[j];
				break;
			}
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

	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);


	cout << "Ż�⿡ �����߽��ϴ�." << endl;
}
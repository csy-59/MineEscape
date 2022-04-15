// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
using namespace std;

//ȭ�� ǥ���ϴ� ��� �Ŵ���
struct printManual {
	char border = '*';		//â ���
	char plain = ' ';		//�׳� ��
	char mist = '=';		//�Ⱥ��̴� ��
	char player = 'O';		//�÷��̾�
	char exit = 'E';		//�ⱸ
	char well = '#';		//ȸ���� �칰
	char stalactite = 'T';	//������
	char jewelry = 'J';		//����
	char item = 'F';		//������(�÷���)
} manual;

//�� Ÿ���� Ÿ��
struct tileTypeInfo {
	int x = -1, y = -1;
	char print = manual.plain;
	int score = 0;
} plain;

//Ÿ�� ����(ǥ�õǴ� ������ �ش� Ÿ���� ����)
struct tileInfo {
	char print = manual.plain;
	tileTypeInfo type = plain;
};

//�������� ���� ���
struct mapInfo {
	int gameMapSize = 0;		//�� ũ��
	int gameStalactiteCount = 0;//������ ��
	int gameJewelryCount = 0;	//���� ��
	int gameItemCount = 0;		//������ ��
	int plusStamina = 0;		//�߰��Ǵ� ���׹̳�(������ ���� �ٸ�)
	int maxStamina = 0;			//�ش� ���� �ִ� ���׹̳� ��

};

//�÷��̾� ����
struct player {
	tileTypeInfo tile = { 0,0,manual.player,-1 };
	int stamina = 0; //���׹̳�
	int score = 0; //���� ����
	int walk = 0; //���� ������ ��
	int sight = 3; //�þ�
};

int main()
{

	//char gameMap[49][49] = { '/' }; //�� // �� �ִ� ������ +2 (��輱) +7 (level3������ �迭 �����÷ο� ������)
	//int gameMapSize; //�� ũ��
	//int gameSight = 3; //�þ� ũ��
	//int gameEscapePosition[2];	//�ⱸ ��ġ // { x, y }
	//int gamePlayerPosition[2] = { 1, 1 }; //�÷��̾� ��ġ // { x, y }
	//char gameKey; //�Է�Ű
	//int inputGameLevel; //���̵� �Է�
	//int gamesTalactiteCount; //������ ����
	//int gamesTalactitePosition[10][2]; //������ ��ġ �迭 // { x, y }
	//int gameJewelryCount; //���� ����
	//int gameJewelryPosition[10][2]; // ���� ��ġ �迭 // { x, y }
	//int gameJewelryScore[10]; // ���� ����
	//int gameItemPosition[6][2];	//������ ��ġ �迭 // { x, y }
	//int gameItemCount = 6; //������ ����
	//char well = '#';
	//int gamePlayerChance;
	//int wellLocation[2];
	//int gameJewelryBasicSocre[3] = { 100,200,300 };//���� �⺻ ����(���⼭ �������� ����)
	//bool gameClear = 1;
	//int score = 0;
	//int walk = 0;
	//int setPosition[30][2] = { { 0, 0 } }; // �ߺ����� �ʴ� ���� ��ǥ�� ����ϱ� ���� ���߹迭 // { x, y }
	//int plusStamina = 0; // ���׹̳� ���̵� ����

	mapInfo mapInfo;
	tileInfo gameMap[42][42];//��
	tileTypeInfo stalactiteInfo[20];//������
	tileTypeInfo jewelryInfo[25]; //����
	tileTypeInfo itemInfo[6]; //������
	tileTypeInfo exit;// �ⱸ
	tileTypeInfo well;// �칰
	tileTypeInfo border = { -1,-1,manual.border,0 }; //���

	player player; // �÷��̾�

	char gameKey; //�Է�Ű
	int inputGameLevel; //���̵� �Է�

	int gameJewelryBasicSocre[3] = { 100,200,300 };//���� �⺻ ����(���⼭ �������� ����)
	int setPosition[30][2] = { { 0, 0 } }; // �ߺ����� �ʴ� ���� ��ǥ�� ����ϱ� ���� ���߹迭 // { x, y }
	//���� Ŭ���� ����
	bool gameClear = true;

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
			mapInfo.gameMapSize = 20;
			mapInfo.gameStalactiteCount = 4;
			mapInfo.gameJewelryCount = 5;
			mapInfo.gameItemCount = 1;
			mapInfo.plusStamina = 7;
			break;
		case 2:
			mapInfo.gameMapSize = 30;
			mapInfo.gameStalactiteCount = 7;
			mapInfo.gameJewelryCount = 7;
			mapInfo.gameItemCount = 2;
			mapInfo.plusStamina = 12;
			break;
		case 3:
			mapInfo.gameMapSize = 40;
			mapInfo.gameStalactiteCount = 10;
			mapInfo.gameJewelryCount = 10;
			mapInfo.gameItemCount = 6;
			mapInfo.plusStamina = 22;
			break;
		default:
			cout << "�߸��� �Է�" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "�ε���..." << endl;
	srand(time(NULL));

	// ���� ��ǥ 20�� ����
	for (int j = 0; j < 30; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			do {
				setPosition[j][0] = rand() % (mapInfo.gameMapSize - 1) + 2;
				setPosition[j][1] = rand() % (mapInfo.gameMapSize - 1) + 2;
			} while (j != i && (setPosition[j][0] == setPosition[i][0] && setPosition[j][1] == setPosition[i][1])); //�ߺ� üũ
		}
	}

	//�칰 ��ġ ����
	for (int i = 0; i < 30; i++)	// �칰�� ��� ����(3*3��� ����)�� ������ �� ��ġ
	{
		if (setPosition[i][0] > mapInfo.gameMapSize / 3 && setPosition[i][0] < 2 * mapInfo.gameMapSize / 3 &&
			setPosition[i][1] > mapInfo.gameMapSize / 3 && setPosition[i][1] < 2 * mapInfo.gameMapSize / 3)
		{
			well.x = setPosition[i][0];
			well.y = setPosition[i][1];
			well.print = manual.well;
			well.score = 0;
			for (int j = i; j < 19; j++)
			{
				setPosition[j][0] = setPosition[j + 1][0];
				setPosition[j][1] = setPosition[j + 1][1];
			}
			setPosition[29][0] = 0;
			setPosition[29][1] = 0;
			break;
		}
		else if (i == 29)
		{
			well.x = setPosition[i][0];
			well.y = setPosition[i][1];
			well.print = manual.well;
			well.score = 0;

		}
	}
	//map�� ǥ��
	gameMap[well.x][well.y].type = well;
	gameMap[well.x][well.y].print = well.print;
	mapInfo.maxStamina = well.x + well.y + mapInfo.plusStamina;

	//Ż�� ��ġ ����
	exit.x = setPosition[0][0];
	exit.y = setPosition[0][1];
	exit.print = manual.exit;
	exit.score = 0;
	gameMap[exit.x][exit.y].type = exit;
	gameMap[exit.x][exit.y].print = exit.print;

	//������, ����, ������ ��ġ ����
	for (int i = 1; i < 1 + mapInfo.gameStalactiteCount + mapInfo.gameJewelryCount + mapInfo.gameItemCount; i++)	// ������ǥ�� �� ��ҿ� ���� (gameEscapePosition, gamesTalactitePosition, gameJewelryPosition, gameItemPosition)
	{
		//������
		if (i <= mapInfo.gameStalactiteCount)
		{
			stalactiteInfo[i - 1].x = setPosition[i][0];
			stalactiteInfo[i - 1].y = setPosition[i][1];
			stalactiteInfo[i - 1].print = manual.stalactite;
			stalactiteInfo[i - 1].score = 0;
			gameMap[stalactiteInfo[i - 1].x][stalactiteInfo[i - 1].y].type = stalactiteInfo[i - 1];
			gameMap[stalactiteInfo[i - 1].x][stalactiteInfo[i - 1].y].print = stalactiteInfo[i - 1].print;
		}
		//����
		else if (i <= mapInfo.gameStalactiteCount + mapInfo.gameJewelryCount)
		{
			int position = i - (mapInfo.gameStalactiteCount + 1);
			jewelryInfo[position].x = setPosition[i][0];
			jewelryInfo[position].y = setPosition[i][1];
			jewelryInfo[position].print = manual.jewelry;
			//���� ���� ����
			jewelryInfo[position].score = gameJewelryBasicSocre[rand() % 3];
			gameMap[jewelryInfo[position].x][jewelryInfo[position].y].type = jewelryInfo[position];
			gameMap[jewelryInfo[position].x][jewelryInfo[position].y].print = jewelryInfo[position].print;
		}
		//������
		else if (i <= mapInfo.gameStalactiteCount + mapInfo.gameJewelryCount + mapInfo.gameItemCount)
		{
			int position = i - mapInfo.gameStalactiteCount + mapInfo.gameJewelryCount + 1;
			itemInfo[position].x = setPosition[i][0];
			itemInfo[position].y = setPosition[i][1];
			itemInfo[position].print = manual.item;
			itemInfo[position].score = 0;
			gameMap[itemInfo[position].x][itemInfo[position].y].type = itemInfo[position];
			gameMap[itemInfo[position].x][itemInfo[position].y].print = itemInfo[position].print;
		}
	}

	//�÷��̾� �ʱ� �ڸ� ����
	player.tile.x = 1;
	player.tile.y = 1;
	player.tile.print = manual.player;
	player.stamina = mapInfo.maxStamina;
	player.score = 0;
	player.walk = 0;

	// �ּ� �̵��Ÿ�
	mapInfo.maxStamina = (well.x + well.y) + mapInfo.plusStamina;

	//�ʱ� ȭ��

	// gameMap �ʱ�ȭ
	for (int j = 0; j < mapInfo.gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < mapInfo.gameMapSize + 2; i++) // map
		{
			//���
			if (i == 0 || j == 0 || i == mapInfo.gameMapSize + 1 || j == mapInfo.gameMapSize + 1) {
				gameMap[i][j].print = manual.border;
				gameMap[i][j].type = border;
			}
			//�׳� ��
			else
				gameMap[i][j].print = manual.mist;
			//gameMap[i][j].print = gameMap[i][j].type.print;

		}
	}

	// �÷��̾� �þ� ���� // sight
	for (int i = -1 * player.sight; i < player.sight + 1; i++) {
		for (int j = -1 * player.sight; j < player.sight + 1; j++) {
			gameMap[player.tile.x + i][player.tile.y + j].print = gameMap[player.tile.x + i][player.tile.y + j].type.print;
		}
	}

	// �÷��̾� ��ġ ���ε�
	gameMap[player.tile.x][player.tile.y].print = player.tile.print;

	// �̵� �� ȭ�� ���� 
	system("cls");
	do
	{
		// ȭ�� ǥ��
		for (int j = 0; j < mapInfo.gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < mapInfo.gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j].print;
			}
			cout << endl;
		}

		//�ϴ� ���ھ�, ���׹̳� ǥ��
		cout << "stamina: " << player.stamina << endl;
		cout << "score: " << player.score << endl;
		cout << "walk: " << player.walk << endl;

		gameKey = _getch();

		bool errPosition = 0; // �̵��Ұ� ���� ǥ�ÿ�

		// �÷��̾� ��ġ ���� (switch��)
		switch (gameKey)
		{
		case 'W':
		case 'w':
			//��
			errPosition = player.tile.y <= 1;

			//������ ����
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if (player.tile.x == stalactiteInfo[j].x && (player.tile.y - 1) == stalactiteInfo[j].y) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//�÷��̾� ����
				player.tile.y--;
				player.stamina--;
				player.walk++;
			}
			break;
		case 'A':
		case 'a':
			//��
			errPosition = player.tile.x <= 1;

			//������ ����
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if ((player.tile.x - 1) == stalactiteInfo[j].x && player.tile.y == stalactiteInfo[j].y) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//�÷��̾� ����
				player.tile.x--;
				player.stamina--;
				player.walk++;
			}
			break;
		case 'S':
		case 's':
			//��
			errPosition = player.tile.y >= mapInfo.gameMapSize;

			//������ ����
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if (player.tile.x == stalactiteInfo[j].x && (player.tile.y + 1) == stalactiteInfo[j].y) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//�÷��̾� ����
				player.tile.y++;
				player.stamina--;
				player.walk++;
			}
			break;
		case 'D':
		case 'd':
			//��
			errPosition = player.tile.x >= mapInfo.gameMapSize;

			//������ ����
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if ((player.tile.x + 1) == stalactiteInfo[j].x && player.tile.y == stalactiteInfo[j].y) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//�÷��̾� ����
				player.tile.x++;
				player.stamina--;
				player.walk++;
			}
			break;
		default:
			errPosition = 1;
			break;
		}

		//����, ������, �칰 ���� ó���� ���� ����
		char temp = gameMap[player.tile.x][player.tile.y].type.print;

		//���� ���� ����
		if (temp == manual.jewelry) {
			player.score += gameMap[player.tile.x][player.tile.y].type.score;
			gameMap[player.tile.x][player.tile.y].type = plain;
		}

		//������ ȹ��(�þ� Ȯ��)
		if (temp == manual.item) {
			player.sight++;
			gameMap[player.tile.x][player.tile.y].type = plain;
		}

		//�칰 ����(���׹̳� ȸ��)
		if (temp == manual.well) {
			player.stamina = mapInfo.maxStamina;
		}


		// gameMap �ʱ�ȭ
		for (int j = 0; j < mapInfo.gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < mapInfo.gameMapSize + 2; i++) // map
			{
				//���
				if (i == 0 || j == 0 || i == mapInfo.gameMapSize + 1 || j == mapInfo.gameMapSize + 1)
					gameMap[i][j].print = manual.border;
				//�׳� ��
				else
					gameMap[i][j].print = manual.mist;
				//gameMap[i][j].print = gameMap[i][j].type.print;

			}
		}


		// �÷��̾� �þ� ���� // sight
		for (int i = -1 * player.sight; i < player.sight + 1; i++) {
			for (int j = -1 * player.sight; j < player.sight + 1; j++) {
				gameMap[player.tile.x + i][player.tile.y + j].print = gameMap[player.tile.x + i][player.tile.y + j].type.print;
			}
		}

		// �÷��̾� ��ġ ���ε�
		gameMap[player.tile.x][player.tile.y].print = player.tile.print;

		// �̵� �Ѱ� ���
		//errPosition == 1 ? cout << "�̵� �Ұ�" << endl : cout << gameKey << "\t" << gamePlayerChance << endl;

		if (player.stamina == 0) // ���׹̳� 0 �Ǹ� ���� ����
		{
			gameClear = 0;
			break;
		}

		// ȭ�� ����
		system("cls");

	} while (player.tile.x != exit.x || player.tile.y != exit.y);

	system("cls");
	cout << "====================" << endl;
	gameClear ? cout << "Ż�⿡ �����߽��ϴ�." << endl : cout << "Ż�⿡ �����߽��ϴ�." << endl;
	cout << "score: " << player.score << endl;
	cout << "walk: " << player.walk << endl;
	cout << "====================" << endl;
}
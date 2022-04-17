#include <iostream>
#include <conio.h>
using namespace std;

struct Position // { x, y }��ǥ
{
	int x;
	int y;
}setPosition[50];
// �ⱸ, �÷��̾�, ������, ����, ������, �칰, ���� ��ǥ

struct ShowManual
{
	char player = { 'O' };
	char dark = { '=' };
	char boundary = { '*' };
	char escape = { 'E' };
	char well = { '#' };
	char flat = { ' ' };
	char forest = { '^' };
	char swamp = { '~' };
	char stalactite = { 'T' };
	char jewelry = { 'J' };
	char item = { 'F' };
}showManual;

struct Player // �÷��̾� ���� ������ ����ü
{
	Position position = { 1, 1 };	// ��ġ
	int stamina = 0;	// �̵� ��ȸ
	int score = 0;	// ȹ�� ����
	int walk = 0;	// �̵� Ƚ��
	int sight = 3;	// �þ� ����
}player;

struct Tile	// ��ġ�� ������Ʈ ����ü
{
	Position position;	// ��ġ
	char show;	// ���
	int score;	// ����
}flat = { {0,0}, showManual.flat, 0 };

struct GameMap	// ���� ���� ǥ�� �� �Ӽ� ���� 
{
	char show = showManual.flat;	// ǥ�� ���
	Tile tile = flat;	// �Ӽ�
};

struct LevelInfo
{
	int mapSize = 0;		//�� ũ��
	int stalactiteCount = 0;//������ ��
	int jewelryCount = 0;	//���� ��
	int itemCount = 0;		//������ ��
	int forestCount = 10;	//�� Ÿ�� ��
	int swampCount = 10;	//�� Ÿ�� ��
	//int plusStamina = 0;		//�߰��Ǵ� ���׹̳�(������ ���� �ٸ�)
	int maxStamina = 0;			//�ش� ���� �ִ� ���׹̳� ��
	int staminaDecrease[3] = { -1, -2, -3 }; // �Ƿε�
}level;

int main()
{
	// ����ü ���� �� �ʱ�ȭ
	GameMap gameMap[49][49] = { showManual.flat, flat }; // �� ��ü // �� �ִ� ������ +2 (��輱) +7 (level3������ �迭 �����÷ο� ������)
	Tile stalactite[10];	// ������
	for (int i = 0; i < 10; i++)
	{
		stalactite[i] = { {0,0}, showManual.stalactite, 0 };
	} // ������ �ʱ�ȭ
	Tile jewelry[10] = { {0,0}, showManual.jewelry, 0 }; // ����
	for (int i = 0; i < 10; i++)
	{
		jewelry[i] = { {0,0}, showManual.jewelry, 0 };
	} // ���� �ʱ�ȭ
	Tile item[10] = { {0,0}, showManual.item, 0 }; // ������
	for (int i = 0; i < 10; i++)
	{
		item[i] = { {0,0}, showManual.item, 0 };
	} // ������ �ʱ�ȭ
	Tile forest[10] = { {0,0}, showManual.forest, 0 }; // ��
	for (int i = 0; i < 10; i++)
	{
		forest[i] = { {0,0}, showManual.forest, 0 };
	} // �� �ʱ�ȭ
	Tile swamp[10] = { {0,0}, showManual.swamp, 0 }; // ��
	for (int i = 0; i < 10; i++)
	{
		swamp[i] = { {0,0}, showManual.swamp, 0 };
	} // �� �ʱ�ȭ
	// Tile flat = { 0 }; // ����
	Tile well = { {0,0}, showManual.well, 0 }; // �칰
	Tile escape = { {0,0}, showManual.escape, 0 }; // �ⱸ
	Tile dark = { {0,0}, showManual.dark, 0 }; // ����
	Tile boundary = { {0,0}, showManual.boundary, 0 }; // ���

	//char gameMap[49][49]; //�� // �� �ִ� ������ +2 (��輱) +7 (level3������ �迭 �����÷ο� ������)
	char gameKey; //�Է�Ű
	int inputGameLevel; //���̵� �Է�

	int gameJewelryBasicSocre[3] = { 100,200,300 };//���� �⺻ ����(���⼭ �������� ����)
	bool gameClear = 1;

	// int plusStamina = 0; // ���׹̳� ���̵� ����

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
			level.mapSize = 20;
			level.stalactiteCount = 4;
			level.jewelryCount = 5;
			//player.sight = 5; // sight
			level.itemCount = 1;
			// level.plusStamina = 7;
			break;
		case 2:
			level.mapSize = 30;
			level.stalactiteCount = 7;
			level.jewelryCount = 7;
			//player.sight = 4; // sight
			level.itemCount = 2;
			// level.plusStamina = 12;
			break;
		case 3:
			level.mapSize = 40;
			level.stalactiteCount = 10;
			level.jewelryCount = 10;
			//player.sight = 3; // sight
			level.itemCount = 6;
			// level.plusStamina = 22;
			break;
		default:
			cout << "�߸��� �Է�" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "�ε���..." << endl;
	srand(time(NULL));
	// ���� ��ǥ 50�� ����
	for (int j = 0; j < 50; j++)
	{
		for (int i = 0; i < 50; i++)
		{
			do {
				setPosition[j].x = rand() % level.mapSize + 1;
				setPosition[j].y = rand() % level.mapSize + 1;
			} while (j != i && (setPosition[j].x == setPosition[i].x && setPosition[j].y == setPosition[i].y));
		}
	}

	for (int i = 0; i < 50; i++)	// �칰�� ��� ����(3*3��� ����)�� ������ �� ��ġ
	{
		if (setPosition[i].x > level.mapSize / 3 && setPosition[i].x < 2 * level.mapSize / 3 &&
			setPosition[i].y > level.mapSize / 3 && setPosition[i].y < 2 * level.mapSize / 3)
		{
			well.position.x = setPosition[i].x;
			well.position.y = setPosition[i].y;
			for (int j = i; j < 49; j++)
			{
				setPosition[j].x = setPosition[j + 1].x;
				setPosition[j].y = setPosition[j + 1].y;
			}
			setPosition[49].x = 0;
			setPosition[49].y = 0;
			break;
		}
		else if (i == 49)
		{
			well.position.x = setPosition[i].x;
			well.position.y = setPosition[i].y;
		}
	}
	// gameMap�� ����
	gameMap[well.position.x][well.position.y].tile = well;
	gameMap[well.position.x][well.position.y].show = well.show;

	for (int i = 0; i < 1 + level.stalactiteCount + level.jewelryCount + level.itemCount
		+ level.forestCount + level.swampCount; i++)	// ������ǥ�� �� ��ҿ� ���� (gameEscapePosition, sTalactite.position, jewelry.position, item.position)
	{
		if (i == 0)
		{
			escape.position.x = setPosition[0].x;
			escape.position.y = setPosition[0].y;
			gameMap[escape.position.x][escape.position.y].tile = escape;
			gameMap[escape.position.x][escape.position.y].show = escape.show;
			// gameMap[escape.position[0].x][escape.position[0].y] = typeManual.escape;
		}
		else if (i >= 1 && i <= level.stalactiteCount)
		{
			stalactite[i - 1].position.x = setPosition[i].x;
			stalactite[i - 1].position.y = setPosition[i].y;
			gameMap[stalactite[i - 1].position.x][stalactite[i - 1].position.y].tile = stalactite[i - 1];
			gameMap[stalactite[i - 1].position.x][stalactite[i - 1].position.y].show = stalactite[i - 1].show;
		}
		else if (i > level.stalactiteCount && i <= level.stalactiteCount + level.jewelryCount)
		{
			int I = i - (level.stalactiteCount + 1);
			jewelry[I].position.x = setPosition[i].x;
			jewelry[I].position.y = setPosition[i].y;
			//���� ���� ����
			jewelry[I].score = gameJewelryBasicSocre[rand() % 3];
			gameMap[jewelry[I].position.x][jewelry[I].position.y].tile = jewelry[I];
			gameMap[jewelry[I].position.x][jewelry[I].position.y].show = jewelry[I].show;
		}
		else if (i > level.stalactiteCount + level.jewelryCount && i <= level.stalactiteCount + level.jewelryCount + level.itemCount)
		{
			int I = i - (level.stalactiteCount + level.jewelryCount + 1);
			item[I].position.x = setPosition[i].x;
			item[I].position.y = setPosition[i].y;
			gameMap[item[I].position.x][item[I].position.y].tile = item[I];
			gameMap[item[I].position.x][item[I].position.y].show = item[I].show;
		}
		else if (i > level.stalactiteCount + level.jewelryCount + level.itemCount && i <= level.stalactiteCount + level.jewelryCount + level.itemCount + level.forestCount)
		{
			int I = i - (level.stalactiteCount + level.jewelryCount + level.itemCount + 1);
			forest[I].position.x = setPosition[i].x;
			forest[I].position.y = setPosition[i].y;
			gameMap[forest[I].position.x][forest[I].position.y].tile = forest[I];
			gameMap[forest[I].position.x][forest[I].position.y].show = forest[I].show;
		}
		else if (i > level.stalactiteCount + level.jewelryCount + level.itemCount + level.forestCount && i <= level.stalactiteCount + level.jewelryCount + level.itemCount + level.forestCount + level.swampCount)
		{
			int I = i - (level.stalactiteCount + level.jewelryCount + level.itemCount + level.forestCount + 1);
			swamp[I].position.x = setPosition[i].x;
			swamp[I].position.y = setPosition[i].y;
			gameMap[swamp[I].position.x][swamp[I].position.y].tile = swamp[I];
			gameMap[swamp[I].position.x][swamp[I].position.y].show = swamp[I].show;
		}
	}

	// �ּ� �̵��Ÿ�
	// player.stamina = (well.x + well.y) + plusStamina;
	// �ʱ� (�ִ�) ���׹̳� ����
	player.stamina = 2 * level.mapSize;
	level.maxStamina = 2 * level.mapSize;

	//�ʱ� ȭ��

	//// gameMap �ʱ�ȭ
	//for (int j = 0; j < level.mapSize + 2; j++) // map
	//{
	//	for (int i = 0; i < level.mapSize + 2; i++) // map
	//	{
	//		if (i == 0 || j == 0 || i == level.mapSize + 1 || j == level.mapSize + 1)
	//		{
	//			gameMap[j][i].show = showManual.boundary;
	//			gameMap[j][i].tile = boundary;
	//		}
	//		else
	//			gameMap[j][i].show = showManual.dark; // map
	//	}
	//}

	//// �÷��̾� ��ġ ���ε�
	//gameMap[player.position.x][player.position.y].show = showManual.player;

	// �÷��̾� �þ� ���� // sight
	for (int i = -1 * player.sight; i < player.sight + 1; i++) {
		for (int j = -1 * player.sight; j < player.sight + 1; j++) {
			gameMap[player.position.x + i][player.position.y + j].show = gameMap[player.position.x + i][player.position.y + j].tile.show;
		}
	}

	////�칰 ��ġ ����
	//if (gameMap[well.position.x][well.position.y].show == showManual.flat)
	//	gameMap[well.position.x][well.position.y].show = showManual.well;
	//// Ż������(gameEscape) ����
	//if (gameMap[escape.position.x][escape.position.y].show == showManual.flat)
	//	gameMap[escape.position.x][escape.position.y].show = showManual.escape;
	////������ ����
	//for (int i = 0; i < level.stalactiteCount; i++) {
	//	if (gameMap[stalactite[i].position.x][stalactite[i].position.y].show == showManual.flat)
	//		gameMap[stalactite[i].position.x][stalactite[i].position.y].show = showManual.stalactite;
	//}
	////���� ����
	//for (int i = 0; i < level.jewelryCount; i++) {
	//	if (gameMap[jewelry[i].position.x][jewelry[i].position.y].show == showManual.flat)
	//		gameMap[jewelry[i].position.x][jewelry[i].position.y].show = showManual.jewelry;
	//}
	////������ ����
	//for (int i = 0; i < level.itemCount; i++) {
	//	if (gameMap[item[i].position.x][item[i].position.y].show == showManual.flat)
	//		gameMap[item[i].position.x][item[i].position.y].show = showManual.item;
	//}
	////�� ����
	//for (int i = 0; i < level.forestCount; i++) {
	//	if (gameMap[forest[i].position.x][forest[i].position.y].show == showManual.flat)
	//		gameMap[forest[i].position.x][forest[i].position.y].show = showManual.forest;
	//}
	////�� ����
	//for (int i = 0; i < level.swampCount; i++) {
	//	if (gameMap[swamp[i].position.x][swamp[i].position.y].show == showManual.flat)
	//		gameMap[swamp[i].position.x][swamp[i].position.y].show = showManual.swamp;
	//}

	// �̵� �� ȭ�� ���� 
	system("cls");
	do
	{
		// gameMap �ʱ�ȭ
		for (int j = 0; j < level.mapSize + 2; j++) // map
		{
			for (int i = 0; i < level.mapSize + 2; i++) // map
			{
				if (i == 0 || j == 0 || i == level.mapSize + 1 || j == level.mapSize + 1)
				{
					gameMap[i][j].show = boundary.show;
					gameMap[i][j].tile = boundary;
				}
				else
					gameMap[i][j].show = dark.show; // map
			}
		}

		// �÷��̾� �þ� ���� // sight
		for (int i = -1 * player.sight; i < player.sight + 1; i++) {
			for (int j = -1 * player.sight; j < player.sight + 1; j++) {
				gameMap[player.position.x + i][player.position.y + j].show = gameMap[player.position.x + i][player.position.y + j].tile.show;
			}
		}

		// �÷��̾� ��ġ ���ε�
		gameMap[player.position.x][player.position.y].show = showManual.player;

		// ȭ�� ǥ��
		for (int j = 0; j < level.mapSize + 2; j++) // map
		{
			for (int i = 0; i < level.mapSize + 2; i++) // map
			{
				cout << gameMap[i][j].show;
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
			errPosition = player.position.y <= 1;

			if (!errPosition) {
				//������ ����
				for (int j = 0; j < level.stalactiteCount; j++) {
					if ((player.position.y - 1) == stalactite[j].position.y &&
						player.position.x == stalactite[j].position.x) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				player.position.y -= 1;
				player.stamina += level.staminaDecrease[0]; // �÷��̾� ���׹̳� ���� : ����
				// ��, ��
				for (int i = 0; i < 10; i++) {
					if (player.position.x == forest[i].position.x && player.position.y == forest[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[1];
					}
					else if (player.position.x == swamp[i].position.x && player.position.y == swamp[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[2];
					}
				}
				player.walk++;
			}
			break;
		case 'A':
		case 'a':
			//��
			errPosition = player.position.x <= 1;

			if (!errPosition) {
				//������ ����
				for (int j = 0; j < level.stalactiteCount; j++) {
					if (player.position.y == stalactite[j].position.y &&
						(player.position.x - 1) == stalactite[j].position.x) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				player.position.x -= 1;
				player.stamina += level.staminaDecrease[0]; // �÷��̾� ���׹̳� ���� : ����
				// ��, ��
				for (int i = 0; i < 10; i++) {
					if (player.position.x == forest[i].position.x && player.position.y == forest[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[1];
					}
					else if (player.position.x == swamp[i].position.x && player.position.y == swamp[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[2];
					}
				}
				player.walk++;
			}
			break;
		case 'S':
		case 's':
			//��
			errPosition = player.position.y >= level.mapSize;

			if (!errPosition) {
				//������ ����
				for (int j = 0; j < level.stalactiteCount; j++) {
					if ((player.position.y + 1) == stalactite[j].position.y &&
						player.position.x == stalactite[j].position.x) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}
			if (!errPosition) {
				player.position.y += 1;
				player.stamina += level.staminaDecrease[0]; // �÷��̾� ���׹̳� ���� : ����
				// ��, ��
				for (int i = 0; i < 10; i++) {
					if (player.position.x == forest[i].position.x && player.position.y == forest[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[1];
					}
					else if (player.position.x == swamp[i].position.x && player.position.y == swamp[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[2];
					}
				}
				player.walk++;
			}
			break;
		case 'D':
		case 'd':
			//��
			errPosition = player.position.x >= level.mapSize;

			if (!errPosition) {
				//������ ����
				for (int j = 0; j < level.stalactiteCount; j++) {
					if (player.position.y == stalactite[j].position.y &&
						(player.position.x + 1) == stalactite[j].position.x) {
						//���� ������ ��ġ�� ��ģ�ٸ�
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				player.position.x += 1;
				player.stamina += level.staminaDecrease[0]; // �÷��̾� ���׹̳� ���� : ����
				// ��, ��
				for (int i = 0; i < 10; i++) {
					if (player.position.x == forest[i].position.x && player.position.y == forest[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[1];
					}
					else if (player.position.x == swamp[i].position.x && player.position.y == swamp[i].position.y)
					{
						player.stamina -= level.staminaDecrease[0];
						player.stamina += level.staminaDecrease[2];
					}
				}
				player.walk++;
			}
			break;
		default:
			errPosition = 1;
			break;
		}

		//����, ������, �칰 ���� ó���� ���� ����
		char temp = gameMap[player.position.x][player.position.y].tile.show;

		//���� ���� ȹ�� //���� ������ ������ ���ڿ� ���ٸ� ������ ���� ȹ��
		if (temp == showManual.jewelry) {
			player.score += gameMap[player.position.x][player.position.y].tile.score;
			gameMap[player.position.x][player.position.y].tile = flat;
		}

		//������ ȹ��(�þ� Ȯ��) //���� ������ �������� ���ڿ� ���ٸ� ������ ���� ȹ��
		if (temp == showManual.item) {
			player.sight++;
			gameMap[player.position.x][player.position.y].tile = flat;
		}

		//�칰 ����(���׹̳� ȸ��) //���� ������ �������� ���ڿ� ���ٸ� ������ ���� ȹ��
		if (temp == showManual.well) {
			player.stamina = level.maxStamina; // �ʱ�(�ִ�) ���׹̳ʷ� ȸ��
		}

		//// gameMap �ʱ�ȭ
		//for (int j = 0; j < level.mapSize + 2; j++) // map
		//{
		//	for (int i = 0; i < level.mapSize + 2; i++) // map
		//	{
		//		(i == 0 || j == 0 || i == level.mapSize + 1 || j == level.mapSize + 1) ?
		//			gameMap[j][i].show = showManual.boundary : gameMap[j][i].show = showManual.dark; // map
		//	}
		//}
		//// �÷��̾� ��ġ ���ε�
		//gameMap[player.position.x][player.position.y].show = showManual.player;
		//// �÷��̾� �þ� ���� // sight
		//for (int i = -1 * player.sight; i < player.sight + 1; i++) {
		//	for (int j = -1 * player.sight; j < player.sight + 1; j++) {
		//		if (gameMap[player.position.x + i][player.position.y + j].show == showManual.dark)
		//			gameMap[player.position.x + i][player.position.y + j].show = showManual.flat;
		//	}
		//}
		////�칰 ��ġ ����
		//if (gameMap[well.position.x][well.position.y].show == showManual.flat)
		//	gameMap[well.position.x][well.position.y].show = showManual.well;
		//// Ż������(gameEscape) ����
		//if (gameMap[escape.position.x][escape.position.y].show == showManual.flat)
		//	gameMap[escape.position.x][escape.position.y].show = showManual.escape;
		////������ ����
		//for (int i = 0; i < level.stalactiteCount; i++) {
		//	if (gameMap[stalactite[i].position.x][stalactite[i].position.y].show == showManual.flat)
		//		gameMap[stalactite[i].position.x][stalactite[i].position.y].show = showManual.stalactite;
		//}
		////���� ����
		//for (int i = 0; i < level.jewelryCount; i++) {
		//	if (gameMap[jewelry[i].position.x][jewelry[i].position.y].show == showManual.flat)
		//		gameMap[jewelry[i].position.x][jewelry[i].position.y].show = showManual.jewelry;
		//}
		////������ ����
		//for (int i = 0; i < level.itemCount; i++) {
		//	if (gameMap[item[i].position.x][item[i].position.y].show == showManual.flat)
		//		gameMap[item[i].position.x][item[i].position.y].show = showManual.item;
		//}
		////�� ����
		//for (int i = 0; i < level.forestCount; i++) {
		//	if (gameMap[forest[i].position.x][forest[i].position.y].show == showManual.flat)
		//		gameMap[forest[i].position.x][forest[i].position.y].show = showManual.forest;
		//}
		////�� ����
		//for (int i = 0; i < level.swampCount; i++) {
		//	if (gameMap[swamp[i].position.x][swamp[i].position.y].show == showManual.flat)
		//		gameMap[swamp[i].position.x][swamp[i].position.y].show = showManual.swamp;
		//}
		//// �̵� �Ѱ� ���
		//errPosition == 1 ? cout << "�̵� �Ұ�" << endl : cout << gameKey << "\t" << player.stamina << endl;

		if (player.stamina == 0) // ���׹̳� 0 �Ǹ� ���� ����
		{
			gameClear = 0;
			break;
		}

		// ȭ�� ����
		system("cls");

	} while (player.position.x != escape.position.x || player.position.y != escape.position.y);

	system("cls");
	cout << "====================" << endl;
	gameClear ? cout << "Ż�⿡ �����߽��ϴ�." << endl : cout << "Ż�⿡ �����߽��ϴ�." << endl;
	cout << "score: " << player.score << endl;
	cout << "walk: " << player.walk << endl;
	cout << "====================" << endl;
}
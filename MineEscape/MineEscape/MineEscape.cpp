#include <iostream>
#include <conio.h>
using namespace std;

struct Position // { x, y }좌표
{
	int x;
	int y;
}setPosition[50];
// 출구, 플레이어, 종유석, 보석, 아이템, 우물, 랜덤 좌표

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

struct Player // 플레이어 관련 데이터 구조체
{
	Position position = { 1, 1 };	// 위치
	int stamina = 0;	// 이동 기회
	int score = 0;	// 획득 점수
	int walk = 0;	// 이동 횟수
	int sight = 3;	// 시야 범위
}player;

struct Tile	// 배치할 오브젝트 구조체
{
	Position position;	// 위치
	char show;	// 모양
	int score;	// 점수
}flat = { {0,0}, showManual.flat, 0 };

struct GameMap	// 게임 맵의 표시 및 속성 저장 
{
	char show = showManual.flat;	// 표시 모양
	Tile tile = flat;	// 속성
};

struct LevelInfo
{
	int mapSize = 0;		//맵 크기
	int stalactiteCount = 0;//종류석 수
	int jewelryCount = 0;	//보석 수
	int itemCount = 0;		//이이템 수
	int forestCount = 10;	//숲 타일 수
	int swampCount = 10;	//늪 타일 수
	//int plusStamina = 0;		//추가되는 스테미나(레벨에 따라 다름)
	int maxStamina = 0;			//해당 판의 최대 스테미나 수
	int staminaDecrease[3] = { -1, -2, -3 }; // 피로도
}level;

int main()
{
	// 구조체 선언 및 초기화
	GameMap gameMap[49][49] = { showManual.flat, flat }; // 맵 전체 // 맵 최대 사이즈 +2 (경계선) +7 (level3에서의 배열 오버플로우 방지용)
	Tile stalactite[10];	// 종유석
	for (int i = 0; i < 10; i++)
	{
		stalactite[i] = { {0,0}, showManual.stalactite, 0 };
	} // 종유석 초기화
	Tile jewelry[10] = { {0,0}, showManual.jewelry, 0 }; // 보석
	for (int i = 0; i < 10; i++)
	{
		jewelry[i] = { {0,0}, showManual.jewelry, 0 };
	} // 보석 초기화
	Tile item[10] = { {0,0}, showManual.item, 0 }; // 아이템
	for (int i = 0; i < 10; i++)
	{
		item[i] = { {0,0}, showManual.item, 0 };
	} // 아이템 초기화
	Tile forest[10] = { {0,0}, showManual.forest, 0 }; // 숲
	for (int i = 0; i < 10; i++)
	{
		forest[i] = { {0,0}, showManual.forest, 0 };
	} // 숲 초기화
	Tile swamp[10] = { {0,0}, showManual.swamp, 0 }; // 늪
	for (int i = 0; i < 10; i++)
	{
		swamp[i] = { {0,0}, showManual.swamp, 0 };
	} // 늪 초기화
	// Tile flat = { 0 }; // 평지
	Tile well = { {0,0}, showManual.well, 0 }; // 우물
	Tile escape = { {0,0}, showManual.escape, 0 }; // 출구
	Tile dark = { {0,0}, showManual.dark, 0 }; // 암흑
	Tile boundary = { {0,0}, showManual.boundary, 0 }; // 경계

	//char gameMap[49][49]; //맵 // 맵 최대 사이즈 +2 (경계선) +7 (level3에서의 배열 오버플로우 방지용)
	char gameKey; //입력키
	int inputGameLevel; //난이도 입력

	int gameJewelryBasicSocre[3] = { 100,200,300 };//보석 기본 점수(여기서 랜덤으로 배정)
	bool gameClear = 1;

	// int plusStamina = 0; // 스테미너 난이도 조절

	// 게임 난이도 설정 // map // sight
	cout << "=================" << endl;
	cout << ">> MINE ESCAPE <<" << endl;
	cout << "=================" << endl;
	do {
		cout << "난이도 입력(1~3): ";
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
			cout << "잘못된 입력" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "로딩중..." << endl;
	srand(time(NULL));
	// 랜덤 좌표 50개 저장
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

	for (int i = 0; i < 50; i++)	// 우물을 가운데 영역(3*3등분 기준)에 가능한 한 배치
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
	// gameMap에 저장
	gameMap[well.position.x][well.position.y].tile = well;
	gameMap[well.position.x][well.position.y].show = well.show;

	for (int i = 0; i < 1 + level.stalactiteCount + level.jewelryCount + level.itemCount
		+ level.forestCount + level.swampCount; i++)	// 랜덤좌표를 각 요소에 대입 (gameEscapePosition, sTalactite.position, jewelry.position, item.position)
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
			//보석 점수 설정
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

	// 최소 이동거리
	// player.stamina = (well.x + well.y) + plusStamina;
	// 초기 (최대) 스테미너 지정
	player.stamina = 2 * level.mapSize;
	level.maxStamina = 2 * level.mapSize;

	//초기 화면

	//// gameMap 초기화
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

	//// 플레이어 위치 업로드
	//gameMap[player.position.x][player.position.y].show = showManual.player;

	// 플레이어 시야 지정 // sight
	for (int i = -1 * player.sight; i < player.sight + 1; i++) {
		for (int j = -1 * player.sight; j < player.sight + 1; j++) {
			gameMap[player.position.x + i][player.position.y + j].show = gameMap[player.position.x + i][player.position.y + j].tile.show;
		}
	}

	////우물 위치 지정
	//if (gameMap[well.position.x][well.position.y].show == showManual.flat)
	//	gameMap[well.position.x][well.position.y].show = showManual.well;
	//// 탈출지점(gameEscape) 지정
	//if (gameMap[escape.position.x][escape.position.y].show == showManual.flat)
	//	gameMap[escape.position.x][escape.position.y].show = showManual.escape;
	////종유석 지정
	//for (int i = 0; i < level.stalactiteCount; i++) {
	//	if (gameMap[stalactite[i].position.x][stalactite[i].position.y].show == showManual.flat)
	//		gameMap[stalactite[i].position.x][stalactite[i].position.y].show = showManual.stalactite;
	//}
	////보석 지정
	//for (int i = 0; i < level.jewelryCount; i++) {
	//	if (gameMap[jewelry[i].position.x][jewelry[i].position.y].show == showManual.flat)
	//		gameMap[jewelry[i].position.x][jewelry[i].position.y].show = showManual.jewelry;
	//}
	////아이템 지정
	//for (int i = 0; i < level.itemCount; i++) {
	//	if (gameMap[item[i].position.x][item[i].position.y].show == showManual.flat)
	//		gameMap[item[i].position.x][item[i].position.y].show = showManual.item;
	//}
	////숲 지정
	//for (int i = 0; i < level.forestCount; i++) {
	//	if (gameMap[forest[i].position.x][forest[i].position.y].show == showManual.flat)
	//		gameMap[forest[i].position.x][forest[i].position.y].show = showManual.forest;
	//}
	////늪 지정
	//for (int i = 0; i < level.swampCount; i++) {
	//	if (gameMap[swamp[i].position.x][swamp[i].position.y].show == showManual.flat)
	//		gameMap[swamp[i].position.x][swamp[i].position.y].show = showManual.swamp;
	//}

	// 이동 및 화면 갱신 
	system("cls");
	do
	{
		// gameMap 초기화
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

		// 플레이어 시야 지정 // sight
		for (int i = -1 * player.sight; i < player.sight + 1; i++) {
			for (int j = -1 * player.sight; j < player.sight + 1; j++) {
				gameMap[player.position.x + i][player.position.y + j].show = gameMap[player.position.x + i][player.position.y + j].tile.show;
			}
		}

		// 플레이어 위치 업로드
		gameMap[player.position.x][player.position.y].show = showManual.player;

		// 화면 표시
		for (int j = 0; j < level.mapSize + 2; j++) // map
		{
			for (int i = 0; i < level.mapSize + 2; i++) // map
			{
				cout << gameMap[i][j].show;
			}
			cout << endl;
		}

		//하단 스코어, 스테미나 표시
		cout << "stamina: " << player.stamina << endl;
		cout << "score: " << player.score << endl;
		cout << "walk: " << player.walk << endl;

		gameKey = _getch();

		bool errPosition = 0; // 이동불가 에러 표시용

		// 플레이어 위치 변경 (switch문)
		switch (gameKey)
		{
		case 'W':
		case 'w':
			//끝
			errPosition = player.position.y <= 1;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < level.stalactiteCount; j++) {
					if ((player.position.y - 1) == stalactite[j].position.y &&
						player.position.x == stalactite[j].position.x) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				player.position.y -= 1;
				player.stamina += level.staminaDecrease[0]; // 플레이어 스테미너 감산 : 평지
				// 숲, 늪
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
			//끝
			errPosition = player.position.x <= 1;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < level.stalactiteCount; j++) {
					if (player.position.y == stalactite[j].position.y &&
						(player.position.x - 1) == stalactite[j].position.x) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				player.position.x -= 1;
				player.stamina += level.staminaDecrease[0]; // 플레이어 스테미너 감산 : 평지
				// 숲, 늪
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
			//끝
			errPosition = player.position.y >= level.mapSize;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < level.stalactiteCount; j++) {
					if ((player.position.y + 1) == stalactite[j].position.y &&
						player.position.x == stalactite[j].position.x) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}
			if (!errPosition) {
				player.position.y += 1;
				player.stamina += level.staminaDecrease[0]; // 플레이어 스테미너 감산 : 평지
				// 숲, 늪
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
			//끝
			errPosition = player.position.x >= level.mapSize;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < level.stalactiteCount; j++) {
					if (player.position.y == stalactite[j].position.y &&
						(player.position.x + 1) == stalactite[j].position.x) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				player.position.x += 1;
				player.stamina += level.staminaDecrease[0]; // 플레이어 스테미너 감산 : 평지
				// 숲, 늪
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

		//보석, 아이템, 우물 관련 처리를 위한 템프
		char temp = gameMap[player.position.x][player.position.y].tile.show;

		//보석 점수 획득 //만약 템프가 보석의 글자와 같다면 보석의 점수 획득
		if (temp == showManual.jewelry) {
			player.score += gameMap[player.position.x][player.position.y].tile.score;
			gameMap[player.position.x][player.position.y].tile = flat;
		}

		//아이템 획득(시아 확장) //만약 템프가 아이템의 글자와 같다면 보석의 점수 획득
		if (temp == showManual.item) {
			player.sight++;
			gameMap[player.position.x][player.position.y].tile = flat;
		}

		//우물 접촉(스테미너 회복) //만약 템프가 아이템의 글자와 같다면 보석의 점수 획득
		if (temp == showManual.well) {
			player.stamina = level.maxStamina; // 초기(최대) 스테미너로 회복
		}

		//// gameMap 초기화
		//for (int j = 0; j < level.mapSize + 2; j++) // map
		//{
		//	for (int i = 0; i < level.mapSize + 2; i++) // map
		//	{
		//		(i == 0 || j == 0 || i == level.mapSize + 1 || j == level.mapSize + 1) ?
		//			gameMap[j][i].show = showManual.boundary : gameMap[j][i].show = showManual.dark; // map
		//	}
		//}
		//// 플레이어 위치 업로드
		//gameMap[player.position.x][player.position.y].show = showManual.player;
		//// 플레이어 시야 지정 // sight
		//for (int i = -1 * player.sight; i < player.sight + 1; i++) {
		//	for (int j = -1 * player.sight; j < player.sight + 1; j++) {
		//		if (gameMap[player.position.x + i][player.position.y + j].show == showManual.dark)
		//			gameMap[player.position.x + i][player.position.y + j].show = showManual.flat;
		//	}
		//}
		////우물 위치 지정
		//if (gameMap[well.position.x][well.position.y].show == showManual.flat)
		//	gameMap[well.position.x][well.position.y].show = showManual.well;
		//// 탈출지점(gameEscape) 지정
		//if (gameMap[escape.position.x][escape.position.y].show == showManual.flat)
		//	gameMap[escape.position.x][escape.position.y].show = showManual.escape;
		////종유석 지정
		//for (int i = 0; i < level.stalactiteCount; i++) {
		//	if (gameMap[stalactite[i].position.x][stalactite[i].position.y].show == showManual.flat)
		//		gameMap[stalactite[i].position.x][stalactite[i].position.y].show = showManual.stalactite;
		//}
		////보석 지정
		//for (int i = 0; i < level.jewelryCount; i++) {
		//	if (gameMap[jewelry[i].position.x][jewelry[i].position.y].show == showManual.flat)
		//		gameMap[jewelry[i].position.x][jewelry[i].position.y].show = showManual.jewelry;
		//}
		////아이템 지정
		//for (int i = 0; i < level.itemCount; i++) {
		//	if (gameMap[item[i].position.x][item[i].position.y].show == showManual.flat)
		//		gameMap[item[i].position.x][item[i].position.y].show = showManual.item;
		//}
		////숲 지정
		//for (int i = 0; i < level.forestCount; i++) {
		//	if (gameMap[forest[i].position.x][forest[i].position.y].show == showManual.flat)
		//		gameMap[forest[i].position.x][forest[i].position.y].show = showManual.forest;
		//}
		////늪 지정
		//for (int i = 0; i < level.swampCount; i++) {
		//	if (gameMap[swamp[i].position.x][swamp[i].position.y].show == showManual.flat)
		//		gameMap[swamp[i].position.x][swamp[i].position.y].show = showManual.swamp;
		//}
		//// 이동 한계 출력
		//errPosition == 1 ? cout << "이동 불가" << endl : cout << gameKey << "\t" << player.stamina << endl;

		if (player.stamina == 0) // 스테미나 0 되면 게임 오버
		{
			gameClear = 0;
			break;
		}

		// 화면 갱신
		system("cls");

	} while (player.position.x != escape.position.x || player.position.y != escape.position.y);

	system("cls");
	cout << "====================" << endl;
	gameClear ? cout << "탈출에 성공했습니다." << endl : cout << "탈출에 실패했습니다." << endl;
	cout << "score: " << player.score << endl;
	cout << "walk: " << player.walk << endl;
	cout << "====================" << endl;
}
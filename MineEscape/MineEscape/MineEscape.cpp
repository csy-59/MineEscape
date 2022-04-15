// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
using namespace std;

//화면 표시하는 요소 매뉴얼
struct printManual {
	char border = '*';		//창 경계
	char plain = ' ';		//그냥 땅
	char mist = '=';		//안보이는 곳
	char player = 'O';		//플래이어
	char exit = 'E';		//출구
	char well = '#';		//회복의 우물
	char stalactite = 'T';	//종류석
	char jewelry = 'J';		//보석
	char item = 'F';		//아이템(플래시)
} manual;

//각 타일의 타입
struct tileTypeInfo {
	int x = -1, y = -1;
	char print = manual.plain;
	int score = 0;
} plain;

//타일 정보(표시되는 정보와 해당 타일의 정보)
struct tileInfo {
	char print = manual.plain;
	tileTypeInfo type = plain;
};

//전반적인 게임 요소
struct mapInfo {
	int gameMapSize = 0;		//맵 크기
	int gameStalactiteCount = 0;//종류석 수
	int gameJewelryCount = 0;	//보석 수
	int gameItemCount = 0;		//이이템 수
	int plusStamina = 0;		//추가되는 스테미나(레벨에 따라 다름)
	int maxStamina = 0;			//해당 판의 최대 스테미나 수

};

//플래이어 정보
struct player {
	tileTypeInfo tile = { 0,0,manual.player,-1 };
	int stamina = 0; //스테미나
	int score = 0; //얻은 점수
	int walk = 0; //걸은 걸음의 수
	int sight = 3; //시야
};

int main()
{

	//char gameMap[49][49] = { '/' }; //맵 // 맵 최대 사이즈 +2 (경계선) +7 (level3에서의 배열 오버플로우 방지용)
	//int gameMapSize; //맵 크기
	//int gameSight = 3; //시야 크기
	//int gameEscapePosition[2];	//출구 위치 // { x, y }
	//int gamePlayerPosition[2] = { 1, 1 }; //플레이어 위치 // { x, y }
	//char gameKey; //입력키
	//int inputGameLevel; //난이도 입력
	//int gamesTalactiteCount; //종유석 개수
	//int gamesTalactitePosition[10][2]; //종유석 위치 배열 // { x, y }
	//int gameJewelryCount; //보석 개수
	//int gameJewelryPosition[10][2]; // 보석 위치 배열 // { x, y }
	//int gameJewelryScore[10]; // 보석 점수
	//int gameItemPosition[6][2];	//아이템 위치 배열 // { x, y }
	//int gameItemCount = 6; //아이템 개수
	//char well = '#';
	//int gamePlayerChance;
	//int wellLocation[2];
	//int gameJewelryBasicSocre[3] = { 100,200,300 };//보석 기본 점수(여기서 랜덤으로 배정)
	//bool gameClear = 1;
	//int score = 0;
	//int walk = 0;
	//int setPosition[30][2] = { { 0, 0 } }; // 중복하지 않는 랜덤 좌표를 기록하기 위한 이중배열 // { x, y }
	//int plusStamina = 0; // 스테미너 난이도 조절

	mapInfo mapInfo;
	tileInfo gameMap[42][42];//맵
	tileTypeInfo stalactiteInfo[20];//종류석
	tileTypeInfo jewelryInfo[25]; //보석
	tileTypeInfo itemInfo[6]; //아이템
	tileTypeInfo exit;// 출구
	tileTypeInfo well;// 우물
	tileTypeInfo border = { -1,-1,manual.border,0 }; //경계

	player player; // 플레이어

	char gameKey; //입력키
	int inputGameLevel; //난이도 입력

	int gameJewelryBasicSocre[3] = { 100,200,300 };//보석 기본 점수(여기서 랜덤으로 배정)
	int setPosition[30][2] = { { 0, 0 } }; // 중복하지 않는 랜덤 좌표를 기록하기 위한 이중배열 // { x, y }
	//게임 클리어 여부
	bool gameClear = true;

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
			cout << "잘못된 입력" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "로딩중..." << endl;
	srand(time(NULL));

	// 랜덤 좌표 20개 저장
	for (int j = 0; j < 30; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			do {
				setPosition[j][0] = rand() % (mapInfo.gameMapSize - 1) + 2;
				setPosition[j][1] = rand() % (mapInfo.gameMapSize - 1) + 2;
			} while (j != i && (setPosition[j][0] == setPosition[i][0] && setPosition[j][1] == setPosition[i][1])); //중복 체크
		}
	}

	//우물 위치 지정
	for (int i = 0; i < 30; i++)	// 우물을 가운데 영역(3*3등분 기준)에 가능한 한 배치
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
	//map에 표시
	gameMap[well.x][well.y].type = well;
	gameMap[well.x][well.y].print = well.print;
	mapInfo.maxStamina = well.x + well.y + mapInfo.plusStamina;

	//탈출 위치 지정
	exit.x = setPosition[0][0];
	exit.y = setPosition[0][1];
	exit.print = manual.exit;
	exit.score = 0;
	gameMap[exit.x][exit.y].type = exit;
	gameMap[exit.x][exit.y].print = exit.print;

	//종유석, 보석, 아이템 위치 지정
	for (int i = 1; i < 1 + mapInfo.gameStalactiteCount + mapInfo.gameJewelryCount + mapInfo.gameItemCount; i++)	// 랜덤좌표를 각 요소에 대입 (gameEscapePosition, gamesTalactitePosition, gameJewelryPosition, gameItemPosition)
	{
		//종유석
		if (i <= mapInfo.gameStalactiteCount)
		{
			stalactiteInfo[i - 1].x = setPosition[i][0];
			stalactiteInfo[i - 1].y = setPosition[i][1];
			stalactiteInfo[i - 1].print = manual.stalactite;
			stalactiteInfo[i - 1].score = 0;
			gameMap[stalactiteInfo[i - 1].x][stalactiteInfo[i - 1].y].type = stalactiteInfo[i - 1];
			gameMap[stalactiteInfo[i - 1].x][stalactiteInfo[i - 1].y].print = stalactiteInfo[i - 1].print;
		}
		//보석
		else if (i <= mapInfo.gameStalactiteCount + mapInfo.gameJewelryCount)
		{
			int position = i - (mapInfo.gameStalactiteCount + 1);
			jewelryInfo[position].x = setPosition[i][0];
			jewelryInfo[position].y = setPosition[i][1];
			jewelryInfo[position].print = manual.jewelry;
			//보석 점수 설정
			jewelryInfo[position].score = gameJewelryBasicSocre[rand() % 3];
			gameMap[jewelryInfo[position].x][jewelryInfo[position].y].type = jewelryInfo[position];
			gameMap[jewelryInfo[position].x][jewelryInfo[position].y].print = jewelryInfo[position].print;
		}
		//아이템
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

	//플레이어 초기 자리 지정
	player.tile.x = 1;
	player.tile.y = 1;
	player.tile.print = manual.player;
	player.stamina = mapInfo.maxStamina;
	player.score = 0;
	player.walk = 0;

	// 최소 이동거리
	mapInfo.maxStamina = (well.x + well.y) + mapInfo.plusStamina;

	//초기 화면

	// gameMap 초기화
	for (int j = 0; j < mapInfo.gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < mapInfo.gameMapSize + 2; i++) // map
		{
			//경계
			if (i == 0 || j == 0 || i == mapInfo.gameMapSize + 1 || j == mapInfo.gameMapSize + 1) {
				gameMap[i][j].print = manual.border;
				gameMap[i][j].type = border;
			}
			//그냥 땅
			else
				gameMap[i][j].print = manual.mist;
			//gameMap[i][j].print = gameMap[i][j].type.print;

		}
	}

	// 플레이어 시야 지정 // sight
	for (int i = -1 * player.sight; i < player.sight + 1; i++) {
		for (int j = -1 * player.sight; j < player.sight + 1; j++) {
			gameMap[player.tile.x + i][player.tile.y + j].print = gameMap[player.tile.x + i][player.tile.y + j].type.print;
		}
	}

	// 플레이어 위치 업로드
	gameMap[player.tile.x][player.tile.y].print = player.tile.print;

	// 이동 및 화면 갱신 
	system("cls");
	do
	{
		// 화면 표시
		for (int j = 0; j < mapInfo.gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < mapInfo.gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j].print;
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
			errPosition = player.tile.y <= 1;

			//종유석 연산
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if (player.tile.x == stalactiteInfo[j].x && (player.tile.y - 1) == stalactiteInfo[j].y) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//플래이어 연산
				player.tile.y--;
				player.stamina--;
				player.walk++;
			}
			break;
		case 'A':
		case 'a':
			//끝
			errPosition = player.tile.x <= 1;

			//종유석 연산
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if ((player.tile.x - 1) == stalactiteInfo[j].x && player.tile.y == stalactiteInfo[j].y) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//플래이어 연산
				player.tile.x--;
				player.stamina--;
				player.walk++;
			}
			break;
		case 'S':
		case 's':
			//끝
			errPosition = player.tile.y >= mapInfo.gameMapSize;

			//종유석 연산
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if (player.tile.x == stalactiteInfo[j].x && (player.tile.y + 1) == stalactiteInfo[j].y) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//플래이어 연산
				player.tile.y++;
				player.stamina--;
				player.walk++;
			}
			break;
		case 'D':
		case 'd':
			//끝
			errPosition = player.tile.x >= mapInfo.gameMapSize;

			//종유석 연산
			if (!errPosition) {
				for (int j = 0; j < mapInfo.gameStalactiteCount; j++) {
					if ((player.tile.x + 1) == stalactiteInfo[j].x && player.tile.y == stalactiteInfo[j].y) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				//플래이어 연산
				player.tile.x++;
				player.stamina--;
				player.walk++;
			}
			break;
		default:
			errPosition = 1;
			break;
		}

		//보석, 아이템, 우물 관련 처리를 위한 탬프
		char temp = gameMap[player.tile.x][player.tile.y].type.print;

		//보석 점수 수정
		if (temp == manual.jewelry) {
			player.score += gameMap[player.tile.x][player.tile.y].type.score;
			gameMap[player.tile.x][player.tile.y].type = plain;
		}

		//아이템 획득(시아 확장)
		if (temp == manual.item) {
			player.sight++;
			gameMap[player.tile.x][player.tile.y].type = plain;
		}

		//우물 접촉(스테미너 회복)
		if (temp == manual.well) {
			player.stamina = mapInfo.maxStamina;
		}


		// gameMap 초기화
		for (int j = 0; j < mapInfo.gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < mapInfo.gameMapSize + 2; i++) // map
			{
				//경계
				if (i == 0 || j == 0 || i == mapInfo.gameMapSize + 1 || j == mapInfo.gameMapSize + 1)
					gameMap[i][j].print = manual.border;
				//그냥 땅
				else
					gameMap[i][j].print = manual.mist;
				//gameMap[i][j].print = gameMap[i][j].type.print;

			}
		}


		// 플레이어 시야 지정 // sight
		for (int i = -1 * player.sight; i < player.sight + 1; i++) {
			for (int j = -1 * player.sight; j < player.sight + 1; j++) {
				gameMap[player.tile.x + i][player.tile.y + j].print = gameMap[player.tile.x + i][player.tile.y + j].type.print;
			}
		}

		// 플레이어 위치 업로드
		gameMap[player.tile.x][player.tile.y].print = player.tile.print;

		// 이동 한계 출력
		//errPosition == 1 ? cout << "이동 불가" << endl : cout << gameKey << "\t" << gamePlayerChance << endl;

		if (player.stamina == 0) // 스테미나 0 되면 게임 오버
		{
			gameClear = 0;
			break;
		}

		// 화면 갱신
		system("cls");

	} while (player.tile.x != exit.x || player.tile.y != exit.y);

	system("cls");
	cout << "====================" << endl;
	gameClear ? cout << "탈출에 성공했습니다." << endl : cout << "탈출에 실패했습니다." << endl;
	cout << "score: " << player.score << endl;
	cout << "walk: " << player.walk << endl;
	cout << "====================" << endl;
}
// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{

	char gameMap[42][42] = { '/' }; //맵
	int gameMapSize; //맵 크기
	int gameSight; //시아 크기

	int gameEscape[2];	//출구 위치
	int gamePlayerPosition[2] = { 1, 1 }; //플레이어 위치
	char gameKey; //입력키
	int inputGameLevel; //난이도 입력

	int gamesTalactiteCount; //종유석 개수
	int gamesTalactitePosition[5][2]; //종유석 위치 배열

	int gameJewelryCount; //보석 개수
	int gameJewelryPosition[7][2]; // 보석 위치 배열
	int gameJewelryScore[7]; // 보석 위치 배열

	int gameItem[2][4];	//아이템 위치 배열
	int gameItemCount = 4; //아이템 개수

	char well = '#';
	int wellLocation;

	int gameJewelryBasicSocre[3] = { 100,200,300 };//보석 기본 점수(여기서 랜덤으로 배정)
	bool gameClear = 1;
	int score = 0;
	int walk = 0;

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
			gameMapSize = 20;
			gamesTalactiteCount = 4;
			gameJewelryCount = 5;
			gameSight = 5; // sight
			gameItemCount = 1;
			break;
		case 2:
			gameMapSize = 30;
			gamesTalactiteCount = 5;
			gameJewelryCount = 6;
			gameSight = 4; // sight
			gameItemCount = 2;
			break;
		case 3:
			gameMapSize = 40;
			gamesTalactiteCount = 7;
			gameJewelryCount = 7;
			gameSight = 3; // sight
			gameItemCount = 4;
			break;
		default:
			cout << "잘못된 입력" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	int gamePlayerChance = gameMapSize * 2;
	wellLocation = gameMapSize / 2;

	cout << "로딩중..." << endl;

	//탈출 위치 지정
	bool isExitPossibile = true;
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		gameEscape[1] = rand() % gameMapSize + 1;

		//플레이어 초기위치 판별
		if ((gameEscape[0] == 1 && gameEscape[1] == 1) && (gameEscape[0] == wellLocation && gameEscape[1] == wellLocation))
			isExitPossibile = false;

	} while (!isExitPossibile);

	//종유석 위치
	for (int i = 0; i < gamesTalactiteCount; i++) {
		bool isStalactitePossible = true;
		do {
			isStalactitePossible = true;
			srand(time(NULL));
			gamesTalactitePosition[i][0] = rand() % gameMapSize + 1;
			gamesTalactitePosition[i][1] = rand() % gameMapSize + 1;

			//플레이어 초기위치 판별
			if ((gamesTalactitePosition[i][0] == 1 && gamesTalactitePosition[i][1] == 1) &&
				(gamesTalactitePosition[i][0] == wellLocation && gamesTalactitePosition[i][1] == wellLocation))
				isStalactitePossible = false;

			//탈출 위치 판별
			if (gamesTalactitePosition[i][1] == gameEscape[1] && gamesTalactitePosition[i][0] == gameEscape[0])
				isStalactitePossible = false;

			for (int j = 0; j < i; j++) {
				if (gamesTalactitePosition[j][0] == gamesTalactitePosition[i][0] &&
					gamesTalactitePosition[j][1] == gamesTalactitePosition[i][1]) {
					//만약 종유석 위치와 겹친다면
					isStalactitePossible = false;
					break;
				}
			}
		} while (!isStalactitePossible);
		//종유석의 위치가 플레이어/탈출 위치/벽/다른 종유석/시아 위치가 아닐 경우 저장 완료.
	}

	//보석 위치
	for (int i = 0; i < gameJewelryCount; i++) {

		bool isJewelryPossible = true;

		do {
			isJewelryPossible = true;

			srand(time(NULL));
			gameJewelryPosition[i][0] = rand() % gameMapSize + 1;
			gameJewelryPosition[i][1] = rand() % gameMapSize + 1;

			if ((gamesTalactitePosition[i][0] == 1 && gamesTalactitePosition[i][1] == 1) &&
				(gamesTalactitePosition[i][0] == wellLocation && gamesTalactitePosition[i][1] == wellLocation))
				isJewelryPossible = false;

			if ((gameJewelryPosition[i][1] == gameEscape[1] && gameJewelryPosition[i][0] == gameEscape[0]))
				isJewelryPossible = false;

			for (int j = 0; j < gamesTalactiteCount; j++) {
				if (gameJewelryPosition[i][0] == gamesTalactitePosition[j][0] &&
					gameJewelryPosition[i][1] == gamesTalactitePosition[j][1]) {
					//만약 종유석 위치와 겹친다면
					isJewelryPossible = false;
					break;
				}
			}

			for (int j = 0; j < i; j++) {
				if (gameJewelryPosition[j][0] == gameJewelryPosition[i][0] &&
					gameJewelryPosition[j][1] == gameJewelryPosition[i][1]) {
					//만약 보석 위치와 겹친다면
					isJewelryPossible = false;
					break;
				}
			}
		} while (!isJewelryPossible);
		//보석의 위치가 플레이어/탈출 위치/벽/다른 종유석/시아 위치가 아닐 경우 저장 완료.

		//보석 점수 설정
		srand(time(NULL));
		gameJewelryScore[i] = gameJewelryBasicSocre[rand() % 3];

	}


	//아이템 위치
	for (int i = 0; i < gameItemCount; i++) {

		bool isItemPossible = true;

		do {
			isItemPossible = true;

			srand(time(NULL));
			gameItem[i][0] = rand() % gameMapSize + 1;
			gameItem[i][1] = rand() % gameMapSize + 1;

			//플레이어/우물 위치 판별
			if ((gameItem[i][0] == 1 && gameItem[i][1] == 1) &&
				(gameItem[i][0] == wellLocation && gameItem[i][1] == wellLocation))
				isItemPossible = false;

			//탈출 판별
			if ((gameItem[i][1] == gameEscape[1] && gameItem[i][0] == gameEscape[0]))
				isItemPossible = false;

			//종유석 판별
			for (int j = 0; j < gamesTalactiteCount; j++) {
				if (gameItem[i][0] == gamesTalactitePosition[j][0] &&
					gameItem[i][1] == gamesTalactitePosition[j][1]) {
					//만약 종유석 위치와 겹친다면
					isItemPossible = false;
					break;
				}
			}

			//보석 판별
			for (int j = 0; j < gameJewelryCount; j++) {
				if (gameItem[i][0] == gameJewelryPosition[j][0] &&
					gameItem[i][1] == gameJewelryPosition[j][1]) {
					//만약 보석 위치와 겹친다면
					isItemPossible = false;
					break;
				}
			}

			//아이템 판별
			for (int j = 0; j < i; j++) {
				if (gameItem[i][0] == gameJewelryPosition[j][0] &&
					gameItem[i][1] == gameJewelryPosition[j][1]) {
					//만약 보석 위치와 겹친다면
					isItemPossible = false;
					break;
				}
			}
		} while (!isItemPossible);
		//보석의 위치가 플레이어/탈출 위치/벽/다른 종유석/시아 위치가 아닐 경우 저장 완료.
	}


	//초기 화면

	// gameMap 초기화
	for (int j = 0; j < gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < gameMapSize + 2; i++) // map
		{
			(i == 0 || j == 0 || i == gameMapSize + 1 || j == gameMapSize + 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '='; // map
		}
	}

	// 플레이어 위치 업로드
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// 플레이어 시야 지정 // sight
	for (int i = -1 * gameSight; i < gameSight + 1; i++) {
		for (int j = -1 * gameSight; j < gameSight + 1; j++) {
			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '=')
				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
		}
	}

	//우물 위치 지정
	if (gameMap[wellLocation][wellLocation] == ' ')
		gameMap[wellLocation][wellLocation] = well;

	// 탈출지점(gameEscape) 지정
	if (gameMap[gameEscape[0]][gameEscape[1]] == ' ')
		gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	//종유석 지정
	for (int i = 0; i < gamesTalactiteCount; i++) {
		if (gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] == ' ')
			gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] = 'T';
	}

	//보석 지정
	for (int i = 0; i < gameJewelryCount; i++) {
		if (gameMap[gameJewelryPosition[i][0]][gameJewelryPosition[i][1]] == ' ')
			gameMap[gameJewelryPosition[i][0]][gameJewelryPosition[i][1]] = 'J';
	}

	//아이템 지정
	for (int i = 0; i < gameItemCount; i++) {
		if (gameMap[gameItem[i][0]][gameItem[i][1]] == ' ')
			gameMap[gameItem[i][0]][gameItem[i][1]] = 'F';
	}

	// 이동 및 화면 갱신 
	system("cls");
	do
	{
		// 화면 표시
		for (int j = 0; j < gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}

		//하단 스코어, 스테미나 표시
		cout << "stamina: " << gamePlayerChance << endl;
		cout << "score: " << score << endl;
		cout << "walk: " << walk << endl;

		gameKey = _getch();

		bool errPosition = 0; // 이동불가 에러 표시용

		// 플레이어 위치 변경 (switch문)
		switch (gameKey)
		{
		case 'W':
		case 'w':
			//끝
			errPosition = gamePlayerPosition[1] <= 1;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < gamesTalactiteCount; j++) {
					if ((gamePlayerPosition[1] - 1) == gamesTalactitePosition[j][1] &&
						gamePlayerPosition[0] == gamesTalactitePosition[j][0]) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				gamePlayerPosition[1] -= 1;
				gamePlayerChance--;
				walk++;
			}
			break;
		case 'A':
		case 'a':
			//끝
			errPosition = gamePlayerPosition[0] <= 1;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < gamesTalactiteCount; j++) {
					if (gamePlayerPosition[1] == gamesTalactitePosition[j][1] &&
						(gamePlayerPosition[0] - 1) == gamesTalactitePosition[j][0]) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				gamePlayerPosition[0] -= 1;
				gamePlayerChance--;
				walk++;
			}
			break;
		case 'S':
		case 's':
			//끝
			errPosition = gamePlayerPosition[1] >= gameMapSize;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < gamesTalactiteCount; j++) {
					if ((gamePlayerPosition[1] + 1) == gamesTalactitePosition[j][1] &&
						gamePlayerPosition[0] == gamesTalactitePosition[j][0]) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}
			if (!errPosition) {
				gamePlayerPosition[1] += 1;
				gamePlayerChance--;
				walk++;
			}
			break;
		case 'D':
		case 'd':
			//끝
			errPosition = gamePlayerPosition[0] >= gameMapSize;

			if (!errPosition) {
				//종유석 연산
				for (int j = 0; j < gamesTalactiteCount; j++) {
					if (gamePlayerPosition[1] == gamesTalactitePosition[j][1] &&
						(gamePlayerPosition[0] + 1) == gamesTalactitePosition[j][0]) {
						//만약 종유석 위치와 겹친다면
						errPosition = true;
						break;
					}
				}
			}

			if (!errPosition) {
				gamePlayerPosition[0] += 1;
				gamePlayerChance--;
				walk++;
			}
			break;
		default:
			errPosition = 1;
			break;
		}

		//보석 점수 수정
		for (int j = 0; j < gameJewelryCount; j++) {
			if (gamePlayerPosition[1] == gameJewelryPosition[j][1] &&
				gamePlayerPosition[0] == gameJewelryPosition[j][0]) {
				//만약 보석 위치와 겹친다면 보석의 점수 획득
				score += gameJewelryScore[j];
				gameJewelryPosition[j][1] = 0;
				gameJewelryPosition[j][0] = 0;
				break;
			}
		}

		//아이템 획득(시아 확장)
		for (int i = 0; i < gameItemCount; i++) {
			if (gamePlayerPosition[0] == gameItem[i][0] && gamePlayerPosition[1] == gameItem[i][1]) {
				gameSight++;
				gameItem[i][0] = NULL;
				gameItem[i][1] = NULL;
			}
		}

		//우물 접촉(스테미너 회복)
		if (gamePlayerPosition[1] == wellLocation && gamePlayerPosition[0] == wellLocation) {
			gamePlayerChance = gameMapSize * 2;
		}

		// gameMap 초기화
		for (int j = 0; j < gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < gameMapSize + 2; i++) // map
			{
				(i == 0 || j == 0 || i == gameMapSize + 1 || j == gameMapSize + 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '='; // map
			}
		}

		// 플레이어 위치 업로드
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// 플레이어 시야 지정 // sight
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '=')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}

		//우물 위치 지정
		if (gameMap[wellLocation][wellLocation] == ' ')
			gameMap[wellLocation][wellLocation] = well;

		// 탈출지점(gameEscape) 지정
		if (gameMap[gameEscape[0]][gameEscape[1]] == ' ')
			gameMap[gameEscape[0]][gameEscape[1]] = 'E';

		//종유석 지정
		for (int i = 0; i < gamesTalactiteCount; i++) {
			if (gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] == ' ')
				gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] = 'T';
		}

		//보석 지정
		for (int i = 0; i < gameJewelryCount; i++) {
			if (gameMap[gameJewelryPosition[i][0]][gameJewelryPosition[i][1]] == ' ')
				gameMap[gameJewelryPosition[i][0]][gameJewelryPosition[i][1]] = 'J';
		}

		//아이템 지정
		for (int i = 0; i < gameItemCount; i++) {
			if (gameMap[gameItem[i][0]][gameItem[i][1]] == ' ')
				gameMap[gameItem[i][0]][gameItem[i][1]] = 'F';
		}

		// 이동 한계 출력
		errPosition == 1 ? cout << "이동 불가" << endl : cout << gameKey << "\t" << gamePlayerChance << endl;

		if (gamePlayerChance == 0) // 스테미나 0 되면 게임 오버
		{
			gameClear = 0;
			break;
		}

		// 화면 갱신
		system("cls");

	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);

	cout << "====================" << endl;
	gameClear ? cout << "탈출에 성공했습니다." << endl : cout << "탈출에 실패했습니다." << endl;
	cout << "score: " << score << endl;
	cout << "walk: " << walk << endl;
	cout << "====================" << endl;
}
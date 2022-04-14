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

	int gameJewelryCount; //보석 갯수
	int gameJewelryPosition[7][2]; // 보석 위치 배열
	int gameJewelryScore[7]; // 보석 위치 배열

	int gameJewelryBasicSocre[3] = { 100,200,300 };//보석 기본 점수(여기서 랜덤으로 배정)

	
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
			cout << "잘못된 입력" << endl;
			break;
		}
	} while (inputGameLevel > 3 || inputGameLevel < 1);

	cout << "로딩중..." << endl;

	// 난수 생성, gameEscape(탈출구) 설정
	//// x축
	//srand(time(NULL));
	//gameEscape[0] = rand();
	//srand(time(NULL));
	//gameEscape[0] += rand();
	//gameEscape[0] %= gameMapSize; // map
	//
	//// y축
	//srand(time(NULL));
	//gameEscape[1] = rand();
	//srand(time(NULL));
	//gameEscape[1] += rand();
	//gameEscape[1] %= 20; // map
	//
	//// gameEscape = {0, 0} 제외
	//while (gameEscape[0] == 0 || gameEscape[1] == 0 || gameEscape[0] == 19 || gameEscape[1] == 19 || (gameEscape[0] == 1 && gameEscape[1] == 1))
	//{
	//	gameEscape[0] = rand();
	//	gameEscape[0] %= 20; // map
	//	gameEscape[1] = rand();
	//	gameEscape[1] %= 20; // map
	//}

	//탈출 위치 지정
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		srand(time(NULL));
		gameEscape[1] = rand() % gameMapSize + 1;
	} while (gameEscape[0] == 1 && gameEscape[1] == 1);

	// 탈출지점(gameEscape) 지정
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	// 플레이어 위치(gamePlayerPosition) 지정
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// 플레이어 초기 시야 지정
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
		}
	}

	// gameMap 초기화
	for (int j = 0; j < gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < gameMapSize + 2; i++) // map
		{
			(i == 0 || j == 0 || i == gameMapSize + 1 || j == gameMapSize + 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '/'; // map
		}
	}

	//종유석 위치
	for (int i = 0; i < gamesTalactiteCount;i++) {
		bool isStalactitePossible = true;
		do {
			isStalactitePossible = true;
			srand(time(NULL));
			gamesTalactitePosition[i][0] = rand() % gameMapSize + 1;
			srand(time(NULL));
			gamesTalactitePosition[i][1] = rand() % gameMapSize + 1;

			if ((gamesTalactitePosition[i][0] == 1 && gamesTalactitePosition[i][1] == 1))
				isStalactitePossible = false;

			if ((gamesTalactitePosition[i][0] == gameEscape[1] && gamesTalactitePosition[i][1] == gameEscape[0]))
				isStalactitePossible = false;

			for (int j = 0;j < i;j++) {
				if (gamesTalactitePosition[j][0] == gamesTalactitePosition[i][0] &&
					gamesTalactitePosition[j][1] == gamesTalactitePosition[i][1]) {
					//만약 종유석 위치와 겹친다면
					isStalactitePossible = false;
					break;
				}
			}
		} while (!isStalactitePossible);
		//종유석의 위치가 플레이어/탈출 위치/벽/다른 종유석/시아 위치가 아닐 경우 저장 완료.

		//안전한 종유석의 자리라면 종유석으로 지정
		gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] = 'T';
		cout << gamesTalactitePosition[i][0] << " " << gamesTalactitePosition[i][1] << endl;
	}

	//보석 위치
	for (int i = 0; i < gameJewelryCount;i++) {
		bool isJewelryPossible = true;
		do {
			isJewelryPossible = true;

			srand(time(NULL));
			gameJewelryPosition[i][0] = rand() % gameMapSize + 1;
			srand(time(NULL));
			gameJewelryPosition[i][1] = rand() % gameMapSize + 1;

			if ((gameJewelryPosition[i][0] == 1 && gameJewelryPosition[i][1] == 1))
				isJewelryPossible = false;

			if ((gameJewelryPosition[i][0] == gameEscape[1] && gameJewelryPosition[i][1] == gameEscape[0]))
				isJewelryPossible = false;

			for (int j = 0;j < gamesTalactiteCount;j++) {
				if (gameJewelryPosition[i][0] == gamesTalactitePosition[j][0] &&
					gameJewelryPosition[i][1] == gamesTalactitePosition[j][1]) {
					//만약 종유석 위치와 겹친다면
					isJewelryPossible = false;
					break;
				}
			}

			for (int j = 0;j < i;j++) {
				if (gameJewelryPosition[j][0] == gameJewelryPosition[i][0] &&
					gameJewelryPosition[j][1] == gameJewelryPosition[i][1]) {
					//만약 보석 위치와 겹친다면
					isJewelryPossible = false;
					break;
				}
			}
		} while (!isJewelryPossible);
		//보석의 위치가 플레이어/탈출 위치/벽/다른 종유석/시아 위치가 아닐 경우 저장 완료.

		//안전한 보석의 자리라면 보석으로 지정
		gameMap[gameJewelryPosition[i][0]][gameJewelryPosition[i][1]] = 'J';
		cout << gameJewelryPosition[i][0] << " " << gameJewelryPosition[i][1] << endl;

		//보석 점수 설정
		srand(time(NULL));
		gameJewelryScore[i] = gameJewelryBasicSocre[rand() % 3];

	}

	//회복 우물 위치

	// 이동 및 화면 갱신 
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
		gameKey = _getch();
		// 초기화
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = ' ';
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {								// sight
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {							// sight
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == ' ')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = '/';
			}
		}

		bool errPosition = 0; // 이동불가 에러 표시용

		// 플레이어 위치 변경 (switch문)
		switch (gameKey)
		{
		case 'W':
		case 'w':
			for (int j = 0;j < gamesTalactiteCount;j++) {
				if ((gamePlayerPosition[1] - 1) == gamesTalactitePosition[j][1] &&
					gamePlayerPosition[0] == gamesTalactitePosition[j][0]) {
					//만약 종유석 위치와 겹친다면
					errPosition = true;
					break;
				}
			}
			if (gamePlayerPosition[1] > 1 && !errPosition)
				gamePlayerPosition[1] -= 1;
			break;
		case 'A':
		case 'a':
			for (int j = 0;j < gamesTalactiteCount;j++) {
				if (gamePlayerPosition[1] == gamesTalactitePosition[j][1] &&
					(gamePlayerPosition[0]-1) == gamesTalactitePosition[j][0]) {
					//만약 종유석 위치와 겹친다면
					errPosition = true;
					break;
				}
			}
			if (gamePlayerPosition[0] > 1 && !errPosition)
				gamePlayerPosition[0] -= 1;
			break;
		case 'S':
		case 's':
			for (int j = 0;j < gamesTalactiteCount;j++) {
				if ((gamePlayerPosition[1]+1) == gamesTalactitePosition[j][1] &&
					gamePlayerPosition[0] == gamesTalactitePosition[j][0]) {
					//만약 종유석 위치와 겹친다면
					errPosition = true;
					break;
				}
			}
			if (gamePlayerPosition[1] < gameMapSize + 1 && !errPosition)
				gamePlayerPosition[1] += 1;
			break;
		case 'D':
		case 'd':
			for (int j = 0;j < gamesTalactiteCount;j++) {
				if (gamePlayerPosition[1] == gamesTalactitePosition[j][1] &&
					(gamePlayerPosition[0] + 1) == gamesTalactitePosition[j][0]) {
					//만약 종유석 위치와 겹친다면
					errPosition = true;
					break;
				}
			}
			if (gamePlayerPosition[1] < gameMapSize + 1 && !errPosition)
				gamePlayerPosition[0] += 1;
			break;
		default:
			errPosition = 1;
			break;
		}

		// 플레이어 위치 업로드
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// 플레이어 시야 지정 // sight
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}

		// 화면 갱신
		system("cls");

	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);


	cout << "탈출에 성공했습니다." << endl;
}
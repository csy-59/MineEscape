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
			(i == 0 || j == 0 || i == gameMapSize - 1 || j == gameMapSize - 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '/';
		}
	}

	//종유석 위치
	for (int i = 0; i < gamesTalactiteCount; i++) {
		do {
			srand(time(NULL));
			gamesTalactitePosition[i][0] = rand() % gameMapSize + 1;
			srand(time(NULL));
			gamesTalactitePosition[i][1] = rand() % gameMapSize + 1;
		} while ((gamesTalactitePosition[i][0] == 1 && gamesTalactitePosition[i][1] == 1) ||
			(gamesTalactitePosition[i][0] == gameEscape[0] && gamesTalactitePosition[i][1] == gameEscape[1]));
		//종유석의 위치가 플레이어/탈출 위치/벽/다른 종유석/시아 위치가 아닐 경우 저장 완료.

		//안전한 종유석의 자리라면 종유석으로 지정
		gameMap[gamesTalactitePosition[i][0]][gamesTalactitePosition[i][1]] = 'T';
	}



	//보석 위치

	//회복 우물 위치

	system("cls");

	do {
		// 초기화면 표시
		for (int j = 0; j < gameMapSize + 2; j++) // map
		{
			for (int i = 0; i < gameMapSize + 2; i++) // map
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}

		gameKey = _getch();

		// 대소문자 무관계 인식
		if (gameKey >= 97 && gameKey <= 122) // ASCII code a = 97, z = 122
		{
			gameKey -= 32;
		}
		bool errPosition = 0;

		// 플레이어 위치 변경 (switch문)
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

		// 이동 한계 (if문)
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

		// 플레이어 위치 업로드
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// 플레이어 시야 지정 // sight
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}

		// 화면 갱신
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

		// 이동 한계 출력
		if (gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] == 'T' || errPosition == 1)
			cout << "이동 불가" << endl;
		else
			cout << gameKey << endl;


	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);


	// 이동 및 화면 갱신
	//while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1])
	//{
	//	gameKey = _getch();
	//
	//	//초기화
	//	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = ' ';
	//	for (int i = -1; i < 2; i++) {
	//		for (int j = -1; j < 2; j++) {
	//			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == ' ')
	//				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = '/';
	//		}
	//	}
	//	// 대소문자 무관계 인식
	//	if (gameKey >= 97 && gameKey <= 122) // ASCII code a = 97, z = 122
	//	{
	//		gameKey -= 32;
	//	}
	//	bool errPosition = 0;
	//	
	//	// 플레이어 위치 변경 (switch문)
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
	//	// 이동 한계 (if문)
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
	//	// 플레이어 위치 업로드
	//	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';
	//
	//	// 플레이어 시야 지정 // sight
	//	for (int i = -1; i < 2; i++) {
	//		for (int j = -1; j < 2; j++) {
	//			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
	//				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
	//		}
	//	}
	//
	//	// 화면 갱신
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
	//	// 이동 한계 출력
	//	if (gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] == 'T' || errPosition == 1)
	//		cout << "이동 불가" << endl;
	//	else
	//		cout << gameKey << endl;
	//}

	cout << "탈출에 성공했습니다." << endl;
}
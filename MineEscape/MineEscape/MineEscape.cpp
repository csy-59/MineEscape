// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{	
	// 게임 난이도 설정 // map // sight
	int gameLevel[3] = {1, 2, 3};
	int inputGameLevel;
	char gameMap[20][20]{}; // map

	//cin >> inputGameLevel;

	//switch (inputGameLevel)
	//{
	//case 1:
	//	char gameMap[20][20]; // map
	//	int gameMapSize = 20;
	//	int gameSight = 3; // sight
	//	break;
	//case 2:
	//	char gameMap[20][20]; // map
	//	int gameMapSize = 20;
	//	int gameSight = 3; // sight
	//	break;
	//case 3:
	//	char gameMap[20][20]; // map
	//	int gameMapSize = 20;
	//	int gameSight = 3; // sight
	//	break;
	//}

	
	int gameEscape[2];
	int gamePlayerPosition[2] = { 1, 1 };
	char gameKey;
	int stamina = 10; // 남은횟수 추가
	bool gameOver = false;

	// 난수 생성, gameEscape 설정
	// x축
	srand(time(NULL));
	gameEscape[0] = rand();
	srand(time(NULL));
	gameEscape[0] += rand();
	gameEscape[0] %= 20; // map

	// y축
	srand(time(NULL));
	gameEscape[1] = rand();
	srand(time(NULL));
	gameEscape[1] += rand();
	gameEscape[1] %= 20; // map

	// gameEscape = {0, 0} 제외
	while (gameEscape[0] == 0 || gameEscape[1] == 0 || gameEscape[0] == 19 || gameEscape[1] == 19 || (gameEscape[0] == 1 && gameEscape[1] == 1))
	{
		gameEscape[0] = rand();
		gameEscape[0] %= 20; // map
		gameEscape[1] = rand();
		gameEscape[1] %= 20; // map
	}

	// gameMap 초기화
	for (int j = 0; j < 20; j++) // map
	{
		for (int i = 0; i < 20; i++) // map
		{
			(i == 0 || j == 0 || i == 19 || j == 19) ? gameMap[j][i] = '*' : gameMap[j][i] = '/';
		}
	}

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

	// 초기화면 표시
	for (int j = 0; j < 20; j++) // map
	{
		for (int i = 0; i < 20; i++) // map
		{
			cout << gameMap[i][j];
		}
		cout << endl;
	}

	// 이동 및 화면 갱신
	while (!gameOver)
	{
		gameKey = _getch();

		//초기화
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = ' ';
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == ' ')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = '/';
			}
		}
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
			--stamina;
			break;
		case 'A':
			gamePlayerPosition[0] -= 1;
			--stamina;

			break;
		case 'S':
			gamePlayerPosition[1] += 1;
			--stamina;

			break;
		case 'D':
			gamePlayerPosition[0] += 1;
			--stamina;

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
		//gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]
		
		//게임 종료 반복문
		if (gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] == gameMap[gameEscape[0]][gameEscape[1]])
		{
			gameOver = true;
		}
		// 이동 한계 출력
		errPosition == 1 ? cout << "이동 불가" << endl : cout << gameKey << endl;
		cout << "남은횟수" << stamina << endl;
		if (stamina == 0)
		{
			gameOver = true;
			cout << "탈출에 실패 했습니다." << endl;
		}
	}
	cout << "게임종료" << endl;
}
// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{

	int inputMapLevel, inputSightLevel;
	cin >> inputMapLevel >> inputSightLevel;
	int gameMapSize;
	char gameMap[42][42] = { ' ' };
	int gameSight;
	int gameEscape[2];
	int gamePlayerPosition[2] = { 1, 1 };
	int gameItem[2][4];
	int gameItemCount = 4;
	int gamePlayerChance = 20;
	char wellLocation = '#';

	char gameKey;

	// 게임 난이도 설정 // map // sight
	switch (inputMapLevel)
	{
	case 1:
		gameMapSize = 20; // map
		break;
	case 2:
		gameMapSize = 30; // map
		break;
	case 3:
		gameMapSize = 40; // map
		break;
	}

	switch (inputSightLevel)
	{
	case 1:
		gameSight = 3; // sight
		break;
	case 2:
		gameSight = 2; // sight
		break;
	case 3:
		gameSight = 1; // sight
		break;
	}






	//탈출 위치 지정
	do {
		srand(time(NULL));
		gameEscape[0] = rand() % gameMapSize + 1;
		srand(time(NULL));
		gameEscape[1] = rand() % gameMapSize + 1;
	} while (gameEscape[0] == 1 && gameEscape[1] == 1);

	//아이템 위치 지정
	for (int i = 0; i < gameItemCount; i++) {
		do {
			gameItem[0][i] = rand() % gameMapSize + 1;
			gameItem[1][i] = rand() % gameMapSize + 1;
		} while (gameItem[0][i] == 1 && gameItem[1][i] == 1);
	}

	


	// gameMap 초기화
	for (int j = 0; j < gameMapSize + 2; j++) // map
	{
		for (int i = 0; i < gameMapSize + 2; i++) // map
		{
			(i == 0 || j == 0 || i == gameMapSize + 1 || j == gameMapSize + 1) ? gameMap[j][i] = '*' : gameMap[j][i] = '/'; // map
		}
	}

	// 탈출지점(gameEscape) 저장
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	for (int i = 0; i < gameItemCount; i++) {
		gameMap[gameItem[0][i]][gameItem[1][i]] = 'I';
	}


	// 플레이어 위치(gamePlayerPosition) 지정
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// 플레이어 초기 시야 지정
	for (int i = -1 * gameSight; i < gameSight + 1; i++) {				// sight
		for (int j = -1 * gameSight; j < gameSight + 1; j++) {			// sight
			if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
				gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
		}
	}



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
			gamePlayerPosition[1] -= 1;
			gamePlayerChance--;
			break;
		case 'A':
		case 'a':
			gamePlayerPosition[0] -= 1;
			gamePlayerChance--;
			break;
		case 'S':
		case 's':
			gamePlayerPosition[1] += 1;
			gamePlayerChance--;
			break;
		case 'D':
		case 'd':
			gamePlayerPosition[0] += 1;
			gamePlayerChance--;
			break;
		default:
			errPosition = 1;
			break;
		}

		// 이동 한계 (if문)
		if (gamePlayerPosition[0] > gameMapSize) // map
		{
			gamePlayerPosition[0] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[0] < 1)
		{
			gamePlayerPosition[0] += 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] > gameMapSize) // map
		{
			gamePlayerPosition[1] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] < 1)
		{
			gamePlayerPosition[1] += 1;
			errPosition = 1;
		}



		// 플레이어 시야 지정 // sight
		for (int i = -1 * gameSight; i < gameSight + 1; i++) {
			for (int j = -1 * gameSight; j < gameSight + 1; j++) {
				if (gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] == '/')
					gameMap[gamePlayerPosition[0] + i][gamePlayerPosition[1] + j] = ' ';
			}
		}
		//우물 위치 지정
		gameMap[gameMapSize/2][gameMapSize/2] = wellLocation;
		// 플레이어 위치 업로드
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';
		for (int i = 0; i < gameItemCount; i++)
			if (gamePlayerPosition[0] == gameItem[0][i] && gamePlayerPosition[1] == gameItem[1][i]) {
				gameSight+=2;
			}
		if (gamePlayerPosition[0] == gameMap[gameMapSize / 2][gameMapSize / 2] && gamePlayerPosition[1] == [gameMapSize / 2][gameMapSize / 2]) {
			gamePlayerChance = 20;
		}
		

				// 화면 갱신
				system("cls");

		// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;
		// 이동 한계 출력
		errPosition == 1 ? cout << "이동 불가" << endl : cout << gameKey << "\t" << gamePlayerChance << endl;
		
	} while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1]);

	cout << "탈출에 성공했습니다." << endl;
}
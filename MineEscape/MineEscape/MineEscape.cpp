// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
	char gameMap[10][10];
	int gameEscape[2];
	int gamePlayerPosition[2] = { 0, 0 };
	char gameKey;

	// 난수 생성, gameEscape 설정
	// x축
	srand(time(NULL));
	gameEscape[0] = rand();
	srand(time(NULL));
	gameEscape[0] += rand();
	gameEscape[0] %= 10;

	// y축
	srand(time(NULL));
	gameEscape[1] = rand();
	srand(time(NULL));
	gameEscape[1] += rand();
	gameEscape[1] %= 10;

	// gameEscape = {0, 0} 제외
	while (gameEscape[0] == 0 && gameEscape[1] == 0)
	{
		gameEscape[0] = rand();
		gameEscape[0] %= 10;
		gameEscape[1] = rand();
		gameEscape[1] %= 10;
	}

	// gameMap 초기화
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			gameMap[j][i] = '#';
		}
	}

	// 탈출지점(gameEscape) 표시
	gameMap[gameEscape[0]][gameEscape[1]] = 'E';

	// 플레이어 위치(gamePlayerPosition) 표시
	gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

	// 초기화면 표시
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			cout << gameMap[i][j];
		}
		cout << endl;
	}

	// 이동 및 화면 갱신
	while (gamePlayerPosition[0] != gameEscape[0] || gamePlayerPosition[1] != gameEscape[1])
	{
		gameKey = _getch();

		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = '#';
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
		if (gamePlayerPosition[0] > 9)
		{
			gamePlayerPosition[0] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[0] < 0)
		{
			gamePlayerPosition[0] += 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] > 9)
		{
			gamePlayerPosition[1] -= 1;
			errPosition = 1;
		}
		else if (gamePlayerPosition[1] < 0)
		{
			gamePlayerPosition[1] += 1;
			errPosition = 1;
		}

		// 플레이어 위치 업로드
		gameMap[gamePlayerPosition[0]][gamePlayerPosition[1]] = 'O';

		// 화면 갱신
		system("cls");

		// cout << gamePlayerPosition[0] << gamePlayerPosition[1] << endl;

		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				cout << gameMap[i][j];
			}
			cout << endl;
		}
		// 이동 한계 출력
		errPosition == 1 ? cout << "이동 불가" << endl : cout << gameKey << endl;
	}

	cout << "탈출에 성공했습니다." << endl;
}
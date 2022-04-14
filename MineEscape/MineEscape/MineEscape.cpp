// MineEscape.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;


int main()
{
    int playerX, playerY, escapeX, escapeY, inputKey;
    srand(time(NULL));
    escapeX = rand() % 9 + 1;
    escapeY = rand() % 9 + 1;
    playerX = 1;
    playerY = 1;
    char array[12][12] = {};
    char playerSight = ' ';

    while (1) {
        for (int i = 1; i < 11; i++) {
            for (int j = 1; j < 11; j++) {
                array[i][j] = '#';
            }
        }
        
        
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                array[playerX + i][playerY + j] = playerSight;
            }
        }
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                if((i==0 || i==11) || (j==0) || (j==11))
                array[i][j] = '*';
            }
            
        }
        array[escapeX][escapeY] = 'E';
        array[playerX][playerY] = 'O';
        
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                cout << (char)array[i][j];
            }
            cout << endl;
        }


        
        
        


        if (playerX == escapeX && playerY == escapeY) {
            cout << "탈출에 성공했습니다!!!" << endl;
            //break;
        }
        inputKey = _getch();
        switch (inputKey) {
        case 97:
            if (playerY <= 1) {
                break;
            }
            playerY--;
            break; // 왼쪽으로 가유~
        case 115:
            if (playerX >= 10) {
                break;
            }
            playerX++;
            break; // 아래로 가유~
        case 100:
            if (playerY >= 10) {
                break;
            }
            playerY++;
            break; // 오른쪽으로 가유~
        case 119:
            if (playerX <= 1) {
                break;
            }
            playerX--;
            break; // 위로 가유~
        }

        system("cls");
    }
}
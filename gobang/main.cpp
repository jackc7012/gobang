#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <string>

#include "GoBang.h"

void * hd = nullptr;
const int window_width = 600;
const int window_height = 500;

int main(){
	CGoBang m_gobang;
	int game_type = 1;
	m_gobang.InitGraph(hd, game_type, window_width, window_height);
	m_gobang.DrawBackground(hd);
	m_gobang.PlayGame(hd);
	system("pause");
	return 0;
}
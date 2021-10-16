#ifndef __GO_BANG_H__
#define __GO_BANG_H__

#include <graphics.h>
#include <thread>
#include <chrono>

const int checker_board_x = 15;
const int checker_board_y = 15;
const int checker_board_width = 30;
const int checker_radius = 12;
const int coordinate[] = {30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360, 390, 420, 450};

enum Player 
{
	NONE,
	PLAYER,
	ADVERSARY,
};

enum CheckerScore
{
	ONECHESS = 1,
	TWOCHESS = 3,
	ALIVETHREECHESS = 7,
	THREECHESS = 10,
	ALIVEFOURCHESS = 13,
	FOURCHESS = 15,
};

struct CheckerLocation
{
	int x_;
	int y_;
	CheckerLocation()
	{
		x_ = -1;
		y_ = -1;
	}
};

class CGoBang
{
public:
	CGoBang(void);
	~CGoBang(void);

	void InitGraph(void *hd_, const int type_, const int width_, const int height_);

	bool DrawBackground(void* hd_);

	bool PlayGame(void* hd_);

private:
	void FindLocation(const int x_, const int y_);

	void JudgeLocation(const int x_, const int y_, CheckerLocation &checkerlocation_);

	void DrawChecker(const Player player_, const int x_, const int y_);

	bool JudgeWin(const Player player_, CheckerLocation &checkerlocation_);

	void JudgeAdversary();

private:
	int type_;
	int rounds_;
	int window_width_;
	int window_height_;
	int game_width_;
	int game_height_;
	Player checker_board_[checker_board_x][checker_board_y];
	Player now_turn_;
	CheckerLocation player_location_;
	int checker_score_[checker_board_x][checker_board_y];
};
#endif // !__GO_BANG_H__



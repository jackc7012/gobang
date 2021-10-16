#include "GoBang.h"


CGoBang::CGoBang(void)
{
	type_ = 0;
	rounds_ = 0;
	window_width_ = window_height_ = -1;
	game_width_ = game_height_ = 1;
	memset(checker_board_, NONE, sizeof(checker_board_));
	memset(checker_score_, 0, sizeof(checker_score_));
	now_turn_ = NONE;
}


CGoBang::~CGoBang(void)
{
}

void CGoBang::InitGraph(void *hd_, const int type_, const int width_, const int height_)
{
	HWND hd = initgraph(width_, height_);
	window_width_ = width_;
	window_height_ = height_;
	hd_ = hd;
	game_width_ = (checker_board_x + 1) * checker_board_width;
	game_height_ = (checker_board_y + 1) * checker_board_width;
	now_turn_ = ((type_ == 1) ? PLAYER : ADVERSARY);
	std::thread thr(std::bind(&CGoBang::JudgeAdversary, this));
	thr.detach();
}

bool CGoBang::DrawBackground(void* hd_)
{
	setbkcolor(LIGHTGRAY);
	cleardevice();

	for (int i = 0; i <= game_width_; i += checker_board_width)
	{
		line(i, 0, i, game_height_);
	}

	for (int i = 0; i <= game_height_; i += checker_board_width)
	{
		line(0, i, game_width_, i);
	}
	return true;
}

bool CGoBang::PlayGame(void* hd_)
{
	MOUSEMSG mmsg;
	while (1)
	{
		mmsg = GetMouseMsg();
		if (WM_LBUTTONUP == mmsg.uMsg && now_turn_ == PLAYER)
		{
			FindLocation(mmsg.x, mmsg.y);
		}
	}
	
	return true;
}

void CGoBang::FindLocation(const int x_, const int y_)
{
	CheckerLocation checklocation;
	JudgeLocation(x_, y_, checklocation);
	player_location_.x_ = checklocation.x_;
	player_location_.y_ = checklocation.y_;
	if (checklocation.x_ != -1 && checklocation.y_ != -1)
	{
		DrawChecker(PLAYER, checklocation.x_, checklocation.y_);
	}	
}

void CGoBang::JudgeLocation(const int x_, const int y_, CheckerLocation &checkerlocation_)
{
	int left = 0, right = sizeof(coordinate) / sizeof(coordinate[0]), mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (x_ > coordinate[mid] + 10)
		{
			left = mid;
		}
		else if (x_ < coordinate[mid] - 10)
		{
			right = mid;
		}
		else if ((x_ > (coordinate[mid] - 10)) && (x_ < (coordinate[mid] + 10)))
		{
			checkerlocation_.x_ = mid;
			break;
		}	
	}

	left = 0, right = sizeof(coordinate) / sizeof(coordinate[0]);
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (y_ > coordinate[mid] + 10)
		{
			left = mid;
		}
		else if (y_ < coordinate[mid] - 10)
		{
			right = mid;
		}
		else if ((y_ > (coordinate[mid] - 10)) && (y_ < (coordinate[mid] + 10)))
		{
			checkerlocation_.y_ = mid;
			break;
		}
	}
}

void CGoBang::DrawChecker(const Player player_, const int x_, const int y_)
{
	setfillcolor(player_ == PLAYER ? BLACK : WHITE);
	setlinecolor(player_ == PLAYER ? BLACK : WHITE);
	fillcircle(coordinate[x_], coordinate[y_], checker_radius);
	checker_board_[x_][y_] = player_;
	now_turn_ = ADVERSARY;
}

bool CGoBang::JudgeWin(const Player player_, CheckerLocation &checkerlocation_)
{
	int location_x = checkerlocation_.x_;
	int location_y = checkerlocation_.y_;
	int chess_count = 0;
	//  横
	if (location_y - 4 >= 0)
	{
		for (int y = location_y - 4; y < checker_board_x; ++y)
		{
			if (checker_board_[location_x][y] == player_)
			{
				chess_count += 1;
				if (chess_count == 5)
					return true;
			}				
		}
	}
	else if (location_y + 4 <= checker_board_y)
	{
		for (int y = 0; y < location_y + 4; ++y)
		{
			if (checker_board_[location_x][y] == player_)
			{
				chess_count += 1;
					if (chess_count == 5)
						return true;
			}
		}
	}
	else
	{
		for (int y = 0; y < location_y + 4; ++y)
		{
			if (checker_board_[location_x][y] == player_)
			{
				chess_count += 1;
				if (chess_count == 5)
					return true;
			}
		}
	}
	//  竖
	//  左对角线
	//  右对角线
	
}


void CGoBang::JudgeAdversary()
{
	int max_x = -1, max_y = -1, max_sum = 0;
	while (1)
	{
		if (now_turn_ == ADVERSARY)
		{	
			for (int x = 0; x < checker_board_x; ++x)
			{
				for (int y = 0; y < checker_board_y; ++y)
				{
					if (checker_board_[x][y] == PLAYER)
					{
						if ((x - 1 >= 0) && (y - 1 >= 0) && checker_board_[x - 1][y - 1] == NONE) 
							checker_score_[x - 1][y - 1] += 1;
						if ((y - 1 >= 0) && checker_board_[x][y - 1] == NONE) 
							checker_score_[x][y - 1] += 1;
						if ((x + 1 <= checker_board_y) && (y - 1 >= 0) && checker_board_[x + 1][y - 1] == NONE) 
							checker_score_[x + 1][y - 1] += 1;
						if ((x - 1 >= 0) && checker_board_[x - 1][y] == NONE) 
							checker_score_[x - 1][y] += 1;
						if ((x + 1 <= checker_board_y) && checker_board_[x + 1][y] == NONE) 
							checker_score_[x + 1][y] += 1;
						if ((x - 1 >= 0) && (y + 1 <= checker_board_x) && checker_board_[x - 1][y + 1] == NONE) 
							checker_score_[x - 1][y + 1] += 1;
						if ((y + 1 <= checker_board_x) && checker_board_[x][y + 1] == NONE) 
							checker_score_[x][y + 1] += 1;
						if ((x + 1 <= checker_board_y) && (y + 1 <= checker_board_x) && checker_board_[x + 1][y + 1] == NONE) 
							checker_score_[x + 1][y + 1] += 1;
					}
				}
			}
			max_sum = 0;
			for (int x = 0; x < checker_board_x; ++x)
			{
				for (int y = 0; y < checker_board_y; ++y)
				{
					if (checker_board_[x][y] == NONE && checker_score_[x][y] > max_sum)
					{
						max_sum = checker_score_[x][y];
						max_x = x;
						max_y = y;
					}
				}
			}
			DrawChecker(ADVERSARY, max_x, max_y);
			now_turn_ = PLAYER;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}


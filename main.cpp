#include <sstream> 
#include <iostream> 
#include <iomanip>


class Othello
{

private:
	int map[8][8];

	int turn = -1;

	void draw() {
		std::system("cls");

		for (int i = 0; i < 8; i++) {
			std::cout << "-------------------------\n";
			for (int j = 0; j < 8; j++) {
				int cell = map[i][j];
				std::cout << "|" << std::setw(2) << (cell == 0 ? " " : cell == -1 ? "o" : cell == -2 ? "*" : std::to_string(cell));
			}
			std::cout << "|\n";
		}
		std::cout << "-------------------------\n";

		if (game_end) {
			int wc = 0;
			int bc = 0;

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					int cell = map[i][j];
					if (cell == -1) {
						wc++;
					}
					if (cell == -2) {
						bc++;
					}
				}
			}

			std::cout << "White:" << wc << "     Black:" << bc;
		}
		else {
			std::cout << "NowPlayer[" << (turn == -1 ? "o" : "*") << "]";
		}
	}

	short check(int num = 0) {

		bool search = num > 0 ? true : false;
		short flag = 0;

		for (int i = 0; i < 8 && !search; i++) {
			for (int j = 0; j < 8; j++) {
				int cell = map[i][j];
				if (cell > 0) {
					map[i][j] = 0;
				}
			}
		}

		int enemy = turn == -1 ? -2 : -1;

		int play_num = 1;
		bool alive = false;
		int space = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				int cell = map[i][j];

				if (cell == enemy) {
					alive = true;
				}

				if (cell != 0) {
					space++;
				}

				if (cell != num && search) {
					continue;
				}

				if (cell >= 0) {
					if (i > 0) {
						if (enemy == map[i - 1][j]){
							for (int k = 2; i - k > -1; k++) {
								if (turn == map[i - k][j])
								{
									flag |= (1 << 0);

								}
								else if (0 <= map[i - k][j]) {
									break;
								}
							}
						}
					}
					if (i < 8) {
						if (enemy == map[i + 1][j]) {
							for (int k = 2; i + k < 8; k++) {
								if (turn == map[i + k][j])
								{
									flag |= (1 << 1);
								}
								else if (0 <= map[i + k][j]) {
									break;
								}
							}
						}
					}
					if (j > 0) {
						if (enemy == map[i][j - 1]) {
							for (int k = 2; j - k > -1; k++) {
								if (turn == map[i][j - k])
								{
									flag |= (1 << 2);
								}
								else if (0 <= map[i][j - k]) {
									break;
								}
							}
						}
					}
					if (j < 8) {
						if (enemy == map[i][j + 1]) {
							for (int k = 2; j + k < 8; k++) {
								if (turn == map[i][j + k])
								{
									flag |= (1 << 3);
								}
								else if (0 <= map[i][j + k]) {
									break;
								}
							}
						}
					}
					if (i > 0 && j > 0) {
						if (enemy == map[i - 1][j - 1]) {
							for (int k = 2; i - k > -1 && j - k > -1; k++) {
								if (turn == map[i - k][j - k])
								{
									flag |= (1 << 4);
								}
								else if (0 <= map[i - k][j - k]) {
									break;
								}
							}
						}
					}
					if (i < 8 && j < 8) {
						if (enemy == map[i + 1][j + 1]) {
							for (int k = 2; i + k < 8 && j + k < 8; k++) {
								if (turn == map[i + k][j + k])
								{
									flag |= (1 << 5);
								}
								else if (0 <= map[i + k][j + k]) {
									break;
								}
							}
						}
					}
					if (i > 0 && j < 8) {
						if (enemy == map[i - 1][j + 1]) {
							for (int k = 2; i - k > -1 && j + k < 8; k++) {
								if (turn == map[i - k][j + k])
								{
									flag |= (1 << 6);
								}
								else if (0 <= map[i - k][j + k]) {
									break;
								}
							}
						}
					}
					if (i < 8 && j > 0) {
						if (enemy == map[i + 1][j - 1]) {
							for (int k = 2; i + k < 8 && j - k > -1; k++) {
								if (turn == map[i + k][j - k])
								{
									flag |= (1 << 7);
								}
								else if (0 <= map[i + k][j - k]) {
									break;
								}
							}
						}
					}

					if (flag != 0 && !search) {
						map[i][j] = play_num++;
						flag = 0;
					}
				}
			}
		}
		
		if (play_num == 1 && !search) {
			if (!alive || space >= 64) {
				reslut();
				return flag;
			}
			turn = turn == -1 ? -2 : -1;
			check();
		}

		return flag;
	}

	void reslut() {
		game_end = true;
	}

public:
	bool game_end = false;
	int init() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				map[i][j] = 0;
			}
		}

		map[3][3] = -1;
		map[3][4] = -2;
		map[4][3] = -2;
		map[4][4] = -1;

		check();
		draw();

		return 0;
	}

	void play(int num) {

		int enemy = turn == -1 ? -2 : -1;

		short flag = check(num);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (num == map[i][j]) {

					if (i > 0) {
						if (flag & (1 << 0)) {
							for (int k = 1; i - k > -1; k++) {
								if (turn == map[i - k][j])
								{
									break;
								}
								else if (0 <= map[i - k][j]) {
									break;
								}
								map[i - k][j] = turn;
							}
						}
					}
					if (i < 8) {
						if (flag & (1 << 1)) {
							for (int k = 1; i + k < 8; k++) {
								if (turn == map[i + k][j])
								{
									break;
								}
								else if (0 <= map[i + k][j]) {
									break;
								}
								map[i + k][j] = turn;
							}
						}
					}
					if (j > 0) {
						if (flag & (1 << 2)) {
							for (int k = 1; j - k > -1; k++) {
								if (turn == map[i][j - k])
								{
									break;
								}
								else if (0 <= map[i][j - k]) {
									break;
								}
								map[i][j - k] = turn;
							}
						}
					}
					if (j < 8) {
						if (flag & (1 << 3)) {
							for (int k = 1; j + k < 8; k++) {
								if (turn == map[i][j + k])
								{
									break;
								}
								else if (0 <= map[i][j + k]) {
									break;
								}
								map[i][j + k] = turn;
							}
						}
					}
					if (i > 0 && j > 0) {
						if (flag & (1 << 4)) {
							for (int k = 1; i - k > -1 && j - k > -1; k++) {
								if (turn == map[i - k][j - k])
								{
									break;
								}
								else if (0 <= map[i - k][j - k]) {
									break;
								}
								map[i - k][j - k] = turn;
							}
						}
					}
					if (i < 8 && j < 8) {
						if (flag & (1 << 5)) {
							for (int k = 1; i + k < 8 && j + k < 8; k++) {
								if (turn == map[i + k][j + k])
								{
									break;
								}
								else if (0 <= map[i + k][j + k]) {
									break;
								}
								map[i + k][j + k] = turn;
							}
						}
					}
					if (i > 0 && j < 8) {
						if (flag & (1 << 6)) {
							for (int k = 1; i - k > -1 && j + k < 8; k++) {
								if (turn == map[i - k][j + k])
								{
									break;
								}
								else if (0 <= map[i - k][j + k]) {
									break;
								}
								map[i - k][j + k] = turn;
							}
						}
					}
					if (i < 8 && j > 0) {
						if (flag & (1 << 7)) {
							for (int k = 1; i + k < 8 && j - k > -1; k++) {
								if (turn == map[i + k][j - k])
								{
									break;
								}
								else if (0 <= map[i + k][j - k]) {
									break;
								}
								map[i + k][j - k] = turn;
							}
						}
					}

					map[i][j] = turn;

					goto exit;
				}
			}
		}
		exit:

		turn = enemy;

		check();
		draw();
	}
};

int main() {
	Othello o;
	o.init();
	for (;!o.game_end;) {
		int num;
		std::cin >> num;
		o.play(num);
	}

	std::cin;
	return 0;
}
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(200);


    WINDOW* game_window = newwin(20, 40, 5, 10);
    box(game_window, 0, 0);

    int snake_length = 5;
    int head_x = 5;
    int head_y = 5;
    int move_x = 1;
    int move_y = 0;
    int score = 0;

    bool game_over = false;
    bool eats = false;

    vector<vector<int>> snake_positions = {
        {head_x, head_y},
        {head_x - 1, head_y},
        {head_x - 2, head_y},
        {head_x - 3, head_y},
        {head_x - 4, head_y}
    };

    vector<int> food = {
        rand() % 18 + 1,
        rand() % 38 + 1
    };


    while (true) {


        if (game_over) {
            werase(game_window);
            box(game_window, 0, 0);
            mvwprintw(game_window, 8, 10, "GAME OVER");
            mvwprintw(game_window, 10, 8, "Score: %d", score);
            mvwprintw(game_window, 12, 5, "Press 'r' to restart");
            mvwprintw(game_window, 13, 5, "Press 'q' to quit");
            wrefresh(game_window);

            int ch;
            while (true) {
                ch = getch();
                if (ch == 'q') {
                    endwin();
                    return 0;
                }
                if (ch == 'r') {
                    snake_length = 5;
                    head_x = 5;
                    head_y = 5;
                    move_x = 1;
                    move_y = 0;
                    score = 0;

                    snake_positions = {
                        {head_x, head_y},
                        {head_x - 1, head_y},
                        {head_x - 2, head_y},
                        {head_x - 3, head_y},
                        {head_x - 4, head_y}
                    };

                   food  = {rand() % 18 + 1, rand() % 38 + 1};

                    game_over = false;
                    break;
                }
            }
        }

        werase(game_window);
        box(game_window, 0, 0);
        mvprintw(2, 10, "Score: %d", score);

        int ch = getch();

        if (ch == KEY_UP && move_y != 1) {
            move_x = 0; move_y = -1;
        }
        else if (ch == KEY_DOWN && move_y != -1) {
            move_x = 0; move_y = 1;
        }
        else if (ch == KEY_LEFT && move_x != 1) {
            move_x = -1; move_y = 0;
        }
        else if (ch == KEY_RIGHT && move_x != -1) {
            move_x = 1; move_y = 0;
        }

        head_x += move_x;
        head_y += move_y;

        if (head_x <= 0 || head_x >= 39 || head_y <= 0 || head_y >= 19) {
            game_over = true;
            continue;
        }


        for (int i = snake_length - 1; i > 0; i--) {
            snake_positions[i] = snake_positions[i - 1];
        }
        snake_positions[0] = {head_x, head_y};

  
        for (int i = 1; i < snake_length; i++) {
            if (snake_positions[i] == snake_positions[0]) {
                game_over = true;
            }
        }

\
        if (head_y == food[0] && head_x == food[1]) {
            score++;
            snake_length++;
            snake_positions.push_back(snake_positions.back());

            while (true) {
                food = {rand() % 18 + 1, rand() % 38 + 1};
                bool ok = true;
                for (auto &p : snake_positions) {
                    if (p[0] == food[1] && p[1] == food[0]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) break;
            }
        }

        mvwprintw(game_window, food[0], food[1], "*");
        
        mvwprintw(game_window, head_y, head_x, "O");
        for (int i = 1; i < snake_length; i++) {
            mvwprintw(game_window,
                      snake_positions[i][1],
                      snake_positions[i][0],
                      ".");
        }

        wrefresh(game_window);
    }

    endwin();
    return 0;
}
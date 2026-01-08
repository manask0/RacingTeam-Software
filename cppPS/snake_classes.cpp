#include <ncurses.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


class Snake {
public:
    int snake_length;
    int head_x, head_y;
    int move_x, move_y;
    vector<vector<int>> snake_positions;

    Snake() {
        reset();
    }

    void reset() {
        snake_length = 5;
        head_x = 5;
        head_y = 5;
        move_x = 1;
        move_y = 0;

        snake_positions = {
            {head_x, head_y},
            {head_x - 1, head_y},
            {head_x - 2, head_y},
            {head_x - 3, head_y},
            {head_x - 4, head_y}
        };
    }

    void move() {
        head_x += move_x;
        head_y += move_y;

        for (int i = snake_length - 1; i > 0; i--) {
            snake_positions[i] = snake_positions[i - 1];
        }
        snake_positions[0] = {head_x, head_y};
    }

    bool hitsWall() {
        return (head_x <= 0 || head_x >= 39 || head_y <= 0 || head_y >= 19);
    }

    bool hitsSelf() {
        for (int i = 1; i < snake_length; i++) {
            if (snake_positions[i] == snake_positions[0]) {
                return true;
            }
        }
        return false;
    }

    void grow() {
        snake_length++;
        snake_positions.push_back(snake_positions.back());
    }

    void draw(WINDOW* win) {
        mvwprintw(win, head_y, head_x, "O");
        for (int i = 1; i < snake_length; i++) {
            mvwprintw(win,
                      snake_positions[i][1],
                      snake_positions[i][0],
                      ".");
        }
    }
};

class Food {
public:
    vector<int> pos;

    Food() {
        respawn();
    }

    void respawn() {
        pos = {rand() % 18 + 1, rand() % 38 + 1};
    }

    void respawnSafe(const vector<vector<int>>& snake_positions) {
        while (true) {
            pos = {rand() % 18 + 1, rand() % 38 + 1};
            bool ok = true;
            for (auto &p : snake_positions) {
                if (p[0] == pos[1] && p[1] == pos[0]) {
                    ok = false;
                    break;
                }
            }
            if (ok) break;
        }
    }

    void draw(WINDOW* win) {
        mvwprintw(win, pos[0], pos[1], "*");
    }
};


class Game {
public:
    WINDOW* game_window;
    Snake snake;
    Food food;
    int score;
    bool game_over;

    Game() {
        init();
    }

    void init() {
        initscr();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        timeout(200);

        game_window = newwin(20, 40, 5, 10);
        box(game_window, 0, 0);

        srand(time(0));

        score = 0;
        game_over = false;
    }

    void restart() {
        snake.reset();
        food.respawn();
        score = 0;
        game_over = false;
    }

    void handleInput(int ch) {
        if (ch == KEY_UP && snake.move_y != 1) {
            snake.move_x = 0; snake.move_y = -1;
        }
        else if (ch == KEY_DOWN && snake.move_y != -1) {
            snake.move_x = 0; snake.move_y = 1;
        }
        else if (ch == KEY_LEFT && snake.move_x != 1) {
            snake.move_x = -1; snake.move_y = 0;
        }
        else if (ch == KEY_RIGHT && snake.move_x != -1) {
            snake.move_x = 1; snake.move_y = 0;
        }
    }

    void update() {
        snake.move();

        if (snake.hitsWall()) {
            game_over = true;
            return;
        }

        if (snake.hitsSelf()) {
            game_over = true;
            return;
        }

        if (snake.head_y == food.pos[0] && snake.head_x == food.pos[1]) {
            score++;
            snake.grow();
            food.respawnSafe(snake.snake_positions);
        }
    }

    void draw() {
        werase(game_window);
        box(game_window, 0, 0);
        mvprintw(2, 10, "Score: %d", score);

        food.draw(game_window);
        snake.draw(game_window);

        wrefresh(game_window);
    }

    void gameOverScreen() {
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
                exit(0);
            }
            if (ch == 'r') {
                restart();
                break;
            }
        }
    }

    void run() {
        while (true) {
            if (game_over) {
                gameOverScreen();
            }

            int ch = getch();
            handleInput(ch);

            update();
            draw();
        }
    }
};

int main() {
    Game game;
    game.run();
    endwin();
    return 0;
}

// Wrote snake.cpp on my own (without OOP). Used AI to implement snake_classes.cpp with OOP.
// Possible Addition - assign random number to food, based on which length of snake increases differently.
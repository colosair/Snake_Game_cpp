#include "Game.h"

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    
    int win_height = 27;
    int win_width = 50;
    WINDOW* game_win = newwin(win_height, win_width, 3, 3);

    Game game(game_win);
    game.gameStart();
    
    return 0;
}

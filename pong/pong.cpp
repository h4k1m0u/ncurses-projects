#include <ncurses.h>
#include <unistd.h>

/*
 * Hello world: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
 * Tutorial1: https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/
 * Tutorial2: https://www.viget.com/articles/c-games-in-ncurses-using-multiple-windows/
 */

// 30 FPS => 33.33 ms/frame
#define DELAY 60000

int main() {
    // screen dimensions
    int n_rows, n_cols;
    int border_size = 1;
    
    // score
    int score_size = 3;
    int score = 0;

    // initial ball coordinates & speed
    int x = 1;
    int y = 1;
    int speed_x = 1;
    int speed_y = 1;

    // initialize library
    initscr();
    getmaxyx(stdscr, n_rows, n_cols);

    // remove cursor & echo
    curs_set(FALSE);
    noecho();

    // initialize windows
    WINDOW *window_field = newwin(n_rows - score_size, n_cols, 0, 0);
    WINDOW *window_score = newwin(score_size, n_cols, n_rows - score_size, 0);

    // main loop
    while(1) {
        // update field window
        wclear(window_field);
        box(window_field, 0, 0);
        mvwprintw(window_field, y, x, "o");
        wrefresh(window_field);

        // update score window
        wclear(window_score);
        box(window_score, 0, 0);
        mvwprintw(window_score, 1, 1, "Score: %d", score);
        wrefresh(window_score);

        usleep(DELAY);

        // move ball
        x += speed_x;
        y += speed_y;
        
        // increment score when bouncing against wall
        if (x >= n_cols - border_size || x <= border_size) {
            speed_x *= -1;
            score++;
        }
        if (y >= n_rows - score_size - border_size || y <= border_size) {
            speed_y *= -1;
            score++;
        }
    }

    // clean up & back to terminal mode
    delwin(window_field);
    delwin(window_score);
    endwin();
    
    return 0;
}

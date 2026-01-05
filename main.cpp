#include <ncurses.h>
#include <vector>
#include <string>

size_t i_selected = 0;

const int BORDER_THICKNESS = 1;
const int PADDING_X = 10;
const int PADDING_Y = 5;

static size_t get_menu_width(const std::vector<std::string>& menu) {
  size_t width = 0;

  for (const std::string& menu_item : menu) {
    width = std::max(menu_item.size(), width);
  }

  return width;
}

static void draw_menu(WINDOW* win, const std::vector<std::string>& menu) {
  for (size_t i = 0; i < menu.size(); ++i) {
    const std::string& menu_item = menu[i];

    if (i == i_selected)
      wattr_on(win, A_REVERSE | A_BOLD | COLOR_PAIR(1), NULL);
    else
      wattr_off(win, A_REVERSE | A_BOLD | COLOR_PAIR(1), NULL);

    // leave space for border
    int row = i + BORDER_THICKNESS + PADDING_Y;
    const int COL = BORDER_THICKNESS + PADDING_X;
    mvwprintw(win, row, COL, "%s", menu_item.c_str());
  }
}

int main() {
  const std::vector<std::string> MENU = {
    "> Start",
    "> Save",
    "> Settings",
    "> Quit",
  };
  const size_t N_MENU_ITEMS = MENU.size();
  size_t width_menu = get_menu_width(MENU);

  // initialize ncurses
  initscr();

  // enable colors
  start_color();

  // assign default terminal's fg/bg colors to color=-1 in init_pair()
  use_default_colors();

  // # of lines & cols for entire terminal
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  printf("# lines: %d, # cols: %d\n", rows, cols);

  // new window that doesn't cover all terminal (coords start from 0)
  int rows_menu = N_MENU_ITEMS + 2*BORDER_THICKNESS + 2*PADDING_Y;
  int cols_menu = width_menu + 2*BORDER_THICKNESS + 2*PADDING_X;
  int x_menu = rows / 2 - rows_menu / 2;
  int y_menu = cols / 2 - cols_menu / 2;
  WINDOW* win = newwin(rows_menu, cols_menu, x_menu, y_menu);
  printf("# lines win: %d, # cols win: %d\n", rows_menu, cols_menu);
  printf("# x: %d, # y: %d\n", x_menu, y_menu);

  // get typed character (by getch()) without waiting for '\n'
  cbreak();

  // allows to detect the arrow-key pressed (in getch)
  // keypad(stdscr, TRUE);
  keypad(win, TRUE);

  // prevent character read by getch() from being printed on stdout
  noecho();

  // sets the cursor state to invisible
  curs_set(0);

  // terminal has colors capability
  if (has_colors()) {
    init_pair(1, COLOR_BLUE, -1);
  }

  // draw borders around window
  wattr_on(win, A_BOLD | COLOR_PAIR(1), NULL);
  box(win, ACS_VLINE, ACS_HLINE);
  wattr_off(win, A_BOLD | COLOR_PAIR(1), NULL);

  int c = 0;

  while (c != 'q' && c != 'Q') {
    draw_menu(win, MENU);

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(win);

    if (c == KEY_UP)
      i_selected = i_selected == 0 ? N_MENU_ITEMS - 1 : i_selected - 1;
    else if (c == KEY_DOWN)
      i_selected = i_selected == N_MENU_ITEMS - 1 ? 0 : i_selected + 1;
  }

  delwin(win);
  endwin();

  return 0;
}

/*  AUTHOR: Anas Rchid <rchid.anas@gmail.com>
 *   ABOUT: this is a program that generates a standard
 *          9x9 Sudoku puzzle 
 * CREATED: 06/18/2017
 */

#include "../include/sdku.h"
#include "../include/sdku-alloc.h"

int MAX_ROWS = 0, MAX_COLUMNS = 0;

int main()
{
  srand(time(NULL));

  initscr();

  getmaxyx(stdscr,MAX_ROWS, MAX_COLUMNS);

  if(MAX_ROWS < 28 || MAX_COLUMNS < 75) {
	endwin();
	return 1;
  }
  
  sdku_t *s = gensdku(Y_DIM, X_DIM);

  putsdku(s);

  refresh();
  getch();
  freesdku(s, Y_DIM, X_DIM);

  endwin();
  
  return 0;
}

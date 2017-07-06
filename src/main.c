/*           _____           _       _                  
 *    _     / ____|         | |     | |             _   
 *  _| |_  | (___  _   _  __| | ___ | | ___   _   _| |_ 
 * |_   _|  \___ \| | | |/ _` |/ _ \| |/ / | | | |_   _|
 *   |_|    ____) | |_| | (_| | (_) |   <| |_| |   |_|  
 *         |_____/ \__,_|\__,_|\___/|_|\_\\__,_|        
 *                                                      
 *	 AUTHOR: Anas Rchid <rchid.anas@gmail.com>
 *    ABOUT: this is a program that generates a standard
 *           9x9 Sudoku puzzle. (maybe a game later) 
 *  CREATED: 06/18/2017
 */

#include "../include/sdku.h"
#include "../include/sdku-alloc.h"

int MAX_ROWS = 0, MAX_COLUMNS = 0;

int main()
{
  srand(time(NULL));
  initscr();
  getmaxyx(stdscr,MAX_ROWS, MAX_COLUMNS);

  bool is_not_wide = (MAX_COLUMNS < MIN_SCR_X ||
					  MAX_ROWS < MIN_SCR_Y);

  if(is_not_wide) {
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

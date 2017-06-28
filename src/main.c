/*  AUTHOR: Anas Rchid <rchid.anas@gmail.com>
 *   ABOUT: this is a program that generates a standard
 *          9x9 Sudoku puzzle 
 * CREATED: 06/18/2017
 */

#include "../include/sdku.h"
#include "../include/sdku-alloc.h"

int main()
{
  srand(time(NULL));

  sdku_t *s = initsdku(Y_DIM, X_DIM);
  putsdku(s);
  
  freesdku(s, Y_DIM, X_DIM);
  
  return 0;
}

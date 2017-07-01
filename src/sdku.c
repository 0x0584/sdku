#include "../include/sdku.h"

int printsdku(sdku_t *sdku, int ydim, int xdim)
{
  if(!sdku) goto FAILURE;

  /* This is O(scary), but seems quick enough in practice.
   * for each block */
  for(int j = 0; j < ydim/3; ++j)
	for(int i = 0; i < xdim/3; ++i)
	  /* for each cell in the block */
	  for(int jj = 0; jj < ydim/3; ++jj)
		for(int ii = 0; ii < xdim/3; ++ii) {
		  /* don't miss with those! until i comment them! */
		  int y = (MAX_ROWS/Y_DIM) + (jj*2 + j*4*2);
		  int x = (MAX_COLUMNS/X_DIM) + (ii*3 + i*4*3);
		  int value = sdku->block[j][i].grid[jj][ii].value;

		  mvprintw(y, x, "%2d", value);
		}
  
  return 0;

 FAILURE: return -1;
}

void shuffvalues(int *v, int size)
{
  bool used[size];
  int index0, index1,
	seed = rand();			/* a trick to update the seed
							 * within the function */

  for(int i = 0; i < size; ++i) used[i] = false;

  if(size%2) srand(++seed), index0 = index1 = rand()%size;
  else index0 = 0, index1 = (size - 1);

  for(int i = 0; i < 9; ++i) {
	while(used[index0] || used[index1]) {
	BEGINNIG:
	  index0 = rand()%9;
	  srand(++seed);
	  index1 = rand()%9;

	  if(index0 == index1) goto BEGINNIG;
	  else break;
	}

	used[index0] = used[index1] = true; /* check as used */

	int tmp;
	tmp = v[index0]; v[index0] = v[index1]; v[index1] = tmp;
  }
}

bool isinlist(node_t *head, const cell_t *this)
{
  node_t *foohead = head;

  while(true) {
	int value = foohead->cell->value;

	if(value == this->value) return true;
	else if(!(foohead->next)) break; /* we reach the end of the list */
	else foohead = foohead->next;	 /* move to the next element */
  }

  return false;
}

bool isinblock(const block_t *blck, cell_t *c)
{
  for(int j = 0; j < Y_DIM/3; ++j)
	for(int i = 0; i < X_DIM/3; ++i)
	  if(blck->grid[j][i].value == c->value)
		return true;
  return false;
}

sdku_t * gensdku(sdku_t *sdku, int ydim, int xdim)
{
  /* key-idea: take a number from the `value` array and store
   * it in a foo-variable. take the next unvisited-cell
   * (starting at cell-0,0). make sure that the number does not
   * appear twice:
   *
   *	+ in the same row    : y-axis
   *	+ in the same column : x-axis
   *	+ in the same block  : the square is 3x3
   *
   * # in the same row: bool isinrow(row, value)
   *
   * we have saved the pointer of the row in a variable.
   * it's the cell's row
   *
   * check the row to see if it already has a value similar
   * to foo-variable. if so, take the next-value and store
   *    if in the foo-variable, and repeat the process
   * recursively until our condition, isinrow emains false.
   *
   *	RET: the value
   *
   * then, keep going through the column and the block
   *
   * # in the same column: bool isincolumn(column, value)
   * # in the same block: bool isinblock(block, value)
   *
   * the same treatment as the isinrow except passing the
   * column, indeed the block of cells too instead of the row
   *
   * the order of checking is the following:
   *
   *	1. row
   *	2. column
   *	3. block
   *
   * the three of those must return true, in order to fill
   * a cell, otherwise chose the next-value from values and
   * store it in foo-variable. repeat the whole treatment;
   * recursively. until all the array is filled.
   */

  int values[9] = {
	1, 2, 3,
	4, 5, 6,
	7, 8, 9
  };


  return sdku;
}

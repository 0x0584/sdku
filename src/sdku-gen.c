#include "../include/sdku.h"

int printsdku(sdku_t *sdku, int ydim, int xdim)
{

  if(!sdku) goto FAILURE;

  /* for each block */
  for(int j = 0; j < ydim/3; ++j) {
	for(int i = 0; i < xdim/3; ++i) {
	  /* for each cell in the block */
	  for(int jj = 0; jj < ydim/3; ++jj) {
		for(int ii = 0; ii < xdim/3; ++ii) {
		  printf(" %d |", sdku->block[j][i].grid[jj][ii].value);
		}
		putchar('\t');
	  }
	  putchar('\n');
	}
	putchar('\n');
  }

  return 0;

  FAILURE: return -1;
}

cell_t ** initgrid(int ygrid, int xgrid)
{
  cell_t **foocell = NULL;

  foocell = (cell_t **) malloc(ygrid * sizeof(cell_t *));

  for(int j = 0; j < ygrid; ++j) {
	foocell[j] = (cell_t *) malloc(xgrid * sizeof(cell_t));
	for(int i = 0; i < xgrid; ++i) {
	  foocell[j][i].value = -1;
	  /* foocell[j][i].row = &(foocell[j][0]); */
	  /* foocell[j][i].column = foocell[j]; */
	}
  }

  return foocell;
}

block_t ** initblock(int yblock, int xblock)
{
  block_t **fooblock = NULL;

  fooblock = (block_t **) malloc(yblock * sizeof(block_t *));

  for(int j = 0; j < yblock; ++j) {
	fooblock[j] = (block_t *) malloc(xblock * sizeof(block_t));
	for(int i = 0; i < xblock; ++i)
	  fooblock[j][i].grid = initgrid(yblock, xblock);
  }
  
  return fooblock;
}

sdku_t * initsdku(int ysdku, int xsdku)
{
  sdku_t *foosdku = NULL;

  int xb = xsdku/3, yb = ysdku/3;  
     
  foosdku = (sdku_t *) malloc(sizeof(sdku_t));

  foosdku->block = initblock(xb, yb); /* the block is 3x3 */
  
  return gensdku(foosdku, ysdku, xsdku);
}

void shuffvalues(int *v, int size)
{
  bool used[size];
  int index0, index1;

  for(int i = 0; i < size; ++i) used[i] = false;

  if(size%2) index0 = index1 = rand()%size;
  else index0 = 0, index1 = (size-1);

  for(int i = 0; i < 9; ++i) {
	while(used[index0] || used[index1]) {
	BEGINNIG:
	  if(!used[index0]) index0 = rand()%9;
	  if(!used[index1]) index1 = rand()%9;
	  
	  if(index0 == index1) goto BEGINNIG;
	}
	
	used[index0] = used[index1] = true;

	int tmp = v[index0];
	v[index0] = v[index1];
	v[index1] = tmp; 
  }
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

  for(int i = 0; i < 9; ++i){
	shuffvalues(values, 9);

	for(int j = 0; j < 9; ++j){
	  printf("%d ", values[j]);
	}
	putchar('\n');
  }
  
  /* free(values); */
  
  return sdku;
}

int freesdku(sdku_t *sdku, int ydim, int xdim)
{
  for(int j = 0; j < ydim/3; ++j) {
	for(int i = 0; i < xdim/3; ++i) {
	  for(int jj = 0; jj < ydim/3; ++jj) {
		free(sdku->block[j][i].grid[jj]);
	  }
	}
	free(sdku->block[j]);
  }
  
  free(sdku->block);
  free(sdku);
  
  return 0;
}

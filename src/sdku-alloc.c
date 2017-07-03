#include "../include/sdku.h"
#include "../include/sdku-alloc.h"

sdku_t * initsdku(int ydim, int xdim)
{  
  int getindex(int b_index, int g_index) {    
	return 3*b_index + g_index;
  }

  sdku_t *foosdku = NULL;

  int xb = xdim/3, yb = ydim/3;

  foosdku = (sdku_t *) malloc(sizeof(sdku_t));

  foosdku->block = initblock(xb, yb); /* the block is 3x3 */

  /* here! */
  /* key-idea: loop over blocks and their cells
   * then for each block, */

  /*
   *   j\i   0   1   2       3   4   5       6   7   8
   *
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   0   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   1   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   2   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *       
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   3   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   4   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   5   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *       
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   6   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   7   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   *   8   |   |   |   |   |   |   |   |   |   |   |   |
   *       +---+---+---+   +---+---+---+   +---+---+---+
   */

  node_t **row = (node_t **) malloc(Y_DIM * sizeof(node_t *)),
  	**col = (node_t **) malloc(X_DIM * sizeof(node_t *));

  for(int i = 0; i < Y_DIM; ++i) {
	row[i] = (node_t *) malloc(sizeof(node_t));
	col[i] = (node_t *) malloc(sizeof(node_t));
	
	row[i]->cell = NULL;
	row[i]->next = NULL;
	col[i]->cell = NULL;
	col[i]->next = NULL;
  }
  
  /* for each block */
  for(int j = 0; j < yb; ++j)
	for(int i = 0; i < xb; ++i){
	  block_t *b = &(foosdku->block[j][i]);

	  /* for each cell in the block */
	  for(int jj = 0; jj < yb; ++jj)
		for(int ii = 0; ii < xb; ++ii) {
		  cell_t *c = &(b->grid[jj][ii]);
		  
		  c->row = appendto(row[getindex(j,jj)],c);
		  c->column = appendto(col[getindex(i,ii)],c);
		}
	}
  
  return foosdku;
}

int foo;
cell_t ** initgrid(int ygrid, int xgrid)
{
  cell_t **foocell = NULL;

  foocell = (cell_t **) malloc(ygrid * sizeof(cell_t *));

  for(int j = 0; j < ygrid; ++j) {
	foocell[j] = (cell_t *) malloc(xgrid * sizeof(cell_t));
	for(int i = 0; i < xgrid; ++i) {
	  foocell[j][i].value = foo++;
	  foocell[j][i].row = NULL;
	  foocell[j][i].column = NULL;
	}
  }

  return foocell;
}

block_t ** initblock(int yblock, int xblock)
{
  block_t **fooblock = NULL;
  int yg = yblock, xg = xblock;

  fooblock = (block_t **) malloc(yblock * sizeof(block_t *));

  for(int j = 0; j < yblock; ++j) {
	fooblock[j] = (block_t *) malloc(xblock * sizeof(block_t));
	for(int i = 0; i < xblock; ++i)
	  fooblock[j][i].grid = initgrid(yg, xg);
  }

  return fooblock;
}

node_t * appendto(node_t *head, cell_t *cell)
{

  /* no head is found */
  if(!(head)) {
	head = (node_t *) malloc(sizeof(node_t));
	head->cell = cell, head->next = NULL;
	goto RET;
  }

  /* key-idea: append the cell to the last node
   *		   in the head */

  node_t *foo = head;

  /* move to the end of the list */
  while(foo->next) foo = foo->next;
  /* append the new node */
  foo->cell = cell;
  foo->next = NULL;
  
 RET:
  return head;
}


int freesdku(sdku_t *sdku, int ydim, int xdim)
{
  for(int j = 0; j < ydim/3; ++j) {
	for(int i = 0; i < xdim/3; ++i) {
	  for(int jj = 0; jj < ydim/3; ++jj) {
		for(int ii = 0; ii < xdim/3; ++ii) {
		  if(sdku->block[j][i].grid[jj][ii].row) {
			free(sdku->block[j][i].grid[jj][ii].row);
			sdku->block[j][i].grid[jj][ii].row = NULL;
		  }
		  if(sdku->block[j][i].grid[jj][ii].column) {
			free(sdku->block[j][i].grid[jj][ii].column);
			sdku->block[j][i].grid[jj][ii].column = NULL;
		  }
		}
		free(sdku->block[j][i].grid[jj]);
	  }
	}
	free(sdku->block[j]);
  }

  free(sdku->block);
  free(sdku);

  return 0;
}

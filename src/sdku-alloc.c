#include "../include/sdku.h"
#include "../include/sdku-alloc.h"

node_t * appendto(node_t *head, cell_t *cell)
{
  if(!(head->cell)) {
	head->cell = cell; head->next = NULL;	
	goto RET;
  }

  node_t *tmp = head, *foo = malloc(sizeof *foo);

  foo->cell = cell; foo->next = NULL;
  
  while(tmp->next) tmp = tmp->next;

  tmp->next = foo;
  
 RET:  return head;
}

int getindex(int b_index, int g_index) {
  /* the index of the block move 
   * the index of the cell by 3 */
  int index = 3*b_index + g_index;
  return index;
}

sdku_t * initsdku(int ydim, int xdim)
{
  sdku_t *sdku = NULL;

  int xb = xdim/3, yb = ydim/3;

  sdku = malloc(sizeof *sdku);

  sdku->block = initblock(xb, yb); /* the block is 3x3 */
  
  node_t **row = malloc(Y_DIM * sizeof *row),
  	**col = malloc(X_DIM * sizeof *col);

  for(int i = 0; i < Y_DIM; ++i) {
	row[i] = malloc(sizeof **row);
	col[i] = malloc(sizeof **col);
	
	row[i]->cell = NULL; row[i]->next = NULL;
	col[i]->cell = NULL; col[i]->next = NULL;
  }

  for(int j = 0; j < yb; ++j)
  	for(int i = 0; i < xb; ++i) {
	  block_t *b = &(sdku->block[j][i]);

  	  /* for each cell in the block */
  	  for(int jj = 0; jj < yb; ++jj)
  		for(int ii = 0; ii < xb; ++ii) {
  		  cell_t *c = &(b->grid[jj][ii]);
		  /* append the current cell into the correct roe/column 
		   * by taking the index via getindex() */
		  c->row    = appendto(row[getindex(j, jj)], c);
		  c->column = appendto(col[getindex(i, ii)], c);
		}
	}
    
  return sdku;
}

int foo;
cell_t ** initgrid(int ygrid, int xgrid)
{
  cell_t **cell = NULL;

  cell = malloc(ygrid * sizeof *cell);

  for(int j = 0; j < ygrid; ++j) {
	cell[j] = malloc(xgrid * sizeof **cell);
	for(int i = 0; i < xgrid; ++i) {
	  cell[j][i].value  = FRESH_CELL;
	  cell[j][i].row    = NULL;
	  cell[j][i].column = NULL;
	}
  }

  return cell;
}

block_t ** initblock(int yblock, int xblock)
{
  block_t **block = NULL;
  int yg = yblock, xg = xblock;

  block = malloc(yblock * sizeof *block);

  for(int j = 0; j < yblock; ++j) {
	block[j] = malloc(xblock * sizeof **block);
	for(int i = 0; i < xblock; ++i)
	  block[j][i].grid = initgrid(yg, xg);
  }

  return block;
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

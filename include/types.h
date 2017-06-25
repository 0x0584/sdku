#ifndef _TYPES_H
#define _TYPES_H

#ifndef __cpluslpus
typedef enum _BOOL_TYPE { false = (1==0), true = !false } bool;
#endif

typedef struct _SUDOKU_CELL_STRUCT cell_t;
typedef struct _SUDOKU_BLOCK_STRUCT block_t;
typedef struct _SUDOKU_PUZZLE_STRUCT sdku_t;
typedef cell_t * row_t;
typedef cell_t* clmn_t;

#endif	/* _TYPES_H */

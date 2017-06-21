/* you can print the value of the fisrt column if you 
 * de-reference the pointer of the lines.
 * the y-th one in this example (i.e. the i-th one) */
#include <stdio.h>

#define SIZE 9

int main()
{
  int array[SIZE][SIZE], x, y;

  for(y = 0; y < SIZE; ++y)
    for(x = 0; x < SIZE; ++x)
      array[y][x] = (x + y);

  for(y = 0; y < SIZE; ++y) {
    for(x = 0; x < SIZE; ++x)
      printf("(%d-%d)\t", x, y);
    for(x = 0; x < SIZE; ++x)
      printf(" %d ", array[y][x]);

    printf("\t[%d]\n", *(array[y]));
  }
  
  return 0;
}

#include <stdio.h>

enum ISIN_ENUM{ ROW = 1<<0, CLMN = 1<<1, SQUR = 1<<2 };

int isinrow(int index, int value)
{
  return index + value;
}

int isincolumn(int index, int value)
{
  return index + value;
}

int isinsquar(int index, int value)
{
  return index + value;
}

int main()
{
  int (*isin[3])(int index, int value) = {isinrow, isincolumn, isinsquar};
  
  int x = isin[0](0,0);
  printf("%d\n",isin[0](0,0));
  
  return 0;
}

#include <stdio.h>
#include <stdlib.h>

char* make_uppercase(char* str, char new[6])
{
  unsigned int i = 0;
  unsigned dif = 'a' - 'A';
  while(*(new + i) = *(str + i)) {
    if (*(str + i) >= 'a' && *(str + i) <= 'z')
      *(new + i++) -= dif;
  }
  return new;
}

void upper(char* p_arr, const int size)
{
  char* new_str = (char*)malloc(size * sizeof(char));
  char* move;
  for(move = p_arr; move != p_arr + size; move++) {
    printf("%c\n", *(move) - 32);
    *new_str = *move - 32;
  }
  printf("%p\n", p_arr);
  free(p_arr);
  p_arr = new_str;
}

int main()
{
  char new_str[6];
  char* input = "hello";
  char* str = make_uppercase(input, new_str);
  upper(input, 5);
  while(*input)
    printf("%c\n", *input++);
  return 0;
}

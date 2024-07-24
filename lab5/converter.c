#include <stdio.h>

int main ()
{ 
  int i = 0;
  char mas[28];
  for (; i != 20; i++ ){
    mas[i]='t';
  }
  mas[20]=0xeb;
  mas[21]=0x51;
  mas[22]=0x55;
  mas[23]=0x55;
  mas[24]=0x55;
  mas[25]=0x55;
  mas[26]=0x00;
  mas[27]=0x00;

  FILE *file = fopen("input.txt", "w");
  fwrite(mas, sizeof (mas[0]), sizeof(mas), file);
  fclose(file);

  return 0;  
}

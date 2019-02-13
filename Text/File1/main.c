#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *MyFile;
  
  MyFile= fopen("Test.txt", "a");// make File
  MyFile= fopen("Test.txt", "w");// Write File
  
  fprintf(MyFile,"%s%d\n", "hello!", 30);
  fclose(MyFile);
  system("PAUSE");	
  return 0;
}

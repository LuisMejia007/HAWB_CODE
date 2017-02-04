
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_LENGTH(array) (sizeof(array)/sizeof(array[0]))

void readFile(FILE *filePointer);
void appendToFile(FILE *filePointer, char *name);
void writeToFile(FILE *filePointer, float array[10]);


int main(int argc, char **argv)
{
   FILE *fp;
   char name[30];
   float array[10];
   float num = 0.0;
   int i = 0;
   

   for(i = 0; i < ARRAY_LENGTH(array); i++)
   {
       scanf("%f",&num);
       array[i] = num;
   }
   
   printf("\n");
   
   fp = fopen("newFile.csv", "w");
   writeToFile(fp, array);
   fp = fopen("newFile.csv", "r");
   readFile(fp);   
}

void writeToFile(FILE *filePointer, float array[10])
{
   int i = 0;
   
   for(i = 0; i < 10; i++)
   {
       fprintf(filePointer,"%f\n" ,array[i]);
   }
   
   fclose(filePointer);
}

void readFile(FILE *filePointer)
{
   int character = 0;
   
   if(filePointer)
   {
       while((character = getc(filePointer)) != EOF)
       {
           putchar(character);
       }
       printf("\n");
       fclose(filePointer);
   }
   
   fclose(filePointer);
}

void appendToFile(FILE *filePointer, char *name)
{
   fprintf(filePointer, name);
   
   fclose(filePointer);
}
#include <stdio.h>

int main(int argc, char* argv[])
{
   printf("protection program started to run\n");
   int i;
   do
   {
   	printf("enter zero to terminate, any other number to continue\n");
   	scanf("%d", &i);
   }while (i != 0);	

   printf("terminating protection progrma\n");
   return 0;
}

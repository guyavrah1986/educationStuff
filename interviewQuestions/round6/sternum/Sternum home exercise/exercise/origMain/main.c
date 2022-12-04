#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void hexdump (void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}


struct function_holder_struct
{
	void (*function_ptr)(void);
};

void myfunc() {
   printf("myfunc was called\n");
}

void prepare_allocation(char* addr, unsigned int len) {
    memset(addr, 'A', len);
}

int main(int argc, char* argv[])
{
   if( argc != 2 ) {
      printf("main [memset size]\n");
      return 1;
   }
   char* str = NULL;
   int size =  atoi(argv[1]); 
   printf("main\n");
   int i;
   printf("main - please enter a number\n");
   scanf("%d", &i);
   struct function_holder_struct* func_holder;
   str = malloc(4);
   func_holder = malloc(4);
   func_holder->function_ptr = &myfunc;
   printf("func_holder->function_ptr address 0x%x\n", (unsigned int)&myfunc);
   printf("func_holder(%p) was allocated with size %d\n", (void*)func_holder, 4);
   printf("str(%p) was allocated with size %d\n", (void*)str, size);

   prepare_allocation(str, size);
   
   printf("Hexdump");
   hexdump(str - 16, 16 + 4 + (unsigned int)&func_holder->function_ptr - (unsigned int)str);
   
   func_holder->function_ptr();
   free(str);
   free(func_holder);
   return 0;
}

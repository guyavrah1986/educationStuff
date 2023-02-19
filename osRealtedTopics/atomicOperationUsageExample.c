#include <linux/bitops.h>
//#include <asm/bitops.h>

int main()
{
    unsigned long bit_array = 0;
    int bit_position = 2;

    // Set the bit at position 2 in the bit array
    int previous_value = test_and_set_bit(bit_position, &bit_array);

    // Check the previous value of the bit
    if (previous_value)
    {
        printf("Bit was already set\n");
    }
    else
    {
        printf("Bit was not set\n");
    }

    return 0;
}

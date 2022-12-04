#include <iostream>

using namespace std;

int comapreTwoMacAddresses(const unsigned char mac1[6], const unsigned char mac2[6])
{
	uint32_t* m1 = (uint32_t*)(mac1);
	uint32_t* m2 = (uint32_t*)(mac2);

	cout << "comapreTwoMacAddresses - after casting to uint32_t, m1:" << static_cast<unsigned>(*m1) << endl;
	cout << "comapreTwoMacAddresses - after casting to uint32_t, m2:" << static_cast<unsigned>(*m2) << endl;

	if (m1 == m2)
	{
		cout << "comapreTwoMacAddresses - MAC addresses are equal" << endl;
		return 0;
	}
	
	cout << "comapreTwoMacAddresses - MAC addresses are NOT equal" << endl;
	return 1;
}

size_t findNumOfOnBits(unsigned char byte)
{
	cout << "findNumOfOnBits - got the number(decimal):" << static_cast<unsigned>(byte) << endl;
	const size_t numOfBits = 8;
	const unsigned char mask = 0b00000001;
	size_t counter = 0;

	for (size_t i = 0; i < (sizeof(byte) * numOfBits); ++i)
	{
		counter += (byte & mask);
		byte = byte >> 1;
	}		

	return counter;
}


void sortFixedSizeArray()
{
	const size_t arrLen = 255;
	
}


int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	const unsigned char val = 5;
	size_t res = findNumOfOnBits(val);
	cout << "main - findNumOfOnBits(" << static_cast<unsigned>(val) << "):" << static_cast<unsigned>(res) << endl;
	

	const unsigned char mac1[6] = {0x00, 0x01, 0x00, 0x00, 0x05, 0x06};
	const unsigned char mac2[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	cout << "main - comapreTwoMacAddresses returned:" << comapreTwoMacAddresses(mac1, mac2) << endl;

	cout << "main - end" << endl;
	return 0;
}

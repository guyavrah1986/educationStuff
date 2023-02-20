#pragma once

struct sampleStruct
{
	int x;
	int y;
	char c;
}__attribute__((packed));


/* This ifdef allows the header to be used from both C and C++ 
 * because C does not know what this extern "C" thing is. */
#ifdef __cplusplus
extern "C" {
#endif
struct sampleStruct funcThatGetPointerToCppClassAndTreatItAsStrcut(void* pStruct);
#ifdef __cplusplus
}
#endif

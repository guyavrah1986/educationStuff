#ifndef C_H_
#define C_H_

struct sampleStruct
{
	int x;
	int y;
	char c;
};


/* This ifdef allows the header to be used from both C and C++ 
 * because C does not know what this extern "C" thing is. */
#ifdef __cplusplus
extern "C" {
#endif
void funcThatGetPointerToCppClassAndTreatItAsStrcut(void* pStruct);
#ifdef __cplusplus
}
#endif

#endif /* C_H_ */

/* Austin Hoppe
 * 29 September 2013
 * stringah1.h */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef __STRAH1_H__
#define __STRIH1_H__

#include "includes_stringah1.h"

typedef struct StrAH1 StrAH1_t;
typedef long Length_StrAH1_t;

/* Don't expose this to the client. This will be the actual function referred to in each m_fp_extendStrAH1 function pointer.
 * This implementation (like any other function pointers) will need to be established before allocStrAH1() */
short m_f_extendStrAH1(StrAH1_t *extendArg, long lNumPlaces);

struct StrAH1 {
	/* The length of the actual string contents, and also the index of the first char of padding */
	Length_StrAH1_t length;
	/* The maximum number of chars that can be put in the padding. Also the index just before the NULL terminator */
	long lCap;
	/* Don't expose this to the client. The underlying string storage implementation is char array.
	 * StrAH1 chars are guaranteed to be contiguous in memory, but the content of padding is undefined.
	 * Consequently, extending this string will require allocating (N+5) more chars of memory */
	char *cpData;
	/* Don't expose this to the client. Padding will be increased by exactly lNumPlaces.
	 * The NULL terminator will be 'pushed back' by lNumPlaces, which are pre-allocated */
	short (*m_fp_extendStrAH1)(StrAH1_t *extendArg, long lNumPlaces);
};

/* Ensure that allocArg is an uninitialized or recently free()'d pointer. */
short allocStrAH1(StrAH1_t *allocArg);

short appendStrAH1(StrAH1_t *appendArg, const char *cpAppendSource);

Length_StrAH1_t getLengthStrAH1(StrAH1_t *getLengthArg);

char getCharAtStrAH1(StrAH1_t *getCharAtArg, long lIndexArg);

/* cpDestination needs to be an uninitialized pointer, i.e. newly created or recently free()'d */
short substrStrAH1(StrAH1_t *substrArg, char *cpDestination, long lInd1Arg, long lInd2Arg);
/* Releases malloc()'d memory for data members in destroyArg */

/* Use this sparingly.. */
char * showRawStrAH1(StrAH1_t *showRawArg);

short destroyStrAH1(StrAH1_t *destroyArg);

#endif /* __STRAH1_H__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

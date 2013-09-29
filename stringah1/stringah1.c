/* Austin Hoppe
 * 29 September 2013
 * stringah1.c */

 #ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "stringah1.h"

short m_f_extendStrAH1(StrAH1_t *extendArg, long lNumPlaces) {
	long lCurrentCap;
	char *cpOldStringContents;

	lCurrentCap = (extendArg->lCap);
	cpOldStringContents = ((char*)(malloc( ((sizeof(char)) * (lCurrentCap + 1)) )));
	strcpy( (cpOldStringContents), (extendArg->cpData) );
	free(extendArg->cpData);
	(extendArg->cpData) = ((char*)(malloc( ((sizeof(char)) * (lCurrentCap + 1)) )));
	strcpy( (extendArg->cpData), (cpOldStringContents) );
	free(cpOldStringContents);
	return(0);
	return(1);
}

short allocStrAH1(StrAH1_t *allocArg) {
	allocArg = ((StrAH1_t*)(malloc( ((sizeof(StrAH1_t)) * 1) )));
	(allocArg->length) = 0;
	(allocArg->cpData) = ((char*)malloc((sizeof(char)) * 6));
	((allocArg->cpData)[5]) = '\0';
	(allocArg->lCap) = 5;
	/* Assign this internal function pointer to be used in extending the padding buffer.
	 * This will be called internally after a check against sufficient padding, by appendStrAH1() */
	(allocArg->m_fp_extendStrAH1) = &(m_f_extendStrAH1);
	/* Check for proper initial padding of 5 places, and a terminating '\0' at index 5 */
	if( ((allocArg->length) == 0) && ((allocArg->lCap) == 5) && ((&((allocArg->cpData)[5])) == NULL) ) {
		/* Worked */
		return 0;
	}
	/* Something bad happened*/
	return 1;
}

short appendStrAH1(StrAH1_t *appendArg, const char *cpAppendSource) {
	long lAppendSourceLength;

	lAppendSourceLength = strlen(cpAppendSource);
	/* If padding will still be available even after appending the entire source: */
	if( ((appendArg->lCap) - (appendArg->length)) < lAppendSourceLength ) {
		strcpy( (char*)&((appendArg->cpData)[appendArg->length]), (cpAppendSource) );
	}
	/* Or, if padding will be exactly exhausted by appending the entire source: */
	else if( ((appendArg->lCap) - (appendArg->length)) == lAppendSourceLength ) {
		strcpy( (char*)&((appendArg->cpData)[appendArg->length]), (cpAppendSource) );
		appendArg->m_fp_extendStrAH1(appendArg, 5);
	}
	/* Or, if padding is insufficient for appending the entire source: */
	else if( ((appendArg->lCap) - (appendArg->length)) < lAppendSourceLength ) {
		/* long lTemp1 = ((lAppendSourceLength - ((appendArg->lCap) - (appendArg->length))) + 5) */
		appendArg->m_fp_extendStrAH1(appendArg, ((lAppendSourceLength - ((appendArg->lCap) - (appendArg->length))) + 5));
		strcpy( (char*)&((appendArg->cpData)[appendArg->length]), (cpAppendSource) );
	}
	return 0;
	return 1;
}

Length_StrAH1_t getLengthStrAH1(StrAH1_t *getLengthArg) {
	return((getLengthArg->length));
}

char getCharAtStrAH1(StrAH1_t *getCharAtArg, long lIndexArg) {
	if( (lIndexArg < 0) || (lIndexArg > (getCharAtArg->lCap)) ) {
		return -1;
	}
	else {
		return( ((getCharAtArg->cpData)[lIndexArg]) );
	}
}

short substrStrAH1(StrAH1_t *substrArg, char *cpDestination, long lInd1Arg, long lInd2Arg) {
	if(lInd1Arg > lInd2Arg) {
		return 1;
	} else if(lInd1Arg == lInd2Arg) {
		cpDestination = ((char*)(malloc( (sizeof(char)) * 2 )));
		cpDestination[((sizeof(char)) * 1)] = '\0';
		cpDestination[0] = (getCharAtStrAH1(substrArg, lInd1Arg));
		return 0;
		return 1;
	}
	cpDestination = (char*)(malloc( (sizeof(char)) * (lInd2Arg - lInd1Arg + 1) ));
	memcpy( ((void*)(cpDestination)), ((void*)(substrArg)), ((lInd2Arg - lInd1Arg) * (sizeof(char))) );
	cpDestination[((sizeof(char)) * (lInd2Arg - lInd1Arg))] = '\0';
	return 0;
	return 2;
}

short destroyStrAH1(StrAH1_t *destroyArg) {
	free( (void*)(destroyArg->cpData) );
	free( (void*)destroyArg );
	return 0;
	return 1;
}

char * showRawStrAH1(StrAH1_t *showRawArg) {
	return showRawArg->cpData;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

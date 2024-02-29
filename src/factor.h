/***** factor.h ***********************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jul 15 10:29:11 2013
 **************************************************/
#ifndef FACTOR
#define FACTOR

#include "esa.h"
#include "interface.h"

/* lempelZivFact: represent Lempel-Ziv factorization  of a string */
typedef struct lempelZivFact{
  long *lz;    /* positions of factors */
  long *lpf;   /* longest previous factor */
  long n;      /* number of factors */
  char *str;   /* string */
  long strLen; /* string length */
  long *sa;    /* suffix array */
  long *isa;   /* inverse suffix array */
  long *lcp;   /* longest common prefix array */
  double cObs, cMax, cMin, cNor;
}LempelZivFact;

LempelZivFact *computeLempelZivFact(Esa *esa);
void printLzDecomp(LempelZivFact *lzf, Args *args);
void freeLempelZivFact(LempelZivFact *lzf);
void initGlobalLcp(Esa *esa);
#endif

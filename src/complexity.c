/***** complexity.c *******************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Wed Jul 15 10:49:56 2015
 **************************************************/
#include <math.h>
#include "eprintf.h"
#include "esa.h"
#include "factor.h"


LempelZivFact *lzComplexity(Sequence *seq){
  LempelZivFact *lzf;
  Esa *esa;
  long nf;
  double l;

  esa = getEsa(seq);
  lzf = computeLempelZivFact(esa);
  nf = lzf->n;
  l = seq->len - 1;
  lzf->cObs = nf/l;
  lzf->cMin = 2./l;
  lzf->cMax = log(4.)/log(l/4.);
  lzf->cNor = (lzf->cObs - lzf->cMin)/(lzf->cMax - lzf->cMin);

  return lzf;
}

/* mlComplexity: match length complexity */
LempelZivFact *mlComplexity(Sequence *seq){
  LempelZivFact *lzf;
  Esa *esa;
  long i,j;
  long *ml;   /* match lengths */

  esa = getEsa(seq);
  /* construct and fill array of match lengths */
  lzf = (LempelZivFact *)emalloc(sizeof(LempelZivFact));
  ml = (long *)emalloc(esa->n*sizeof(long));
  for(i=0;i<esa->n-1;i++){
    if(esa->lcp[i] < esa->lcp[i+1])
      ml[esa->sa[i]] = esa->lcp[i+1];
    else
      ml[esa->sa[i]] = esa->lcp[i];
  }
  ml[esa->sa[i]] = esa->lcp[i];
  lzf->lz = (long *)emalloc(esa->n*sizeof(long));
  lzf->lz[0] = 0;
  /* compute observed number of match factors */
  i = 0;
  j = 1;
  while(i < esa->n){
    if(ml[i])
      i += ml[i];
    else
      i++;
    lzf->lz[j++] = i;
  }
  lzf->lz = (long *)erealloc(lzf->lz,(j+1)*sizeof(long));
  lzf->n = j-1;
  /* complete lzf for possible table output */
  lzf->sa = esa->sa;
  lzf->isa = esa->isa;
  lzf->lcp = esa->lcp;
  /* the longest previous factors requires the computation of the LZ factors */
  LempelZivFact *lzf2 = computeLempelZivFact(esa);
  lzf->lpf = lzf2->lpf;
  /* free array of match lengths */
  free(ml);
  return lzf;
}

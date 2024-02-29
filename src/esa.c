/***** esa.c **************************************
 * Description: Enhanced Suffix Array.
 * Reference: Abouelhoda, Kurtz, and Ohlebusch
 *   (2002). The enhanced suffix array and its
 *   applications to genome analysis. Proceedings
 *   of the Second Workshop on Algorithms in 
 *   Bioinformatics, Springer Verlag, Lectore Notes
 *   in Compter Science.
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jul 15 11:11:19 2013
 **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <divsufsort.h>
#include <string.h>
#include "eprintf.h"
#include "esa.h"

void addSa(Esa *esa, Sequence *seq){
  long i, n, *sa2;
  sauchar_t *t;
  saidx_t *sa1;

  esa->n = seq->len;
  n = esa->n;
  t = (sauchar_t *)seq->seq;
  sa1 = (saidx_t *)emalloc((size_t)n * sizeof(saidx_t));
  if(divsufsort(t,sa1,(saidx_t)n) != 0){
    printf("ERROR[esa]: suffix sorting failed.\n");
    exit(-1);
  }
  sa2 = (long *)emalloc(n*sizeof(long));
  for(i=0;i<n;i++)
    sa2[i] = (long)sa1[i];
  free(sa1);
  esa->sa = sa2;
}

/* addLcp: compute LCP array using the algorithm in Figure 3
 *   of Kasai et al (2001). Linear-time longest-common-prefix
 *   computation in suffix arrays and its applications. LNCS 2089
 *   p. 191-192.
 */
void addLcp(Esa *esa, Sequence *seq){
  long i, j, h, n, *rank, *lcp;
  char *t;

  n = seq->len;
  t = seq->seq;
  long *sa = esa->sa;
  rank = (long *)emalloc(n*sizeof(long));
  lcp = (long *)emalloc(n*sizeof(long));
  for(i=0;i<n;i++)
    rank[sa[i]] = i;
  h = 0;
  lcp[0] = 0;
  for(i=0;i<n;i++){
    if(rank[i] > 0){
      j = sa[rank[i]-1];
      while(t[i+h] == t[j+h])
	h++;
      lcp[rank[i]] = h;
      if(h>0)
	h--;
    }
  }
  esa->isa = rank;
  esa->lcp = lcp;
}

Esa *getEsa(Sequence *seq){
  Esa *esa;

  esa = (Esa *)emalloc(sizeof(Esa));
  addSa(esa, seq);
  addLcp(esa, seq);
  
  return esa;
}

void freeEsa(Esa *esa){

  free(esa->sa);
  free(esa->lcp);
  free(esa->isa);

  free(esa);
}

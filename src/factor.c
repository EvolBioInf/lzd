/***** factor.c ***********************************
 * Description: Compute the longest previous factor
 *   array using a suffix array and a longest 
 *   common prefix array.
 * Reference: Crochemore, M., Ilie, L. and Smyth,
 *   W. F. (2008). A simple algorithm for com-
 *   puting the Lempel Ziv factorization. In:
 *   Data Compression Conference, p. 482-488.
 *   Computing longest previous factor in linear
 *   time and applications.
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jul 15 10:29:09 2013
 **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "factor.h"
#include "stack.h"
#include "eprintf.h"
#include "esa.h"
#include "interface.h"

long minimum(long a, long b){
  if(a < b)
    return a;
  else
    return b;
}

long maximum(long a, long b){
  if(a > b)
    return a;
  else
    return b;
}

/*
 * computeLpf: Compute longest previous factor
 * Reference: M. Crochemore, L. Ilie, W.F. Smyth. 
 *   A simple algorithm for computing the Lempel-Ziv
 *   factorization, in: J.A. Storer, M.W. Marcellini
 *   (Eds.), 18th Data Compression Conference, IEEE 
 *   Computer Society, Los Alamitos, CA, 2008,
 *   pp. 482-488.
 */
long *computeLpf(Esa *esa){
  long i, n;
  long *lpf, *sa, *lcp;

  n = esa->n;
  /* Copy lcp array */
  lcp = emalloc((n+1)*sizeof(long));
  for(i=0; i<n; i++)
    lcp[i] = esa->lcp[i];
  esa->sa = erealloc(esa->sa,(n+1)*sizeof(long));
  lpf = (long *)emalloc((n+1) * sizeof(long));
  
  sa = esa->sa;
  sa[n] = -1;
  lcp[n] = 0;
  lpf[n] = 0;
  stackInit(1);
  stackPush(0);

  for(i=1;i<=n;i++){
    while(!stackEmpty() &&     
	  (sa[i] < sa[stackTop()] ||  
	   (sa[i] > sa[stackTop()] && lcp[i] <= lcp[stackTop()]))){
      if(sa[i] < sa[stackTop()]){
	lpf[sa[stackTop()]] = maximum(lcp[stackTop()],lcp[i]);
	lcp[i] = minimum(lcp[stackTop()],lcp[i]);
      }else
	lpf[sa[stackTop()]] = lcp[stackTop()];
      stackPop();
    }
    if(i < n)
      stackPush(i);
  }
  freeStack();
  free(lcp);

  return lpf;
}

void freeLempelZivFact(LempelZivFact *lzf){
  free(lzf->lz);
  free(lzf);
}

LempelZivFact *computeLempelZivFact(Esa *esa){
  long i, n, *lpf;
  LempelZivFact *lzf;

  lzf = (LempelZivFact *)emalloc(sizeof(LempelZivFact));
  lzf->sa = esa->sa;
  lzf->lcp = esa->lcp;
  lzf->isa = esa->isa;

  n = esa->n;

  lpf = computeLpf(esa);
  lzf->lz = (long *)emalloc(n*sizeof(long));
  lzf->lz[0] = 0; 
  i = 0;
  while(lzf->lz[i] < n){
    lzf->lz[i+1] = lzf->lz[i] + maximum(1,lpf[lzf->lz[i]]);
    i++;
  }
  lzf->n = i;
  lzf->lpf = lpf;
  return lzf;
}

void printLzDecomp(LempelZivFact *lzf, Args *args){
  int i, j;

  long *lcp = lzf->lcp;
  long *sa = lzf->sa;
  long *isa = lzf->isa;
  long *lpf = lzf->lpf;
  lcp[0] = -1; /* follow convention used in my lectures */
  if(args->t){
    if(args->l){
      printf("\\begin{center}\n\\begin{tabular}{rcrrrrl}\\hline\n");
      printf("$i$ & $\\mathtt{w}[i]$ & $\\mathtt{sa}[i]$ & $\\mathtt{lcp}[i]$ & $\\mathtt{isa}[i]$ & $\\mathtt{lpf}[i]$ & $\\mathtt{t}[\\mathtt{sa}[i]]]$\\\\\\hline\n");
    }else {
      printf("i\tw[i]\tsa[i]\tlcp[i]\tisa[i]\tlpf[i]\tt[sa[i]]\n");
    }
    for(i=0;i<lzf->strLen-1;i++){
      if(args->l){
	if(args->o)
	  printf("%d & $\\mathtt{%c}$ & %ld & %ld & %ld & %ld & $\\mathtt{",i+1,lzf->str[i],sa[i]+1,lcp[i],isa[i]+1,lpf[i]);
	else
	  printf("%d & $\\mathtt{%c}$ & %ld & %ld & %ld & %ld & $\\mathtt{",i,lzf->str[i],sa[i],lcp[i],isa[i],lpf[i]);
      }else{
	if(args->o)
	  printf("%d\t%c\t%ld\t%ld\t%ld\t%ld\t",i+1,lzf->str[i],sa[i]+1,lcp[i],isa[i]+1,lpf[i]);
	else {
	  printf("%d\t%c\t%ld\t%ld\t%ld\t%ld\t",i,lzf->str[i],sa[i],lcp[i],isa[i],lpf[i]);
	}
      }
      for(j=sa[i];j<lzf->strLen-1;j++)
	printf("%c",lzf->str[j]);
      if(args->l)
	printf("}$\\\\");
      printf("\n");
    }
    if(args->l)
      printf("\\hline\\end{tabular}\n\\end{center}\n");
  }
  j = 0;
  if(args->l)
    printf("\\[\n");
  for(i=0;i<lzf->n-1;i++){
    if(args->l)
      printf("\\mathtt{");
    for(j=lzf->lz[i];j<lzf->lz[i+1];j++)
      printf("%c",lzf->str[j]);
    if(args->l)
      printf("}");
    if(args->l)
      printf("\\cdot");
    else
      printf(".");
  }
  if(args->l)
    printf("\\mathtt{");
  for(j=lzf->lz[i];j<lzf->strLen-1;j++)
    printf("%c",lzf->str[j]);
  if(args->l)
    printf("}\n\\]\n");
  else
    printf("\n");
}

/***** lzd.c **************************************
 * Description: Lempel-Ziv decomposition.
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Wed Jul 29 16:03:05 2015
 **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "interface.h"
#include "eprintf.h"
#include "sequenceData.h"
#include "complexity.h"

void scanFile(int fd, Args *args){
Sequence *seq;
char *origSeq;
  int i;
  long origLen;
  LempelZivFact *lzf;

  seq = readFasta(fd);
  origLen = seq->len;
  origSeq = seq->seq;
  for(i=0;i<seq->numSeq;i++){
    if(i){
      seq->len = seq->borders[i]-seq->borders[i-1]-1;
      seq->seq += (seq->borders[i]+1);
      if(args->m) {
	lzf = mlComplexity(seq);
      } else
	lzf = lzComplexity(seq);
      seq->seq -= (seq->borders[i]+1);
    }else{
      seq->len = seq->borders[i];
      if(args->m) {
	lzf = mlComplexity(seq);
      } else
	lzf = lzComplexity(seq);
    }
    lzf->str = origSeq;
    lzf->strLen = origLen;
    if(args->n){
      printf("# n\tn/site\n");
      printf("%ld\t%g\n",lzf->n,(double)lzf->n/(double)lzf->strLen);
    }else {
      printLzDecomp(lzf,args);
      seq->seq = origSeq;
      freeLempelZivFact(lzf);
    }
  }
  seq->len = origLen;
  freeSequence(seq);
}

int main(int argc, char *argv[]){
  int i, fd;
  char *version;
  Args *args;

  version = "0.7";
  setprogname2("lzd");
  args = getArgs(argc, argv);
  if(args->v)
    printSplash(version);
  if(args->h || args->e)
    printUsage(version);
  if(args->numInputFiles == 0){
    fd = 0;
    scanFile(fd, args);
  }else{
    for(i=0;i<args->numInputFiles;i++){
      fd = open(args->inputFiles[i],0);
      scanFile(fd, args);
      close(fd);
    }
  }
  free(args);
  free(progname());
  return 0;
}

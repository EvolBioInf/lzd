/***** interface.c ************************************************
 * Description: Routine for gathering arguments from the command
 *              line.
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Sun Jun 20 13:12:10 2004.
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "interface.h"
#include "eprintf.h"

Args *args;

Args *getArgs(int argc, char *argv[]){
  int c;
  char *optString = "hvtmnlo";

  args = (Args *)emalloc(sizeof(Args));
  args->l = 0;
  args->n = 0;
  args->m = 0;
  args->t = 0;
  args->h = 0;
  args->v = 0;
  args->e = 0;
  args->o = 0;

  c = getopt(argc, argv, optString);
  while(c != -1){
    switch(c){
    case 'n': /* print number of factors only */
      args->n = 1;
      break;
    case 'o': /* one-based numbering? */
      args->o = 1;
      break;
    case 'l': /* LaTeX output? */
      args->l = 1;
      break;
    case 'm': /* match factor decomposition? */
      args->m = 1;
      break;
    case 't': /* print tables? */
      args->t = 1;
      break;
    case '?': /* fall-through is intentional */
    case 'h': /* print help */
      args->h = 1;
      break;
    case 'v': /* print version */
      args->v = 1;
      break;
    default:
      printf("# unknown argument: %c\n",c);
      args->e = 1;
      return args;
    }
    c = getopt(argc, argv, optString);
  }
  args->inputFiles = argv + optind;
  args->numInputFiles = argc - optind;
  return args;
}


void printUsage(char *version){
  printf("Usage: %s [options] [inputFiles]\n",progname());
  printf("Purpose: Print Lempel-Ziv decomposition of input string\n");
  printf("Example: lzd foo.fasta\n");
  printf("Options:\n");
  printf("\t[-t print table of SA, LCP, ISA, and LPF; default: print only decomposition]\n");
  printf("\t[-m print match decomposition; default: print LZ decomposition]\n");
  printf("\t[-l LaTeX output]\n");
  printf("\t[-n number of factors only; default: print decomposition]\n");
  printf("\t[-o one-based numbering]\n");
  printf("\t[-h print this help message and exit]\n");
  printf("\t[-v print program information and exit]\n");
  exit(0);
}

void printSplash(char *version){
  printf("%s %s\n",progname(),version);
  printf("Reference: Crochemore, M., Ilie, L. and Smyth,\n");
  printf("  W. F. (2008). A simple algorithm for com-\n");
  printf("  puting the Lempel Ziv factorization. In:\n");
  printf("  Data Compression Conference, p. 482-488.\n");
  printf("  Computing longest previous factor in linear\n");
  printf("  time and applications.\n");
  printf("Written by Bernhard Haubold.\n");
  printf("Distributed under the GNU General Public License.\n");
  exit(0);
}

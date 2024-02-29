#ifndef INTERFACE
#define INTERFACE

#define DEFAULT_B 32 * BUFSIZ /* default buffer size */

/* define argument container */
typedef struct args{
  char n;   /* print only number of factors? */
  char t;   /* print table of suffix array, etc? */
  char m;   /* print match factor decomposition? */
  char h;   /* help message? */
  char v;   /* version message? */
  char e;   /* error message? */
  char l;   /* latex output? */
  char o;   /* one-based numbering? */
  char **inputFiles;
  int b;    /* buffer size */
  int numInputFiles;
} Args;

Args *getArgs(int argc, char *argv[]);
void printUsage(char *version);
void printSplash(char *version);

#endif

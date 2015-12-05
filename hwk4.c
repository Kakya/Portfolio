#include <stdio.h>   /* printf  */
#include <string.h>  /* strncmp */
#include <stdlib.h>  /* atoi, strtol    */

extern int  quintuple (int);  /* arg*5                               */
extern long long_sqrt (long); /* largest long s.t. ans**2 <= arg?    */
extern int  caller    (int);  /* calls other function and more       */
extern int  abundant  (int);  /* is sum of divisors greater than it? */

extern int  sum_evens(int[],int); /* returns sum of all evens in array */


int main(int argc, char ** argv){
  /* check for enough arguments.*/
  if (argc<3){
    printf("error - not enough arguments.\n\n\tusage: hwk4 funcname arg1 arg2 arg3 ...\n\n");
    return 1;
  }
  
  /* find our first argument, assuming it's an int. */
  int n = atoi(argv[2]);
  
  /* dispatch to correct function and call it, printing the result. */
  if ( ! strncmp("quintuple",argv[1],10)){
    printf("%d\n",quintuple(n));
  }
  else if ( ! strncmp("long_sqrt",argv[1],10)){
    /* need to read in a long instead of an int.*/
    char *endptr;
    long temp = strtol(argv[2],&endptr, 10);
    printf("%ld\n",long_sqrt(temp));
  }
  else if ( ! strncmp("abundant",argv[1],10)){
    printf("%d\n",abundant(n));
  }
  else if ( ! strncmp("caller",argv[1],10)){
    printf("%d\n",caller(n));
  }
  else if ( ! strncmp("sum_evens",argv[1],10)){
    // get the array items, build array.
    int xs [n];
    for (int i=0; i<n; i++){
      xs[i] = atoi(argv[i+3]);
    }
    printf("%d\n",sum_evens(xs,n));
  }
  else {
    printf("error - unrecognized command '%s'.\n",argv[1]);
    return 2;
  }
}

#include "randcpuid.h"
#include <dlfcn.h> /*Dynamic loading lib*/
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*Print format */
static bool
writebytes (unsigned long long x, int nbytes)
{
  int ndigits = nbytes * 2;
  do
    {
      if (putchar ("0123456789abcdef"[x & 0xf]) < 0)
        return false;
      x >>= 4;
      ndigits--;
    }
  while (0 < ndigits);

  return 0 <= putchar ('\n');
}


int main(int argc, char **argv) {
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
        perror (argv[1]);
      else
        valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }
  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;
  void* dl_ret;
  char* error;
  unsigned long long (*rand64) (void);
  if (rdrand_supported ()) {
      dl_ret = dlopen("randlibhw.so", RTLD_LAZY);
      if(dl_ret == NULL) {
	fprintf(stderr, "Error opening randlibhw.so: %s\n", dlerror());
	exit(1);
      }
      rand64 = dlsym(dl_ret, "rand64");
      error = dlerror();
      if(error != NULL) {
	fprintf(stderr, "dlsym rand64 error: %s\n", error);
	exit(1);
      }
      printf("HW\n");
  }
  else
    {
      dl_ret = dlopen("randlibsw.so", RTLD_LAZY);
      if(dl_ret == NULL) {
	fprintf(stderr, "Error opening randlibsw.so: %s\n", dlerror());
	exit(1);
      }
      rand64 = dlsym(dl_ret, "rand64");
      error = dlerror();
      if(error != NULL) {
	fprintf(stderr, "dlsym rand64 error: %s\n", error);
	exit(1);
      }
      printf("SW\n");
    }
  int wordsize = sizeof rand64 ();
  int output_errno = 0;
  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
        {
          output_errno = errno;
          break;
        }
      nbytes -= outbytes;
    } while (0 < nbytes);
  
  if (fclose (stdout) != 0)
    output_errno = errno;
  
  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      return 1;
    }
  dlclose(dl_ret);
  return 0;
}

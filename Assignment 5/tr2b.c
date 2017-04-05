#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char* from = argv[1];
    char* to = argv[2];
    int i, k, c;
    int status = 0;

    if (argc != 3 && (strlen(from) != strlen(to))) {
        fprintf(stderr, "Incorrect arguments\n");
        exit(1);
    }
    for (i = 0; i < strlen(from); i++) {
      for (k = 0; k < strlen(from); k++) {
            if (from[i] == from[k] && i != k) {
                fprintf(stderr, "from has duplicate characters\n");
                exit(1);
            }
        }
    }
    c = getchar();
    while (c != EOF) {
      for ( i = 0; i < strlen(from); i++) {
	if(c == from[i]) {
	  putchar( to[i] );
	  status = 1;
	}
      }
       if (status == 0) { 
            putchar(c); 
        }
        c = getchar();
	status = 0;
    }
}

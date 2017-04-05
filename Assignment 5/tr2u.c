#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char* from = argv[1];
    char* to = argv[2];
    int i, k;
    char buf;
    ssize_t c;
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
    i = strlen(from);
    c = read(0, &buf, 1);
     while (c != 0) {
       for ( i = 0; i < strlen(from); i++) {
            if(buf == from[i]) {
                write(1, to+i, 1);
                status = 1;
            }
	    }
        if (status == 0) { 
            write(1, &buf, 1); 
        }
	c = read(0, &buf, 1);
        status = 0;
   }
    			
}

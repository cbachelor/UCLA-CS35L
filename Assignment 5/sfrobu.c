#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int flagF = 0;

/*frobcmp with no flag*/
int frobcmp(char const * a, char const * b) {
  while (1) {
    if (*a == ' ' && *b == ' ')
      {
        return 0;
      }
    else if ((((*a)^42) > ((*b)^42)) || (*a == ' '))
     {
        return 1;
     }
    else if ((((*a)^42) < ((*b)^42)) || (*b == ' '))
      {
        return -1;
      }
    a++;
    b++;
  }
}

/*frobcmp with the f flag; applies uppercase*/
int frobcmpWf(char const * a, char const * b) {
    int upperA, upperB;
    int usedA, usedB;
  while (1) {
    upperA = ((int) (*a)^42);
    upperB = ((int) (*b)^42);

    if(upperA >= 0)
        usedA = toupper(upperA);
    else
        usedA = upperA;

    if(upperB >= 0)
        usedB = toupper(upperB);
    else
        usedB = upperB;

    if (*a == ' ' && *b == ' ')
      {
        return 0;
      }
    else if ((usedA > usedB) || (*a == ' '))
     {
        return 1;
     }
    else if ((usedA < usedB) || (*b == ' '))
      {
        return -1;
      }
    a++;
    b++;
  }
}
/*changes cmp depending on if -f flag is up*/
int frobcmpCaller(char const** a, char const** b) {
        if(flagF == 0)
	  return frobcmp(*a, *b);
        else if(flagF == 1)
	  return frobcmpWf(*a, *b);
}
/*if input is regular file*/
char* regFileRead(dev_t fileSize, int* tracker) {
    int c, size;
    int increment = 0;
    int last;
    char buf;
    char* arr = malloc(fileSize);
    size = fileSize;
    c = read(0, &buf, 1);
    while (c != 0) {
        arr[increment] = buf;
	if(buf != ' ')
	  last = increment;
        c = read(0, &buf, 1);
        increment++;
	/*increases size for changing file sizes*/
        if(increment >= size && c != 0) {
            arr = realloc(arr, size+1);
            size++;
        }
    }
    *tracker = last;
    return arr;
}

/*For piped input, etc */
char* noRegFileRead(int* tracker){
    char* arr = malloc(sizeof(char));
    char buf;
    int c, size;
    size = 1;
    c = read(0, &buf, 1);
    while (c != 0) {
        arr[size-1] = buf;
        c = read(0, &buf, 1);
        if(c != 0) {
	  arr = realloc(arr, size+1);
	  size++;
	}
    }
    if(buf == ' ')
      size--;
    *tracker = size;
    return arr;
}

int main(int argc, char **argv) {
  int k, i, wordSize, arrSize;
 int* tracker;
 int bufSize = 0;
 tracker = &bufSize;
 char prevChar = 'a';
 char* word = malloc(1);
 char* fileBuf;
 char** arr = malloc(sizeof(char *));
 char* flag = argv[1];
 if(argc == 1 ) {
   ;
 }
 else if(strcmp(argv[1], "-f") == 0){    /*checks for flags */
   flagF = 1;
 }
 else if(argc > 2) {
   fprintf(stderr, "Incorrect flag\n");
   exit(1);
 }

   /* allocating memory based on input */
  struct stat data;
  fstat(0, &data);
  if(S_ISREG(data.st_mode)) {
    fileBuf = regFileRead(data.st_size, tracker);
    }
  else {
    fileBuf = noRegFileRead(tracker);
    }   
    bufSize = *tracker;

    /* separate read input into different words */
    wordSize = 1;
    arrSize = 1;
    for (k = 0; k < bufSize; k++) {
        word[wordSize - 1] = fileBuf[k];
        if(k == bufSize - 1 && fileBuf[k] != ' '){
	  /*end case*/
            word = realloc(word, wordSize + 2);
            wordSize= wordSize + 2;
            word[wordSize - 2] = ' ';
	    word[wordSize - 1] = '\0';
	    arr[arrSize-1] = malloc(wordSize);
	    strcpy(arr[arrSize-1], word);
	    free(word);
	    break;
        }
        else if(word[wordSize -1] == ' '){
            if(prevChar != ' '){
	      /*allocates memory as words are separated by spaces*/
                prevChar = word[wordSize -1];
		word = realloc(word, wordSize + 1);
		wordSize++;
		word[wordSize - 1] = '\0';
		arr[arrSize-1] = malloc(wordSize);
                strcpy(arr[arrSize-1], word);
                arr = realloc(arr, sizeof(char*)*arrSize + sizeof(char*));
                arrSize++;
                free(word);
                word = malloc(1);
                wordSize  = 1;
            }
        }
        else {
	  /*default case*/
            word = realloc(word, wordSize + 1);
            prevChar = word[wordSize -1];
            wordSize++;
        }
    }
    free(fileBuf);
    if(arrSize > 1) {
      qsort(arr, arrSize, sizeof(char *), (int(*) (const void *, const void *)) frobcmpCaller);
    }
    for (k = 0; k < arrSize; k++) {
      i = 0;
      while(1) {       
	write(1, &(arr[k][i]), 1);
	if(arr[k][i] == ' ')
	  break;
	i++;  
      }
      free(arr[k]);
    }
    free(arr);
}

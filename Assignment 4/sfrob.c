#include <stdio.h>
#include <stdlib.h>

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

int frobcmpCaller(char const** a, char const** b) {
	return frobcmp(*a, *b);
}


int main() {
  char** arr = malloc(sizeof(char *));  /*allocate array of pointers to arrays*/
  int k;
  int *arrSizePtr;
  int arrSize = 1;
  arrSizePtr = &arrSize;
  int stringSize = 1;
  for (k = 0; k < arrSize; k++) {
      arr[k] = malloc(stringSize);     /*for each pointer to array allocate 1 char*/
    }
    int c;
    int* arrSize1 = arrSizePtr;
    int arrCounter = 0;
    int stringCounter = 0;
    char lastchar = 'a';
    while (1) {
      c = getchar();
      if (c == EOF) {
          if (arrCounter == 0 && stringCounter == 0) {
            *arrSize1 = 0;
            break;
          }
          if (lastchar != ' ') {
              arr[arrCounter] = realloc(arr[arrCounter], stringSize + 1);
	      arr[arrCounter][stringCounter] = ' ';
	      stringSize++;
	      stringCounter++;
	  }
	  /*arr[arrCounter] = realloc(arr[arrCounter], stringSize + 1);
	    arr[arrCounter][stringCounter] = '\0'; */
	arrCounter++;
	*arrSize1 = arrSize;
	break;          /* end in EOF*/
      }
      char ch = (char)c;
    arr[arrCounter] = realloc(arr[arrCounter], stringSize + 1);
    stringSize = stringSize + 1;	
    arr[arrCounter][stringCounter] = ch;
    stringCounter++;
    if (ch == ' ') {            /* Move to next string if there is space*/
      if(lastchar != ' ') {
	/*arr[arrCounter] = realloc(arr[arrCounter], stringSize + 1);
	  arr[arrCounter][stringCounter] = '\0'; */
	     arrCounter++;
            stringSize = 2;
            stringCounter = 0;
	    arr = realloc(arr, sizeof(char*)*arrSize + sizeof(char*));
	    arrSize = arrSize + 1;
            if (arr == NULL) {
              fprintf(stderr, "Problem reallocating3\n");
              exit(1);
            }
            arr[arrSize -1] = malloc(1);
      }
    }
    
      lastchar = ch;
    }
   
  if(arrSize !=0) {
    qsort(arr, *arrSize1, sizeof(char *), (int(*) (const void *, const void *)) frobcmpCaller);
  }
  /* for (k = 0; k < arrSize; k++) {
    printf("%s", arr[k]);
     free(arr[k]);
  }
  free(arr); */
  for(k = 0; k < *arrSize1; k++){
    for(c = 0; ; c++) {
      putchar(arr[k][c]);
      if(arr[k][c] == ' ')
	{
	  break;
	}
    }
    
      
    }
    
}
  




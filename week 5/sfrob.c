#include <stdio.h>
#include <stdlib.h>


int frobcmp(char const *a, char const *b)
{
  const char *arr1=*(char **)a;
  const char *arr2=*(char **)b;

  for( ; ;arr1++,arr2++)
    {
      int num_1=(int)*arr1;
      int num_2=(int)*arr2;

      if(num_1==32&&num_2==32)
	return 0;
      else if(num_1==32)
	return -1;
      else if(num_2==32)
	return 1;

      num_1^=42;
      num_2^=42;
      if(num_1>num_2)
	return 1;
      else if(num_1<num_2)
	return -1;
    }
  return 1;
}

int cmpfunc(const void *a,const void *b)
{
  return frobcmp(a,b);
}


int main()
{
  int size_input=30;

  char *input=(char*) malloc(sizeof(char)*size_input);

  if(input==NULL)
    {
      fprintf(stderr,"Can't allocate space for the input");
      exit(1);
    }

  int index=0;
  int word=getchar();
  while(word!=EOF)
    {
      input[index++]=(char)word;
      if(index==size_input)
	{
	  input=(char*) realloc(input,size_input*2);
	  size_input*=2;
	  if(input==NULL)
	    {
	      fprintf(stderr,"Can't allocate space for the input");
	      exit(1);
	    }
	}

      word=getchar();
    }

  if(index==0)
    exit(0);

  if(input[index-1]!=' ')
    {
      input[index]=' ';
      index++;
    }

  int countofwords=0;
  int i=0;
  for(i=0;i<index;i++)
    if(input[i]==' ')
      countofwords++;

  char *output=input;
  char **ptrtooutput=(char **)malloc(countofwords*sizeof(char*));

  if(ptrtooutput==NULL)
    {
      fprintf(stderr,"Can't allocate space");
      exit(1);
    }

  int k=0;
  int j=0;
  //might have problems
   for(k=0;k<index;k++)
    {
        if(input[k]==' ')
        {
            ptrtooutput[j]=output;
            j++;
            output=&input[k+1];
        }
    }

  qsort(ptrtooutput,countofwords,sizeof(char*),cmpfunc);


   int m;
    for(m=0;m<countofwords;m++)
    {
        char *toprint=ptrtooutput[m];
        while(*toprint!=' ')
        {
            putchar(*toprint);
            toprint++;
        }
        putchar(*toprint);
    }
    

  free(ptrtooutput);
  free(input);
  exit(0);
}

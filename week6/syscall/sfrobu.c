#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
int countcompare=0;

int frobcmp(char const *a, char const *b)
{
  countcompare++;
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
  
  struct stat filedata;
  int buf=1024;
  fstat(0,&filedata);
  int size_input=filedata.st_size;
  char *input;

  if(S_ISREG(filedata.st_mode))
  {
    input=(char*) malloc(sizeof(char)*size_input);
  }
  else
    {
      input=(char *) malloc(sizeof(char)*buf);
      size_input=buf;
    }

  if(input==NULL)
    {
      fprintf(stderr,"No memory for input");
      exit(1);
    }

  int index=0;
  char s;
  while(read(0,&s,1))
    {
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
     input[index++]=s;
    }
      
  if(index==0)
    exit(0);

  if(input[index-1]!=' ')
    {
      if(index!=size_input)
	{
           input[index]=' ';
           index++;
	}
      else
	{
	  size_input++;
	  input=(char *) realloc(input,sizeof(char)*size_input);
	  if(input==NULL)
            {
              fprintf(stderr,"Can't allocate space for the input");
              exit(1);
	    }
	  input[index]=' ';
	  index++;
	}
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
	    write(1,toprint,1);
            toprint++;
        }
        write(1,toprint,1);
    }


  free(ptrtooutput);
  free(input);
  fprintf(stderr,"Comparisons: %d\n",countcompare);
  exit(0);
}




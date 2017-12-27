#include <stdio.h>

int main(int argc, char** argv)
{
  if(argc!=3)
    {
      fprintf(stderr,"Wrong number of parameters");
      return 1;
    }


  int len1=0,len2=0;
  while(argv[1][len1]!='\0')
    {
      len1++;
    }

  while(argv[2][len2]!='\0')
    {
      len2++;
    }


  if(len1!=len2)
    {
      fprintf(stderr,"Different length of from and to");
      return 1;
    }

  int i,j;
  for(i=0;i<len1;i++)
    {
      for(j=i+1;j<len1;j++)
	if(argv[1][i]==argv[1][j])
	  {
	    fprintf(stderr,"Duplicates in from");
	    return 1;
	  }
    }

  char word[1];
  while(read(0,word,1))
    {
      int match=0;
      for(i=0;i<len1;i++)
	{
	if(argv[1][i]==*word)
	  {
	    *word=argv[2][i];
	    write(1,word,1);
	    match=1;
	    break;
	  }
	}
      if(match==0)
	write(1,word,1);
    }

  return 0;
}

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

  int word=getchar();
  int match=0;
  while(word!=EOF)
    {
      char cword=(char)word;
      for(i=0;i<len1;i++)
	{
	  if(argv[1][i]==cword)
	    {
	      putchar(argv[2][i]);
	      match=1;
	      break;
	    }
	}
      if(match==0)
	putchar(cword);
      match=0;
      word=getchar();
    }
  return 0;
}
  
	  
	
	   
	  

#!/usr/bin/python

import random, sys
from optparse import OptionParser

class comm:
    def __init__(self,file1):
        f1=open(file1,'r')
        self.lines=f1.readlines()
        f1.close()
        
    def getline(self):
        return self.lines

   
   

    
def main():
    version_msg="%prog 2.0"
    usage_msg="""%prog [-123] [-u] File1 File2 
    compare sorted files FILE1 and FILE2 line by
    line. With no option, produce 3 columns. 
    -1:Suppres column1
    -2:Suppress column2
    -3:Suppress column3
    -u:Compare two unsorted files
    """
    
    parser= OptionParser(version=version_msg,usage=usage_msg)
    parser.add_option("-1",action="store_true",dest="option1",default=False,help="suppress column1(lines unique to FILE1)")
    parser.add_option("-2",action="store_true",dest="option2",default=False,help="suppress column2(lines unique to FILE2)")
    parser.add_option("-3",action="store_true",dest="option3",default=False,help="suppress column3(lines in both FILE1 and FILE2)")
    parser.add_option("-u",action="store_true",dest="sortit",default=False,help="compare two unsorted files")
    
    options,args= parser.parse_args(sys.argv[1:])
    if len(args) != 2:
        parser.error("wrong number of operands")
    
    inputfile1=args[0]
    inputfile2=args[1]
    col1=[]
    col2=[]
    list1=[]
    list2=[]
    list3=[]
    toprint=[]

    
    if(inputfile1=="-"):
             col1=sys.stdin.readlines()
    else:
             generator1=comm(inputfile1)
             col1=generator1.getline()
    if(inputfile2=="-"):
             col2=sys.stdin.readlines()
    else:
             generator2=comm(inputfile2)
             col2=generator2.getline()

                      
    for cur in col1:
        for curl in col2:
               if(cur==curl):
                      list3.append(cur)
                      col2.remove(curl)
                      col1.remove(cur)
                      break 

    for cur in col1:
        if "\n" not in cur:
            cur+="\n"
    for cur in col2:
        if "\n"	not in cur:
            cur+="\n"
        
    list1=col1
    list2=col2
    
    if(options.option1&options.option2&options.option3):
        sys.stdout.write("")

    elif(options.option1&options.option2):
        for cur in list3:
         sys.stdout.write(cur)
        sys.stdout.write("\n")

    elif(options.option1&options.option3):
        for cur in list2:
          sys.stdout.write(cur)
        

    elif(options.option2&options.option3):
        for cur in list1:
          sys.stdout.write(cur)
        

    elif(options.option1):
        for cur in list2:
            toprint.append((0,cur))
        for cur in list3:
            toprint.append((1,cur))
        toprint=sorted(toprint,key=lambda x:x[1])
        for cur in toprint:
          sys.stdout.write('\t'*cur[0])
          sys.stdout.write(cur[1])
        sys.stdout.write("\n")
    
    elif(options.option2):
        for cur in list1:
            toprint.append((0,cur))
        for cur in list3:
            toprint.append((1,cur))
        toprint=sorted(toprint,key=lambda x:x[1])
        for cur in toprint:
          sys.stdout.write('\t'*cur[0])
          sys.stdout.write(cur[1])
        sys.stdout.write("\n")

    elif(options.option3):
        for cur in list1:
            toprint.append((0,cur))
        for cur in list2:
            toprint.append((1,cur))
        toprint=sorted(toprint,key=lambda x:x[1])
        for cur in toprint:
          sys.stdout.write('\t'*cur[0])
          sys.stdout.write(cur[1])
        sys.stdout.write("\n")

    elif(options.sortit):
     for cur in list1:
        sys.stdout.write(cur)
     sys.stdout.write("\n")
     for cur in list3:
        sys.stdout.write(2*"\t")
        sys.stdout.write(cur)

     for cur in list2:
        sys.stdout.write("\t")
        sys.stdout.write(cur)
     sys.stdout.write("\n")   
    
    else:
     for cur in list1:
      toprint.append((0,cur))
     for cur in list2:
      toprint.append((1,cur))
     for cur in list3:
      toprint.append((2,cur))
     toprint=sorted(toprint,key=lambda x:x[1])
     for cur in toprint:
      sys.stdout.write('\t'*cur[0])
      sys.stdout.write(cur[1])
     sys.stdout.write("\n") 

if __name__ == "__main__":
    main()


from fa import *
from reex import *
from fio import *
from cfg1 import *


f_2_10 = open('f_2_13.txt','a')

for i in range(1,100): 
              r = reStringRGenerator(smallAlphabet(5),size=5).generate() 
              f_2_10.seek(0)               
              f_2_10.write(str(str2regexp(r))+'\n')

f_2_10.close() 


#!/usr/bin/python

import urllib2  
import time    
from bs4 import BeautifulSoup  

time.clock()  
for i in range(1,2):  
    url = 'http://bj.lianjia.com/ershoufang/pg'+str(i)+'/'  
    page = urllib2.urlopen(url)  
    soup = BeautifulSoup(page)  
    for link in soup.find_all('div','houseInfo'):  
        context = link.get_text()  
        print(context)  
print(time.clock())  

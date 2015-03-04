# -*- coding: utf-8 -*-
"""
Created on Tue Mar  3 10:03:55 2015

@author: frederik
"""

import matplotlib.pyplot as plt
fig = plt.figure()
ax = fig.add_subplot(111)


result_file = 'build/test_results.txt'

f = open(result_file, 'r')

matches = []


for line in f:
    datalist = line.split(' ')
#    print int(datalist[0]), float(datalist[1][:-1])
      
    matches.append( ( float(datalist[1][:-1]) , int(datalist[0] ) ) ) 

#print matches

sorted_by_first = sorted(matches, key=lambda tup: tup[0])

#print sorted_by_first

sorted_by_first.reverse()

print sorted_by_first

precision = []
recall = []
lines = []

for i in range(0, len(sorted_by_first), len(sorted_by_first)/10 ):
    true = 0
    false = 0
    for index in range(i):
        if sorted_by_first[index][1]:
            true += 1
        else:
            false += 1
    try:
        print "precision", float(true)/(true + false )
        precision.append( float(true)/(true + false ) )
        print "recall", float(true)/len(sorted_by_first)
        recall.append( float(true)/len(sorted_by_first) )
    except:
        print 0
    
tmp, = plt.plot(precision, recall, label='Line 2')  

lines.append(tmp)

plt.xlim(0, 1) 
plt.ylim(0, 1) 

plt.xlabel('precision')
plt.ylabel('recall')
plt.legend([lines[0]], [ 'Precision Recall'])
plt.grid()
plt.show()        
    


#print od

#    if od[i] = 1:
#        true += 1
#    else:
#        false += 1
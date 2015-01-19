result_file = "video_states.txt"

f = open(result_file, 'w')

import numpy as np

for i in [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80]:
    f.write("0.0 " + str( i/180.0 * np.pi) + " 0.0\n")

result_file = "2D_states.txt"

f = open(result_file, 'w')

import numpy as np
for i in [0, 10, 20, 30, 40, 50, 60, 70, 80]:
    for j in [0, 10, 20, 30, 40, 50, 60, 70, 80]:
        f.write("0.0 " + str( i/180.0 * np.pi) + " " + str( j/180.0 * np.pi) + "\n")

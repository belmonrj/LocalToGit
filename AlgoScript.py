# Script to test for self-defind correlation

import math
import numpy as np

def Correlation(m,n,b,l):
    return b[math.ceil(m/l)][math.ceil(n/l)]

if __name__ == '__main__':
    m = int(input('number of particles(n): '))
    l = int(input('number of desired correlations(k): '))
    i,j = map(int, input("particle indices: ").split())
    b = np.identity(math.ceil(m/l), dtype = int)

    print(Correlation(i,j,b,l))

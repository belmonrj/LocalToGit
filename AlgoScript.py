# Script to test for self-defind correlation

import math
import random
import numpy as np
import matplotlib.pyplot as plt

def Correlation(m,n,b,l):
    return b[math.ceil(m/l)][math.ceil(n/l)]

def EventGenerator(mult,k):
    i = 0
    j = []
    b = np.identity(mult, dtype = int)
    while i <= mult:
        j.append(Correlation(random.randint(1,mult), random.randint(1,mult), b, k))
        i += 1
    return j

def SumOfEvents(runs,k):
    u = []
    for i in range(runs):
        return sum(EventGenerator(100,k)
if __name__ == '__main__':
#    m = int(input('number of particles(n): '))
#    l = int(input('number of desired correlations(k): '))
#    i,j = map(int, input("particle indices: ").split())
#    b = np.identity(math.ceil(m/l), dtype = int)

#    print(Correlation(i,j,b,l))

    plt.plot(EventGenerator(10000))
    plt.ylabel('correlations')
    plt.show()

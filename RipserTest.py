import numpy as np
from ripser import ripser
from persim import plot_diagrams

#rips = Rips()
#data = []
#for i in range(100):
#    data.append(random.randint(0,100))
#diagrams = rips.fit_transform(data)
#rips.plot(diagrams)
data = np.random.random((100,2))
diagrams = ripser(data)['dgms']
plot_diagrams(diagrams, show=True)

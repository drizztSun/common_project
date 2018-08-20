
import matplotlib.pyplot as plt
import numpy as np


def draw_complex_graph():

    x = np.random.random(size=10000)
    y = np.random.normal(loc=0., scale=1., size=10000)

    plt.figure()
    gspec = gridspec.GridSpec(3, 3)

    top_hist = plt.subplot(gspec[0, 1:])
    side_hist = plt.subplot(gspec[1:, 0])
    lower_right = plt.subplot(gspec[1:, 1:])

    lower_right.scatter(x, y)
    top_hist.hist(x, bins=100, normed=True)
    side_hist.hist(y, bins=100, orientation='horizontal', normed=True)
    side_hist.invert_xaxis()



def hotGraphic():


    plt.figure()
    y = np.random.normal(loc=0., scale=1., size=10000)
    x = np.random.random(size=10000)
    plt.hist2d(x, y, bins=25)


if __name__=="__main__":

    plt.figure()
    # First row, Second line
    plt.subplot(1, 2, 1)

    linear_data = np.arange(1, 9)
    plt.plot(linear_data, '-o')



    fig, ((ax1, ax2, ax3), (ax4, ax5, ax6)) = plt.subplots(2, 3, sharex=True, sharey=True)
    
    #ax5.plot(exponential_data, '-')
   

    pass

    
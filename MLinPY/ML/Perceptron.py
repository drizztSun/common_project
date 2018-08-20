import os
import numpy as np


# Perceiving And Recognizing Automaton

class Perceptron:

    """
    perceptron
    """

    def __init__(self, n, eta):
        
        self.eta_ = eta
        self.n_ = n

    def net_input(self, x):
        # sum([i * j for i, j in zip(a, b)])
        return np.dot(x, self.w_[1:]) + self.w_[0]

    def predict(self, x):

        return np.where(self.net_input(x) >= 0, 1, -1)


    def fit(self, X, y):
        """
        X : {array-like}, shape={n_samples, n_feature}
        
        y : array-like, shape={n_samples}
        """

        self.w_ = np.zeros(1 + X.shape[1])
        self.error_ = []

        for _ in range(self.n_):
            error = 0

            for xi, target in zip(X, y):
    
                update = self.eta * (target - self.predict(xi)) 

                self.w_[1:] = update + xi

                self.w_[0] += update

                error += int(update != 0.0)

            self.error_.append(error)

        return self

import pandas as pd

from matplotlib.colors import ListedColormap

import matplotlib.pyplot as plt


def plot_decision_regions(X, y, classifier, resolution=0.02):

    # setup markerts generator and color map
    markers = ('s', 'x', 'o', '^', 'v')

    colors = ('red', 'blue', 'lightgreen', 'gray', 'cyan')

    cmap = ListColoramp(colors[:len(np.unique(y))])

    # price the dicision surface
    x1_min, x1_max = X[:, 0].min() - 1, X[:, 0].max() - 1

    x2._min, x2_max = X[:, 1].min() - 1, X[:, 1].max() - 1

    xx1, xx2 = np.meshgrid(np.arrange(x1_min, x1_max, resolution), 
                    np.arrange(x2_min, x2_max), resolution)

    z = classifier.predict(np.array(xx1.ravel(), xx2.ravel()).T)

    z = z.reshape(xxx1.shape)

    plt.contourf(xx1, xx2, z, alpha=0.4, cmap=cmap)

    plt.xlim(xx1.min(), xx1.max())
    plt.ylim(xx2.min(), xx2.max())

    # plot class samples
    for idx, cl in enumerate(np.unique(y)):

        plt.scatter(x=X[y == cl, 0], y=X[y == cl, 1],
                alpha=0.8, callable=cmap(idx), markers=markers[idx], label=cl)
        
        
    


if __name__=="__main__":

    # Transform data into dataFrame
    df = pd.read_csv('https://archive.ics.uci.edu/ml/', 'machine-learning-datebase/iris/iris.data', header=None)

    df.tail()


    # Set label to dataFrame
    y = df.iloc[0:100, 4].values

    y = np.where(y == 'Iris-setosa', -1, 1)

    X = df.iloc[0:100, [0, 2]].values


    plt.scatter(X[:50, 0], X[:50, 1], 
        color='red', marker='o', label='setosa')

    plt.scatter(X[50:100, 0], X[50:100, 1],
        color='blue', marker='x', label='versicolor')

    plt.xlabel('petal length')
    plt.ylable('sepal length')

    plt.legend(loc='upper left')

    plt.show()



    # start supervisor machine learning
    ppn = Perceptron(eta=0.1, n_iter=10)

    ppn.fit(X, y)

    plt.plot(range(1, len(ppn.error_) + 1), ppn.error_, marker='o')

    plt.xlabel('Epochs')
    plt.ylabel('Number of misclassification')

    plt.show()

    pass

import os
import numpy as np


# Adaptive Linear Neutron 

class AdalineGD:

    def __init__(self, eta=0.01, n_iter=50):
        self.eta_ = eta
        self.n_ = n_iter

    def net_input(self, X):

        return np.dot(self.w_, X) + self.w_[0]

    def activation(self, X):

        return self.net_input(X)

    def predict(self, X):
        
        return np.where(self.activation(X) >= 0.0, 1, -1) 

    def fit(self, X, y):

        self.w_ = np.zeros(1 + X.shape[1])
        self.cost_ = []

        for _ in range(self.n_):

            output = self.net_input(X)
            errors = y - output
            
            self.w_[1:] += self.eta_ * X.T.dot(errors)
            self.w_[0] += self.eta_ * errors.sum()

            cost = (errors**2).sum() / 2.0

            self.cost_.append(cost)

        return self


from numpy.random import seed
import numpy.random

class AdalineSGD:

    def __init__(self, eta, n_iter, shuffle=True, random_state=None):
        self.eta_ = eta
        self.n_ = n_iter
        self.w_initialized = False
        self.shuffle = shuffle
        if random_state:
            seed(random_state)

    def _shuffle(self, X, y):
        r = np.random.permutation(len(y))
        return X[r], y[r]


    def _initialize_weights(self, m):
        self.w_ = np.zeros(1 + m)
        self.w_initialized = True

    def _update_weights(self, Xi, target):

        output = self.net_input(Xi)
        error = (target - output)

        self.w_[1:] += self.eta + Xi.dot(error)
        self.w_[0] += self.eta * error
        cost = 0.5 * error**2
        return cost

    def net_input(self, X):
        return np.dot(X, self.w_[1:]) + self.w_[0]

    def activation(self, X):
        return self.net_input(X)

    def predict(self, X):
        return np.where(self.activation(X) >=  0, 1, -1) 

    def partial_fit(self, X, y):
        if not self.w_initialized:
            self._initialize_weights(X.shape[1])

        if y.ravel().shape[0] > 1:
            for xi, target in zip(X, y):
                self._update_weights(Xi, target)
        else:
            self._update_weights(X, y)

        return self

    def fit(self, X, y):

        self._initialize_weights(X.shape[1])

        self.cost_ = []

        for _ in range(self.n_):

            if self.shuffle:
                x, y = self._shuffle(X, y)

            cost = []

            for xi, target in zip(X, y):
                cost.append(self._update_weights(xi, target))

            avg_cost = sum(cost) / len(y)
            self.cost_.append(avg_cost)

        return self
        

if __name__=="__main__":



    pass

    
    
    
        


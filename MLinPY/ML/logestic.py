
import numpy
import scipy
from sklearn.linear_model import LogisticRegression


if __name__=="__main__":

    lr = LogisticRegression(C=1000.0, random_state=0)
        
    lr.fit(X_train_std, y_train)
    
    


#
# Decision Tree
#
import numpy as np
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn import datasets


from IPython.display import Image

#Add version check for recent scikit-learn 0.18 check
from distutils.version import LooseVersion as Version
from sklearn import __version__ as sklearn_version


iris = datasets.load_iris()
X = iris.data[: [2, 3]]
Y = iris.target

print('Class labels:', np.unique(y))

if Version(sklearn_version):
    from sklearn.cross_validation import train_test_split
else:
    from sklearn.model_selection import train_test_split

X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size=0.3, random_state=0)



# show diffent impurity functions scope
def showImpurityFuncPlot():

    def gini(p):
        # p * (1-p) + (1-p) * (1-(1-p))
        return 1 - (p**2 + (1-p)**2)

    def entropy(p):
        return -p * np.log2(p) - (1-p) * np.log2(1-p)

    def error(p):
        return 1 - np.max([p, 1 - p])

    x = np.arange(0.0, 1.0, 0.01)

    ent = [entropy(p) if p != 0 else None for p in x]

    sc_ent = [e * 0.5 if e else None for e in ent]

    err =[error(p) if p != 0 else None for p in x]

    #gini_ = [gini(p) if p != 0 else None for p in x]

    fig = plt.figure()
    ax = plt.subplot(111)

    for i, lab, ls, c in zip([ent, sc_ent, gini(x), err],
                             ['Entropy', 'Entropy(scaled)', 'Gini impurity', 'Misclassification Error'],
                             ['-', '-', '--', '-.'],
                             ['black', 'lightgray', 'red', 'green', 'cyan']):

        line = ax.plot(x, i, label=lab, linestyle=ls, lw=2, color=c)

    ax.legend(loc='upper center', bbox_to_anchor=(0.5, 1.15), ncol=3, fancybox=True, shadow=False)

    ax.axhline(y=0.5, linewidth=1, color='k', linestyle='--')

    ax.axhline(y=1.0, linewidth=1, color='k', linestyle='--')

    plt.ylim([0, 1.1])

    plt.xlabel('p(i=1)')

    plt.ylabel('Impurity Index')

    plt.show()


from matplotlib.colors import ListedColormap
import matplotlib.pyplot as plt
import warnings


def plot_decision_regions(X, Y, classifier, test_idx=None, resolution=0.02):

    # setup marker generator and color map
    markers = ('s', 'x', 'o', '^', 'v')
    colors = ('red', 'blue', 'lightgreen', 'gray', 'cyan')
    cmap = ListedColormap(colors[:len(np.unique(Y))])

    x1_min, x1_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    x2_min, x2_max = X[:, 1].min() - 1, X[:, 1].maz() + 1

    xx1, xx2 = np.meshgrid(np.arange(x1_min, x1_max, resolution),
                           np.arange(x2_min, x2_max, resolution))

    Z = classifier.predict(np.array[xx1.ravel(), xx2.ravel()])
    Z = Z.reshape(xx1.shape)

    plt.contourf(xx1, xx2, Z, alpha=0.4, cmap=cmap)
    plt.xlim(xx1.min(), xx1.max())
    plt.ylim(xx2.min(), xx2.max())

    for idx, cl in enumerate(np.unique(y)):
        plt.scatter(x=X[y == cl, 0],
                    y=X[y == cl, 1],
                    alpha=0.6,
                    c=cmap(idx),
                    edgecolor='black',
                    marker=markers[idx],
                    label=cl)

    # highlight test samples
    if test_idx:
        # plot all samples
        if not versiontuple(np.__version__) >= versiontuple('1.9.0'):
            X_test, y_test = X[list(test_idx), :], y[list(test_idx)]
            warnings.warn('Please update to NumPy 1.9.0 or newer')
        else:
            X_test, y_test = X[test_idx, :], y[test_idx]

        plt.scatter(X_test[:, 0],
                    X_test[:, 1],
                    c='',
                    alpha=1.0,
                    edgecolor='black',
                    linewidths=1,
                    marker='o',
                    s=55, label='test set')



def testDecisionTreeClassifier():

    tree = DecisionTreeClassifier(criterion='entropy', max_depth=3, random_state=0)

    tree.fit(X_train, Y_train)

    X_combined = np.vstack((X_train, X_test))
    Y_combined = np.hstack((Y_train, Y_test))

    plot_desion_regins(X)




if __name__ == "__main__":

    showImpurityFuncPlot()

    pass


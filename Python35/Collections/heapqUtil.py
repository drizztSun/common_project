import os
import heapq




def heapsort(iterable):
    h = []
    for val in iterable:
        heapq.heappush(h, val)
    return [ heapq.heappop(h) for i in range(len(h)) ]




def main():

    A = [1, 6, 2, 5, 4, 3]
    
    B = heapsort(A)

    print(B)

    
    
    
    
    




if __name__=="__main__":


    pass
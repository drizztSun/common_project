import random
def jackpot_1999(a, b, c):
    i = 0
    while i < 10:
        secret = random.randint(1,10)

        print("GOLD RUSH",i)
        temp = input("guess")
        guess = int(temp)
        while guess != secret:
                temp = input("NOPE")
                guess =int(temp)
                if guess == secret:                             
                    print("+999999 golds")
                else:
                    if guess > secret:
                        print("smaller one")
                    else:
                        print("TOO SMALL")            
        i = i + 1

#bingo ='popeyes and marki marki' 
#answer = input('What do i want to eat today')

#while True:
    #if answer == bingo:
        #break
    #answer = input("?")
#print("that's better")        


# cal(1, 2, '+') 3
# cal(3, 4, '*') 12
# cal(3, 1, '-') 2
# cal(6, 2, '/') 3

# operator, 1, 2

# logical operator
# not(1), and, or (2)
# !, &&, ||

def cal(a, b, c):
    print(type(a), type(b))
    if (type(a) != int and type(a) != float) or (type(b) != int and type(b) != float):
        print("ERROR")    
        return
  
    if c == "+":
        return a + b
    elif c == '-':    
        return a - b
    elif c == '*':
        return a * b
    elif c == '/':
        
        if b == 0:
            print("(ERROR)")
            return    
        return a / b




def test_list():

    a = [1, 2, 3, 4, 5, 6]

    print(a)

    i = 0
    while i < len(a):
        a[i] += 1
        i += 1

    for i in range(len(a)):
        print(a[i])

    print( max(a) )
    print( min(a) )
    print( sum(a) )
    print( list(sorted(a)) )
    print( list(reversed(a)) )
    #print( list(enumerate(a)) )
    #print(list(zip(a)))
    print( dir(a) )

    a.append('200')
    print( a )

    print("pop ele: ", a.pop() )

    print( a.extend([123456789,987654321,'matt']) )
    print( a.count(1) )
    print( a.reverse() )
    a.sort()
    print( a )
    a.sort(reverse=True)
    print( a )
    
    print( a.index(6) )
    print( a.remove('100') )
    
    a.append([11])
    a.extend([[11],22])
    
    for i in range(len(a)):
        print(a[i])

    i = 0
    while i < len(a):
        print(a[i])
        i +=1
    
    



    






class Cat(object):

    def __init__(self):
        pass

    def run(self):
        self._speed = 10


def partcal1(n):
    res = n
    for i in range(1,n):
        res *=i
    return res



def fact_recur(n):
    if n == 0:
        return 1
    return n * fact_recur(n-1)

print(fact_recur(5))


def f(n):
    if n == 2 or n == 1:
        return 1
    return f(n-1)+f(n-2)
    
        
print(f(4))
        
def han(n,x,y,z):
    if n == 1:
        print(x,'-->',z)
    han(n-1,x,z,y)    
    print(x,'-->',z)
    han(n-1,)

                  
      
     

if __name__ == '__main__':
    print(partcal1(5))
    print(dir(__builtins__))


    b = [ i for i in range(101)]

    total = 0
    for i in range (101):
        total += b[i]

    print(total)

    


    a = [ [ i for i in range(10) ] for _ in range(10)]
    e = 0
    for i in range(10):
        for j in range(10):
            e +=a[i][j]
    print(e)


    s = [ [ [i for i in range(10) ] for _ in range(10) ] for _ in range(99)]
    f = 0
    for i in range(99):
        for j in range(10):
            for k in range(10):
                f +=s[i][j][k]
    print(f)            



    a = 1234567890
    b = 9876543210
    c = 3.141592653
    #jackpot_1999(a,b,c)

    p = cal(1, 2, '+')
    p = cal(3, 4, '*')
    p = cal(3, 1, '-')
    p = cal(6, 2, '/')
    p = cal(4, 0, '/')
    p = cal(999, 999, '*')
    p = cal(0.92, 0.23,'*')
    p = cal('mom','dad','*')

    target = [(1, 2, '+'), (2, 3, '*')]
    i = 0
    while i < len(target):
        
        a = target[i][0]
        b = target[i][1]
        c = target[i][2]
        p = cal(a, b, c)
        print(p)
        i += 1


    for i in range(len(target)):
        
        a = target[i][0]
        b = target[i][1]
        c = target[i][2]
        p = cal(a, b, c)
        print(p)
    
    c = Cat()
    c.run()

    
    a = [800,1,3,4,2,4,2,5,2,2,8,90,67,45,22,2,3,40,]

    print(a.count(2))




    def count2(a, b):
        n = 0
        for i in range(len(a)):
            if a[i] == b:
                n = n + 1
        return n

    print(count2(a, 2))



        
    
        
        

        

def can_divided_by5(a):
    i = 0
    while i < len(a):

        if a[i] % 5 == 0:
            return True
            break
        
        a[i] *= 2
        i = i+1
    else:
        return False
        print("There is no number divided by 5")

def BIG(a):
    i = 0
    while i<len(a):
        a[i] = a[i]**2
        i +=1

print("why")


a = [1,2,3,4,5,6,7,8,9]
BIG(a)
print(a) 

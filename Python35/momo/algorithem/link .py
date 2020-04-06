class node:
	def __init__(self, data):
		self._data = data
		self._next = None


def search(head,data):
    while head.next:
        if head == data:
            return head
        head = head.next

def makelink(arr):
    head = tail = None
    for i in arr:
        if head == tail == None :
            head = tail = node(i)
        else:
            tail._next = node(i)
            tail = tail._next
    return head

class dnode:
    def __init__(self, data):
        self._data = data
        self.__dadeatpoop = 'dadeatpoop'
        self._next = None
        self._prev = None

def makeDlink(arr):
    head = tail = None
    for i in arr:
        if head == tail == None:
            head = tail = dnode(i)

        else:
            tmp = dnode(i)
            tmp._prev = tail
            tail._next = tmp
            tail = tail._next
    return head, tail


def reverse(head):
    new_head = None
    
    while head:
        dep = head._next
        if new_head == None:
            new_head = head
            new_head._next = None
        else:
            head._next = new_head  
            new_head = head
        head = dep
    return new_head
   
def Dlinkreverse(head, tail):
    new_head = None
    new_tail = None
    
    while head:
        dep = head._next
        if new_head == None and new_tail == None:
            new_head = head
            new_tail = new_head
            new_head._next = None
            head = dep

        else:
           new_head._prev = head
           head._next = new_head
           head._prev = None
           new_head = head
           head = dep 
    return new_head, new_tail


def even_first_odd_last(head):
    ehead, m = None, None
    ohead, h = None, None
    
    while head:
        next_ = head._next
        if head._data % 2 == 0:
            if ehead == None:
                ehead = head
                h = ehead
            else:
                ehead._next = head
                ehead = ehead._next
            ehead._next = None
        else:
            if ohead == None:
                ohead = head
                m = ohead
            else:
                ohead._next = head
                ohead = ohead._next 
            ohead._next = None   
        head = next_
        
    if ehead == None:
        return m	
    ehead._next = m
    return h


if __name__ == "__main__":
    

    print(makeDlink(arr= [1, 2, 3, 4, 5, 6, 7, 8])) 

    print(type(SyntaxError))

    print(reverse(head = makelink(arr=[1, 2, 3, 4, 5])))

    t = makeDlink(arr=[1, 2, 3])
    print(Dlinkreverse(head = t[0], tail= t[1]))
    
    t = makelink(arr=[2, 4, 6, 8, 10])
    even_first_odd_last(t)
    
    t = makelink(arr=[1, 3, 5, 7, 9])
    even_first_odd_last(t)

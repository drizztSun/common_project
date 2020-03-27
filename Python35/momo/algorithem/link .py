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
            head = tail = node(i)

        else:
            tmp = node(i)
            tmp._prev = tail
            tail._next = tmp
            tail = tail._next
    return head._data, tail._data


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
   
      



if __name__ == "__main__":
    

    
    
    print(makeDlink(arr= [1, 2, 3, 4, 5, 6, 7, 8])) 

    print(type(SyntaxError))

    print(reverse(head = makelink(arr=[1, 2, 3, 4, 5])))




















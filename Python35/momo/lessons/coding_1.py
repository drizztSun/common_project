

def number_generator(nums):

    res = []

    for hundred in nums:
        for tens in nums:
            for ones in nums:
                res.append(100*hundred + 10*tens + ones)

    return res

# 235 = 2 * 100 + 3 * 10 + 5  4 * 4 *4

if __name__ == '__main__':


    nums = [2, 3, 5, 7]

    # build hundreds
    for hundreds in nums: # 2, and them 3, and then 5, ..7

        # build tens
        for tens in nums: # 2.. 3.. 5.. 7

            for ones in nums:

                if not (hundreds == tens or tens == ones or hundreds == ones): # hundreds != tens and tens != ones and hundreds != ones

                    print(hundreds * 100 + tens * 10 + ones) # 2, 3 ,5  235



    # print( number_generator(nums=[2, 6, 9, 7]) )

    print("Hello, Python!")

    a = [1, 2, 3, 4, 5, 6]  # list

    print(a)

    # index

    print(a[0])

    print(a[1])

    index = 0  # 0 is start index of list

    print(len(a))  # len() bulit-in function to check the length of something, like list. 0 is start index, last index will be 'len(a) - 1',  len(a) always return the boundary of end

    # i = 0

    # while i < len(a):

    # list object's func

    # list

    a.append(7)  # put new element at the end of list

    a.append(8)

    print(a)

    print(a.pop())  # pop out the end element of the list.

    print(list(range( 6)))  # built-in fucntion, range(start, end, step), range(1, 6) [1, 2, 3, 4, 5] no ending value. start is 0 by default, step is 1 by default

    for i in range(len(a) + 1):  # i will be index

        print(i)

        if a[i] % 2 == 1:

            print(f'odd number {a[i]}')

        elif a[i] % 2 == 0:

            print(f'even number {a[i]}')

    for c in a:  # a is iterable object, c will be copy of element in list.

        if c % 2 == 1:

            print(f'odd number {c}')

        elif c % 2 == 0:

            print(f'even number {c}')


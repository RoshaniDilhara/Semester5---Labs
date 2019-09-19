#!/usr/bin/python

def fib_r(x) :
    if (x <= 2):
        return 1
    return fib_r(x-1) + fib_r(x-2)


def fib_i(x) :
    a = 1
    b = 1
    fib = 1
    i = 2
    while i < x:
        fib = a +b
        a = b
        b = fib
        i+=1
        
    return fib

x = 40

for i in range (0,41):
    import time
    start = time.time()
    k = str(fib_r(i))
    #print(k)
    #print("Fib of " + str(i) + " = " + str(fib_r(i)))
    endR = time.time()
    print((endR - start)*1000)

print("---------------------")    

for j in range (0,41):
    import time
    start = time.time()
    l = str(fib_i(j))
    #print(l)
    #print ("Fib of " + str(j) + " = " + str(fib_i(j)))
    endI = time.time()
    print((endI - start)*1000)





import numpy as np

t = 20

print(t)
for test in range(t):
    N = np.random.randint(1,high=5)
    M = np.random.randint(1,high=5)
    print(N,M)

    a = ""
    for i in range(N):
        c = np.random.randint(1,high=5)
        a += str(c)+" "
    print(a)

    for i in range(N):
        b = ""
        for j in range(M):
            d = np.random.randint(1,high=5)
            b += str(d)+" "
        print(b)

    print()
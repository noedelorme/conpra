import numpy as np

t = 20

print(t)
for test in range(t):
    n = np.random.randint(1,high=16)
    m = np.random.randint(0,high=max(2,round(n/2)))
    print(n)
    board = [['.' for i in range(n)] for j in range(n)]

    for i in range(m):
        x = np.random.randint(0,high=n)
        y = np.random.randint(0,high=n)
        board[x][y]='x'
    

    for i in range(n):
        a =""
        for j in range(n):
            a+=board[i][j]
        print(a)
    print()
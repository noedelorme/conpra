from sys import stdin, stdout

# *****************************************************
# Using Lucas' and Fermat's little theorem to calculate nCk (binomial coeff) mod m, m is prime
# Source: https://fishi.devtail.io/weblog/2015/06/25/computing-large-binomial-coefficients-modulo-prime-non-prime/
# *****************************************************

# modular exponentiation: b^e % mod 
# python's built-in pow(b,e,mod) would be faster than this function, 
# but I am still keeping it here for completion
def mod_exp(b,e,mod):
    r = 1
    while e > 0:
        if (e&1) == 1:
            r = (r*b)%mod
        b = (b*b)%mod
        e >>= 1

    return r

# get degree of p in n! (exponent of p in the factorization of n!)
def fact_exp(n,p):
    e = 0
    u = p
    t = n
    while u <= t:
        e += t//u
        u *= p

    return e

# convert given number n into array of its base b representation
# most significant digit is at rightmost position in array
def get_base_digits(n,b):
    d = []
    while n > 0:
        d.append(n % b)
        n  = n // b

    return d

# Using Fermat's little theorem to compute nCk mod p
# considering cancelation of p in numerator and denominator
# Note: p must be prime
def fermat_binom_advanced(n,k,p):
    # check if degrees work out
    num_degree = fact_exp(n,p) - fact_exp(n-k,p)
    den_degree = fact_exp(k,p)
    if num_degree > den_degree:
        return 0

    if k > n:
        return 0

    # calculate numerator and cancel out occurrences of p
    num = 1
    for i in range(n,n-k,-1):
        cur = i
        while cur%p == 0:
            cur //= p
        num = (num*cur)%p

    # calculate denominator and cancel out occurrences of p
    denom = 1
    for i in range(1,k+1):
        cur = i
        while cur%p == 0:
            cur //= p
        denom = (denom*cur)%p

    # numerator * denominator^(p-2) (mod p)
    return (num * mod_exp(denom,p-2,p))%p

# Using Lucas' theorem to split the problem into smaller sub-problems
# In this version assuming p is prime
def lucas_binom(n,k,p):
    # get n and k in base p representation
    np = get_base_digits(n,p)
    kp = get_base_digits(k,p)

    # calculate (nCk) = (n0 choose k0)*(n1 choose k1) ... (ni choose ki) (mod p)
    binom = 1
    for i in range(len(np)-1,-1,-1):
        ni = np[i]
        ki = 0
        if i < len(kp):
            ki = kp[i]

        binom = (binom * fermat_binom_advanced(ni,ki,p)) % p

    return binom


# *****************************************************
# Compute Chinese Remainder
# Source: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
# *****************************************************

# Returns modulo inverse of a with respect to m using extended Euclid Algorithm.
def inv(a, m) :
     
    m0 = m
    x0 = 0
    x1 = 1
 
    if (m == 1) :
        return 0
 
    # Apply extended Euclid Algorithm
    while (a > 1) :
        # q is quotient
        q = a // m
 
        t = m
 
        # m is remainder now, process
        # same as euclid's algo
        m = a % m
        a = t
 
        t = x0
 
        x0 = x1 - q * x0
 
        x1 = t
     
    # Make x1 positive
    if (x1 < 0) :
        x1 = x1 + m0
 
    return x1
 
# k is size of num[] and rem[].
# Returns the smallest
# number x such that:
# x % num[0] = rem[0],
# x % num[1] = rem[1],
# ..................
# x % num[k-2] = rem[k-1]
# Assumption: Numbers in num[]
# are pairwise coprime
# (gcd for every pair is 1)
def findMinX(num, rem, k) :
     
    # Compute product of all numbers
    prod = 1
    for i in range(0, k) :
        prod = prod * num[i]
 
    # Initialize result
    result = 0
 
    # Apply above formula
    for i in range(0,k):
        pp = prod // num[i]
        result = result + rem[i] * inv(pp, num[i]) * pp
     
     
    return result % prod



# *****************************************************
# I didn't manage to implement my own version of the algorithms (Binomial coefficient modulo primes and Chinese Remainder) with C++.
# So I used implemenattions found on the Internet to perform those two steps one after the other.
# (Sources are given above.)
# Step 1: I Compute the binomial coefficient modulo each primes factor of 223092870
# Step 2: I use the Chinese remainder theorem to compite the binomial coefficient modulo 223092870
# *****************************************************

def main():
    t = int(stdin.readline())
    for testcase in range(t):
        n,m = stdin.readline().split()
        n = int(n)
        m = int(m)
        
        primes = [2,3,5,7,11,13,17,19,23]
        coeffs = []
        for i in range(9):
            coeffs.append(lucas_binom(n,m,primes[i]))

        print("Case #"+str(testcase+1)+":", findMinX(primes, coeffs, 9))

if __name__ == "__main__":
    main()
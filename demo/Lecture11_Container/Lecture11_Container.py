"""这里使用两种方法对一个列表进行求和"""

def mysum(L):
    """Use recursion to sum a list"""
    if L == []:
        return 0
    else:
        return L[0] + mysum(L[1:])

def sum_iter(L):
    sum = 0
    for element in L:
        sum += element
    return sum

"""list conprehension"""
def divisiors(n):
    """get the divisor of n"""
    return [1] + [x for x in range(2, n) if n%x == 0]

def reverse(str):
    """Reverse a string"""
    if len(str) == 1:
        return str
    else:
        return reverse(str[1:]) + str[0]

"""A example of data abstraction(Although it is betterb to use class"""
# Constructor
def gcd(x, y):
    """return the greatest common divisor of x and y"""
    if x < y:
        g = x
    else:
        g = y
    while (x % g != 0 or y % g != 0 ) and g > 1:
        g -= 1
    return g
    

def rational(n, d):
    """Create a rational number"""
    g = gcd(n, d)
    return [n // g, d // g]

def numer(x):
    """return the numerator of x"""
    return x[0]

def denom(x):
    """Return the denominator of x"""
    return x[1]

"""Another version of rational using higher-order function
def rational(n, d):
    '''Create a rational number using higher-order function'''
    def selecter(name):
        if name == 'n':
            return n
        elif name == 'd':
            return d
    return selecter

def numer(x):
    # Notice that in this example, rational number is a function, 
    # which is created a higher-order function
    return x('n')

def denom(x):
    return x('d')
"""

def add_rational(x, y):
    """Add two rational numbers"""
    return rational(numer(x) * denom(y) + numer(y) * denom(x), denom(x) * denom(y))

def mul_rational(x, y):
    """multiply two rational numbers"""
    return rational(numer(x) * numer(y), denom(x) * denom(y))

def equal_rational(x, y):
    """Whether x is equal to y"""
    return numer(x) * denom(y) == numer(y) * denom(x)

def print_rational(x):
    """Print a rational number"""
    print(numer(x), "/", denom(x))
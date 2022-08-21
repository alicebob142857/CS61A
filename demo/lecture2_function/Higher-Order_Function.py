"""Generalization"""
from math import pi, sqrt

def Area(r, shape_const):
    assert r > 0, 'A length must be positive'
    # assert相当于c++的异常抛出，如果前一个第一个表达式为false,则抛出第二个表达式
    return r * r * shape_const

def Area_square(r):
    return Area(r, 1)

def Area_circle(r):
    return Area(r, pi)
def Area_hexagon(r):
    return Area(r, 3 * sqrt(3) / 2)

def Identity(k):
    return k

def Cube(k):
    return pow(k, 3)

def Summation(n, term):
    """Sum the first N terms of a sequece
    
    >>> Summation(5, Cube)
    225
    >>> Summation(5, Identity)
    15
    """
    total, k = 0, 1
    while k <= n:
        total, k = total + term(k), k + 1
    return total

def Sum_naturals(n):
    """Sum the first N natural number
    
    >>> Sum_naturals(5)
    15
    """
    return Summation(n, Identity)

def sum_cubes(n):
    """sum the first N cubes of natural number

    >>> sum_cubes(5)
    225
    """
    return Summation(n, Cube)

def make_adder(n):
    """Return a function that takes k and return k + N
    
    >>> add_three = make_adder(3)
    >>> add_three(4)
    7
    """
    def adder(k):
        return k + n
    return adder
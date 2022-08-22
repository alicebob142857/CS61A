# Introduction

## 1. 英文词汇
parenthesis 圆括号
precedence 优先级
remainder 余数
quotient 商
compound statement 复合语句
suite of the clause 嵌套从句
abbreviation 缩写

## 2. Function
```
def <name>(<formal parameters>):
    return <return expression>
```
squirrel 隐藏

## 3. Control and None

### 3.1 None
python中没有返回值的函数，实际上返回的是None
```
print(print(1), print(2))
```
最后的输出为
```
1
2
None None
```

### 3.2 Pure Function纯函数
Pure function : 返回具体的值
Non-pure function : 除了返回值外有其他的作用

### 3.3 miscellaneous python feature复杂的python特性

#### 3.3.1 除法
/ 浮点除法 floordiv
// 整数除法 truediv
% 取余数 mod

#### 3.3.2 interpreter and doctest
python3 -i <filename>.py
以interactive interpreter的方式，导入py文件
```
"""一个python示例"""
from operator import floordiv, mod

def divide_exact(n, d):
    """Return the quotient and remainder of dividing N by D
    >>> q, r = divide_exact(2013, 10)
    >>> q
    201
    >>> r
    3
    """
    return floordiv(n, d), mod(n, d)
```
可以通过输入python3 -m doctest <filename>.py来模拟文档化注释中的样例输出 
如果得到了和预期一样的输出，终端上将没有输出
输入python3 -m doctest -v <filename>.py将得到具体的检查情况

### 3.4. 函数设计
1. 一个函数只执行一个特定任务
2. 最好不要写重复的代码
3. 通用地定义函数

## 4. Higher-Order Function高阶函数
高阶函数：以函数为形参或者以函数为返回值的函数
优势：
1. 抽象化
2. 避免代码重复
3. 便于一个函数处理一个工作
### 4.1. 设计函数的例子
```
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
```

### 4.2. 将函数名作为参数传入
```
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
```

### 4.3. Function as return values将函数名作为参数传出
```
def make_adder(n):
    """Return a function that takes k and return k + N
    
    >>> add_three = make_adder(3)
    >>> add_three(4)
    7
    """
    def adder(k):
        return k + n
    return adder
```

## 5. lambda expression
### 5.1. lambda Expression
lambda表达式：将一个函数表达式和一个名字绑定
```
>>> x = 10
>>> square = x * x
>>> x
10
>>> square
100
>>> square = lambda x: x * x
>>> square(4)
16
>>> square(10)
100
>>> (lambda x: x * x)(3)
9
```

### 5.2. Lambda Expression VS Def Statements
区别：
lambda表达式是没有名字的，而函数是有intrinsic name的

## 6. Control 控制表达式
### 6.1. 为什么不用函数代替statement？
statement在执行的过程中可以选择跳过或者重复某些语句，但是函数必须执行每一个形参。这是函数无法代替的特性。

### 6.2. Control Expressions
#### 6.2.1. short circuiting
逻辑表达式and 和 or 会出现短路的现象导致右侧表达式不会被执行。这一点和cpp相似，值得注意。
```
from math import sqrt
def has_big_sqrt(x):
    return x > 0 and sqrt(x) > 10
    
python3 -i <filename>.py
>>> has_big sqrt(-1000)
False
```
注意，这里不会出现报错。如果没有短路现象，那么and表达式右侧就会被执行，对负数进行开方操作是会报错的。然而由于存在短路现象，在左侧x > 0 为False后，就不会执行右侧的语句了。

#### 6.2.2. Conditional Expression
<consequent> if <predicate> else <alternative>
```
x = 0
abs(1 / x if x != 0 else 0)
"""等价于
x = 0
if x != 0:
    abs(1 / x)
else:
    0
"""
```

## 7. Function

### 7.1. Self Reference
一个函数可以将自己作为返回值
```
def print_all(x):
    print(x)
    return print_all
    
>>> print_all(1)(2)(3)
1
2
3
```
```
>>> def print_sum(x):
...     print(x)
...     def next_sum(y):
...         return print_sum(x + y)
...     return next_sum
... 
>>> print_sum(1)(2)(3)
1
3
6
```

### 7.2. Function Currying
我们看到，make_adder函数可以生成add_three, add_three可以做加法，同时，我们有add函数，可以直接做加法
```
>>> add_three = make_adder(3)
>>> make_adder(3)(2)
5
>>> add(3, 2)
5
```
我们用adder来构造make_adder
```
def curry2(f):
    def g(x):
        def h(y):
            return f(x, y)
        return h
    return g

>>> m = curry2(add)
>>> add_three = m(3)
>>> add_three(2)
5
>>> curry = lambda f: lambda x: lambda y: f(x, y)

```
Curry: 将多参数的函数转化为单参数的Higher-Order Function

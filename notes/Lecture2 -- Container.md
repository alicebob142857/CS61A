# Lecture 2

## 0 英文词汇
numerator 分子
denominator 分母


## 1. List
相比于C++, Python的列表有一些特殊的语法
```
>>> array1 = [1, 2]
>>> array2 = [3, 4]
>>> array1 + array2 * 2
[1, 2, 3, 4, 3, 4]
```

## 2. Container
### 2.1. build-in operator
```
>>> digits = [1, 2, 3]
>>> 1 in digits
True
>>> 4 in digits
False
>>> 4 not in digits
True
```
## 2.2. Range
range(a, b): `$a\le x<b$`范围内所有的连续整数值
range不是list
```
>>> range(2)
range(0, 2)
>>> list(range(2))
[0, 1]
```
range可以用来使for循环重复特定的次数
```
def cheer():
 for _ in range(3):
    print('Go Bears!')
```

## 2.3. List Conprehension 列表推导式
```
>>> odds = [1, 3, 5, 7, 9]
>>> [x + 1 for x in odds]
[2, 4, 6, 8, 10]
>>> [x for x in odds if 25 % x == 0]
[1, 5]
```

## 2.4. string
n.b.string可以用来表示代码
```
>>> 'print("Hello world")'
'print("Hello world")'
>>> exec('print("Hello world")')
Hello world
```
string也是一种sequence(就像C里面的字符串数组一样)
```
>>> city = 'Berkeley'
>>> len(city)
8
>>> city[3]
'k'
```
值得注意的是，string中的in和not in，不是寻找string中包含的字符，而是寻找string中包含的子字符串
```
>>> '天真' in '今天真热'
True
```

## 3. Data Abstraction
### 3.1. Pairs
Pair可以用list来表示，通过unpacking来获得取值
```
>>> pair = [1, 2]
>>> x, y = pair
>>> x
1
>>> pair[0]
1
>>> from operator import getitem
>> getitem(pair, 0)
1
```

### 3.2. Data Abstraction思想
<img src="https://s2.loli.net/2022/08/23/79YkwmQXxcANRIg.png" width="100%">
外部接口<-内部私有数据结构<-底层实现，要分别进行封装，隐藏和抽象。
首先，选取合适的数据结构，将核心的数据进行封装（比如rational使用list）
其次，对外封装数据（将rational的分子和分母用函数接口，而不是直接使用x[0], x[1]进行调用）
最后，对外封装方法

```
"""A example of data abstraction(Although it is betterb to use class"""
# Constructor
def rational(n, d):
    """Create a rational number"""
    if n > d:
        g = d
    else:
        g = n
    while (n % g != 0 or d % g != 0) and g > 1 :
        g -= 1
    return [n // g, d // g]

def numer(x):
    """return the numerator of x"""
    return x[0]

def denom(x):
    """Return the denominator of x"""
    return x[1]

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
```
由于进行了数据的抽象，我们甚至可以用函数实现rational number的数据结构，这样对data representation的修改不影响公用接口的调用
```
"""Another version of rational using higher-order function"""
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
```

### 3.3. dictionary字典
1. 花括号创建字典
```
a = {'I': 1, 'V':5, 'X':10}
```
注意，在字典中，键值对是无序的

2. 可以通过键访问值，但不能通过值访问键
```
>>> a['X']
10
>>> a[10]
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
KeyError: 10
```
3. 一些相关的函数。这些函数返回的是相关数据的list
```
>>> a.keys()
dict_keys(['I', 'V', 'X'])
>>> a.values()
dict_values([1, 5, 10])
>>> a.items()
dict_items([('I', 1), ('V', 5), ('X', 10)])
```
4. 通过dict可以将键值对list转化为dictionary
```
>>> items = a.items()
>>> items
dict_items([('I', 1), ('V', 5), ('X', 10)])
>>> dict(items)
{'I': 1, 'V': 5, 'X': 10}
```
5. in

get()方法输入键后返回值。如果在字典中没有这个键，则返回输入的默认值
```
>>> 'X' in a
True
>>> 'X-ray' in a 
False
>>> a.get('X', 0)
10
>>> a.get('X-ray', 0)
0
```
6. dictionary conprehension
```
>>> {x: x * x for x in range(10)}
{0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81}

```

7. 键值不能重复，否则会随机返回其中一个值
```
>>> {1: 2, 1: 3}
{1: 3}
```

8. Limitations

值可以是list, 但是键不可以是list(键不可以是list, dictionary, 以及其他一切mutable的数据类型, 键只能是常量)
```
>>> {1: [1]}
{1: [1]}
>>> {[1]: 1}
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: unhashable type: 'list'
```
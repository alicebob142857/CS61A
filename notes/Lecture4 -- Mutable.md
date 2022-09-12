# Mutable
## 1. Mutable Sequence
### 1.1. string的类方法
```
>>> s = 'Hello'
>>> s.upper()
'HELLO'
>>> s.lower()
'hello'
>>> s.swapcase()
'hELLO'
>>> s
'Hello'
```
### 1.2. ASCII码
```
>>> a = 'A'
>>> ord(a)
65
>>> hex(ord(a))
'0x41'
>>> # Notice that 0x41 tells the position of 'A' in ASCII
>>> # row 4 line 1
```

<img src="https://s2.loli.net/2022/09/07/PRrMETKYZH5JNua.png" width="100%">

由于历史原因，ASCII码中保留着一些特殊的字符。比如'BEL'(\a)，表示电脑提示音，输入这个字符电脑会发出‘登登登’的声音

### 1.3. Unicode
```
>>> from unicodedata import name, lookup
>>> name('A')
'LATIN CAPITAL LETTER A'
>>> name('你')
'CJK UNIFIED IDEOGRAPH-4F60'
>>> lookup('WHITE SMILING FACE')
'☺'
>>> lookup('SNOWMAN')
'☃'
>>> lookup('BABY')
'👶'
>>> lookup('BABY').encode()
b'\xf0\x9f\x91\xb6'
>>> lookup('A').encode()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
KeyError: "undefined character name 'A'"
>>> 'A'.encode()
b'A'
```

### 1.4. List
```
>>> suits = ['coin', 'string', 'myriad']
>>> original_suits = suits
>>> # pop the last element of a list
>>> suits.pop()
'myriad'
>>> suits.remove('string')
>>> suits
['coin']
>>> # Add a new element to the end of list
>>> suits.append('cup')
>>> # Add a list to the end of the original list
>>> suits.extend(['sword', 'club'])
>>> suits
['coin', 'cup', 'sword', 'club']
>>> suits[2] = 'spade'
>>> suits[0:2] = ['heart', 'diamond']
>>> suits
['heart', 'diamond', 'spade', 'club']
```
值得注意的是，如果将两个list相互赋值的话，这两个变量会指向同一块内存。原因可能是，list对象之间的赋值使用的是浅赋值，只是赋值了指针，没有复制指针指向的内存。可以使用切片的方法制造副本。
```
>>> a = [1]
>>> b = a
>>> b == a
True
>>> a.append(2)
>>> a == b
True
>>> a
[1, 2]
>>> b
[1, 2]
>>> c = a[:]
>>> a.append(3)
>>> c
[1, 2]
>>> a
[1, 2, 3]
```
可以用is和==区分这两种相等。
- 如果is为True，则两个变量具有相同的身份
- 如果==为True，则两个变量具有相同的值
```
>>> [10] == [10]
True
>>> [10] is [10]
False
```

```
>>> def f(s=[]):
...     s.append(1)
...     return len(s)
... 
>>> f()
1
>>> f()
2
>>> f()
3
```

### 1.5. Dictionary
```
>>> numerals = {'I': 1, 'V': 5, 'X': 10}
>>> numerals['X']
10
>>> numerals['X'] = 11
>>> numerals['X']
11
>>> numerals['L'] = 50
>>> numerals.pop('X')
11
>>> numerals.get('X')
>>> numerals
{'I': 1, 'V': 5, 'L': 50}
``` 

### 1.6. Mutable的作用域
python中需要注意mutable default argument
```
>>> def f(s=[]):
...     s.append(1)
...     return len(s)
... 
>>> f()
1
>>> f()
2
>>> f()
3
```
- 究其原因，首先，mutable是全局变量，修改这个变量只会修改这个变量的值，不会创造一个新的变量
- 其次，只有immutable(number, tuple等)在被修改值时，会重新创建一个变量，导致immutable变量是局部变量
```
>>> def g():
...     a.append(1)
... 
>>> a = []
>>> g()
>>> a
[1]
>>> g()
>>> a
[1, 1]
```
对于上面的mutable default argument，我们的解决方案是
```
def f(s=None):
    if s == None:
        s = []
    pass
```

## 2. Tuple元组
```
# 一些定义tuple的方法
>>> (1, 2, 3, 4)
(1, 2, 3, 4)
>>> 1, 2, 3, 4
(1, 2, 3, 4)
>>> ()
()
>>> tuple()
()
>>> tuple([2, 3, 5])
(2, 3, 5)
# 输入2,才会返回一个只包含一个2的tuple
>>> 2, 
(2,)
>>> 2
2
>>> (3, 5) + (4, 6)
(3, 5, 4, 6)
>>> 5 in (3, 4, 5)
True
```

## 3. 一些栗子
```
>>> s = [2, 3]
>>> t = [1, 4]
>>> s.append(t)
>>> s
[2, 3, [1, 4]]
>>> t = 0
>>> s
[2, 3, [1, 4]]
```
- 这里我们注意到，t=0将name t绑定到了一个immutable 0上，此时t不再绑定在[1, 4]上，所以s没有变化


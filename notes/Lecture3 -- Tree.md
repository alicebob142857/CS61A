# Tree

## 1. Box-and-pointer notation
### 1.1. Sequence Aggregation
#### 1.1.1. Sum()
```
sum(iterable[,start])->value
```
[]表示start参数是可有可无的
start参数决定了相加的数据形式。start的默认值是数字0，也就是说默认sum的是数字
```
>>> sum([1, 2, 3])
6
>>> # Sum将list中的数据和start相加
>>> sum([1, 2],3)
6
>>> sum(['1', '2'], 3)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: unsupported operand type(s) for +: 'int' and 'str'

>>> # 没有start的时候，list不能相加，因为start默认为0
>>> sum([[1], [2]])
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: unsupported operand type(s) for +: 'int' and 'list'
>>> # start设置为list后可以相加
>>> sum([[1], [2]], [3])
[3, 1, 2]
```

#### 1.1.2. max()
```
max(iterable[,ket=func])->value
```
max返回一组数的最大值。如果加入函数方法，则返回函数返回值最大的那个数。
```
>>> max(range(3))
2
>>> max(0, 1, 2)
2
>>> max(range(2), key = lambda x: 1 - (1 - x) ** 2)
1
```
#### 1.1.3. all()
- bool函数
```
>>> bool(1)
True
>>> bool(-1)
True
>>> bool(0)
False
>>> bool('hello world')
True
>>> bool('')
False
>>> bool()
False
```

- all()函数判断，输入值的bool函数返回值是否都为True
```
>>> all(range(5))
False
>>> all([x<5 for x in range(5)])
True
```
上次看到17:28
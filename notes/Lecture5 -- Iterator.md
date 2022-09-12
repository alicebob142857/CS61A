# Iterator

## 1. Data Stucture

### 1.1. list
```
>>> s = [3, 4, 5]
>>> t = iter(s)
>>> t
<list_iterator object at 0x7fb4580c2250>
>>> next(t)
3
>>> next(t)
4
>>> next(t)
5
>>> next(t)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```
可以用list讲一个literation还原为list，但是此时，指针之前的所有数据将会丢失
```
>>> list(t)
[]
```

### 1.2. Dictionary
python 3.6之后，dictionary中的数据按照添加的顺序进行排列。Dictionary是mutable，所有dictionary也能成为iteration。
```
>>> d = {'one': 1, 'two': 2, 'three': 3}
>>> d['zero'] = 0
>>> d
{'one': 1, 'two': 2, 'three': 3, 'zero': 0}
>>> d.keys()
dict_keys(['one', 'two', 'three', 'zero'])
>>> k = iter(d.keys())
>>> next(k)
'one'
>>> next(k)
'two'
```
如果中途dictionary发生了变化，iteration将会报错
```
>>> d['four'] = 4
>>> next(k)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
RuntimeError: dictionary changed size during iteration
```
此时需要重新将新的d转化为iteration

### 1.3. iteration和For Statement的区别
```
>>> r = range(3)
>>> for i in r:
...     print(i)
... 
0
1
2
>>> ri = iter(r)
>>> next(ri)
0
>>> for i in ri:
...     print(i)
... 
1
2
>>> for i in r:
...     print(i)
... 
0
1
2
```

## 2. Build-in iteration Fucntions
### 2.1. Build-in Function
map(func, iterable):
Iterate over func(x) for x in iterable

filter(func, iterable):
Iterate over x in iterable if func(x)

zip(first_iter, second_iter):
Iterate over co-indexed (x, y) pairs

reversed(sequence):
Iterate over x in a sequence in reverse order
### 2.2. Lazy Computation
编译器只会在一个值将要被使用的时候计算他
```
# Some Function about iterable
def double(x):
    print('**', x, '=>', 2*x, '**')
    return 2*x
```
定义了double
```
>>> map(double, [3, 5, 7])
<map object at 0x7fba101fbc90>
>>> # Notice that we didn't print anything
>>> # This tells us that the computation is not done before we use the data
>>> m = map(double, [3, 5, 7])
>>> next(m)
** 3 => 6 **
6
>>> # Now the double is computed
>>> next(m)
** 5 => 10 **
10
>>> m = map(double, range(3, 7))
>>> f = lambda y: y>= 10
>>> t = filter(f, m)
>>> next(t)
** 3 => 6 **
** 4 => 8 **
** 5 => 10 **
10
>>> # It refused to do extra work
>>> next(t)
** 6 => 12 **
12
```

## 3. Generator
### 3.1. yield
```
>>> def plus_minus(x):
...     yield x
...     yield -x
... 
>>> t = plus_minus(3)
>>> next(t)
3
>>> next(t)
-3
>>> t
<generator object plus_minus at 0x7fba101f0050>
```
yield关键字和return相似，但是它可以被输入多次，并且产生一个generator
```
>>> t = evens(1, 10)
>>> next(t)
2
>>> next(t)
4
>>> list(evens(1, 10))
[2, 4, 6, 8]
```
### 3.2. yield from
以下的两组代码等价
```
# yield
for x in a :
    yield a
    
# yield from
yield from a

```
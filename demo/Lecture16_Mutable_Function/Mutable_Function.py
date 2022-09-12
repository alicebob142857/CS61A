def make_withdraw(balance):
    """Return a withdraw function with a starting balance."""
    def withdraw(amount):
        """Return the remained balance after withdrawing"""
        # nonlocal: with nonlocal, we can modify the variable in make_withdraw frame,
        # or the variable in make_withdraw is readonly
        nonlocal balance
        if amount > balance:
            return 'Insufficient funds'
        balance = balance - amount
        return balance
    return withdraw

# An example of nonlocal variable 
# Mutation undermine the referentially transparency
def f(x):
    x = 4 
    def g(y):
        def h(z):
            nonlocal x
            x = x + 1
            return x + y + z
        return h
    return g
a = f(1)
b = a(2)
total = b(3) + b(4)

# Some Function about iterable
def double(x):
    print('**', x, '=>', 2*x, '**')
    return 2*x

# An example about generator
def evens(start, end):
    """Generate a iteration with even numbers"""
    # make sure the start is an even number
    even = start + (start % 2)
    while even < end:
        yield even
        even += 2


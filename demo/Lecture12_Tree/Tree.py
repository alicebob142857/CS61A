# the data abstraction of tree

# construct a tree
def tree(label, branches=[]):
    for branch in branches:
        assert is_tree(branch), 'A branch must be a tree!'
    return [label] + list(branches)

# return a tree's branches
def branches(tree):
    return tree[1:]

# return a tree's label
def label(tree):
    return tree[0]

# tell whether a data structure is a tree
def is_tree(tree):
    if type(tree) != list or len(tree) < 1:
        return False
    for branch in branches(tree):
        if not is_tree(branch):
            return False
    return True

# tell whether a data is a leaf
def is_leaf(tree):
    return not branches(tree)
    # notice that leaf is a tree, whose branch is an empty list

# Tree Processing
# define a tree of Fibonacci
def fib_tree(n):
    if n <= 1: # the tree is just a leaf when n = 0 or -1
        return tree(n)
    else: # build the two brn=anches of the fibonacci tree
        left, right = fib_tree(n - 2), fib_tree(n - 1)
        return tree(label(left) + label(right), [left, right])
 
# Count the number of the leaves using recursion
def count_leaves(t):
    if is_leaf(t):
        return 1
    else:
        return sum([count_leaves(branch) for branch in branches(t)])

# return all the leaves of a tree using the feature of function 'sum'
def leaves(tree):
    if is_leaf(tree):
        return [label(tree)]
    else:
        return sum([leaves(b) for b in branches(tree)], [])

# return a tree with the same structure as t but its labels of the leaves plus 1
def increment_leaves(t):
    if is_leaf(t):
        return tree(label(t) + 1)
    else: # the label of the branches nodes doesn't change
        return tree(label(t), [increment_leaves(b) for b in branches(t)])

# return a tree with the same structure as t but all itsn labels plus 1
def increment(t):
    return tree(label(t) + 1, [increment(b) for b in branches(t)])
    # a trick: this function doesn't need a base condition
    # because when the tree is a leaf, its branches is [],
    # which doesn't call the recursion function 

# Print the structure of a tree
def print_tree(tree, indent=0):
    # using indents to show the structre of a tree
    print(' ' * indent, str(label(tree)))
    for b in branches:
        print_tree(b, indent+1)

# The following is the two way to define recursion function
# We take factorial as example
def factorial(n):
    """Compute the result from down to up"""
    if n == 0:
        return 1
    else:
        return n * factorial(n - 1)

def fact_times(n, k):
    """Return k * n!
    Compute the result from up to down
    """
    if n == 0:
        return k
    else:
        return fact_times(n - 1, k * n)

# Now we apply this method to the tree function
# Sum all the labels from the root to the leaves
# so_far can be used to control the data type by inputing 0, '', etc
def print_sums(t, so_far=0):
    so_far += label(t)
    if is_leaf(t): # if it reaches the leaf, output the sum
        return so_far
    for b in branches:
        print_sums(b, so_far)


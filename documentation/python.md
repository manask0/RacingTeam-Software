### Numpy
Array object in numpy is call ndarray. These are faster than lists since they're stored at one place in the memory. (locality of reference, it is easy to access and manipulate them).
"""import numpy  
  
arr = numpy.array([1, 2, 3, 4, 5])  
  
print(arr)"""
To create an `ndarray`, we can pass a list, tuple or any array-like object into the `array()` method, and it will be converted into an `ndarray`:
To access elements from 2-D arrays we can use comma separated integers representing the dimension and the index of the element.
The `astype()` function creates a copy of the array, and allows you to specify the data type as a parameter.

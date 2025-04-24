#!/usr/bin/python3
"""
Module for calculating the minimum number of operations
to achieve exactly n 'H' characters using Copy All and Paste.
"""


def minOperations(n):
    """
    Calculates the minimum number of operations to get n 'H' characters.
    
    Parameters:
    n (int): Target number of characters
    
    Returns:
    int: Minimum number of operations required, or 0 if impossible
    """
    if n < 2:
        return 0

    operations = 0
    divisor = 2

    while n > 1:
        while n % divisor == 0:
            operations += divisor
            n //= divisor
        divisor += 1

    return operations

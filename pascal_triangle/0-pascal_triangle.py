#!/usr/bin/python3
"""
0-pascal_triangle
Defines a function pascal_triangle(n) that returns
a list of lists representing Pascal's triangle of size n.
"""


def pascal_triangle(n):
    """
    Generate Pascal's triangle up to row n (1-indexed).

    Args:
        n (int): number of rows to generate.

    Returns:
        list[list[int]]: the triangle as a list of rows.
                         Returns [] if n <= 0.
    """
    if n <= 0:
        return []

    triangle = [[1]]
    while len(triangle) < n:
        prev = triangle[-1]
        # Inner values are sums of adjacent numbers from previous row
        inner = [prev[i] + prev[i + 1] for i in range(len(prev) - 1)]
        triangle.append([1] + inner + [1])

    return triangle


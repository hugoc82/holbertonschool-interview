#!/usr/bin/python3
import sys

def is_safe(queens, row, col):
    """Vérifie si une reine peut être placée à (row, col) sans conflit."""
    for r, c in queens:
        if c == col or abs(row - r) == abs(col - c):
            return False
    return True

def solve_nqueens(n, row=0, queens=[], solutions=[]):
    """Résout récursivement le problème des N reines via backtracking."""
    if row == n:
        solutions.append(queens[:])
        return

    for col in range(n):
        if is_safe(queens, row, col):
            queens.append([row, col])
            solve_nqueens(n, row + 1, queens, solutions)
            queens.pop()

def main():
    """Point d'entrée principal du programme."""
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    solutions = []
    solve_nqueens(n, solutions=solutions)
    for solution in solutions:
        print(solution)

if __name__ == "__main__":
    main()

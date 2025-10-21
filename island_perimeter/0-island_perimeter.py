#!/usr/bin/python3
"""
Module 0-island_perimeter

Contient la fonction island_perimeter(grid) qui calcule le périmètre
d'une île représentée par une grille de 0 (eau) et 1 (terre).

Règles :
- Les cellules ont des côtés de longueur 1.
- Connexions horizontales et verticales uniquement.
- Une seule île, pas de lacs internes.
"""


def island_perimeter(grid):
    """Calcule et renvoie le périmètre de l'île.

    Args:
        grid (list[list[int]]): Grille rectangulaire d'entiers 0/1.

    Returns:
        int: Périmètre de l'île (0 si grille vide ou sans terre).

    Méthode:
        On parcourt chaque case. Pour chaque case de terre (1),
        on ajoute 4 au périmètre, puis on soustrait 2 pour chaque
        voisin terrestre adjacent (haut/bas/gauche/droite) déjà compté,
        afin d'éviter de compter deux fois les côtés partagés.

    Complexité:
        O(H*W) en temps, O(1) en mémoire supplémentaire.
    """
    if not grid or not isinstance(grid, list) or not grid[0]:
        return 0

    h = len(grid)
    w = len(grid[0])
    perim = 0

    for r in range(h):
        row = grid[r]
        for c in range(w):
            if row[c] == 1:
                # +4 pour la cellule de terre
                perim += 4

                # si le voisin du haut est aussi de la terre, -2 côtés partagés
                if r > 0 and grid[r - 1][c] == 1:
                    perim -= 2

                # si le voisin de gauche est aussi de la terre, -2 côtés partagés
                if c > 0 and row[c - 1] == 1:
                    perim -= 2

    return perim


#!/usr/bin/python3
"""Making Change — calculer le nombre minimal de pièces pour atteindre un total."""


def makeChange(coins, total):
    """
    Déterminer le plus petit nombre de pièces nécessaire pour atteindre `total`.

    Arguments:
        coins (list): Liste des valeurs des pièces (entiers positifs).
        total (int): Montant cible.

    Renvoie:
        int: Nombre minimal de pièces pour atteindre `total`.
             0 si total <= 0.
             -1 si le total est impossible à atteindre.
    """
    if total <= 0:
        return 0
    if not coins:
        return -1

    # Nettoyage : valeurs uniques et valides
    coins = [c for c in set(coins) if isinstance(c, int) and c > 0]
    if not coins:
        return -1

    # Vérification rapide d'impossibilité via le PGCD des dénominations
    # (implémentation compatible Py3.4, sans math.gcd)
    def _pgcd(a, b):
        while b:
            a, b = b, a % b
        return a

    g = coins[0]
    for c in coins[1:]:
        g = _pgcd(g, c)
    if total % g != 0:
        return -1

    # Programmation dynamique (sac à dos non borné, minimisation du nb de pièces)
    # dp[x] = nb minimal de pièces pour faire x
    INF = total + 1  # sentinelle > toute réponse possible
    dp = [0] + [INF] * total

    # Parcours par pièce pour de bonnes perfs ; l'ordre importe peu pour la justesse
    for coin in coins:
        for amount in range(coin, total + 1):
            if dp[amount - coin] + 1 < dp[amount]:
                dp[amount] = dp[amount - coin] + 1

    return dp[total] if dp[total] != INF else -1


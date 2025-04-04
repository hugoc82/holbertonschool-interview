#!/usr/bin/python3

"""
Module qui permet de déterminer si toutes les boîtes peuvent être ouvertes.

Dans ce module, nous avons une fonction `canUnlockAll` qui prend en entrée une liste de boîtes
où chaque boîte peut contenir des clés pour ouvrir d'autres boîtes. 
La première boîte (index 0) est déverrouillée, et l'objectif est de vérifier si toutes les boîtes
peuvent être ouvertes en utilisant les clés disponibles dans chaque boîte.

Le processus commence par ouvrir la boîte 0 et explorer les autres boîtes à travers les clés que l'on trouve.
Si toutes les boîtes peuvent être ouvertes, la fonction retourne True, sinon False.
"""

def canUnlockAll(boxes):
    """
    Détermine si toutes les boîtes peuvent être ouvertes, en commençant par la boîte 0.
    
    Cette fonction prend une liste de boîtes, où chaque boîte contient des clés pour ouvrir d'autres boîtes.
    Le processus commence avec la boîte 0, qui est déjà déverrouillée, et explore les autres boîtes via les clés disponibles.
    Si toutes les boîtes peuvent être ouvertes, la fonction retourne True, sinon elle retourne False.
    
    Args:
    boxes (list of list): Une liste de listes où chaque liste contient les indices des boîtes que l'on peut ouvrir avec les clés.
    
    Returns:
    bool: Retourne True si toutes les boîtes peuvent être ouvertes, sinon False.
    """
    # Ensemble pour suivre les boîtes ouvertes
    opened = set()
    
    # On commence avec la première boîte, qui est déjà ouverte
    opened.add(0)
    
    # Vérifier si nous pouvons ouvrir toutes les boîtes
    for box in opened:
        # Parcourir les clés dans la boîte actuellement ouverte
        for key in boxes[box]:
            # Si la clé correspond à une boîte qui n'est pas encore ouverte, on l'ouvre
            if key < len(boxes) and key not in opened:
                opened.add(key)
    
    # Si toutes les boîtes ont été ouvertes, retourner True
    return len(opened) == len(boxes)

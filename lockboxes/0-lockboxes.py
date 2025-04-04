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
    opened = set([0])  # La première boîte (boîte 0) est déjà ouverte
    keys_found = set([0])  # On commence avec la clé de la boîte 0
    
    # Tant qu'on a des boîtes à ouvrir, on continue d'explorer
    while keys_found:
        key = keys_found.pop()  # On prend une clé
        # On ajoute toutes les boîtes qui peuvent être ouvertes avec cette clé
        for new_key in boxes[key]:
            if new_key < len(boxes) and new_key not in opened:
                opened.add(new_key)  # Ouvrir la boîte
                keys_found.add(new_key)  # Ajouter la clé pour l'explorer plus tard
    
    # Si le nombre de boîtes ouvertes est égal au nombre total de boîtes, on retourne True
    return len(opened) == len(boxes)

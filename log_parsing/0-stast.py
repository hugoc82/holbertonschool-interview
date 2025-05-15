#!/usr/bin/python3
import sys
import re
from signal import signal, SIGINT

# Liste des codes de statut valides à suivre
valid_status_codes = ['200', '301', '400', '401', '403', '404', '405', '500']

total_size = 0
status_counts = {}
line_count = 0

def print_stats():
    """Affiche les statistiques actuelles"""
    print(f"File size: {total_size}")
    for code in sorted(status_counts.keys()):
        print(f"{code}: {status_counts[code]}")

def handle_interrupt(signum, frame):
    """Gère le CTRL + C"""
    print_stats()
    sys.exit(0)

# Gérer l'interruption clavier
signal(SIGINT, handle_interrupt)

try:
    for line in sys.stdin:
        line = line.strip()
        # Expression régulière pour valider le format
        match = re.match(r'^.+ - \[.+\] "GET /projects/260 HTTP/1\.1" (\d{3}) (\d+)$', line)
        if match:
            status_code = match.group(1)
            file_size = int(match.group(2))
            total_size += file_size

            if status_code in valid_status_codes:
                status_counts[status_code] = status_counts.get(status_code, 0) + 1

            line_count += 1
            if line_count % 10 == 0:
                print_stats()
except KeyboardInterrupt:
    handle_interrupt(None, None)

# En fin de fichier, afficher les stats restantes
print_stats()

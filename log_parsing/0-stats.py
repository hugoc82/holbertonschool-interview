#!/usr/bin/python3
"""
Log parsing script that reads from stdin and prints metrics.

After every 10 lines or on keyboard interruption (CTRL + C),
it prints the total file size and the count of each status code.
"""

import sys

status_codes = {
    '200': 0, '301': 0, '400': 0,
    '401': 0, '403': 0, '404': 0,
    '405': 0, '500': 0
}
total_size = 0
line_count = 0

def print_stats():
    """Display the statistics"""
    print("File size: {}".format(total_size))
    for code in sorted(status_codes.keys()):
        if status_codes[code] > 0:
            print("{}: {}".format(code, status_codes[code]))

try:
    for line in sys.stdin:
        line_count += 1
        parts = line.strip().split()

        # Expected format: <IP> - [<date>] "GET /projects/260 HTTP/1.1" <status> <size>
        if len(parts) >= 7:
            status = parts[-2]
            size = parts[-1]

            # Check if status is valid and size is a number
            if status in status_codes:
                try:
                    total_size += int(size)
                    status_codes[status] += 1
                except ValueError:
                    pass  # Ignore if file size is not a number

        if line_count % 10 == 0:
            print_stats()

except KeyboardInterrupt:
    print_stats()
    raise

print_stats()


#!/usr/bin/python3
"""
Log parsing script that reads from stdin and prints metrics.

After every 10 lines or on keyboard interruption (CTRL + C),
it prints the total file size and the count of each status code.
"""

import sys

def print_stats(total_size, status_codes):
    """Display the statistics"""
    print("File size: {}".format(total_size))
    for code in sorted(status_codes):
        if status_codes[code] > 0:
            print(f"{code}: {status_codes[code]}")

def process_input():
    """Read stdin and process log lines"""
    total_size = 0
    status_codes = {
        '200': 0, '301': 0, '400': 0,
        '401': 0, '403': 0, '404': 0,
        '405': 0, '500': 0
    }
    line_count = 0

    try:
        for line in sys.stdin:
            line_count += 1
            parts = line.strip().split()

            if len(parts) >= 7:
                status = parts[-2]
                size = parts[-1]
                if status in status_codes:
                    try:
                        total_size += int(size)
                        status_codes[status] += 1
                    except ValueError:
                        pass

            if line_count % 10 == 0:
                print_stats(total_size, status_codes)

    except KeyboardInterrupt:
        print_stats(total_size, status_codes)
        raise

    print_stats(total_size, status_codes)

if __name__ == "__main__":
    process_input()

#!/usr/bin/python3
"""
This module provides a function to validate UTF-8 encoding.
"""

def validUTF8(data):
    """
    Check if a given data set represents a valid UTF-8 encoding.
    
    Args:
        data: List of integers, each representing a byte (0-255).
        
    Returns:
        True if data is a valid UTF-8 encoding, False otherwise.
    """
    num_bytes = 0

    for byte in data:
        # We only care about the least significant 8 bits
        byte = byte & 0xFF

        if num_bytes == 0:
            # Count the number of leading 1s to determine the number of bytes
            if (byte >> 5) == 0b110:
                num_bytes = 1
            elif (byte >> 4) == 0b1110:
                num_bytes = 2
            elif (byte >> 3) == 0b11110:
                num_bytes = 3
            elif (byte >> 7) == 0:
                num_bytes = 0
            else:
                return False
        else:
            # Check if byte starts with 10xxxxxx
            if (byte >> 6) != 0b10:
                return False
            num_bytes -= 1

    return num_bytes == 0

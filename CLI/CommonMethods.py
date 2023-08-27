import re


def is_valid_hex_array(data):
    """
    determines if hex array is valid
    :param data:
    :return:
    """
    # num of nibbles in hex array should be divided by 2
    if 0 != len(data) % 2:
        ret_val = False
    else:
        # Hex array sanity
        pattern = re.compile('^[0-9a-fA-F]+$')
        ret_val = bool(pattern.match(data))
    return ret_val
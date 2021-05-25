from upside_down_display import UpsideDownDisplay


def run_application():
    udd = UpsideDownDisplay()
    udd.set_letter_mappings({
        'a': 95,
        'b': 94,
        'c': 93,
        'd': 91,
        'e': 88,
        'f': 87,
        'g': 85,
        'h': 82,
        'i': 81,
        'j': 79,
        'k': 52,
        'l': 54,
        'm': 56,
        'n': 58,
        'o': 59,
        'p': 61,
        'q': 63,
        'r': 65,
        's': 67,
        't': 68,
        'u': 49,
        'v': 48,
        'w': 45,
        'x': 43,
        'y': 41,
        'z': 38,
        '?': 35,
    })
    udd.run()


if __name__ == '__main__':
    run_application()

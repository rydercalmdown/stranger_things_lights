from upside_down_display import UpsideDownDisplay


def run_application():
    udd = UpsideDownDisplay()
    udd.set_letter_mappings({
        'a': 96,
        'b': 95,
        'c': 94,
        'd': 92,
        'e': 89,
        'f': 88,
        'g': 86,
        'h': 83,
        'i': 82,
        'j': 80,
        'k': 53,
        'l': 55,
        'm': 57,
        'n': 59,
        'o': 60,
        'p': 62,
        'q': 64,
        'r': 66,
        's': 68,
        't': 69,
        'u': 50,
        'v': 49,
        'w': 46,
        'x': 44,
        'y': 42,
        'z': 39,
        '?': 36,
    })
    udd.run()


if __name__ == '__main__':
    run_application()

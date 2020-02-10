"""
Unicode data from https://unicode.org/Public/13.0.0/ucd/UnicodeData-13.0.0d6.txt
"""
import csv


def parse_file(iterable, **kwargs):
    reader = csv.reader(iterable, **kwargs)
    for i in reader:
        yield {
            "codePoint": int(i[0], base=16),
            "category": i[2]
        }


def detect_gaps(iterable):
    last = -1
    for i in iterable:
        # gap
        if last + 1 != i["codePoint"]:
            yield (last, i["codePoint"])
        last = i["codePoint"]

    if last != i["codePoint"]:
        yield (last, i["codePoint"])


if __name__ == "__main__":
    import sys

    with open(sys.argv[1], "r") as f:
        s = 0
        c = 0
        for i in detect_gaps(parse_file(f, delimiter=";")):
            if i[1] - i[0] > 50:
                s += i[1]-i[0]
                c += 1
                print("{:x}, {:x} | ".format(*i), i[1] - i[0])
        print(s/0x10FFFD)
        print(c)

import sys

if __name__ == '__main__':
    args = sys.argv[1:]
    out = ""
    for file in args:
        with open(file, 'r', encoding='utf-8', errors='ignore') as f:
            out += "[" + file + "]\n"
            out += f.read()
    with open("out.py.txt", 'w') as f:
        f.write(out)


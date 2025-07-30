import sys

if __name__ == '__main__':
    args = sys.argv[1:]
    out = "".encode()
    for file in args:
        print(file);
        with open(file, 'rb') as f:
            out += ("[" + file + "]\n").encode();
            out += f.read()
    with open("out.py.txt", 'wb') as f:
        f.write(out)


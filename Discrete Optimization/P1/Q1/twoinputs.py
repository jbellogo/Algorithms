import sys 

def main():
    a, b = 0,0
    # READ INPUT
    for i, line in enumerate(sys.stdin):
        if 'Exit' == line.rstrip():
            break
        lst = line.split()
        if i == 0:
            # first line
            a = int(lst[0]) # size of V
            b = int(lst[1]) # size of E
            print(a+b)
            break

if __name__ == "__main__":
    main()

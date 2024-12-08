import pathlib

def open_file(input_file):
    l = []
    with open(input_file, "r") as f:    
        lines = [line.strip() for line in f]
        for line in lines:
            l.append(line.split(' '))
    return l    

def is_incr_ok(list, rm):
    l1 = list.copy()
    if(rm == len(list)):
        return False
    if(rm != -1):
        list.pop(rm)
    for i in range(1, len(list)):
        cmp = int(list[i]) - int(list[i-1])
        if (cmp <= 0 or cmp > 3):
            return is_incr_ok(l1, rm + 1)
    return True

def is_decr_ok(list, rm):
    l1 = list.copy()
    if(rm == len(list)):
        return False
    if(rm != -1):
        list.pop(rm)
    for i in range(1, len(list)):
        cmp = int(list[i - 1]) - int(list[i])
        if (cmp <= 0 or cmp > 3):
            return is_decr_ok(l1, rm + 1)
    return True


if __name__ == "__main__":
    input_file = pathlib.Path(__file__).parent / "input.txt"
    f = open_file(input_file)
    cnt = 0
    for line in f:
        if(is_incr_ok(line, -1) or is_decr_ok(line, -1)):
            cnt += 1
    print("solution: ", cnt)
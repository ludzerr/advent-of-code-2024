import pathlib


def open_file(input_file):
    first_column = []
    second_column = []
    with open(input_file, "r") as f:    
        lines = [line.strip() for line in f]
        for line in lines:
            first_column.append(line.split('   ')[0])
            second_column.append(line.split('   ')[1])
    return first_column, second_column




if __name__ == "__main__":
    input_file = pathlib.Path(__file__).parent / "input.txt"
    first_column, second_column = open_file(input_file)
    first_column.sort()
    second_column.sort()
    d = 0
    for i in range(len(first_column)):
        d += abs(int(first_column[i]) - int(second_column[i]))
    print(d)

        
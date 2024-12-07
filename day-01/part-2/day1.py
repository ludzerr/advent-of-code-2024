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

    s_list = []
    for n1 in first_column:
        number_count = 0
        for n2 in second_column:
            if n1 == n2:
                number_count += 1
        s_list.append(int(n1) * number_count)
    
    d = 0    
    for n in s_list:
        d += n
    print("solution: ",d)

        
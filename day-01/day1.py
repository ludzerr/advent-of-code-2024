import pathlib

input_file = pathlib.Path(__file__).parent / "input.txt"

with open(input_file, "r") as f:    
    lines = [line.strip() for line in f]
    for line in lines:
        splited = line.split('   ')
        print(splited)
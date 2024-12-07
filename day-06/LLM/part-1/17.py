from pathlib import Path

def parse_input(input_text):
    return [list(line) for line in input_text.strip().splitlines()]

def find_start_position(grid):
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            if grid[y][x] == '^':
                return (x, y, 'up')  # x, y, direction
    return None

def get_next_position(x, y, direction):
    if direction == 'up':
        return (x, y - 1)
    elif direction == 'right':
        return (x + 1, y)
    elif direction == 'down':
        return (x, y + 1)
    else:  # left
        return (x - 1, y)

def turn_right(direction):
    directions = {'up': 'right', 'right': 'down', 'down': 'left', 'left': 'up'}
    return directions[direction]

def is_in_bounds(x, y, grid):
    return 0 <= y < len(grid) and 0 <= x < len(grid[0])

def is_obstacle(x, y, grid):
    return grid[y][x] == '#'

def simulate_guard_path(grid):
    # Find starting position
    start = find_start_position(grid)
    if not start:
        return 0
    
    x, y, direction = start
    visited = {(x, y)}
    
    while True:
        # Check position in front
        next_x, next_y = get_next_position(x, y, direction)
        
        # If out of bounds, we're done
        if not is_in_bounds(next_x, next_y, grid):
            break
            
        # If obstacle in front, turn right
        if is_obstacle(next_x, next_y, grid):
            direction = turn_right(direction)
        else:
            # Move forward
            x, y = next_x, next_y
            visited.add((x, y))
    
    return len(visited)

def solve(input_text):
    grid = parse_input(input_text)
    return simulate_guard_path(grid)

if __name__ == "__main__":
    input_file = Path(__file__).parent / "input.txt"
    input_text = input_file.read_text()
    
    result = solve(input_text)
    print(f"Solution: {result}")

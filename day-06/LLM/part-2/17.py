from pathlib import Path
from copy import deepcopy

def parse_input(input_text):
    return [list(line) for line in input_text.strip().splitlines()]

def find_start_position(grid):
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            if grid[y][x] in '^>v<':
                direction = {'v': 'down', '^': 'up', '>': 'right', '<': 'left'}[grid[y][x]]
                return (x, y, direction)
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
    return grid[y][x] == '#' or grid[y][x] == 'O'

def simulate_guard_path(grid, start_x, start_y, start_direction):
    x, y = start_x, start_y
    direction = start_direction
    visited_states = set()  # Track (x, y, direction) states
    path = []
    
    while True:
        state = (x, y, direction)
        path.append((x, y))
        
        # If we've seen this state before, we're in a loop
        if state in visited_states:
            # Find where the loop starts
            loop_start = path.index((x, y))
            loop = path[loop_start:]
            return True, set(loop)
        
        visited_states.add(state)
        
        # Check position in front
        next_x, next_y = get_next_position(x, y, direction)
        
        # If out of bounds, no loop
        if not is_in_bounds(next_x, next_y, grid):
            return False, set()
            
        # If obstacle in front, turn right
        if is_obstacle(next_x, next_y, grid):
            direction = turn_right(direction)
        else:
            # Move forward
            x, y = next_x, next_y

def find_loop_positions(grid):
    start = find_start_position(grid)
    if not start:
        return 0
    
    start_x, start_y, start_direction = start
    loop_positions = []
    
    # Try each empty position
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            # Skip positions that already have something
            if grid[y][x] != '.' or (x == start_x and y == start_y):
                continue
                
            # Try placing an obstacle here
            test_grid = deepcopy(grid)
            test_grid[y][x] = 'O'
            
            # Simulate guard movement
            has_loop, loop = simulate_guard_path(test_grid, start_x, start_y, start_direction)
            if has_loop:
                loop_positions.append((x, y))
    
    return len(loop_positions)

def solve(input_text):
    grid = parse_input(input_text)
    return find_loop_positions(grid)

if __name__ == "__main__":
    input_file = Path(__file__).parent / "input.txt"
    input_text = input_file.read_text()
    
    result = solve(input_text)
    print(f"Solution: {result}")

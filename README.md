# A*Maze

A* Maze is a C++ implementation of the A* search algorithm to navigate a maze generated with recursive backtracking. The program visualizes the pathfinding process, allowing users to observe how the algorithm explores the maze.

## Features

- **Maze Generation**: Uses a recursive backtracking algorithm to generate a random maze.
- **A* Pathfinding**: Implements the A* search algorithm to find the shortest path from a starting point to a goal.
- **Visual Representation**: Displays the maze and the pathfinding process in the terminal using colored characters.
- **User Interaction**: Allows for the modification of maze size and starting/goal positions.

## Getting Started

### Prerequisites

Make sure you have a C++ compiler installed, such as g++, and a terminal that supports ANSI escape codes for colored output.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/AStarMaze.git
   cd AStarMaze
   ```

2. Compile the code:
   ```bash
   g++ main.cpp -o AStarMaze -pthread
   ```

3. Run the program:
   ```bash
   ./AStarMaze
   ```

## Project Structure

- `main.cpp`: Contains the main logic for maze generation and pathfinding.
- `README.md`: Project documentation.
- Other potential resources or headers, if added.

## Code Explanation

- **Maze Generation**: The `generateMaze` function recursively carves out paths in the maze by removing walls between cells.
- **Pathfinding**: The `findBestFit` function utilizes the A* algorithm to navigate through the maze, updating the path taken and visited cells.
- **Visualization**: The `draw` function displays the current state of the maze, including the start position, goal position, visited paths, and current path.

## Customization

You can modify the maze size by changing the `sz` variable in `main.cpp`. The starting position (`x`, `y`) and goal position (`gx`, `gy`) can also be adjusted for different maze configurations.

## Contributing

Contributions are welcome! If you have suggestions for improvements or additional features, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

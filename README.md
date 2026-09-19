# 🧩 Maze Solver

> Generate a new maze, watch it appear in your terminal, and reveal the shortest route from start to finish.

`Maze Solver` is a small C++ console program for Windows. It creates a random, *perfect maze* using recursive backtracking, then solves it with breadth-first search (BFS). Every run produces a fresh maze.

## ✨ Highlights

- 🎲 **Random maze generation** — each maze is carved with randomized depth-first backtracking.
- 🧭 **Shortest-path solving** — BFS finds the minimum-step route from the entrance to the exit.
- 🌈 **Colourful console output** — start, end, walls, and the discovered path are easy to distinguish.
- 📐 **Custom dimensions** — choose a maze height and width from `3` to `70`.
- 🛡️ **Input validation** — invalid or non-numeric dimensions are rejected and requested again.

## 🖥️ Preview

The maze uses this legend in a Windows terminal:

| Symbol | Colour | Meaning |
| :---: | :--- | :--- |
| `[]` | Blue | Start |
| `[]` | Red | End |
| `[]` | Yellow | Wall |
| `--` | Green | Solved path |
| `[]` | White | Open path |

## 🚀 Getting started

### Requirements

- Windows (the program uses the Windows Console API via `windows.h` for colour output)
- A C++ compiler with C++11 support, such as **MSVC** or **MinGW-w64**

### Build

From the project directory, compile the source file:

```powershell
# MinGW-w64 / g++
g++ -std=c++11 -O2 -Wall -Wextra mazeSolver.cpp -o maze-solver.exe
```

Or with the Visual Studio Developer PowerShell:

```powershell
cl /EHsc /std:c++11 mazeSolver.cpp /Femaze-solver.exe
```

### Run

```powershell
.\maze-solver.exe
```

Then enter the desired dimensions when prompted:

```text
Enter maze height (3-70): 21
Enter maze width (3-70): 41
```

Even dimensions are automatically increased by one after validation. This preserves the wall-and-corridor layout used by the generator.

## 🧠 How it works

1. The grid begins filled with walls.
2. **Recursive backtracking** visits cells two spaces away in random directions, opening the wall between each newly visited cell.
3. The entrance at the top-left and exit at the bottom-right are connected to the maze.
4. **Breadth-first search** explores open cells from the entrance while recording each cell’s parent.
5. Once the exit is reached, the parent links are traced backward and rendered as the green solution path.

Because BFS explores level by level, the displayed route is a shortest path in the generated maze.

## 📁 Project structure

```text
Maze-Solver/
├── mazeSolver.cpp   # Generation, solving, and console rendering
└── README.md        # Project documentation
```

## ⚙️ Notes

- Dimensions are capped at `70` before the optional even-to-odd adjustment.
- The application is intended for a Windows terminal that supports the Console API colour attributes.
- No external libraries are required.

## 📄 License

No license is currently specified. Add one before redistributing or accepting outside contributions.

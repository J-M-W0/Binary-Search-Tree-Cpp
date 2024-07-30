# Binary Tree Visualization with SDL2

This repository contains a program for visualizing binary trees using the SDL2 library in C++. 
The program demonstrates the structure and traversal of binary trees through graphical visualization.

## Table of Contents

- [Features](#features)
- [Demo](#demo)
- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Features

- **Binary Tree Visualization**: Graphically visualize the structure of binary trees.
- **Interactive Interface**: Add and remove nodes interactively.
- **Customizable**: Easily modify tree properties and visualization parameters.

## Demo

### Watch the Demo Video
[Watch the demo video](demo.mov)

## Installation

To set up the binary tree visualization program on your local machine, follow these steps:

1. **Clone the Repository**: Download the repository to your local machine using git.
    ```sh
    git clone <repo>
    ```

2. **Navigate to the Project Directory**: Change your current directory to the project's root directory.
    ```sh
    cd <repo-directory>
    ```

3. **Install Dependencies**: Ensure you have SDL2 installed on your system. You can install SDL2 using package managers like `apt` for Ubuntu or `brew` for macOS.
    ```sh
    # For Ubuntu
    sudo apt-get install libsdl2-dev

    # For macOS
    brew install sdl2
    ```

4. **Compile the Program**: Use Makefile to compile the program.
    ```sh
    make
    ```

5. **Run the Program**: Execute the compiled program to start the visualization.
    ```sh
    ./bst
    ```

## Usage

Once the program is running, use the following controls to interact with the binary tree:

**insert**: to insert a value.
**delete**: to delete a value.
**contain**: to check if a value exists in the tree.
**refresh**: to refresh the menu.
**quit**: to quit the program.

## Code Structure

The project consists of the following files:

- `main.cpp`: Contains the main function which is the entry point for the program.
- `UbuntuMono-Regular.ttf`: A TrueType font file used for rendering text in the SDL2 window.
- `README.md`: The documentation file providing an overview of the project, installation instructions, usage, and other relevant information.
- `Makefile`: A makefile containing build instructions for compiling the project using `make`.
- `.gitignore`: A file specifying which files and directories should be ignored by Git.
- `header/bst.hpp`: Header file defining the binary search tree (BST) class and its associated methods.
- `header/utils.hpp`: Header file containing utility functions and definitions used throughout the project.
- `lib/bst.cpp`: Implementation file for the binary search tree (BST) class, containing the logic for tree operations such as insertion, deletion, and traversal.
- `lib/res.cpp`: Implementation file for handling resources, such as loading fonts and managing other assets required by the SDL2 application.
- `lib/util.cpp`: Implementation file for utility functions used throughout the project, including helper functions for rendering and event handling.

## Contributing

Contributions are welcome! If you have any ideas for improvements or find any bugs, feel free to open an issue or submit a pull request. 
Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- Developed by [Junzhe Wang](https://github.com/J-M-W0).
- Special thanks to the SDL2 community for their support and resources.
- Inspired by various binary tree visualization tools and resources.



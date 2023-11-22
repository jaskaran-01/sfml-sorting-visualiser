# Sorting Algorithm Visualization

This project provides a visual representation of various sorting algorithms using SFML for graphics and CMake for build management.

## Tools Used

- **SFML (Simple and Fast Multimedia Library):**
  - SFML is a free and open-source multimedia library designed for creating games and multimedia applications. In this project, SFML is used for rendering graphics and handling events to visualize sorting algorithms.

- **CMake:**
  - CMake is an open-source, cross-platform family of tools designed to build, test, and package software. This project uses CMake for easy and efficient project configuration and building.

## Sorting Algorithms

The project currently visualizes the following sorting algorithms:

- **Binary Sort**
- **Bubble Sort**
- **Quick Sort**
- **Merge Sort**

## How to Build and Run

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/sorting-algorithm-visualization.git
    ```

2. Navigate to the project directory:

    ```bash
    cd sorting-algorithm-visualization
    ```

3. Create a build directory:

    ```bash
    mkdir build
    ```

4. Navigate to the build directory:

    ```bash
    cd build
    ```

5. Generate build files using CMake:

    ```bash
    cmake ..
    ```

6. Build the project:

    ```bash
    cmake --build .
    ```

7. Run the executable:

    ```bash
    ./SortingVisualization
    ```

## How to Use

- Upon running the executable, the program will visualize different sorting algorithms in real-time.
- Use the arrow keys to adjust the speed of the visualization (up key to increase speed, down key to decrease speed).
- The program will start with Binary Sort and move on to Bubble Sort, Quick Sort, and Merge Sort.

## Contributing

If you'd like to contribute to this project, feel free to fork the repository and submit pull requests. Contributions and suggestions are welcome!

## License

This project is licensed under the [MIT License](LICENSE).

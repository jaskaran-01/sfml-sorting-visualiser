#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

const int DELAY = 1;
const int ARRAY_SIZE = 1500;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 1000;
const float MAX_BAR_HEIGHT_PERCENTAGE = 1.0f; // 4/5th of the screen height
const float BAR_WIDTH = static_cast<float>(WINDOW_WIDTH) / ARRAY_SIZE;

// Function to draw the array with varying colors
void drawArray(sf::RenderWindow &window, const std::vector<int> &array) {
  window.clear();

  for (std::size_t i = 0; i < array.size(); ++i) {
    float scaledHeight =
        static_cast<float>(array[i]) / WINDOW_HEIGHT * WINDOW_HEIGHT;

    // Limit the maximum size of the bars to 4/5th of the screen height
    scaledHeight =
        std::min(scaledHeight, MAX_BAR_HEIGHT_PERCENTAGE * WINDOW_HEIGHT);

    sf::RectangleShape bar(sf::Vector2f(BAR_WIDTH, scaledHeight));

    // Calculate color based on height
    sf::Color color(
        static_cast<sf::Uint8>(255 *
                               (array[i] / static_cast<float>(WINDOW_HEIGHT))),
        0,
        static_cast<sf::Uint8>(
            255 * (1 - array[i] / static_cast<float>(WINDOW_HEIGHT))));

    bar.setFillColor(color);
    bar.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - bar.getSize().y);
    window.draw(bar);
  }

  window.display();
}

// Binary sort algorithm with delay
void binarySort(std::vector<int> &array, sf::RenderWindow &window,int speed) {
  for (std::size_t i = 1; i < array.size(); ++i) {
    int key = array[i];
    int low = 0;
    int high = i - 1;

    while (low <= high) {
      int mid = (low + high) / 2;

      if (array[mid] > key) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    for (int j = i - 1; j >= low; --j) {
      array[j + 1] = array[j];
    }

    array[low] = key;

    // Draw the array with varying colors and delay for visualization
    drawArray(window, array);
    std::this_thread::sleep_for(std::chrono::microseconds(speed));

    // Check for events within the sorting loop
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}
void bubbleSort(std::vector<int> &array, sf::RenderWindow &window,int speed) {
  int n = array.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        std::swap(array[j], array[j + 1]);
      }
      // Draw the array with varying colors and delay for visualization
      drawArray(window, array);
      std::this_thread::sleep_for(std::chrono::nanoseconds(speed));
      // Check for events within the sorting loop
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }
    }
  }
}
// Merge Sort With Visualization
void merge(std::vector<int>& arr, int l, int m, int r, sf::RenderWindow& window,int speed) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;

        drawArray(window, arr);  // Draw the array with varying colors for visualization
        std::this_thread::sleep_for(std::chrono::microseconds(speed));  // Add a delay for visualization
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;

        drawArray(window, arr);  // Draw the array with varying colors for visualization
        std::this_thread::sleep_for(std::chrono::microseconds(speed));  // Add a delay for visualization
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;

        drawArray(window, arr);  // Draw the array with varying colors for visualization
        std::this_thread::sleep_for(std::chrono::microseconds(speed));  // Add a delay for visualization
    }
}
void mergeSort(std::vector<int>& arr, int l, int r, sf::RenderWindow& window,int speed) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, window,speed);
        mergeSort(arr, m + 1, r, window,speed);
        merge(arr, l, m, r, window,speed);
    }
}


// Quick Sort With Visualization
int partition(std::vector<int>& arr, int low, int high, sf::RenderWindow& window,int speed) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);

    drawArray(window, arr);  // Draw the array with varying colors for visualization
    std::this_thread::sleep_for(std::chrono::microseconds(speed));  // Add a delay for visualization

    return (i + 1);
}
void quickSort(std::vector<int>& arr, int low, int high, sf::RenderWindow& window,int speed) {
    if (low < high) {
        int pivot = partition(arr, low, high, window,speed);
        quickSort(arr, low, pivot - 1, window,speed);
        quickSort(arr, pivot + 1, high, window,speed);
    }
}



int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sorting Algorithm Visualisation");

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, WINDOW_HEIGHT);

    // Initialize the array with random elements
    std::vector<int> array;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array.push_back(dis(gen));
    }

    bool isVisualizationRunning = true; // Start with binary sort
    bool isBubbleSortRunning = false;
    bool isQuickSortRunning = false;
    bool isMergeSortRunning = false;

    // Main loop
int speed = 1; // Initial speed
while (window.isOpen()) {
    // Handle events within the main loop's while statement
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // Increase or decrease speed using arrow keys
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                    speed++;
                
            } else if (event.key.code == sf::Keyboard::Down) {
                    if(speed<=0)
                      speed--;
                }
            }
        }
    
    if (isVisualizationRunning) {
        // Sort the array using binary sort with delay and event handling
        std::shuffle(array.begin(), array.end(), gen); // Shuffle the array
        binarySort(array, window, speed); // Pass speed to sorting method
        isVisualizationRunning = false;
        isBubbleSortRunning = true;
        isQuickSortRunning = false;
        isMergeSortRunning = false;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Add 3 seconds delay
    } else if (isBubbleSortRunning) {
        // Sort the array using bubble sort with delay and event handling
        std::shuffle(array.begin(), array.end(), gen); // Shuffle the array
        bubbleSort(array, window, speed); // Pass speed to sorting method
        isBubbleSortRunning = false;
        isQuickSortRunning = true;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Add 3 seconds delay
    } else if (isQuickSortRunning) {
        // Sort the array using quick sort with delay and event handling
        std::shuffle(array.begin(), array.end(), gen); // Shuffle the array
        quickSort(array, 0, array.size() - 1, window, speed); // Pass speed to sorting method
        isQuickSortRunning = false;
        isMergeSortRunning = true;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Add 3 seconds delay
    } else if (isMergeSortRunning) {
        // Sort the array using merge sort with delay and event handling
        std::shuffle(array.begin(), array.end(), gen); // Shuffle the array
        mergeSort(array, 0, array.size() - 1, window, speed); // Pass speed to sorting method
        isMergeSortRunning = false;
        // At this point, all visualizations are complete
    } else {
        // Draw the array when not running any algorithm
        drawArray(window, array);
    }
}

    return 0;
}

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


void print_ascii_plot(const std::vector<double>& grid, int nx, int ny) {
    const int cols = 60;
    const int rows = 25;
    const std::string chars = " .-:=+*#%@";

    std::cout << "\nFinal Temperature Profile:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int grid_y = i * ny / rows;
            int grid_x = j * nx / cols;
            double val = grid[grid_y * nx + grid_x];

            int char_idx = static_cast<int>((val / 100.0) * chars.size());
            char_idx = std::clamp(char_idx, 0, static_cast<int>(chars.size()) - 1);

            std::cout << chars[char_idx] << chars[char_idx];
        }
        std::cout << "\n";
    }
}

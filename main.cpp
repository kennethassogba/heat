#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <string>

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

int main() {
    const int nx = 1000;
    const int ny = 1000;
    const int max_iters = 500;
    const double tolerance = 1e-5;

    std::vector<double> u(nx * ny, 0.0);
    std::vector<double> u_new(nx * ny, 0.0);

    auto idx = [nx](int i, int j) { return j * nx + i; };

    for (int i = 0; i < nx; ++i) {
        u[idx(i, ny - 1)] = 100.0;
        u_new[idx(i, ny - 1)] = 100.0;
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int iter = 0; iter < max_iters; ++iter) {
        double max_diff = 0.0;

        for (int j = 1; j < ny - 1; ++j) {
            for (int i = 1; i < nx - 1; ++i) {
                u_new[idx(i, j)] = 0.25 * (u[idx(i - 1, j)] + u[idx(i + 1, j)] +
                                           u[idx(i, j - 1)] + u[idx(i, j + 1)]);

                double diff = std::abs(u_new[idx(i, j)] - u[idx(i, j)]);
                max_diff = std::max(max_diff, diff);
            }
        }

        std::swap(u, u_new);

        if (iter % 50 == 0 || max_diff < tolerance || iter == max_iters - 1) {
            std::cout << "\rIter: " << iter << "/" << max_iters 
                      << " | Max Diff: " << max_diff << " / " << tolerance 
                      << "        " << std::flush;
        }

        if (max_diff < tolerance) {
            std::cout << "Converged after " << iter << " iterations.\n";
            break;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Simulation completed in " << elapsed.count() << " seconds.\n";
    std::cout << "Center temperature: " << u[idx(nx / 2, ny / 2)] << "\n";

    // print_ascii_plot(u, nx, ny);

    return 0;
}

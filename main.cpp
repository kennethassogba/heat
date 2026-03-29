#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>

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
                if (diff > max_diff) {
                    max_diff = diff;
                }
            }
        }

        std::swap(u, u_new);

        if (max_diff < tolerance) {
            std::cout << "Converged after " << iter << " iterations.\n";
            break;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Simulation completed in " << elapsed.count() << " seconds.\n";
    std::cout << "Center temperature: " << u[idx(nx / 2, ny / 2)] << "\n";

    return 0;
}

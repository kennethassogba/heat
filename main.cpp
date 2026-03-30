#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <print>
#include <omp.h>

int main() {
    const int nx = 100;
    const int ny = 100;
    const int max_iters = 50000;
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

        #pragma omp parallel for reduction(max:max_diff)
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
            std::println("Converged after {} iterations.\n", iter);
            break;
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::println("\nSimulation completed in {} seconds.", elapsed.count());
    std::println("Center temperature = {}", u[idx(nx / 2, ny / 2)]);

    return 0;
}

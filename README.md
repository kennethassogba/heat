# Heat diffusion

Simulate how heat moves across a flat surface over time. The core logic involves
a grid of points where each point's new temperature is the average of its four
neighbors:

```cpp
u_new[i, j] = 0.25 * (u[i - 1, j] + u[i + 1, j] +
                      u[i, j - 1] + u[i, j + 1]);
```

## Compile and run

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./heat_diffusion
```

## Objectives

- Write OpenMP, MPI and HIP Kernel
- Understand GPU Architecture
- Harness cache locality
- Coalesced memory access
- HPC performance optimization
- Profiling HPC application
- Roofline analysis

## Roadmap

- Serial Version: Write the basic simulation in modern C++.
Use a 2D array or a flattened 1D vector to store the grid.

- OpenMP: Distribute the grid rows across multiple CPU cores.
Understand shared memory, thread synchronization and cache locality.

- MPI: Split the large grid into smaller rectangles and assign one rectangle to
each MPI process.
To calculate the values at the edges of a rectangle, each process must exchange
data with its neighbors. This is called a halo exchange.
Understand deadlock, load balancing.

- HIP: Move the calculation to the GPU. Write a kernel that runs the averaging
formula on thousands of GPU threads simultaneously.
Manage memory transfers between the CPU and GPU.

## LSP

in build/
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1

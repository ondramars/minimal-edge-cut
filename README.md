
# A minimal edge cut of an edge-valued graph.

The goal of the project is to try parallelization of the minimal edge cut problem solution on a parallel computing system, i.e. on a cluster of computing nodes with multi-core processors with distributed memory and a fast interconnection network.

Libraries for parallelization used in this project are OpenMP and MPI.

## The implementation will be divided into the following iterations

- Implementation of a sequential algorithm for solving the minimal edge cut of an edge-valued graph problem.
- Implementation of a parallel algorithm for a multi-core system using the OpenMP library - version with task parallelism.
- Implementation of a parallel algorithm for a multi-core system using the OpenMP library - version with data parallelism.
- Implementation of a parallel algorithm for a distributed computing cluster using the MPI library.

# =========================================================
# MINI PROJECT:
# Parallel QuickSort using MPI in Python
#
# AIM:
# Evaluate performance enhancement of Parallel
# QuickSort Algorithm using MPI
#
# REQUIREMENTS:
# 1. Install Python
# 2. Install MS-MPI
# 3. Install mpi4py using:
#
#    pip install mpi4py
#
# RUN COMMAND:
#
#    mpiexec -n 4 python parallel_quicksort.py
#
# Here:
# -n 4  => number of parallel processes
#
# =========================================================


# Import MPI Library
from mpi4py import MPI

# Import Random Module
import random

# Import Time Module
import time


# =========================================================
# QUICKSORT FUNCTION
# =========================================================

def quicksort(arr):

    # Base Condition
    if len(arr) <= 1:
        return arr

    # Select Pivot Element
    pivot = arr[len(arr) // 2]

    # Elements smaller than pivot
    left = [x for x in arr if x < pivot]

    # Elements equal to pivot
    middle = [x for x in arr if x == pivot]

    # Elements greater than pivot
    right = [x for x in arr if x > pivot]

    # Recursive QuickSort
    return quicksort(left) + middle + quicksort(right)


# =========================================================
# MPI INITIALIZATION
# =========================================================

# Create MPI communicator
comm = MPI.COMM_WORLD

# Get process rank
# rank = process ID
rank = comm.Get_rank()

# Get total number of processes
size = comm.Get_size()


# =========================================================
# MASTER PROCESS CREATES DATA
# =========================================================

if rank == 0:

    # Generate random array
    data = [random.randint(1, 100) for _ in range(20)]

    print("\nOriginal Array:")
    print(data)

    # List to store chunks
    chunks = []

    # Divide array size by number of processes
    chunk_size = len(data) // size

    # Split array into chunks
    for i in range(size):

        start = i * chunk_size

        end = (i + 1) * chunk_size

        chunks.append(data[start:end])

else:

    # Other processes initially have no data
    chunks = None


# =========================================================
# DISTRIBUTE DATA USING MPI SCATTER
# =========================================================

# Scatter sends chunks to all processes
local_data = comm.scatter(chunks, root=0)

print(f"Process {rank} received: {local_data}")


# =========================================================
# START EXECUTION TIMER
# =========================================================

start_time = time.time()


# =========================================================
# LOCAL QUICKSORT ON EACH PROCESS
# =========================================================

sorted_local = quicksort(local_data)

print(f"Process {rank} sorted: {sorted_local}")


# =========================================================
# GATHER SORTED DATA
# =========================================================

# Gather collects sorted chunks back to master
gathered = comm.gather(sorted_local, root=0)


# =========================================================
# STOP EXECUTION TIMER
# =========================================================

end_time = time.time()


# =========================================================
# MASTER PROCESS FINAL MERGE
# =========================================================

if rank == 0:

    # Empty list for final sorted array
    final_sorted = []

    # Merge all sorted chunks
    for part in gathered:
        final_sorted.extend(part)

    # Final sorting
    final_sorted.sort()

    print("\nFinal Sorted Array:")
    print(final_sorted)

    # Display Execution Time
    print("\nExecution Time:")
    print(end_time - start_time, "seconds")


# =========================================================
# END OF PROGRAM
# =========================================================




####OUTPUT######
"""
Original Array:
[45, 12, 78, 5, 90, 33...]

Process 0 received: [45, 12, 78]
Process 1 received: [5, 90, 33]

Process 0 sorted: [12, 45, 78]
Process 1 sorted: [5, 33, 90]

Final Sorted Array:
[5, 12, 33, 45, 78, 90...]

Execution Time:
0.0012 seconds
"""

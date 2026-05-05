_This project has been created as part of the 42 curriculum by anacharp._

# Codexion
## Description
Codexion is a concurrent programming project simulating a high-pressure development environment where coders must avoid burnout while sharing limited resources. To compile their code, each coder requires two dongles simultaneously. The project focuses on solving complex synchronization challenges, such as resource contention, hardware cooldowns, and priority-based scheduling using a Priority Queue (Heap).

## Instructions
The project includes a Makefile to automate the build process. To compile, run :
```bash
make
```
All arguments are mandatory. The program must be executed as follows:
```bash
./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor] [nb_compils_goal] [cooldown_duration] [scheduler]
```
- number_of_coders : Number of threads (coders).
- time_to_burnout : Max time (ms) a coder can survive without starting a compilation.
- time_to_compile : Duration of the compilation task.
- time_to_debug : Duration of the debugging task.
- time_to_refactor : Duration of the refactoring task.
- nb_compils_goal : All arguments are mandatory. The program must be executed as follows:
- cooldown_duration : Mandatory rest period (ms) for a dongle after being dropped.
- scheduler : Scheduling strategy, must be either fifo or edf.

## Blocking cases handled
### Deadlock Prevention
Deadlocks are prevented by breaking the circular wait condition. Coders always attempt to lock the required dongles in a consistent global order (based on the lowest memory address or ID), ensuring that no two threads can ever block each other in a permanent cycle.

### Starvation Prevention
- FIFO (First-In, First-Out) : Ensures fairness by processing coder requests in the exact order they arrive.
- EDF (Earliest Deadline First) : A more complex strategy where the coder closest to their time_to_burnout is prioritized. This is managed through a Priority Queue (Heap), ensuring the most "at-risk" coders get resources first to prevent simulation failure.

### Cooldown Handling
Dongles are not immediately reusable after being dropped. Our implementation tracks a cld_b (cooldown begin) timestamp for each dongle. A thread attempting to grab a dongle must verify that the current time satisfies the d_cld (duration of cooldown) requirement before successfully locking it.

### Precise Burnout Detection
A dedicated Monitor Thread continuously checks the health of all coders. By comparing the current time with the last_compile timestamp (protected by a mutex), it can detect a burnout within a 1ms margin and trigger the simulation shutdown.

## Thread synchronization mechanisms
### Priority Queue (Heap) Implementation
To support the EDF algorithm, the project implements a custom min-heap. This priority queue stores coder references, sorted by their remaining time before burnout. This data structure allows $O(\log n)$ insertion and extraction, which is critical for maintaining performance under high thread counts.

### Primitives Used
- `pthread_mutex_t`: Used for global state management. In our current implementation, a global_lock protects the integrity of the heap and the dongle states to ensure atomic updates.
- `pthread_cond_t`: Used to manage thread sleeping and waking. Coders wait on condition variables when dongles are unavailable or cooling down, and are woken up via pthread_cond_broadcast when resources are released.
- Log Serialization : All output is wrapped in a log_lock to prevent message interleaving and ensure no logs are printed after a burnout occurs.

### Resource Coordination
- Dongle Access: Each dongle is a structure containing its own mutex and condition variable. This allows granular locking, so Coder A and Coder B can work simultaneously if they use different dongles.
- Log Serialization: All calls to printf are wrapped in a log_lock. This prevents "interleaved" output where two lines of text might merge, and ensures that no logs are printed after the monitor has declared a burnout.

### Race Condition Prevention
- Race conditions are prevented by ensuring that any variable shared between the Monitor and the Coders (such as the stop_flag or last_compile time) is only accessed within a mutex-protected critical section. For instance, when a coder finishes a compilation, they lock their last_lock before updating their status, ensuring the monitor never reads a corrupted or outdated timestamp.

## Resources
### Documentation
- https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
- https://dev.to/yel-bakk/codexion-4fk8
- https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- https://www.geeksforgeeks.org/c/heap-in-c/
- https://nkugwamarkwilliam.medium.com/heap-in-c-programming-made-easy-e84a8b423660
- https://codexion-visualizer.sacha-dev.me/

### AI Usage
AI was used for the following tasks :
- better understanding threads
- help for debugging
- help for translation
- better understanding certain things in C

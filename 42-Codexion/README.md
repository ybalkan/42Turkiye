*This project has been created as part of the 42 curriculum by ybalkan.*

---

# Codexion — Master the race for resources before the deadline masters you

> A concurrent programming simulation inspired by the classic Dining Philosophers problem, reimagined in the world of software developers competing for shared USB dongles to compile quantum code.

---

<img width="3308" height="7041" alt="codexion_00" src="https://github.com/user-attachments/assets/a7a55672-f67d-4498-8d72-42c1c3f4a9df" />

## Description

**Codexion** is a multithreading project written in C that simulates a group of coders sitting in a circular co-working hub. Each coder alternates between three states — **compiling**, **debugging**, and **refactoring** — but compiling requires holding **two USB dongles simultaneously** (one from each side). Since dongles are shared between adjacent coders, careful synchronization is critical to prevent deadlock, starvation, and race conditions.

### Goal

The simulation must:

- Run without any coder burning out (when parameters allow it).
- Stop immediately as soon as one coder burns out, or when every coder has compiled the required number of times.
- Enforce **fair dongle arbitration** via a configurable scheduler (`fifo` or `edf`).
- Log every state change precisely, with burnout detection accurate to within **10 ms**.

### Key Concepts

| Concept | Description |
|---|---|
| **Coder** | A POSIX thread representing a developer |
| **Dongle** | A shared USB device protected by a mutex and a condition variable |
| **Burnout** | A coder fails to start compiling within `time_to_burnout` ms since their last compile (or since simulation start) |
| **Monitor** | A dedicated thread that detects burnout and halts the simulation |
| **Scheduler** | Arbitration policy: `fifo` (arrival order) or `edf` (earliest deadline first) |

### Simulation Rules

- Coders are numbered **1 to N** and sit in a circle: coder 1 is adjacent to coder N.
- Each coder has a dongle on their left and one on their right. With a single coder, there is exactly **one dongle** on the table.
- After compiling, a coder immediately puts both dongles back and starts debugging, then refactoring, then tries to compile again.
- Coders do not communicate with each other and do not know if another coder is about to burn out.

---

## Instructions

### Requirements

- A C compiler with POSIX thread support (`cc -pthread`)
- POSIX-compliant OS (Linux or macOS)

### Compilation

```bash
make
```

Compiles with `-Wall -Wextra -Werror -pthread`. Object files are placed in the `obj/` directory.

```bash
make clean    # Remove object files (obj/)
make fclean   # Remove object files and binary
make re       # Full recompile from scratch
```

### Execution

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
            time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

All arguments are **mandatory**. Invalid inputs (negative numbers, non-integers, unknown scheduler name) are rejected with an error message.

### Arguments

| Argument | Type | Description |
|---|---|---|
| `number_of_coders` | int | Number of coders (= number of dongles) |
| `time_to_burnout` | int (ms) | Max time since last compile start before burnout |
| `time_to_compile` | int (ms) | Duration of the compilation phase |
| `time_to_debug` | int (ms) | Duration of the debugging phase |
| `time_to_refactor` | int (ms) | Duration of the refactoring phase; after this, the coder immediately attempts to compile again |
| `number_of_compiles_required` | int | Compiles needed per coder to end successfully (`0` = run until burnout) |
| `dongle_cooldown` | int (ms) | Unavailability period after a dongle is released |
| `scheduler` | string | Arbitration policy: exactly `fifo` or `edf` |

### Usage Examples

```bash
# 5 coders, 800 ms burnout limit, all phases 200 ms — no compile limit
./codexion 5 800 200 200 200 0 50 fifo

# 4 coders with EDF scheduling, each must compile 3 times
./codexion 4 1000 200 200 200 3 50 edf

# Edge case: single coder (only 1 dongle on table, cannot compile, burns out around 500ms)
./codexion 1 500 200 100 100 5 30 fifo
```

### Log Format

Every state change is printed to stdout in the following format:

```
timestamp_in_ms X has taken a dongle
timestamp_in_ms X is compiling
timestamp_in_ms X is debugging
timestamp_in_ms X is refactoring
timestamp_in_ms X burned out
```

Where `timestamp_in_ms` is the number of milliseconds since simulation start and `X` is the coder number. Two messages never interleave on the same line.

#### Example Output

```
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongle
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out
```

Each compiling action is always preceded by exactly two `has taken a dongle` lines. The `burned out` message appears no more than 10 ms after the actual burnout.

---

## Blocking Cases Handled

### 1. Deadlock Prevention (Coffman's Conditions)

The classic deadlock scenario: every coder holds one dongle and waits for the other, forming a circular wait with no progress. This implementation breaks deadlock by using **condition variables with a priority queue**: a coder that cannot immediately acquire both dongles enqueues its request and releases the CPU without holding any dongle while waiting, eliminating the *hold-and-wait* condition.

| Coffman Condition | Mitigation |
|---|---|
| Mutual Exclusion | Required by design; dongles are exclusive resources |
| Hold and Wait | Eliminated — a coder holds no dongle while waiting for the other |
| No Preemption | N/A — once granted, a dongle is held only during compilation |
| Circular Wait | Eliminated — the scheduler enforces a global priority order; lower-indexed dongle is always acquired first |

### 2. Starvation Prevention

Under **EDF** scheduling, the dongle is always granted to the coder with the earliest burnout deadline (`last_compile_start + time_to_burnout`). This guarantees liveness — no coder is indefinitely deferred — as long as the parameters are physically feasible. Equal deadlines are broken deterministically by coder number.

Under **FIFO** scheduling, requests are served strictly in arrival order, which also prevents indefinite postponement.

### 3. Dongle Cooldown Handling

After a coder releases a dongle, it enters a **cooldown period** of `dongle_cooldown` milliseconds during which it cannot be acquired. This is enforced using `pthread_cond_timedwait`: when a waiter at the head of the queue is selected, if the cooldown has not yet expired, the thread waits with an absolute timeout precisely equal to `release_time`. There is no busy-waiting.

### 4. Precise Burnout Detection

A dedicated **monitor thread** runs independently at 1 ms intervals. At each tick, it acquires `state_mutex`, checks every coder's `last_compile_start` timestamp, and if any coder has exceeded `time_to_burnout`, it sets `stop = 1`, prints the burnout log, and broadcasts to all dongle condition variables. The burnout message is guaranteed to appear **within 10 ms** of the actual burnout event.

### 5. Log Serialization

All state messages are protected by a dedicated **output mutex** (`log_mutex`). A thread acquires the mutex, prints the line, and immediately releases it. This guarantees that no two log messages ever interleave on a single line, even under heavy thread contention.

---

## Thread Synchronization Mechanisms

### `pthread_mutex_t` — Mutual Exclusion

Every shared resource is protected by a mutex:

| Mutex | Protects |
|---|---|
| `dongle.mutex` | Dongle state: availability, cooldown timestamp, wait queue |
| `sim.log_mutex` | Standard output — prevents interleaved log lines |
| `sim.state_mutex` | Global simulation state: `stop` flag, `arrival_seq` counter, compile counts |

**Race condition prevention:** Before the monitor sets `sim->stop = 1`, it acquires `state_mutex`. Coder threads check the flag under the same mutex before any blocking call. This guarantees a coder never enters `pthread_cond_wait` after the stop signal has already been issued.

```c
pthread_mutex_lock(&sim->state_mutex);
if (sim->stop)
{
    pthread_mutex_unlock(&sim->state_mutex);
    return (0);
}
/* safe to proceed */
pthread_mutex_unlock(&sim->state_mutex);
```

### `pthread_cond_t` — Condition Variables

Each dongle has an associated condition variable managing its waiting queue. When a coder cannot acquire a dongle (held by another coder or in cooldown), it enqueues its request and calls `pthread_cond_wait`. When the dongle is released, `pthread_cond_broadcast` wakes all waiters; each waiter then checks the priority queue to determine if it is the rightful next owner.

```c
/* Coder enqueues and sleeps until it is at the head of the queue
   and the dongle is available */
heap_push(&dongle->queue, req);
while (!sim->stop && !can_take(dongle, coder->id))
    pthread_cond_wait(&dongle->cond, &dongle->mutex);
```

Thread-safe communication between coder threads and the monitor is achieved by broadcasting on all dongle condition variables when a burnout is detected, ensuring every sleeping thread wakes up, observes `stop`, and exits cleanly.

### `pthread_cond_timedwait` — Cooldown Enforcement

When a coder is selected from the wait queue but the dongle is still in cooldown, the thread uses `pthread_cond_timedwait` with an absolute deadline equal to `release_time`. This eliminates busy-waiting while enforcing the cooldown precisely:

```c
struct timespec ts;
ts.tv_sec  = release_time / 1000;
ts.tv_nsec = (release_time % 1000) * 1000000L;
pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
```

### Custom Event Implementation & Priority Queue (Min-Heap)

A custom **event implementation** backed by a **binary min-heap** is created per dongle (`t_heap`). No standard library priority queue is used. The condition variables are combined with this heap to create our custom event queue. The comparison key is:

- **FIFO**: `seq` — a monotonically increasing arrival sequence number
- **EDF**: `deadline = last_compile_start + time_to_burnout`; coder number is used as tie-breaker for full determinism

The heap provides **O(log n)** insertion (`heap_push`) and extraction (`heap_pop`).

### Monitor Thread

The monitor thread runs an independent loop with a **1 ms sleep interval**, well within the 10 ms burnout detection requirement. At each iteration it:

1. Acquires `state_mutex` and checks each coder's `last_compile_start`.
2. If any coder has exceeded `time_to_burnout`, sets `stop = 1`, prints the burnout message, then calls `pthread_cond_broadcast` on every dongle condition variable.
3. If `number_of_compiles_required > 0` and every coder has reached that count, sets `stop = 1` and broadcasts.

Broadcasting (rather than signalling one) guarantees **every** sleeping coder thread wakes up, checks the stop flag, and exits — preventing the simulation from hanging after a stop condition.

---

## Allowed External Functions

| Category | Functions |
|---|---|
| Threads | `pthread_create`, `pthread_join` |
| Mutexes | `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy` |
| Condition Variables | `pthread_cond_init`, `pthread_cond_wait`, `pthread_cond_timedwait`, `pthread_cond_signal`, `pthread_cond_broadcast`, `pthread_cond_destroy` |
| Time | `gettimeofday`, `clock_gettime`, `usleep` |
| I/O & Memory | `write`, `printf`, `fprintf`, `malloc`, `free`, `memset` |
| String | `strcmp`, `strlen`, `atoi` |

`libft` is **not** authorized.

---

## Resources

### References

- [POSIX Threads Programming — Blaise Barney, LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [The Little Book of Semaphores — Allen B. Downey](https://greenteapress.com/wp/semaphores/)
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Earliest Deadline First Scheduling — Wikipedia](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)
- [`pthread_cond_timedwait(3p)` — Linux man pages](https://man7.org/linux/man-pages/man3/pthread_cond_timedwait.3p.html)
- [`gettimeofday(2)` — Linux man pages](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### AI Usage

AI assistance (Claude) was used in the following areas:

| Task | Details |
|---|---|
| **README drafting** | Structuring and writing this README based on project notes and subject requirements |
| **Concept clarification** | Explaining EDF scheduling semantics and the difference between `pthread_cond_signal` and `pthread_cond_broadcast` |
| **Edge case discussion** | Brainstorming edge cases such as single-coder scenarios and equal-deadline tie-breaking in EDF |

All generated content was reviewed, tested, and fully understood before being integrated. No AI-generated code was used without manual verification.

---

## Architecture & Data Flow Schema

Below is the visual representation of the project's architecture, threading model, and resource management rules:

![CODEXION Architecture Schema](schema.jpg)

*(A text-based fallback is provided below for offline viewing)*

```text
+-----------------------------------------------------------------------------------------+
|                                CODEXION ARCHITECTURE SCHEMA                             |
+-----------------------------------------------------------------------------------------+

[ 1 ] THREAD MAPPING                      [ 2 ] DONGLE LAYOUT
Each Coder = 1 Dedicated Thread           Circular Table:
Coder 1 -> Thread 1                       [Coder 1] -- (Dongle 1) -- [Coder 2]
Coder 2 -> Thread 2                               |                      |
... created via pthread_create()             (Dongle N)              (Dongle 2)
                                                  |                      |
                                              [Coder N] -- (Dongle 3) -- [Coder 3]

[ 3 ] COOLDOWN MECHANISM                  [ 4 ] MUTEX PROTECTION
Dongle Released -> Cooldown Starts        Every Dongle is protected by its own MUTEX.
During Cooldown: Dongle cannot be taken   (pthread_mutex_t)
Enforced via: pthread_cond_timedwait()

[ 5 ] CONDITION VARIABLES                 [ 6 ] DEADLOCK PREVENTION (CIRCULAR WAIT)
Instead of spinning (CPU waste):          Rule: Always acquire LOWER INDEX dongle first.
Threads sleep via pthread_cond_wait()     e.g., Coder 1 (D1 & D5) -> Takes D1 then D5
Woken up by pthread_cond_broadcast()      e.g., Coder 5 (D4 & D5) -> Takes D4 then D5
                                          This breaks the circular wait!

[ 7 ] SCHEDULING: FIFO vs EDF             [ 8 ] LIVENESS & STARVATION
FIFO: Strict arrival order queue.         EDF guarantees that the coder closest to
EDF: Priority = (last_compile_start       death gets the resource. This ensures no
                + time_to_burnout)        coder starves if the parameters are viable.

[ 9 ] MONITOR THREAD                      [ 10 ] BURNOUT DETECTION
1 Dedicated Monitor Thread                Monitor wakes up every 1ms.
Checks if ANY coder has surpassed         If Burnout occurs: Prints "burned out"
their time_to_burnout limit.              within the strict 10ms threshold.

[ 11 ] FORBIDDEN FUNCTIONS                [ 12 ] SIMULATION END CONDITIONS
No sleep(), no libft, no semaphores.      A. A coder burns out.
Only POSIX thread primitives.             B. All coders reach target compile count.

+-----------------------------------------------------------------------------------------+
| [ CORE DATA STRUCTURE ]  BINARY MIN-HEAP (PRIORITY QUEUE)                               |
|                                                                                         |
| We use a Custom Binary Min-Heap (Array-based) instead of a Linked List.                 |
| WHY? O(log N) insertion/extraction. Fast sorting of deadlines!                          |
| The root always contains the highest priority request (Earliest Deadline or First In).  |
+-----------------------------------------------------------------------------------------+
| [ IMPORTANT ] DOUBLE RESOURCE REQUIREMENT                                               |
|                                                                                         |
| A Coder MUST acquire 2 Dongles before compiling.                                        |
| Output MUST show:                                                                       |
|   1. "X has taken a dongle"                                                             |
|   2. "X has taken a dongle"                                                             |
|   3. "X is compiling"                                                                   |
| If time_to_burnout is exceeded before step 3, the coder dies.                           |
+-----------------------------------------------------------------------------------------+
```


*This project has been created as part of the 42 curriculum by **cerkurt***.

---

## Index

- [Testing Command](#testing-command)
- [Description](#description)
- [Allowed Operations](#allowed-operations)
- [General Requirements](#general-requirements)
- [Benchmark Requirements](#benchmark-requirements-operation-count)
- [Bonus (checker)](#bonus-checker)
- [Algorithm Overview](#algorithm-overview)
  - [Rank Mapping](#1-rank-mapping)
  - [Small Stack Handling](#2-small-stack-handling)
  - [Passport Push Strategy (A → B)](#3-passport-push-strategy-a--b)
  - [Reinsertion Phase (B → A)](#4-reinsertion-phase-b--a)
  - [Final Rotation](#5-final-rotation)
- [Resources](#resources)

---

## Testing Command

```bash
ARG=$(python3 - <<'PY'
import random
n = 500
s = set()
while len(s) < n:
    s.add(random.randint(-2147483648, 2147483647))
print(" ".join(map(str, s)))
PY
)

./push_swap $ARG | wc -l
./push_swap $ARG | ./checker $ARG
```

---

## Description

**Goal**

Create a program called `push_swap` that prints the shortest possible sequence
of stack operations to sort a list of unique integers in ascending order.

Only the allowed operations may be used.

**Stacks**

- **Stack A** → initially filled with integers  
- **Stack B** → initially empty  

---

## Allowed Operations

### Swap
- `sa` — swap top two elements of stack A  
- `sb` — swap top two elements of stack B  
- `ss` — perform `sa` and `sb` simultaneously  

### Push
- `pa` — push top of B onto A  
- `pb` — push top of A onto B  

### Rotate (Up)
- `ra` — rotate stack A  
- `rb` — rotate stack B  
- `rr` — rotate A and B  

### Reverse Rotate (Down)
- `rra` — reverse rotate stack A  
- `rrb` — reverse rotate stack B  
- `rrr` — reverse rotate A and B  

---

## General Requirements

**Allowed functions**
- `read`, `write`, `malloc`, `free`, `exit`
- `ft_printf` (or equivalent)

**Restrictions**
- Global variables are forbidden

**Program behavior**
- Takes integers as arguments (first argument is top of stack A)
- Outputs only valid operations, one per line
- No output if no arguments are given

**Error handling**

Print `Error\n` to `stderr` if:
- Input is not an integer
- Integer overflow / underflow occurs
- Duplicate values exist
- Invalid formatting is detected

---

## Benchmark Requirements (Operation Count)

### 100% Score
- 100 numbers → fewer than **700** operations  
- 500 numbers → fewer than **5500** operations  

### Minimum Validation (80%) — any one set

**Option A**
- 100 < 1100  
- 500 < 8500  

**Option B**
- 100 < 700  
- 500 < 11500  

**Option C**
- 100 < 1300  
- 500 < 5500  

---

## Bonus (checker)

**Program name:** `checker`

**Behavior**
- Reads initial stack A from arguments
- Reads instructions from `stdin`
- Executes instructions on stacks A and B

**Result**
- Prints `OK` if stack A is sorted and B is empty
- Prints `KO` otherwise

**Errors**
- Invalid input
- Invalid instruction
- Duplicate values
- Overflow / underflow

---

## Algorithm Overview

The algorithm uses **rank-based sorting** combined with a **passport (frame)
push strategy**, implemented using **circular arrays**.

### 1. Rank Mapping

All input values are converted to ranks from `0` to `N - 1`.

- Rank `0` → smallest value  
- Rank `N - 1` → largest value  

Raw integer values are no longer used after this step.

**Functions used**
- `index_to_ranks_instack`
- `sort_integer_array`
- `find_index`
- `position_to_value`

---

### 2. Small Stack Handling

Special optimized logic for small stack sizes.

**Functions used**
- `sort_two_a`
- `sort_three_a`
- `sort_four_a`
- `sort_five_a`

---

### 3. Passport Push Strategy (A → B)

Elements are pushed from stack A to B if their rank falls within a defined
frame (passport range).

This keeps stack B partially ordered and minimizes reinsertion cost.

**Functions used**
- `organize_b`
- `define_pass`
- `scan_push_and_pass_update`
- `update_pass`
- `push_a_to_b`
- `rotate_a`

---

### 4. Reinsertion Phase (B → A)

Elements are moved back from B to A using the cheapest rotation cost.

Combined rotations (`rr`, `rrr`) are used when possible.

**Functions used**
- `cheapest_move`
- `insert_in_a`
- `bring_to_top_cost`
- `combined_bring_to_top_cost`
- `apply_move_b_to_a`
- `push_b_to_a`

---

### 5. Final Rotation

After reinsertion, stack A is rotated so that rank `0` is at the top.

This results in a fully sorted stack.

**Functions used**
- `final_rotate_a`
- `value_to_position`
- `rotate_a`
- `reverse_rotate_a`

---

## Resources

- https://www.geeksforgeeks.org/dsa/circular-array/
- https://stackoverflow.com/questions/27892589/c-circular-array
- https://stackoverflow.com/questions/7693992/search-in-circular-array
- https://stackoverflow.com/questions/1452545/shifting-a-circular-array
- https://stackoverflow.com/questions/42603730/algorithms-circular-array-rotation

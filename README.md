# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Readme                                             :+:    :+:             #
#                                                      +:+                     #
#    By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                      #
#                                                    +#+                       #
#    Created: 2025/11/27 16:19:20 by cerkurt       #+#    #+#                  #
#    Updated: 2025/12/02 11:56:24 by cerkurt       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#                             PUSH_SWAP README FILE                            #
#******************************************************************************#

This project has been created as part of the 42 curriculum by <cerkurt>.


#******************************************************************************#
#                               TESTING COMMAND                                #
#******************************************************************************#

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

#******************************************************************************#
#                                 DESCRIPTION                                  #
#******************************************************************************#

Goal:
	• Create a  --program-- "push_swap" that prints the shortest possible
	sequence of stack operations to sort a list of unique integers in ascending
	order.
	• Only the allowed operations may be used.
	
Operate on two stacks:
	• "Stack a" → initially filled with integers
	• "Stack b" → initially empty

#******************************************************************************#

#******************************************************************************#
#                              ALLOWED OPERATIONS                              #
#******************************************************************************#

"SWAP"
	sa  : Swap top two elements of stack a
	sb  : Swap top two elements of stack b
	ss  : Perform sa and sb simultaneously

"PUSH"
	pa  : Push top of b onto top of a
	pb  : Push top of a onto top of b

"ROTATE (UP)"
	ra  : Shift up all elements of a (first becomes last)
	rb  : Shift up all elements of b
	rr  : Perform ra and rb simultaneously

"REVERSE ROTATE (DOWN)"
	rra : Shift down all elements of a (last becomes first)
	rrb : Shift down all elements of b
	rrr : Perform rra and rrb simultaneously

#******************************************************************************#

#******************************************************************************#
#                             GENERAL REQUIREMENTS                             #
#******************************************************************************#

Allowed functions:
	• read, write, malloc, free, exit
	• ft_printf (or equivalent coded by you)

Global variables:
	• Forbidden

Program behavior:
	• Takes integer arguments (first argument is top of stack a)
	• Must output a valid sequence of operations to sort stack a
	• Instructions must each appear on their own line
	• Nothing else should be printed
	• No output when no arguments are given

Error handling:
	• Must print "Error\n" on stderr when:
	• Non-integer input
	• Overflow / underflow
	• Duplicate values
	• Invalid formatting

#******************************************************************************#

#******************************************************************************#
#                      BENCHMARK REQUIREMENTS (OP COUNT)                       #
#******************************************************************************#

To achieve maximum score (100%):
	• 100 random numbers  →  fewer than 700 operations
	• 500 random numbers  →  fewer than 5500 operations

Minimum validation (80%) is achieved with ANY ONE set:

Option A:
	• 100 < 1100 operations
	• 500 < 8500 operations

Option B:
	• 100 < 700 operations
	• 500 < 11500 operations

Option C:
	• 100 < 1300 operations
	• 500 < 5500 operations

#******************************************************************************#

#******************************************************************************#
#                         BONUS REQUIREMENTS (checker)                         #
#******************************************************************************#

Program name:
	• checker

Behavior:
	• Reads initial stack a from arguments
	• Reads instructions from standard input (one per line)
	• Executes all instructions on stacks a and b

After execution:
	• If a is sorted AND b is empty → print "OK"
	• Otherwise → print "KO"

Error cases must print "Error\n" to stderr:
	• Non-integer inputs
	• Overflow / underflow
	• Duplicate values
	• Invalid / unknown instruction name
	• Incorrect formatting

#******************************************************************************#

#******************************************************************************#
#                              ALGORITHM OVERVIEW                              #
#******************************************************************************#

To optimize sorting and reduce the number of operations, my algorithm uses
a rank-based approach combined with *passport approach pushing*. I used circular
array logic and implementation with the stacks, because I found it interesting
to work with. Yes, it caused different bugs than I have faced before but in
general concept it was interesting to work on and was fun too.

1) Rank Mapping
   • All input values are first scanned and *converted to ranks from 0 to N-1*.
   		Functions used;
		* index_to_ranks_instack(t_stack *stack)
		* sort_integer_array(int *tab, unsigned int size)
		* find_index(int *sorted_table, unsigned int size, int val)
		* position_to_value(t_stack *stack, int pos)
   • Rank 0 represents the smallest value, rank N-1 the largest.
   • This scanning is internal only and does NOT change the logical order. Raw
   integer values are not used later in sorting algorithm once they are all
   converted into ranks.
   • It allows simpler comparisons and predictable sorting behavior.

2) Small Stack Handling
   • Special optimized cases exist for stack sizes of 2, 3, 4, and 5.
   • These cases are sorted directly using minimal operations.
		Functions used;
		* sort_two_a(t_stack *a)
		* sort_three_a(t_stack *a)
		* sort_four_a(t_stack *a, t_stack *b)
		* sort_five_a(t_stack *a, t_stack *b)

3) Passport Approach Push Strategy (A -> B)
   • For larger inputs, elements are pushed from stack A to stack B based on
   *if they have a passport in the given rank push constrains or not*. We can
   simply refer these as kind of "frame" or "boundry" or "limit". So we check
   *for each rank "Are you inside this limit to be pushed to B or not?", "Do*
   *you have a passport or not?"*
   • This passport represents a range of ranks (e.g. 0–19, 20–39, ...).
   • This keeps stack B partially ordered and reduces reinsertion cost when I
   want to insert back from B to A.
   • Logic is to keep small ranks at the bottom of the B, thats why we start
   with small frame to search in.
   • When we keep the small numbers at the bottom of the B, while we are pushing
   back to A, A will be almost perfectly sorted and will require minimum
   operations to sort finally.
		Functions used:
		* organize_b(t_stack *a, t_stack *b)
		* define_pass(t_pass *f, int size)
		* scan_push_and_pass_update(t_stack *a, t_stack *b, t_pass *f)
		* update_pass(t_pass *f)
		* position_to_value(t_stack *a, int pos)
		* push_a_to_b(t_stack *a, t_stack *b)
		* rotate_a(t_stack *a)

4) Reinsertion Phase (B -> A)
   • Elements are moved back from stack B to stack A.
   • For each element, the *cheapest rotation cost* is calculated.
   • Combined rotations (rr / rrr) are used whenever possible to reduce cost.
		Functions used;
		* cheapest_move(t_stack *a, t_stack *b)
		* insert_in_a(t_stack *a, int rank)
		* bring_to_top_cost(int pos, int size)
		* combined_bring_to_top_cost(int cost_a, int cost_b)
		* apply_move_b_to_a(t_stack *a, t_stack *b, t_rocost cost)
		* apply_mutual_rotations(...)
		* leftover_rotations_a(...)
		* leftover_rotations_b(...)
		* push_b_to_a(t_stack *b, t_stack *a)

5) Final Rotation
   • After all elements are back in stack A, stack A is rotated so that rank 0
   is at the top.
   • This results in a fully sorted stack in ascending order.
		Functions used;
		* final_rotate_a(t_stack *a)
		* value_to_position(t_stack *a, int value)
		* bring_to_top_cost(int pos, int size)
		* rotate_a(t_stack *a)
		* reverse_rotate_a(t_stack *a)

#******************************************************************************#
#            		              RESOURCES			        	               #
#******************************************************************************#

This project is created on the logic of circular arrays as base.

https://www.geeksforgeeks.org/dsa/circular-array/
https://stackoverflow.com/questions/27892589/c-circular-array
https://www.geeksforgeeks.org/dsa/find-the-index-in-a-circular-array-from-which-prefix-sum-is-always-non-negative/
https://stackoverflow.com/questions/7693992/search-in-circular-array
https://stackoverflow.com/questions/1452545/shifting-a-circular-array
https://stackoverflow.com/questions/42603730/algorithms-circular-array-rotation

################################################################################
##                               END OF FILE                                  ##
################################################################################
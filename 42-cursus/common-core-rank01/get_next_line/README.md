# get_next_line

**Resolution of `common-core-rank01/get_next_line` (version 11) project, *mandatory* & *bonus* parts.**

Features of this solution:
- Solved using lists, not the frequently seen `ft_strjoin()`—very inefficient—method.
- Requests batches of `BUFFER_SIZE` to the OS, `DEFAULT_LIST_SIZE` of them at a time, vastly increasing the efficiency of the execution. This version of **get_next_line** comfortably passes the most unlikely *timeout* tests.
- Fastest possible execution with minimum possible memory allocations for increased performance. Bare essential use of the slow `malloc()` system call, and just three passes over the fetched text: Once during the file reading & copying into memory, another for the *newline* (`\n`) location, and a last pass during the line assembly.
- Neatly fits into a single file, facilitating its incorporation into the user's **libft**. The accessory functions, found in `get_next_line_utils.c`, are simply two other **libft** functions.

Notes:
- The three *bonus* files included are there for 42's **Moulinette** benefit and to reap the 125 score. The basic three *mandatory* `get_next_line.h`, `get_next_line.c`, and `get_next_line_utils.c` also fulfill every demand in the project.

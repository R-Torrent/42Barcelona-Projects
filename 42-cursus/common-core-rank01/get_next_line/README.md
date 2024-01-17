# get_next_line

**Resolution of `common-core-rank01/get_next_line` (version 11) project, *mandatory* & *bonus* parts.**

Features of this solution:
- Solved using lists, not the frequently seen `ft_strjoin()`—very inefficient—method.
- Requests batches of `BUFFER_SIZE` to the OS, `DEFAULT_LIST_SIZE` of them at a time, vastly increasing the efficiency of the execution. This version of **get_next_line** comfortably passes the most unlikely *timeout* tests.
- Fastest possible execution with minimum possible memory allocations for increased performance. Bare essential use of the slow `malloc()` system call, and just **three** passes over the fetched text: Once during the file reading & copying into memory, another for the *newline* (`'\n'`) location, and a last pass during the line assembly.
- Neatly fits into a single file, facilitating its incorporation into the user's **libft**. The accessory functions, found in `get_next_line_utils.c`, are simply two other **libft** functions.

Notes:
- The three `_bonus` files included with the project are there for 42's ***Moulinette*** benefit and to reap the 125 score. The basic three *mandatory* `get_next_line.h`, `get_next_line.c`, and `get_next_line_utils.c` also fulfill every demand in the project.
- The lists employed here are not the *bonus* list structure and related functions coded in the `common-core-rank00/Libft` project. Unfortunately, the extra dereferencing required from the `->content` layer of abstraction makes it impossible to meet ***Norminette***'s stringent rules in a single file.
- This project employs the *mem* functions in `<string.h>` to process the arrays, with additional info on the length of each recorded in the list blocks. The sole `NUL` character (`'\0'`) to be found is the delimiter of the final, assembled line.

---

## Contents

### A. Mandatory part

#### A.1 get_next_line.h

Provides
- Inclusion of headers.
- Macro definitions, notably the conditional definitions of the `BUFFER_SIZE` and `DEFAULT_LIST_SIZE` constants.
- Declaration of all functions with external linkage.
- Definition of the fundamental `struct s_block` blocks that constitute the project's lists. \[**Note**: `t_blocks` is a *typedef* pointer to said structure.\]<br>
	1. `size_t len` processable characters from the *start* point to the end of the block.<br>
	2. `unsigned int index` index (mod `DEFAULT_LIST_SIZE`) of the block; used to mark the need for a new batch allocation of memory.<br>
	3. `struct s_block *prev` previous block in the list.<br>
	4. `char *start` starting point of the line or continuation therefrom in the next blocks.<br>
	5. `char str[BUFFER_SIZE]` complete byte string read from the file.

#### A.2 get_next_line.c

##### A.2.a `char *get_next_line(int fd)`

This function contains the only `static` variable of the project, as instructed in the *bonus* part of the document: An array of pointers to the lists of recorded data, one per file descriptor. \[**Note**: Read the `TODO.txt` file of this GitHub repository.\] This entry function, the only visible from outside the source file, simply checks that no funny values where used for the macro definitions during compilation, and defers work to `read_blocks`. Should that function return `false`, from an error somewhere or because no characters are in storage for a subsequent **get_next_line**, then the list is wiped clean. Returns the line read, or `NULL` if none was to be found or if an error occurred somewhere.

##### A.2.b `static bool read_blocks(int fd, t_blocks *plist, char **line)`

Locates *newline* characters (`'\n'`) in the text calling at the `add_block` function until one is spotted, whence it follows with the `asm_line` function. (This function is also called if no characters are returned from a `read` system call. `read_blocks` then returns to the main function, `get_next_line`, carrying the result of the line-assembling function.) The first and usual case, *newline* spotted, will result in the `asm_line` function receiving further instructions to spare this first block from the `free` axe. In many cases, a few characters from the next line will have been read following the terminating `'\n'`, and these must be kept. `read_blocks` returns a `true` value if and only if these extra characters have been stored.

##### A.2.c `static ssize_t add_block(int fd, t_blocks *plist)`

Fills in a new block of data from the file into the list, linking with its predecessor. Moves the pointer `*plist` to the new block. The block may be the first of a `new_batch`, necessitating a memory allocation of `DEFAULT_LIST_SIZE` blocks of size `sizeof(struct s_block)`. Returns the number of characters read from the file, possibly less than `BUFFER_SIZE`.

##### A.2.d `static bool asm_line(t_blocks *plst_copy, t_blocks *plst_del, char **line)`

Assembles the return string (`*line`) of **get_next_line** from the list starting at `*plst_copy`. It asks for the necessary memory and fills it up by blocks, starting with the terminating `NUL` (`'\0'`) character and working from right to left—hence the label `prev` for *previous* in the `s_block` structure!—. Finally it orders the cleaning of the list starting at `*plst_del`. It will instruct the `clear_blocks` function to skip the first deletion if the pointers `*plst_copy` and `*plst_del` don't agree and if the first pointer is not the first block of its batch. Returns whether the line was created or not.

##### A.2.e `static void clear_blocks(t_blocks *plist, bool skip_first)`

Frees the memory allocated by the blocks occupied with the line just read, starting at `*plist`. The first batch encountered—which is the newest of the lot—is possibly spared if it contains data from the following line to be read. There is a bit of trickiness to figure the actual address of the batch from the address of the current block and its `index` number. `*plist` is pushed all the way back to `NULL`.

#### A.3 get_next_line_utils.c

##### A.3.a `void *ft_memchr(const void *s, int c, size_t n)`

Copied verbatim from the `common-core-rank00/Libft` project.

##### `A.3.b void *ft_memcpy(void *dst, const void *src, size_t n)`

Copied verbatim from the `common-core-rank00/Libft` project.

---

### B. Bonus part

#### B.1 get_next_line_bonus.h

\[**Note**: Identical to **get_next_line.h**, except in name.\]

#### B.2 get_next_line_bonus.c

\[**Note**: Identical to **get_next_line.c**, except in name.\]

#### B.3 get_next_line_utils_bonus.c

\[**Note**: Identical to **get_next_line_utils.c**, except in name.\]

---

### C. Rudimentary testing provided

#### C.1 tester.c

A very simple program that provides confirmation that simultaneous line fetching from various files is possible. Additional tests, such as reading from the `stdin`, reading very short or very long lines, or behaviour from `'\n'` *vs* non-`'\n'` ending files is up to the examiner.

#### C.2 test1.txt

Standard *Lorem ipsum* placeholder; text by Cicero.

#### C.3 test2.txt

Extract from the United States Declaration of Independence.

#### C.4 test3.txt

A string of all the decimal digits, ordered.

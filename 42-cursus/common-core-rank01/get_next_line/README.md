# get_next_line

**Resolution of `common-core-rank01/get_next_line` (version 11) project, *mandatory* & *bonus* parts.**

Features of this solution:
- Solved using lists, not the frequently seen `ft_strjoin()`—very inefficient—method.
- Requests batches of `BUFFER_SIZE` to the OS, `DEFAULT_LIST_SIZE` of them at a time, vastly increasing the efficiency of the execution. This version of **get_next_line** comfortably passes the most unlikely *timeout* tests.
- Fastest possible execution with minimum possible memory allocations for increased performance. Bare essential use of the slow `malloc()` system call, and just **three** passes over the fetched text: Once during the file reading & copying into memory, another for the *newline* (`\n`) location, and a last pass during the line assembly.
- Neatly fits into a single file, facilitating its incorporation into the user's **libft**. The accessory functions, found in `get_next_line_utils.c`, are simply two other **libft** functions.

Notes:
- The three *bonus* files included with the project are there for 42's ***Moulinette*** benefit and to reap the 125 score. The basic three *mandatory* `get_next_line.h`, `get_next_line.c`, and `get_next_line_utils.c` also fulfill every demand in the project.
- The lists employed here are not the *bonus* list structure and related functions coded in the `common-core-rank00/Libft` project. Unfortunately, the extra dereferencing required from the `->content` layer of abstraction makes it impossible to meet ***Norminette***'s stringent rules in a single file.

---

## Contents

### A. Mandatory part

#### A.1 get_next_line.h

Provides, among other stuff,
- Inclusion of headers.
- Macro definitions, notably the conditional definitions of the `BUFFER_SIZE` and `DEFAULT_LIST_SIZE` constants.
- Declaration of all functions with external linkage.
- Definition of the fundamental `struct s_block` blocks that constitute the project's lists. **Note**: `t_blocks` is a *typedef* pointer to said structure.<br>
	1. `size_t len` <br>
	2. `unsigned int index` <br>
	3. `struct s_block *prev` <br>
	4. `char *start` <br>
	5. `char str[BUFFER_SIZE]`

#### A.2 get_next_line.c

##### A.2.a `char *get_next_line(int fd)`

##### A.2.b `static bool read_blocks(int fd, t_blocks *plist, char **line)`

##### A.2.c `static ssize_t add_block(int fd, t_blocks *plist)`

##### A.2.d `static bool asm_line(t_blocks *plst_copy, t_blocks *plst_del, char **line)`

##### A.2.e `static void clear_blocks(t_blocks *plist, bool skip_first)`

#### A.3 get_next_line_utils.c

##### A.3.a `void *ft_memchr(const void *s, int c, size_t n)`

Copied verbatim from the `common-core-rank00/Libft` project.

##### `A.3.b void *ft_memcpy(void *dst, const void *src, size_t n)`

Copied verbatim from the `common-core-rank00/Libft` project.

---

### B. Bonus part

#### B.1 get_next_line_bonus.h

**Note**: Identical to **get_next_line.h**, except in name.

#### B.2 get_next_line_bonus.c

**Note**: Identical to **get_next_line.c**, except in name.

#### B.3 get_next_line_utils_bonus.c

**Note**: Identical to **get_next_line_utils.c**, except in name.

---

### C. Rudimentary testing provided

#### C.1 tester.c

A very simple program that provides confirmation that simultaneous line fetching from various files is possible. Additional tests, such as reading from the `stdin`, reading very short or very long lines, or `\n` *vs* non-`\n` ending files is up to the examiner.

#### C.2 test1.txt

Standard *Lorem ipsum* placeholder; text by Cicero.

#### C.3 test2.txt

Extract from the United States Declaration of Independence.

#### C.4 test3.txt

A string of all decimal digits, ordered.
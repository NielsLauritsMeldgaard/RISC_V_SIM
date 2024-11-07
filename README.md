# RISC_V_SIM

## C Coding Style Guidelines

### 1. **General Structure**
- **Indentation**: Use  **only tabs**.
- **Line Length**: Keep lines **max 80 characters** long.
- **Naming Conventions**: Use **descriptive names** for variables, functions, and types.

### 2. **File Naming**
- **Lowercase** letters for file names.
- Use underscores (`_`) to separate words (e.g., `riscv_simulator.c`).
- Header files use `.h`, source files use `.c`.

### 3. **Function Definitions**
- Function names: **Lowercase** with underscores for separation.
- Function signatures should be **concise** and clear.
- Avoid deep nesting in functions. Split large functions into smaller ones.

### 4. **Variable Naming**
- Use **descriptive names** (e.g., `total_bytes`, `num_iterations`).
- **Constants** in **uppercase** with underscores (e.g., `MAX_BUFFER_SIZE`).

### 5. **Indentation and Spacing**
- Indent blocks of code inside control structures.
- Use **one space** before and after operators (e.g., `a + b`).
- **One space after commas** in function calls and variable declarations.

### 6. **Control Flow**
- Always use braces `{}` with `if`, `for`, `while`, even for single statements.
- **Do not use `goto`** unless absolutely necessary.

### 7. **Comments and Documentation**
- **Comment code where necessary**, explaining why something is done (not what).
- **Block comments** (`/* */`) for larger explanations, **line comments** (`//`) for brief notes.
- **Document functions** with comments above the function, including:
  - Description of the function’s purpose.
  - Parameters and return values.
  - Side effects or special behaviors.

### 8. **Structs, enums exc**
-**Use descriptive names for structs and enums.
-**Always** capital first letter in struct name
Example:
```c
/*
*typedef struct {
*    int x;
*    int y;
*    void (*move)(struct Point*, int, int);
*} Point;
*
*void point_move(Point* p, int dx, int dy) {
*    p->x += dx;
*    p->y += dy;
*}
*
*typedef enum {
*    RED,
*    GREEN,
*    BLUE
*} Color;
*
*/

  
Example:
```c
/*
 * Calculates the sum of two integers.
 *
 * Parameters:
 *   a - first integer
 *   b - second integer
 *
 * Returns:
 *   The sum of the two integers.
 */
int calculate_sum(int a, int b);




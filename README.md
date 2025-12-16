# Stack VM

A minimal stack-based virtual machine with its own bytecode assembler and high-level compiler. Write programs in a simple expression-based language, compile to assembly, assemble to bytecode, and execute.

## What It Does

- **VM**: Executes bytecode using a stack-based architecture
- **Assembler**: Converts human-readable instructions into bytecode
- **Compiler**: Translates high-level function calls into assembly
- **Instruction Set**: PUSH, ADD, SUB, MUL, DIV, EQ, JZ, PRINT, DUP, HALT

## Building

```bash
gcc -o vm src/main.c
gcc -o assembler src/assembler/assembler.c
gcc -o compiler src/compiler/compiler.c
```

## Usage

### Option 1: High-Level Language (Recommended)

#### 1. Write High-Level Code

Create a file `program.txt`:

```
add(5, 10)
print()
sub(20, 5)
print()
mul(3, 4)
print()
```

#### 2. Compile to Assembly

```bash
./compiler program.txt
```

This generates `write_file` containing assembly instructions.

#### 3. Assemble to Bytecode

```bash
./assembler write_file program.bin
```

#### 4. Run

```bash
./vm program.bin
```

Output:
```
15
15
12
```

### Option 2: Direct Assembly

#### 1. Write Assembly Code

Create a file `program.asm`:

```asm
PUSH 5
PUSH 10
ADD
DUP
PRINT
PUSH 3
DIV
DUP
PRINT
PUSH 5000
MUL
PRINT
HALT
```

#### 2. Assemble to Bytecode

```bash
./assembler program.asm program.bin
```

#### 3. Run

```bash
./vm program.bin
```

Output:
```
15
5
25000
```

**How it works**: Pushes 5 and 10, adds them (15), duplicates and prints (15). Divides by 3 (5), duplicates and prints (5). Multiplies by 5000 (25000), prints (25000), then halts.

## Compiler Language Reference

The compiler accepts function-style syntax:

| Function | Arguments | Description |
|----------|-----------|-------------|
| add(a, b) | Two integers | Pushes a and b, adds them, leaves result on stack |
| sub(a, b) | Two integers | Pushes a and b, subtracts b from a, leaves result on stack |
| mul(a, b) | Two integers | Pushes a and b, multiplies them, leaves result on stack |
| div(a, b) | Two integers | Pushes a and b, divides a by b, leaves result on stack (errors on divide by zero) |
| print() | None | Pops and prints top stack value |
| print(n) | One integer | Pushes n and immediately prints it (doesn't affect stack) |

**Stack behavior**: Operations like `add(5, 10)` leave their result on the stack. Use `print()` to pop and display the result, or chain operations together. The compiler automatically inserts a `HALT` instruction at the end.

**Example**:
```
add(100, 50)
mul(2, 3)
print()
print()
```
Output: `6` then `150` (stack is LIFO)

## Instruction Reference

| Instruction | Operand | Description |
|-------------|---------|-------------|
| PUSH n      | Yes     | Push value n onto stack |
| ADD         | No      | Pop two values, push their sum |
| SUB         | No      | Pop b, pop a, push a-b |
| MUL         | No      | Pop two values, push their product |
| DIV         | No      | Pop b, pop a, push a/b (errors on divide by zero) |
| EQ          | No      | Pop two values, push 1 if equal, 0 otherwise |
| JZ addr     | Yes     | Pop value, jump to byte addr if zero |
| PRINT       | No      | Pop and print value |
| DUP         | No      | Duplicate top stack value |
| HALT        | No      | Stop execution |

## Known Issues

- **No label support**: You must calculate byte addresses manually for jumps. Each instruction is 1 byte, instructions with operands are 2 bytes in total.
- **No negative number support**: Stack values are int but PUSH only accepts 0-255.

## Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b my-feature`
3. Make your changes
4. Test thoroughly with sample programs
5. Commit: `git commit -am 'Add feature'`
6. Push: `git push origin my-feature`
7. Open a Pull Request

Before submitting:
- Ensure code compiles without warnings
- Test with at least one working program
- Keep changes focused and documented

## License

MIT License - See `LICENSE` file.

Copyright (c) 2025 Saba 

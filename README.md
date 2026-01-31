# Stack VM

A minimal stack-based virtual machine with its own bytecode assembler and high-level compiler. Write programs in a simple expression-based language, compile to assembly, assemble to bytecode, and execute.

## What It Does

- **VM**: Executes bytecode using a stack-based architecture with 256 words of addressable memory
- **Assembler**: Converts human-readable instructions into bytecode
- **Compiler**: Translates high-level function calls into assembly
- **Instruction Set**: PUSH, ADD, SUB, MUL, DIV, EQ, JZ, JMP, PRINT, DUP, OVER, SWAP, DROP, STORE, LOAD, HALT

## Building

```bash
gcc src/vm.c -o vm
gcc src/assembler/assembler.c -o assembler
gcc src/compiler/compiler.c -o compiler
```

## Usage

### Option 1: Direct Assembly

#### 1. Write Assembly Code

Create a file `program.asm`:

```asm
PUSH 0
DUP
PRINT
PUSH 1
ADD
DUP
PUSH 5
EQ
JZ 2
HALT
```

**Other examples can be found in the `assembly-examples` folder.**

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
0
1
2
3
4

```

### Option 2: High-Level Language **(Not Recommended Due To Being Outdated)** 

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

---

## Instruction Reference

| Instruction | Operand | Description                                                 |
| ----------- | ------- | ----------------------------------------------------------- |
| PUSH n      | Yes     | Push value n onto stack                                     |
| ADD         | No      | Pop two values, push their sum                              |
| SUB         | No      | Pop b, pop a, push a-b                                      |
| MUL         | No      | Pop two values, push their product                          |
| DIV         | No      | Pop b, pop a, push a/b (errors on divide by zero)           |
| EQ          | No      | Pop two values, push 1 if equal, 0 otherwise                |
| JZ addr     | Yes     | Pop value, jump to byte addr if zero                        |
| JMP addr    | Yes     | Unconditionally jump to byte addr                           |
| PRINT       | No      | Pop and print value                                         |
| DUP         | No      | Duplicate top stack value                                   |
| OVER        | No      | Duplicate second stack value (copy value at depth 1 to top) |
| SWAP        | No      | Exchange top two stack values                               |
| DROP        | No      | Discard top stack value                                     |
| STORE addr  | Yes     | Pop value from stack, store at memory address (0-255)       |
| LOAD addr   | Yes     | Push value from memory address (0-255) onto stack           |
| HALT        | No      | Stop execution                                              |

## Compiler Language Reference

The compiler accepts function-style syntax:

| Function  | Arguments    | Description                                                                       |
| --------- | ------------ | --------------------------------------------------------------------------------- |
| add(a, b) | Two integers | Pushes a and b, adds them, leaves result on stack                                 |
| sub(a, b) | Two integers | Pushes a and b, subtracts b from a, leaves result on stack                        |
| mul(a, b) | Two integers | Pushes a and b, multiplies them, leaves result on stack                           |
| div(a, b) | Two integers | Pushes a and b, divides a by b, leaves result on stack (errors on divide by zero) |
| print()   | None         | Pops and prints top stack value                                                   |
| print(n)  | One integer  | Pushes n and immediately prints it (doesn't affect stack)                         |

**Example**:

```
add(100, 50)
mul(2, 3)
print()
print()
```

**Stack behavior**: Operations like `add(5, 10)` leave their result on the stack. Use `print()` to pop and display the result, or chain operations together. The compiler automatically inserts a `HALT` instruction at the end.

## Memory Architecture

The VM provides 256 words of addressable memory (separate from the stack) accessible via STORE and LOAD instructions:

- **Stack**: 2048 words for computation and temporary values
- **Memory**: 256 words for persistent storage at addresses 0-255

**Example using memory**:

```asm
PUSH 67
STORE 0      ; Store 67 at memory address 0
PUSH 420
STORE 1      ; Store 420 at memory address 1
LOAD 0       ; Load value from address 0 (67)
LOAD 1       ; Load value from address 1 (420)
ADD          ; Add them (487)
PRINT
HALT
```

Output: `487`

## Known Issues

- **No label support**: You must calculate byte addresses manually for jumps. Each instruction is 1 byte, instructions with operands are 2 bytes in total.
- **Can't place comments on empty lines**: Every comment has to be written on the same line as the instruction. Comments can't be placed on empty lines where there are no instructions.
- **No bounds checking on address in JZ/JMP**: If the operand for JZ or JMP is out-of-range, it might lead to unexpected behavior, the VM will read/write out of bounds (undefined behavior / crash).
- **Memory addresses are bounds-checked**: STORE and LOAD verify that addresses are within 0-255 range and exit with error code 10 if out of bounds.

## Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b my-feature`
3. Make your changes
4. Test thoroughly with sample programs
5. Commit: `git commit -am 'feat: feature'`
6. Push: `git push origin my-feature`
7. Open a Pull Request

Before submitting:

- Ensure code compiles without warnings
- Test with at least one working program
- Keep changes focused and documented

## License

MIT License - See `LICENSE` file.

Copyright (c) 2025 Saba

# Stack VM

A minimal stack-based virtual machine with its own bytecode assembler. Write simple assembly-like programs, compile them to bytecode, and execute them.

## What It Does

- **VM**: Executes bytecode using a stack-based architecture
- **Assembler**: Converts human-readable instructions into bytecode
- **Instruction Set**: PUSH, ADD, SUB, MUL, DIV, EQ, JZ, PRINT, DUP, HALT

## Building

```bash
gcc -o vm src/main.c
gcc -o assembler src/assembler/assembler.c
```

## Usage

### 1. Write Assembly Code

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

### 2. Assemble to Bytecode

```bash
./assembler program.asm program.bin
```

### 3. Run

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

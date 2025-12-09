# Stack VM

A minimal stack-based virtual machine with its own bytecode assembler. Write simple assembly-like programs, compile them to bytecode, and execute them.

## What It Does

- **VM**: Executes bytecode using a stack-based architecture
- **Assembler**: Converts human-readable instructions into bytecode
- **Instruction Set**: PUSH, ADD, SUB, MUL, DIV, EQ, JZ, PRINT, HALT

## Building

```bash
gcc -o vm src/main.c
gcc -o assembler src/assembler/assembler.c
```

## Usage

### 1. Write Assembly Code

Create a file (see `instructions` for an example) `program.asm`:

```asm
PUSH 10
PUSH 20
ADD
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

Output: `30`

## Example: Countdown Loop

```asm
PUSH 5
PRINT
PUSH 1
SUB
PUSH 0
EQ
JZ 0
HALT
```

This prints numbers from 5 down to 1, then halts when it reaches 0.

**How it works**: Pushes a number, prints it, subtracts 1, checks if zero. If not zero, jumps back to byte 0 (the first PUSH instruction). When it hits zero, the JZ doesn't jump and execution continues to HALT.

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
| HALT        | No      | Stop execution |

## Known Issues

- **No label support**: You must calculate byte addresses manually for jumps. Each instruction is 1 byte, instructions with operands are 2 bytes.
- **No error checking on fread**: The VM doesn't verify that the bytecode file was read successfully.
- **Limited operand range**: Operands are uint8_t, so values are 0-255 only.
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

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

Create a file `program.asm`:

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
PUSH 1
SUB
PRINT
PUSH 0
EQ
JZ 0
HALT
```

This prints numbers from 4 down to 0.

## Instruction Reference

| Instruction | Operand | Description |
|-------------|---------|-------------|
| PUSH n      | Yes     | Push value n onto stack |
| ADD         | No      | Pop two values, push their sum |
| SUB         | No      | Pop b, pop a, push a-b |
| MUL         | No      | Pop two values, push their product |
| DIV         | No      | Pop b, pop a, push a/b |
| EQ          | No      | Pop two values, push 1 if equal, 0 otherwise |
| JZ addr     | Yes     | Pop value, jump to byte addr if zero |
| PRINT       | No      | Pop and print value |
| HALT        | No      | Stop execution |

## Known Issues

- No label support for jumps—you calculate byte addresses manually
- Stack overflow checking is minimal

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

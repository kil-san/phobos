# Phobos

Phobos is a hobbyist 32-bit operating system kernel that boots via the Multiboot
specification and targets the i686 architecture. It ships with just enough
kernel and C library code to bring up a VGA text console, remap and enable the
programmable interrupt controller (PIC), and accept keyboard input through a
simple canonical TTY line discipline.

## Key features

- **Multiboot-ready i686 kernel**: boots under GRUB with a handcrafted linker
  script and entry code in `kernel/arch/i386/asm`.
- **Protected-mode setup**: installs a global descriptor table (GDT) and a fully
  populated interrupt descriptor table (IDT), with ISR and IRQ stubs for early
  debugging.
- **Interrupt-driven keyboard driver**: decodes set-1 scancodes, supports basic
  modifiers, and feeds characters to the kernel TTY.
- **Minimal C library**: the `libc/` directory provides freestanding versions of
  the standard routines needed by the kernel (e.g. `printf`, `scanf`, and the
  common string primitives).
- **Canonical TTY input**: `tty_getline` blocks until a newline is available,
  enabling simple interactive prompts like the greeting in `kernel/kernel.c`.

## Repository layout

```
├── build.sh              # Orchestrates libc and kernel builds into sysroot
├── iso.sh / qemu.sh      # Produce a bootable ISO and launch it in QEMU
├── kernel/               # Kernel sources (arch-specific code, drivers, core)
│   ├── arch/i386         # GDT, IDT, PIC, ISR/IRQ stubs, VGA TTY implementation
│   ├── drivers           # Interrupt-driven keyboard driver
│   └── kernel            # High-level kernel entry point and logic
├── libc/                 # Freestanding libc implementation and headers
└── output/               # Generated artifacts (sysroot, objects, ISO)
```

## Prerequisites

You will need a cross-compilation toolchain and a few utilities:

- `i686-elf-gcc` and binutils (`i686-elf-as`, `i686-elf-ld`, etc.) built with
  `--with-sysroot` or equivalent options
- `grub-mkrescue`, `xorriso`, and `mtools` for producing bootable ISOs
- `qemu-system-i386` (or another emulator/virtual machine) to run the resulting
  image
- GNU `make` (the build scripts default to `gmake` but honour the `MAKE`
  environment variable)

Set the cross-toolchain binaries on your `PATH`. The default host triple is
`i686-elf` (see `default-host.sh`).

## Build and run

```sh
./build.sh    # Compile libc and the kernel into output/sysroot
./iso.sh      # (Optional) Build a GRUB-bootable ISO at output/phoibos.iso
./qemu.sh     # (Optional) Boot the ISO under QEMU for a quick smoke test
```

`build.sh` installs headers and libraries into `output/sysroot` while
`output/intermediate` holds the object files and the linked kernel image. The
kernel binary lives at `output/sysroot/boot/phoibos.kernel`.

To clean all generated artifacts run:

```sh
./clean.sh
```

## Development notes

- All directories listed in `SYSTEM_HEADER_PROJECTS` (currently `libc` and
  `kernel`) publish their headers into the sysroot, allowing the kernel to build
  against the freestanding libc.
- The TTY implementation lives in `kernel/arch/i386/tty.c` and exposes
  `tty_writestring`, `tty_putchar`, `tty_getchar`, and `tty_getline` helpers used by the
  kernel and keyboard driver.
- The keyboard driver in `kernel/drivers/keyboard.c` registers an ISR and pushes
  decoded characters into the TTY buffer.
- `qemu.sh` derives the emulator architecture from the configured host triple,
  so if you change `HOST` in `config.sh` keep the script in sync.

## Roadmap ideas

- Add more robust terminal editing (backspace, history, scrolling)
- Implement paging, heap allocation, and a scheduler
- Provide additional device drivers (timer, serial port) for richer diagnostics
- Introduce a basic filesystem layer and block device abstraction
- Support reading from storage devices (ATA/ATAPI, AHCI, or similar)
- Explore a simple window manager or graphical console experiment
- Flesh out the freestanding libc with more stdio/stdlib/string routines,
  including dynamic allocation support (`malloc`, `free`, `realloc`, etc.)

## License

This repository does not yet ship with an explicit license. If you intend to
redistribute or build upon this code, consider adding one.

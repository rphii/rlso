# 🧵 So - String Object 

Dynamically Allocatable String in C.

## 🛠️ Installation

- Depends on [rphii/metac](https://github.com/rphii/metac)

```sh
git clone https://github.com/rphii/so && cd so
setup build && meson install -C build
```

Installation features:
- `librlso.so` the `So` library
- [man](man) pages *(WIP)*

## 📊 Tests & Coverage

There are various [tests](tests).

### Recommended dependencies

- lcov *(coverage)*
- gcovr *(coverage)*
- valgrind *(recommended)*

#### Gentoo
```sh
emerge -a gcovr lcov valgrind
```

#### Arch
```sh
pacman -S gcovr lcov valgrind
```

### Run

See the provided [run-tests.sh](run-tests.sh) script.

### Results

See output of where the last command put the .html file.

## ✨ Features

*\*Byte counts are assuming a 64 bit machine/architecture.*

1. Any substring has a footprint of 16 bytes
2. Any program-lifetime / data-segment string has a footprint of 16 bytes
3. Operations on the stack, if length is <=15 bytes *(operations without dynamically allocating!)*
4. Dynamically resizable to a heap string, with a maximum length of 2^56-1

Notes:

- Endian doesn't matter (we need to know it to compile / set up TWO structs, and after that it doesn't matter)
- Doesn't matter if machine/architecture is 64 bits or not, it still works (it should! XD)
- Strings are not 0-terminated. Appropriate functions/macros for printing and other opterations shall be provided
- Automatically converts any (sub-) string into a dynamic one, if manipulated

## 🔌 API

*Things that are not linked are planned but not yet implemented.*

| part | description | .h | .c |
| --- | --- |--- | ---|
| [`so-core.md`](md/so-core.md) | core string | [so.h](src/so.h) | [so.c](src/so.c) |
| [`so-cmp.md`](md/so-cmp.md) | comparison | [so-cmp.h](src/so-cmp.h) | [so-cmp.c](src/so-cmp.c) |
| `so-find.md` | find within | [so-find.h](src/so-find.h) | [so-find.c](src/so-find.c) |
| `so-count.md` | count things | [so-count.h](src/so-count.h) | [so-count.c](src/so-count.c) |
| `so-split.md` | split into parts | [so-split.h](src/so-split.h) | [so-split.c](src/so-split.c) |
| `so-splice.md` | splice repeatedly | [so-splice.h](src/so-splice.h) | [so-splice.c](src/so-splice.c) |
| `so-as.md` | string to type conversions | [so-as.h](src/so-as.h) | [so-as.c](src/so-as.c) |
| `so-uc.md` | utf8 + unicode conversions | [so-uc.h](src/so-uc.h) | [so-uc.c](src/so-uc.c) |
| `so-fx.md` | formatting (bold, it, ul, rgb) | | |
| `so-file.md` | read + write files | [so-file.h](src/so-file.h) | [so-file.c](src/so-file.c) |
| `so-env.md` | environment variables | [so-env.h](src/so-env.h) | [so-env.c](src/so-env.c) |
| [`so-trim.md`](md/so-trim.md) | trimming | [so-trim.h](src/so-trim.h) | [so-trim.c](src/so-trim.c) |
| `so-path.md` | handling as path | [so-path.h](src/so-path.h) | [so-path.c](src/so-path.c) |
| [`so-print.md`](md/so-print.md) | printing | [so-print.h](src/so-print.h) | [so-print.c](src/so-print.c) |
| [`so-input.md`](md/so-input.md) | user input | [so-input.h](src/so-input.h) | [so-input.c](src/so-input.c) |


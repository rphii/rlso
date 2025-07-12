# So - String Object

Small String Optimized and Dynamically Allocatable String in C.

## Installation

```sh
git clone https://github.com/rphii/so && cd so
setup build && meson install -C build
```

## Features

*\*Byte counts are assuming a 64 bit machine/architecture.*

1. Any substring has a footprint of 16 bytes
2. Any program-lifetime / data-segment string has a footprint of 16 bytes
3. Operations on the stack, if length is <=15 bytes *(operations without dynamically allocating!)*
4. Dynamically resizable to a heap string, with a maximum length of 2^56-1

Notes:

- Endian doesn't matter (we need to know it to compile / set up TWO structs, and after that it doesn't matter)
- Doesn't matter if machine/architecture is 64 bits or not, it still works (it should! XD)
- Strings are not 0-terminated. Appropriate functions/macros for printing and other opterations shall be provided

## How does it work?

*\*Explanations assuming a 64 bit machine/architecture.*

### Memoy Layout

Consolidating the `so.h` header, we find the main `So` struct:

```c
typedef union So {
    So_Stack stack;
    So_Ref ref;
} So;
```

#### `So_Ref`

This struct is the real heavy-lifter. Without it we could not do much! It's use cases are:

- Allows detection if in stack-mode
- Allows detection if in heap-mode
- Holds potential heap pointer reference
- Holds program-lifetime / data-segment string
- Acts as a substring / reference to substring *(the starting pointer!)* within another string
- ..and therefore holds a string length

```
    [64-bits|64-bits]
    [str ptr|length ]
```

#### `So_Stack`

This struct is only used for short modified strings, <=15 bytes, that do not yet hold a heap-reference.
So, modifications of short strings up to 15 bytes are dynamic-allocation-free!

- Allows detection if in stack-mode
- Allows detection if in heap-mode
- Holds modifiable strings of up to 15 characters

```
    [120-bits |8-bits]
    [stack buf|length]
```

Note that this struct shares the same memory footprint as the previous one, hence why `So` combines them with a `union`.

### Detecting the modes

This is where I illustrate the *actual use* of the previously described memory footprints.

#### `is_stack`

Detection if we're in stack mode or not is really simple - we set length to any number above 1 (and less than 120/8 = 15).

```
    // So_Stack : used as such
    [120-bits |7-bits|1-bit ]
    [stack buf|length|unused]
```

- If length is >0 we're in stack mode!

#### `is_heap`

Detection happens through setting one bit.

```
    // So_Ref : used as such
    [64-bits|56-bits|7-bits|1-bit  ]
    [str ptr|length |unused|is_heap]
```

- If that single bit is set, we're in heap mode!

#### The rest

If none of the previous two modes apply, we're in either of the following, equally-acting modes:

- Program-lifetime / data-segment string
- Substring of another string

### The heap

The heap is yet another struct with 16 bytes!

```
    [64-bits|64-bits ]
    [str ptr|capacity]
```

We don't need the information of the actual heap length within here, BECAUSE
we're using the `So_Ref` struct as soon as we rely on the heap, where we have
the length (of up to 2^56-1) !

```
    // So_Heap :
    [64-bits|64-bits ]
    [str ptr|capacity]
    <---+--->
        | 
        +(heap str ptr is returned to So_Ref :
        |  
        |  // So_Ref : used as such
        |  [64-bits|56-bits|7-bits|1-bit  ]
        \->[str ptr|length |unused|is_heap]
```


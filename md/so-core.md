# so-core

Create `So` from c-strings

```c
#define     so(s)           (So){ .ref.str = (s), .ref.len = sizeof((s)) - 1 }
#define     so_l(s)         (So){ .ref.str = (s), .ref.len = (s) ? strlen((s)) : 0 }
#define     so_ll(s, l)     (So){ .ref.str = (s), .ref.len = (l) }
```

Get `So` at indices

```c
const char  so_at(So s, size_t i);
const char _so_at(So *s, size_t i);
const char  so_at0(So s);
const char _so_at0(So *s);
#define     so_it(s, i) _so_it(&(s), i)
char *     _so_it(So *s, size_t i);
#define     so_it0(s) _so_it0(&(s))
char *     _so_it0(So *s);
```

Get substrings

```c
So          so_i0(So s, size_t i0);
So          so_iE(So s, size_t iE);
So          so_sub(So s, size_t i0, size_t iE);
```

Manipulation

```c
void        so_push(So *s, char c);
void        so_extend(So *s, So b);
void        so_fmt(So *s, const char *fmt, ...);
void        so_fmt_va(So *s, const char *fmt, va_list va);
```

Other useful things

```c

#define     SO_F(s)     (int)(so_len(s)), so_it0(s)
size_t      so_len(So s);
size_t     _so_len(So *s);
void        so_copy(So *s, So b);
So          so_clone(So b);
void        so_resize(So *s, size_t len);
void        so_clear(So *s);
void        so_free(So *s);
```


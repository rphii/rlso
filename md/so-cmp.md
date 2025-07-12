# so-cmp

Suffix indications

- `s` sortable
- `c` case-insensitive
- `p` pointer

Compare strings for equality

```c
int so_cmp(So a, So b);
int so_cmp_s(So a, So b);
int so_cmp_c(So a, So b);
int so_cmp_cs(So a, So b);
int so_cmp_p(So *a, So *b);
int so_cmp_sp(So *a, So *b);
int so_cmp_cp(So *a, So *b);
int so_cmp_csp(So *a, So *b);
```

Compare if string `a` starts with `b` 

```c
int so_cmp0(So a, So b);
int so_cmp0_s(So a, So b);
int so_cmp0_c(So a, So b);
int so_cmp0_cs(So a, So b);
int so_cmp0_p(So *a, So *b);
int so_cmp0_sp(So *a, So *b);
int so_cmp0_cp(So *a, So *b);
int so_cmp0_csp(So *a, So *b);
```

Compare if string `a` ends with `b` 

```c
int so_cmpE(So a, So b);
int so_cmpE_s(So a, So b);
int so_cmpE_c(So a, So b);
int so_cmpE_cs(So a, So b);
int so_cmpE_p(So *a, So *b);
int so_cmpE_sp(So *a, So *b);
int so_cmpE_cp(So *a, So *b);
int so_cmpE_csp(So *a, So *b);
```


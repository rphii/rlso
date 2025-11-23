#include "so-core.h"
#include "so-print.h"
#include "so-heap.h"

inline void so_print(So so) {
    so_fprint(stdout, so);
}

inline void so_println(So so) {
    so_fprintln(stdout, so);
}

inline void so_printdbg(So so) {
    so_fprintdbg(stdout, so);
}


inline void so_fprint(FILE *fp, So so) {
    fprintf(fp, "%.*s", SO_F(so));
}

inline void so_fprintln(FILE *fp, So so) {
    fprintf(fp, "%.*s\n", SO_F(so));
}

inline void so_fprintdbg(FILE *fp, So so) {
    fprintf(stdout, "%c[%.*s]%zu", so_is_heap(so) ? 'h' : 'r',
            SO_F(so), so_len(so));
    if(so_is_heap(so)) {
        fprintf(stdout, "/%zu", so_heap_base(&so)->cap);
        fprintf(stdout, "<sizeof:%zu+%zu+%zu>", sizeof(So), sizeof(So_Heap), so_heap_base(&so)->cap);
    }
    fprintf(stdout, "(%p)", so.str);
    fprintf(stdout, "{");
    for(size_t i = 0; i < so_len(so); ++i) {
        if(i) fprintf(stdout, " ");
        fprintf(stdout, "%02x", (unsigned char)so_at(so, i));
    }
    fprintf(stdout, "}");
    fprintf(stdout, "\n");
}



#include "so.h"
#include "so-print.h"
#include "so-heap.h"

void so_print(So so) {
    printf("%.*s", SO_F(so));
}

void so_println(So so) {
    printf("%.*s\n", SO_F(so));
}

void so_printdbg(So so) {
    printf("%c[%.*s]%zu", so_is_stack(so) ? 's' : so_is_heap(so) ? 'h' : 'r',
            SO_F(so), so_len(so));
    if(so_is_stack(so)) printf("/%zu", SO_STACK_CAP);
    if(so_is_heap(so)) {
        printf("/%zu", so_heap_base(so)->cap);
        printf("<sizeof:%zu+%zu+%zu>", sizeof(So), sizeof(So_Heap), so_heap_base(so)->cap);
    }
    printf("\n");
}


void so_fprint(FILE *fp, So so) {
    fprintf(fp, "%.*s", SO_F(so));
}

void so_fprintln(FILE *fp, So so) {
    fprintf(fp, "%.*s\n", SO_F(so));
}

void so_fprintdbg(FILE *fp, So so) {
    fprintf(fp, "%c[%.*s]%zu", so_is_stack(so) ? 's' : so_is_heap(so) ? 'h' : 'r',
            SO_F(so), so_len(so));
    if(so_is_stack(so)) fprintf(fp, "/%zu", SO_STACK_CAP);
    if(so_is_heap(so)) {
        fprintf(fp, "/%zu", so_heap_base(so)->cap);
        fprintf(fp, "<sizeof:%zu+%zu+%zu>", sizeof(So), sizeof(So_Heap), so_heap_base(so)->cap);
    }
    fprintf(fp, "\n");
}



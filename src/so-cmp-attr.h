#ifndef SO_CMP_ATTR_H

typedef enum {
    SO_CMP                      = 0x00,
    SO_CMP_CASE_INSENSITIVE     = 0x01,
    SO_CMP_SORTABLE             = 0x02,
    SO_CMP_BEGIN                = 0x04,
    SO_CMP_END                  = 0x08,
} So_Cmp_Attr;

#define SO_CMP_ATTR_H
#endif


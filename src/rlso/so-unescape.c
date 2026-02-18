#include "so-unescape.h"
#include "so-trim.h"
#include "so-uc.h"
#include <ctype.h>
#include <rlc.h>

typedef enum {
    SO_UNESCAPE_NONE,
    SO_UNESCAPE_NEXT,
    SO_UNESCAPE_HEX,
    SO_UNESCAPE_OCTAL,
    SO_UNESCAPE_UNICODE_SMALL,
    SO_UNESCAPE_UNICODE_LARGE,
} So_Unescape_List;

#define SO_UNESCAPE_HEX_CHARS       "abcdefABCDEF"
#define SO_UNESCAPE_OCTAL_DIGITS    "0123456"
#define SO_UNESCAPE_BASIC           "abfnrtv\\'\"?e"
#define SO_UNESCAPE_BASIC_LOOKUP    "\a\b\f\n\r\t\v\\\'\"\?\033"

static bool static_parse_hex(size_t *number, char c) {
    bool result = false;
    if(isdigit(c)) {
        *number = (*number << 4) + (c - '0');
        result = true;
    } else if(strchr(SO_UNESCAPE_HEX_CHARS, c)) {
        *number = (*number << 4) + (tolower(c) - 'a') + 10;
        result = true;
    }
    return result;
}

ssize_t so_fmt_unescape(So *out, So so, char delimiter, size_t *consumed) {

    ASSERT_ARG(out);
    So tmp = SO;
    bool found_delimiter_local = false;

    char *esc_basic = 0;
    int status = 0;

    So_Unescape_List id = SO_UNESCAPE_NONE;
    So_Uc_Point ucp = {0};
    
    size_t n_consumed = 0;
    size_t parsed_number = 0;
    size_t len = so.len;
    int n_escaped = 0;

    for(size_t i = 0; i < len; ++i) {
        ++n_consumed;
        bool have_next = (bool)(i + 1 < len);
        char c = so_at(so, i);
        //printff("CHECK C: %c",c);
        switch(id) {
            case SO_UNESCAPE_NONE: {

                if(delimiter && c == delimiter) {
                    found_delimiter_local = true;
                    goto defer;
                }

                if(c == '\\') id = SO_UNESCAPE_NEXT;
                else so_push(&tmp, c);
            } break;
            case SO_UNESCAPE_NEXT: {
                n_escaped = 0;
                parsed_number = 0;
                memset(&ucp, 0, sizeof(ucp));
                if((esc_basic = strchr(SO_UNESCAPE_BASIC, c))) {
                    /* is escape character */
                    so_push(&tmp, SO_UNESCAPE_BASIC_LOOKUP[esc_basic - SO_UNESCAPE_BASIC]);
                    id = SO_UNESCAPE_NONE;
                } else if(c == 'x') {
                    /* is hex escape sequence \xhh.. */
                    id = SO_UNESCAPE_HEX;
                } else if(c == 'o') {
                    /* is octal escape sequence \nnn */
                    id = SO_UNESCAPE_OCTAL;
                } else if(c == 'u') {
                    /* is unicode escape sequence \uhhhh */
                    id = SO_UNESCAPE_UNICODE_SMALL;
                } else if(c == 'U') {
                    /* is unicode escape sequence \Uhhhhhhhh */
                    id = SO_UNESCAPE_UNICODE_LARGE;
                } else {
                    status = i;
                    goto defer;
                }
            } break;
            case SO_UNESCAPE_HEX: {
                bool required = !n_escaped;
                if(static_parse_hex(&parsed_number, c)) {
                    ++n_escaped;
                    if(!have_next) id = SO_UNESCAPE_NONE;
                } else {
                    if(!required) {
                        id = SO_UNESCAPE_NONE;
                    } else {
                        status = i;
                        goto defer;
                    }
                }
                if(id == SO_UNESCAPE_NONE) {
                    so_fmt(&tmp, "%zu", parsed_number);
                }
            } break;
            case SO_UNESCAPE_OCTAL: {
                if(n_escaped < 3) {
                    if(strchr(SO_UNESCAPE_OCTAL_DIGITS, c)) {
                        parsed_number = (parsed_number << 3) + (c - '0');
                        ++n_escaped;
                    } else {
                        status = i;
                        goto defer;
                    }
                }
                if(n_escaped >= 3) {
                    id = SO_UNESCAPE_NONE;
                    so_fmt(&tmp, "%zu", parsed_number);
                }
            } break;
            case SO_UNESCAPE_UNICODE_SMALL: {
                if(n_escaped < 4) {
                    if(static_parse_hex(&parsed_number, c)) {
                        ++n_escaped;
                    } else {
                        status = i;
                        goto defer;
                    }
                }
                if(n_escaped >= 4) {
                    id = SO_UNESCAPE_NONE;
                    ucp.val = parsed_number;
                    if(so_uc_fmt_point(&tmp, &ucp)) {
                        status = i;
                        goto defer;
                    }
                }
            } break;
            case SO_UNESCAPE_UNICODE_LARGE: {
                if(n_escaped < 8) {
                    if(static_parse_hex(&parsed_number, c)) {
                        ++n_escaped;
                    } else {
                        status = i;
                        goto defer;
                    }
                }
                if(n_escaped >= 8) {
                    id = SO_UNESCAPE_NONE;
                    ucp.val = parsed_number;
                    if(so_uc_fmt_point(&tmp, &ucp)) {
                        status = i;
                        goto defer;
                    }
                }
            } break;
        }
        /* error */
        if(id != SO_UNESCAPE_NONE && !have_next) {
            status = i;
            goto defer;
        }
    }
    
defer:
    if(consumed) *consumed = n_consumed;
    if(delimiter && !found_delimiter_local) status = -1LL;
    if(!status) so_extend(out, tmp);
    so_free(&tmp);
    return status;
}


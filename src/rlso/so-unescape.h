#ifndef SO_UNESCAPE_H

#include "so-core.h"

#include <unistd.h>

/* unescape:
 * \a \b \e \f \n \r \t \v \\ \' \" \?
 * \xhh.. => h => hex
 * \oOOO => O octal
 * \uhhhh => h hex
 * \Uhhhhhhhh => h hex
 * */
ssize_t so_fmt_unescape(So *out, So so, So end_delimiter, So break_delimiter, size_t *consumed);

#define SO_UNESCAPE_H
#endif /* SO_UNESCAPE_H */


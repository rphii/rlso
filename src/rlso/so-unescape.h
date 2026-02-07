#ifndef SO_UNESCAPE_H

#include "so-core.h"


/* unescape:
 * \a \b \e \f \n \r \t \v \\ \' \" \?
 * \xhh.. => h => hex
 * \oOOO => O octal
 * \uhhhh => h hex
 * \Uhhhhhhhh => h hex
 * */
size_t so_fmt_unescape(So *out, So so);

#define SO_UNESCAPE_H
#endif /* SO_UNESCAPE_H */


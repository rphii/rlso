#ifndef SO_PATH_H

typedef struct So So;

const So so_get_ext(So str);
const So so_get_noext(So str);
const So so_get_dir(So str);
const So so_get_nodir(So str);
const So so_get_basename(So str);

#define SO_PATH_H
#endif


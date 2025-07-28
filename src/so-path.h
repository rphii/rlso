#ifndef SO_PATH_H

typedef struct So So;

void so_path_join(So *out, So a, So b);
#define so_get_ext(so) _so_get_ext(&(so))
#define so_get_noext(so) _so_get_noext(&(so))
#define so_get_dir(so) _so_get_dir(&(so))
#define so_get_nodir(so) _so_get_nodir(&(so))
#define so_get_basename(so) _so_get_basename(&(so))
const So _so_get_ext(So *str);
const So _so_get_noext(So *str);
const So _so_get_dir(So *str);
const So _so_get_nodir(So *str);
const So _so_get_basename(So *str);

#define SO_PATH_H
#endif


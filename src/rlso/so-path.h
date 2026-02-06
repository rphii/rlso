#ifndef SO_PATH_H

typedef struct So So;

void so_path_join(So *out, So a, So b);
void so_path_get_realpath(So *out, So a);
void so_path_get_current_working_dir(So *out);

const So so_get_ext(So ref);
const So so_get_noext(So ref);
const So so_get_dir(So ref);
const So so_get_nodir(So ref);
const So so_get_basename(So ref);
const So so_ensure_dir(So str);

#define SO_PATH_H
#endif


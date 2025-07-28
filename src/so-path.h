#ifndef SO_PATH_H

typedef struct So So;
typedef struct So_Ref So_Ref;

void so_path_join(So *out, So a, So b);

#define so_get_ext(so) \
    _so_get_ext(so_ref(so))
#define so_get_noext(so) \
    _so_get_noext(so_ref(so))
#define so_get_dir(so) \
    _so_get_dir(so_ref(so))
#define so_get_nodir(so) \
    _so_get_nodir(so_ref(so))
#define so_get_basename(so) \
    _so_get_basename(so_ref(so))

const So _so_get_ext(So_Ref ref);
const So _so_get_noext(So_Ref ref);
const So _so_get_dir(So_Ref ref);
const So _so_get_nodir(So_Ref ref);
const So _so_get_basename(So_Ref ref);

#define SO_PATH_H
#endif


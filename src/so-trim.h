#ifndef SO_TRIM_H

typedef struct So So;
typedef struct So_Ref So_Ref;

#define so_trim(so) _so_trim(so_ref((so)))
#define so_triml(so) _so_triml(so_ref((so)))
#define so_trimr(so) _so_trimr(so_ref((so)))
So _so_trim(So_Ref so);
So _so_triml(So_Ref so);
So _so_trimr(So_Ref so);

#define SO_TRIM_H
#endif


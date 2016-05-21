#include "scop.h"

int             obj_parse(char *file, t_obj *o)
{
    FILE        *f;
    char        line[1024];

    if (!(f = fopen(file, "r")))
        return (-1);
    while (fgets(line, sizeof(line), f))
    {
        if (line[0] == 'o')
            o->name = line + 2;
        else if (line[0] == 'g')
            push(o->group, line + 2);
        else if (strncmp(line, "mtllib", 6) == 0)
            push(o->mtllib, line + 7);
        else if (strncmp(line, "usemtl", 6) == 0)
            push(o->mtl, line + 7)
        else if (line[0] == 's')
            o->smooth_shading = 1;
        else if (line[0] == 'v')
            vec_parse(line, o);
        else if (line[0]  == 'f')
            face_parse(face, o);
    }
    return (1);
}

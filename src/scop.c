#include "scop.h"

void            loop_hook(t_env *e)
{
    mlx_swap_buffers(e->win);
}

int             main(int ac, char **av)
{
    t_env       e;

    if (e.mlx = mlx_init())
    {
        e.win = mlx_new_opengl_window(e.mlx, 500, 500, "scop");
        if (e.win)
        {
            render(&e);
            mlx_loop_hook(e.mlx, loop_hook, &e);
            mlx_loop();
        }
    }
}

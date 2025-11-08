#ifndef CONNECT4_H
# define CONNECT4_H

# include "libft/include/libft.h"

typedef enum    e_status
{
    ongoing,
    draw,
    win,
    lose,
    error
}               e_status;

typedef struct  s_connect4
{
    int rows;
    int columns;
    char **board;
    e_status status;
}               t_connect4;


#endif

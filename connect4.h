#ifndef CONNECT4_H
# define CONNECT4_H

# include "libft/include/libft.h"
//# include "libft.h"
#define EMPTY_CELL '-'
#define PLAYER_CELL 'X'
#define AI_CELL 'O'

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

void draw_board(t_connect4 *game);
void close_all(t_connect4 *game);
void alloc_board(t_connect4 *game);

#endif

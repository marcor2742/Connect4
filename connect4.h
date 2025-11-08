#ifndef CONNECT4_H
# define CONNECT4_H

# include "libft/include/libft.h"
//# include "libft.h"
#define MAX_ROWS 100
#define MAX_COLUMNS 100

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

typedef struct  s_move
{
	int row;
	int column;
}               t_move;

typedef struct  s_connect4
{
    int rows;
    int columns;
    char **board;
    t_move last_move;
    e_status status;
}               t_connect4;

void draw_board(t_connect4 *game);
void close_all(t_connect4 *game);
void alloc_board(t_connect4 *game);


int make_move(t_connect4 *game, int col, char symbol); /* returns row or -1 */
void undo_move(t_connect4 *game, int row, int col);
int check_win_for(t_connect4 *game, char symbol);
int board_full(t_connect4 *game);
int evaluate(t_connect4 *game);
int ai_choose_column(t_connect4 *game, int depth);

int count_direction(t_connect4 *game, int row, int col, int dr, int dc, char player);
void check_win(t_connect4 *game);
void player_turn(t_connect4 *game);


#endif

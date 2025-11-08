#include "connect4.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        ft_printf("Usage: <rows> <columns>\n");
        return 1;
    }

    t_connect4 game;

    if (ft_atoi(argv[1]) < 6 || ft_atoi(argv[2]) < 7) {
        ft_printf("Error: Minimum size is 6 rows and 7 columns.\n");
        return 1;
    }

    game.rows = ft_atoi(argv[1]); //altezza
    game.columns = ft_atoi(argv[2]); //larghezza

    alloc_board(&game);
    while (game.status == ongoing)
    {
        draw_board(&game);
        //draw game board here

        //prendere input dai giocatori
        //ia

        //calcolare dove inserire il gettone (calcolare la riga ultima libera)
        //calcolare vittoria o pareggio
    }

    

    ft_printf("Creating Connect4 game with %d columns and %d rows\n", game.columns, game.rows);

    return 0;
}

void alloc_board(t_connect4 *game)
{
    int i;

    game->board = (char **)malloc(sizeof(char *) * game->rows);
    if (!game->board)
    {
        game->status = error;
        close_all(game);
    }

    for (i = 0; i < game->rows; i++) {
        game->board[i] = (char *)malloc(sizeof(char) * game->columns);
        if (!game->board[i])
        {
            game->status = error;
            close_all(game);
        }
    }
}

void close_all(t_connect4 *game)
{
    ft_free_char_mat(game->board);
    exit(game->status);
}
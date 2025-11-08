#include "connect4.h"

void draw_board(t_connect4 *game);
void close_all(t_connect4 *game);
void alloc_board(t_connect4 *game);

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

void draw_board(t_connect4 *game)
{
    int i, j;
    // ' ', 'O', 'X'
    
    ft_printf("┌");
    for (j = 0; j < game->columns - 1; j++) {
        ft_printf("──┬");
    }
    ft_printf("──┐\n");
    for (i = 0; i < game->rows; i++) {
        ft_printf("│");
        for (j = 0; j < game->columns; j++) {
            if (game->board[i][j] == 'o')
            ft_printf("🔴│");
            else if (game->board[i][j] == 'x')
            ft_printf("🟡│");
            else if (game->board[i][j] == ' ')
            ft_printf("  │");
            else
            ft_printf("  │", game->board[i][j]);
        }
        ft_printf("\n");
        if (i != game->rows - 1) {
            ft_printf("├");
            for (j = 0; j < game->columns - 1; j++) {
                ft_printf("──┼");
            }
            ft_printf("──┤\n");
        }
    }
    ft_printf("└");
    for (j = 0; j < game->columns - 1; j++) {
        ft_printf("──┴");
    }
    ft_printf("──┘\n");

}

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
    game.player_symbol = 'O';
    game.ai_symbol = 'X';

    alloc_board(&game);
    // while (game.status == ongoing)
    // {
        draw_board(&game);
        //draw game board here

        //prendere input dai giocatori
        //ia

        //calcolare dove inserire il gettone (calcolare la riga ultima libera)
        //calcolare vittoria o pareggio
    // }

    

    ft_printf("Creating Connect4 game with %d columns and %d rows\n", game.columns, game.rows);

    return 0;
}
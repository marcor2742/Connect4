#include "connect4.h"

void close_all(t_connect4 *game)
{
    ft_free_char_mat(game->board);
    exit(game->status);
}

// void	draw_board(t_connect4 *game)
// {
// 	for (int i = 0; i < game->rows; i++) {
// 		ft_printf("%s\n", game->board[i]);
// 	}
// }

void alloc_board(t_connect4 *game)
{
    int i;

    game->board = (char **)malloc(sizeof(char *) * (game->rows + 1));
    if (!game->board)
    {
        game->status = error;
        close_all(game);
    }

	game->board[game->rows] = NULL;

    for (i = 0; i < game->rows; i++) {
        game->board[i] = (char *)malloc(sizeof(char) * (game->columns + 1));
        if (!game->board[i])
        {
            game->status = error;
            close_all(game);
        }
		game->board[i][game->columns] = '\0';
    }
}

void init_board(t_connect4 *game)
{
    alloc_board(game);
	
	for (int i = 0; i < game->rows; i++) {
		for (int j = 0; j < game->columns; j++)
			game->board[i][j] = EMPTY_CELL;
	}

}

void player_turn(t_connect4 *game)
{
	int column;
	char *line = NULL;

	while (1) {
		ft_printf("Inserisci la colonna (1-%d): ", game->columns);
		if ((line = get_next_line(0)) != NULL)
		{
			column = ft_atoi(line);
			free(line);
			if (column >= 1 && column <= game->columns && game->board[0][column - 1] == EMPTY_CELL) {
				break;
			}
		}
        ft_printf("Colonna non valida. Riprova.\n");
	}
    // if (!line)
    // {
    //     ft_printf("\n");
    //     game->status = error;
    //     close_all(game);
    // }
	for (int i = game->rows - 1; i >= 0; i--) {
		if (game->board[i][column - 1] == EMPTY_CELL) {
			game->board[i][column - 1] = PLAYER_CELL;
			break;
		}
	}
}

// void close_all(t_connect4 *game)
// {
//     ft_free_char_mat(game->board);
//     exit(game->status);
// }

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
            if (game->board[i][j] == PLAYER_CELL)
            ft_printf("🔴│");
            else if (game->board[i][j] == AI_CELL)
            ft_printf("🟡│");
            else if (game->board[i][j] == EMPTY_CELL)
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

    init_board(&game);
    game.status = ongoing;
    while (game.status == ongoing)
    {
		draw_board(&game);

		//prendere input dai giocatori
		player_turn(&game);
        //ia

        //calcolare vittoria o pareggio

    }
    return 0;
}

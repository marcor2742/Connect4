# include "connect4.h"

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
			if (column >= 1 && column <= game->columns && game->board[0][column - 1] == EMPTY_CELL)
				break;
			else
				ft_printf("Colonna non valida. Riprova.\n");
		}
		else
		{
			ft_printf("\n");
			game->status = error;
			close_all(game);
		}
	}
	for (int i = game->rows - 1; i >= 0; i--) {
		if (game->board[i][column - 1] == EMPTY_CELL) {
			game->board[i][column - 1] = PLAYER_CELL;
			break;
		}
	}
}
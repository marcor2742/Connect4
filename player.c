# include "connect4.h"
# include <stdbool.h>

int count_direction(t_connect4 *game, int row, int col, int dr, int dc, char player)
{
    int count = 0;
    int r = row + dr;
    int c = col + dc;
    
    while (r >= 0 && r < game->rows && c >= 0 && c < game->columns && game->board[r][c] == player) {
        count++;
        r += dr;
        c += dc;
    }
    return count;
}

void check_win(t_connect4 *game)
{
    int row = game->last_move.row;
    int col = game->last_move.column;
    char player = game->board[row][col];
 
    int directions[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };
    
    for (int d = 0; d < 4; d++)
    {
        int count = 1;
        int dr = directions[d][0];
        int dc = directions[d][1];
        
        count += count_direction(game, row, col, dr, dc, player);
        count += count_direction(game, row, col, -dr, -dc, player);
        
        if (count >= 4)
        {
            if (player == PLAYER_CELL)
                game->status = win;
            else if (player == AI_CELL)
                game->status = lose;
            return;
        }
    }

    bool full = true;
    for (int j = 0; j < game->columns; j++) {
        if (game->board[0][j] == EMPTY_CELL) {
            full = false;
            break;
        }
    }
    if (full)
        game->status = draw;
}



static void make_move(t_connect4 *game, int columnIndex)
{
	for (int i = game->rows - 1; i >= 0; i--) {
		if (game->board[i][columnIndex - 1] == EMPTY_CELL) {
			game->board[i][columnIndex - 1] = PLAYER_CELL;
			game->last_move.row = i;
			game->last_move.column = columnIndex - 1;
			break;
		}
	}
}

void player_turn(t_connect4 *game)
{
	int columnIndex;
	char *line = NULL;

	while (1) {
		ft_printf("Inserisci la colonna (1-%d): ", game->columns);
		if ((line = get_next_line(0)) != NULL)
		{
			columnIndex = ft_atoi(line);
			free(line);
			if (columnIndex >= 1 && columnIndex <= game->columns && game->board[0][columnIndex - 1] == EMPTY_CELL)
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
	make_move(game, columnIndex);
}
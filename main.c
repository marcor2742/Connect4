#include "connect4.h"

void close_all(t_connect4 *game)
{
    ft_free_char_mat(game->board);
    exit(game->status == error ? 1 : 0);
}

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

// void player_turn(t_connect4 *game)
// {
// 	int column;
// 	char *line = NULL;

// 	while (1) {
// 		ft_printf("Inserisci la colonna (1-%d): ", game->columns);
// 		if ((line = get_next_line(0)) != NULL)
// 		{
// 			column = ft_atoi(line);
// 			free(line);
// 			if (column >= 1 && column <= game->columns && game->board[0][column - 1] == EMPTY_CELL)
// 				break;
// 			else
// 				ft_printf("Colonna non valida. Riprova.\n");
// 		}
// 		else
// 		{
// 			ft_printf("\n");
// 			game->status = error;
// 			close_all(game);
// 		}
// 	}
//     // if (!line)
//     // {
//     //     ft_printf("\n");
//     //     game->status = error;
//     //     close_all(game);
//     // }
// 	for (int i = game->rows - 1; i >= 0; i--) {
// 		if (game->board[i][column - 1] == EMPTY_CELL) {
// 			game->board[i][column - 1] = PLAYER_CELL;
// 			break;
// 		}
// 	}
// }

void player_turn_graphics(t_connect4 *game, SDL_Renderer *renderer)
{
	while (1)
    {
        SDL_Event event;
		// ft_printf("Inserisci la colonna (1-%d): ", game->columns);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                game->status = error;
                close_all(game);
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                //SDL_Log("key pressed: %d", event.key.key);
                if (event.key.key == 1073741903) // right
                {
                    if (game->hovered < game->columns)
                    {
                        game->hovered++;
                    }
                }
                if (event.key.key == 1073741904) // left
                {
                    if (game->hovered > 1)
                    {
                        game->hovered--;
                        //draw_in_window(game, renderer);
                    }
                }
                if (event.key.key == 32)
                {
	                for (int i = game->rows - 1; i >= 0; i--)
                    {
	                	if (game->board[i][game->hovered - 1] == EMPTY_CELL)
                        {
                            make_move(game, game->hovered - 1, PLAYER_CELL);
	                		//game->board[i][game->hovered - 1] = PLAYER_CELL;
	                		break;
	                	}
	                }
                    return ;
                }
                draw_in_window(game, renderer);
            }
        }
	}
}

void draw_board(t_connect4 *game)
{
    int i, j;
    // ' ', 'O', 'X'
	// inserire numeri colonne
    
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
            ft_printf("  │");
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

// void draw

void draw_in_window(t_connect4 *game, SDL_Renderer *renderer)
{
    int width;
    int height;

    SDL_GetCurrentRenderOutputSize(renderer, &width, &height);

    int cell_w = width / game->columns;
    int cell_h = height / game->rows;
    const int pad = 4;

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    draw_board(game);

    for (int i = 0; i < game->rows; i++)
    {
        for (int j = 0; j < game->columns; j++)
        {
            SDL_FRect cell;
            cell.x = j * cell_w + pad;
            cell.y = i * cell_h + pad;
            cell.w = cell_w - pad * 2;
            cell.h = cell_h - pad * 2;

            /* fill empty cell */
            if (j + 1 == game->hovered)
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
            else
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            if (game->board[i][j] == PLAYER_CELL)
                SDL_SetRenderDrawColor(renderer, 200, 100, 0, 255);
            else if (game->board[i][j] == AI_CELL)
                SDL_SetRenderDrawColor(renderer, 0, 100, 200, 255);
            SDL_RenderFillRect(renderer, &cell);

            /* cell border */
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_FRect border = { j * cell_w, i * cell_h, cell_w, cell_h };
            SDL_RenderRect(renderer, &border);
        }
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool has_graphics = false;

    if ((argc < 3) || (argc > 4)) {
        ft_printf("Usage: <rows> <columns>\n");
        return 1;
    }

    if (argc == 4)
    {
        has_graphics = true;
    }

    t_connect4 game;

    if (ft_atoi(argv[1]) < 6 || ft_atoi(argv[2]) < 7) {
        ft_printf("Error: Size must be integers (rows) >= 6 and (columns) >= 7.\n");
        return 1;
    }

    game.rows = ft_atoi(argv[1]); //altezza
    game.columns = ft_atoi(argv[2]); //larghezza
	// if (game.rows > MAX_ROWS || game.columns > MAX_COLUMNS) {
	// 	ft_printf("Error: Maximum size is %d rows and %d columns.\n", MAX_ROWS, MAX_COLUMNS);
	// 	return 1;
	// }

    init_board(&game);
    game.status = ongoing;
    game.hovered = 1;

    ///////////////////////////////////////////////////////////////////////
    if (has_graphics)
    {
        SDL_Init(SDL_INIT_VIDEO);   // Initialize SDL3
        
        // Create an application window with the following settings:
        window = SDL_CreateWindow(
            "Connect4",                  // window title
            game.columns * 50,           // width, in pixels
            game.rows * 50,              // height, in pixels
            SDL_WINDOW_OPENGL            // flags - see below
        );

        renderer = SDL_CreateRenderer(window, NULL);

        if (renderer == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
        
        // Check that the window was successfully created
        if (window == NULL) {
            // In the case that the window could not be made...
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
            return 1;
        }
    }
    //////////////////////////////////////////////////////////////////////

    while (game.status == ongoing)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                game.status = error;
                close_all(&game);
            }
        }

        if (!has_graphics)
		    draw_board(&game);
        else
            draw_in_window(&game, renderer);

		//prendere input dai giocatori
        if (!has_graphics)
		    player_turn(&game);
        else
            player_turn_graphics(&game, renderer);

    	//draw_board(&game);
        check_result(&game);
        if (game.status != ongoing)
            break;

        ai_choose_column(&game, 2); // depth = 2 example

		check_result(&game);
    }

	draw_board(&game);
	if (game.status == win)
		ft_printf("You win!\n");
	else if (game.status == lose)
		ft_printf("You lose!\n");
	else if (game.status == draw)
		ft_printf("It's a draw!\n");
	
	close_all(&game);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if (has_graphics)
    {
        SDL_Quit();
    }
    return 0;
}

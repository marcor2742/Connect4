// ...existing code...
#include "connect4.h"
// #include <limits.h>
// #include <stdlib.h>

#define WIN_SCORE 1000000
#define THREE_SCORE 1000
#define TWO_SCORE 50
#define OP_THREE_PENALTY 900
#define CENTER_BONUS 6

static int in_bounds(t_connect4 *game, int r, int c)
{
    return r >= 0 && r < game->rows && c >= 0 && c < game->columns;
}

int make_move(t_connect4 *game, int col, char symbol)
{
    if (col < 0 || col >= game->columns) return -1;
    if (game->board[0][col] != EMPTY_CELL) return -1;
    for (int row = game->rows - 1; row >= 0; --row) {
        if (game->board[row][col] == EMPTY_CELL) {
            game->board[row][col] = symbol;
            return row;
        }
    }
    return -1;
}

void undo_move(t_connect4 *game, int row, int col)
{
    if (in_bounds(game, row, col))
        game->board[row][col] = EMPTY_CELL;
}

int board_full(t_connect4 *game)
{
    for (int c = 0; c < game->columns; ++c)
        if (game->board[0][c] == EMPTY_CELL) return 0;
    return 1;
}

static int check_direction(t_connect4 *game, int r, int c, int dr, int dc, char s)
{
    for (int i = 0; i < 4; ++i) {
        int rr = r + i*dr, cc = c + i*dc;
        if (!in_bounds(game, rr, cc) || game->board[rr][cc] != s) return 0;
    }
    return 1;
}

int check_win_for(t_connect4 *game, char s)
{
    for (int r = 0; r < game->rows; ++r) {
        for (int c = 0; c < game->columns; ++c) {
            if (game->board[r][c] != s) continue;
            if (check_direction(game, r, c, 0, 1, s)) return 1;
            if (check_direction(game, r, c, 1, 0, s)) return 1;
            if (check_direction(game, r, c, 1, 1, s)) return 1;
            if (check_direction(game, r, c, 1, -1, s)) return 1;
        }
    }
    return 0;
}

/* scoring di una finestra di 4 */
static int score_window(char a, char b, char c, char d, char ai, char pl)
{
    int ai_count = 0, pl_count = 0, empty_count = 0;
    char arr[4] = {a,b,c,d};
    for (int i = 0; i < 4; ++i) {
        if (arr[i] == ai) ai_count++;
        else if (arr[i] == pl) pl_count++;
        else if (arr[i] == EMPTY_CELL) empty_count++;
    }
    if (ai_count == 4) return WIN_SCORE;
    if (ai_count == 3 && empty_count == 1) return THREE_SCORE;
    if (ai_count == 2 && empty_count == 2) return TWO_SCORE;
    if (pl_count == 3 && empty_count == 1) return -OP_THREE_PENALTY;
    if (pl_count == 2 && empty_count == 2) return -TWO_SCORE;
    return 0;
}

int evaluate(t_connect4 *game)
{
    char ai = AI_CELL;
    char pl = PLAYER_CELL;
    int score = 0;
    int center = game->columns / 2;

    /* piccolo bonus centro */
    for (int r = 0; r < game->rows; ++r)
        if (game->board[r][center] == ai) score += CENTER_BONUS;

    /* orizzontali */
    for (int r = 0; r < game->rows; ++r)
        for (int c = 0; c <= game->columns - 4; ++c)
            score += score_window(game->board[r][c], game->board[r][c+1],
                                  game->board[r][c+2], game->board[r][c+3], ai, pl);

    /* verticali */
    for (int c = 0; c < game->columns; ++c)
        for (int r = 0; r <= game->rows - 4; ++r)
            score += score_window(game->board[r][c], game->board[r+1][c],
                                  game->board[r+2][c], game->board[r+3][c], ai, pl);

    /* diagonali dr */
    for (int r = 0; r <= game->rows - 4; ++r)
        for (int c = 0; c <= game->columns - 4; ++c)
            score += score_window(game->board[r][c], game->board[r+1][c+1],
                                  game->board[r+2][c+2], game->board[r+3][c+3], ai, pl);

    /* diagonali dl */
    for (int r = 0; r <= game->rows - 4; ++r)
        for (int c = 3; c < game->columns; ++c)
            score += score_window(game->board[r][c], game->board[r+1][c-1],
                                  game->board[r+2][c-2], game->board[r+3][c-3], ai, pl);

    return score;
}

static int minimax_ab(t_connect4 *game, int depth, int alpha, int beta, int maximizing)
{
    if (check_win_for(game, AI_CELL)) return  WIN_SCORE;
    if (check_win_for(game, PLAYER_CELL)) return -WIN_SCORE;
    if (depth == 0 || board_full(game)) return evaluate(game);

    if (maximizing) {
        int value = INT_MIN;
        for (int c = 0; c < game->columns; ++c) {
            if (game->board[0][c] != EMPTY_CELL) continue;
            int r = make_move(game, c, AI_CELL);
            if (r == -1) continue;
            int score = minimax_ab(game, depth - 1, alpha, beta, 0);
            undo_move(game, r, c);
            if (score > value) value = score;
            if (value > alpha) alpha = value;
            if (beta <= alpha) break;
        }
        return value;
    } else {
        int value = INT_MAX;
        for (int c = 0; c < game->columns; ++c) {
            if (game->board[0][c] != EMPTY_CELL) continue;
            int r = make_move(game, c, PLAYER_CELL);
            if (r == -1) continue;
            int score = minimax_ab(game, depth - 1, alpha, beta, 1);
            undo_move(game, r, c);
            if (score < value) value = score;
            if (value < beta) beta = value;
            if (beta <= alpha) break;
        }
        return value;
    }
}

int ai_choose_column(t_connect4 *game, int depth)
{
    int best_col = -1;
    int best_score = INT_MIN;
    for (int col = 0; col < game->columns; ++col) {
        if (game->board[0][col] != EMPTY_CELL) continue;
        int row = make_move(game, col, AI_CELL);
        if (row == -1) continue;
        int score = minimax_ab(game, depth - 1, INT_MIN, INT_MAX, 0);
        undo_move(game, row, col);
        if (score > best_score) {
            best_score = score;
            best_col = col;
        }
    }
    return best_col;
}
// ...existing code...
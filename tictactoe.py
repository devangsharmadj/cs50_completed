"""
Tic Tac Toe Player
"""

import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    # Declaring counter variables
    counter_x = 0
    counter_o = 0
    terminal_flag = True
    for row in board:
        for cell in row:
            if cell == EMPTY:
                # Checking for terminal position
                terminal_flag = False
            # Counting the number of X and O values provided
            elif cell == X:
                counter_x += 1
            elif cell == O:
                counter_o += 1
    # Returning based on the number of X and O value
    if terminal_flag:
        return False

    elif counter_o == counter_x:
        return X

    elif counter_o < counter_x:
        return O


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    # Declaring list to be returned
    possible_actions = []
    for i, row in enumerate(board):
        for j, cell in enumerate(row):
            if cell == EMPTY:
                possible_actions.append((i, j))

    # Returning based on the contents of possible_actions
    if not possible_actions:
        return True

    else:
        return possible_actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    # Verifying that the action is correct
    i, j = action
    if 0 > i or i > 2:
        raise IndexError('Actions are not valid: Check the row')
    if 0 > j or j > 2:
        raise IndexError('Actions are not valid: Check the column')
    # Deep - copying the board
    dupl_board = copy.deepcopy(board)
    filler = player(board)
    if isinstance(filler, bool):
        return board
    # Verifying that the cell is empty
    if dupl_board[i][j] != EMPTY:
        # Checking if cell is empty
        raise IndexError('Action is not valid')
    else:
        # Filling in the cell
        dupl_board[i][j] = filler

    return dupl_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    # Checking for X or O winner
    for player in [X, O]:
        # Checking for diagonal win
        for x in [0, 2]:
            win = True
            if x == 0:
                for y in range(0, 3):
                    if board[x + y][y] != player:
                        win = False
                        continue
            elif x == 2:
                for y in range(0, 3):
                    if board[x - y][y] != player:
                        win = False
                        continue

            if win:
                return player
            # Checking for horizontal win
            for x in range(len(board)):
                win = True

                for y in range(len(board)):
                    if board[y][x] != player:
                        win = False
                        continue

                if win:
                    return player
            # Checking for vertical win
            for x in range(3):
                win = True

                for y in range(3):
                    if board[x][y] != player:
                        win = False
                        continue

                if win:
                    return player

    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    # Checking for winner
    if winner(board) is not None:
        return True

    # Checking for empty cells
    for row in board:
        for cell in row:
            if cell == EMPTY:
                return False

    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    # Checking for who the winner is
    temp = winner(board)
    # Returning score based on who won
    if temp == O:
        return -1

    elif temp == X:
        return 1

    else:
        return 0


def max_value(board):
    # Checking for terminal state
    if terminal(board):
        return utility(board)
    # Setting default value
    v = -100
    for act in actions(board):
        # Testing all different possibilities
        v = max(v, min_value(result(board, act)))
    return v


def min_value(board):
    # Checking for terminal state
    if terminal(board):
        return utility(board)
    # Setting up initial value
    v = 100
    for act in actions(board):
        # Testing all different possibilities
        v = min(v, max_value(result(board, act)))
    return v


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    player1 = player(board)
    if player1 == X:
        high_dict = {}
        # Checking for which action has the highest utility score
        for act in actions(board):
            high_dict.update({act: min_value(result(board, act))})
        # Returning action with highest utility score
        return max(high_dict, key=high_dict.get)

    else:
        low_dict = {}
        # Checking for which action has the lowest utility score
        for act in actions(board):
            low_dict.update({act: max_value(result(board, act))})
        # Returning action with lowest utility score
        return min(low_dict, key=low_dict.get)

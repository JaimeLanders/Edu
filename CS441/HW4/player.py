# TODO:
#   - Setup project including all modules needed to run the game: X
#       - Official server daemon (gthd) X
#       - Grossthello player X
#       - Python client X
#       - My submission X
#   - Make manual player to test connections and understand client
#       - Import gthclient.py X
#       - Connect to server X
#       - Display current state X
#       - Make moves using user input X
#       - Get opponents moves X
#       - Play until complete X
#   - Fix illegal move ending game X
#   - Fix printing backwards X
#   - Handle arguments X
#   - Implement depth limited minimax player
#       - Implement value (heuristic) function X
#       - Implement calcmove function (to call minimax)
#   - Add option to gracefully exit the game
#   - Fix handling end of game.
#   - Implement better evaluator (extra)

import gthclient
# import numpy as np
import sys
#import pydevd_pycharm
#if sys.argv[5] == "debug":
#    pydevd_pycharm.settrace('10.0.0.12', port=12345, stdoutToServer=True, stderrToServer=True)

# Source: gthrandom.py from gothello-libclient-python3
def main():
    print("Welcome to Gothello Player 1.0")

    for i in range(1, len(sys.argv)):
        print(sys.argv[i]) # DEBUG

#    me = "black"
    me = sys.argv[1]
    print("me = ", me)
    ip = sys.argv[2]
    print("ip = ", ip)
    servernum = sys.argv[3]
    print("servernum = ", servernum)
    depth = sys.argv[4]
    print("depth = ", depth)
#    if len(sys.argv) > 5 and sys.argv[5] == "debug":
#        pydevd_pycharm.settrace('10.0.0.12', ort=12345, stdoutToServer=True, stderrToServer=True)
#    client = gthclient.GthClient(me, "localhost", 0)
    client = gthclient.GthClient(me, ip, int(servernum))
    opp = gthclient.opponent(me)
#    client.make_move("pass")
#    client.make_move("a1")

#    board = []
#    board = np.zeros((5, 5))
#    print(board)

#    grid = []
#    grid = np.zeros((2, 25))
#    print(grid)

    # Source: gthrandom.py from gothello-libclient-python3
#    grid = {"white": set(), "black": set()}

    side = "black"

    while True:
        show_position()
#        myscore = score(me)
#        print("myscore = ", myscore) # DEBUG
#        oppscore = score(opp)
#        print("oppscore = ", myscore) # DEBUG
        curscore = score(me, opp)
        print("curscore = ", curscore) # DEBUG
#        print(value(grid))

        if side == me :
            userin = input("Your move: ")
            move = userin
            print("My move: ", move)
            minimax(grid, depth, side)
#            move = "pass"
            try:
                client.make_move(move)
                grid[me].add(move)
                board.remove(move)
            except gthclient.MoveError as e:
                print(e)
                if e.cause == e.ILLEGAL:
                    print("You made illegal move, passing")
                    client.make_move("pass")
        else:
            cont, move = cont, move = client.get_move()
            print("Opponents move: ", move)
            if cont and move == "pass":
                print("me: pass to end game")
                client.make_move("pass")
                break
            else:
                if not cont:
                    break
                board.remove(move)
                grid[opp].add(move)

        side = gthclient.opponent(side)

# function minimax(node, depth, maximizingPlayer) is
def minimax(node, depth, maxPlayer):
    print("\nminimax()") # DEBUG
    print("depth = ", depth) # DEBUG
    print("maxPlayer = ", maxPlayer) # DEBUG
#    print() # DEBUG
    # if depth = 0 or node is a terminal node then
    if depth == 0:
        # return the heuristic value of node
        return value(node)
    # if maximizingPlayer then
        # value := −∞
        # for each child of node do
            # value := max(value, minimax(child, depth − 1, FALSE))
        # return value
    # else (* minimizing player *)
        # value := +∞
        # for each child of node do
            # value := min(value, minimax(child, depth − 1, TRUE))
        # return value

#def score(player):
def score(me, opp):
#    print("\nscore()")
#    print(player)
#    return len(grid[player])
    return len(grid[me]), len(grid[opp])

def value(state):
    print("\nvalue()")
    print(state)
#    return 0
    return len(grid["white"]), len(grid["black"])

# Source: gthrandom.py from gothello-libclient-python3
def letter_range(letter):
    for i in range(5):
        yield chr(ord(letter) + i)

# Source: gthrandom.py from gothello-libclient-python3
board = {letter + digit
         for letter in letter_range('a')
         for digit in letter_range('1')}

# Source: gthrandom.py from gothello-libclient-python3
grid = {"white": set(), "black": set()}

def show_position():
    for digit in letter_range('1'):
#        print("digit = ", digit) # DEBUG
        for letter in letter_range('a'):
#            print("letter = ", letter) # DEBUG
#            pos = letter + digit
            pos = letter + str((6 - int(digit))) # Hacky fix
#            print("pos = ", pos) # DEBUG
            if pos in grid["white"]:
                piece = "w"
            elif pos in grid["black"]:
                piece = "b"
            else:
                piece = "."
            print(piece, end="")
        print()

main()
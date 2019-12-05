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
import copy

import gthclient
import random
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
    print("me = ", me) # DEBUG
    ip = sys.argv[2]
    print("ip = ", ip) # DEBUG
    servernum = int(sys.argv[3])
    print("servernum = ", servernum) # DEBUG
    depth = int(sys.argv[4])
    print("depth = ", depth) # DEBUG
#    if len(sys.argv) > 5 and sys.argv[5] == "debug":
#        pydevd_pycharm.settrace('10.0.0.12', ort=12345, stdoutToServer=True, stderrToServer=True)
#    client = gthclient.GthClient(me, "localhost", 0)
    client = gthclient.GthClient(me, ip, servernum)
    opp = gthclient.opponent(me)
#    client.make_move("pass")
#    client.make_move("a1")

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
#        print(value(grid)) # DEBUG

        if side == me :
#            userin = input("Your move: ")
#            move = userin
#            minimax(grid, depth, True)
            val, move = minimax(grid, depth, True)
#            move = "pass"
            print("My move: ", move)
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
                minimax(grid, depth, False)
                client.make_move("pass")
                break
            else:
                if not cont:
                    break
                board.remove(move)
                grid[opp].add(move)

        side = gthclient.opponent(side)

# Algorithm source: https://en.wikipedia.org/wiki/Minimax
# function minimax(node, depth, maximizingPlayer) is
def minimax(node, depth, maxPlayer):
#    print("\nminimax()") # DEBUG
#    print("depth = ", depth) # DEBUG
#    print("maxPlayer = ", maxPlayer) # DEBUG
#    print() # DEBUG
    # if depth = 0 or node is a terminal node then
    pos = 0
    move = random.choice(list(board))
    if depth == 0:
        # return the heuristic value of node
#        return value(node)
        val = value(node)
#        print("val = ", val) # DEBUG
#        return val
        return val[0] # NOT ALWAYS 0!!!
    # if maximizingPlayer then
    if maxPlayer:
        # value := −∞
        val = float("-inf")
#        tgrid = grid
#        tgrid = copy.deepcopy(grid)
#        val = 0
        # for each child of node do
        for digit in letter_range('1'):
            #        print("digit = ", digit) # DEBUG
            for letter in letter_range('a'):
#                print("letter = ", letter) # DEBUG
#                pos = letter + digit
                pos = letter + str((6 - int(digit)))  # Hacky fix
                tgrid = copy.deepcopy(grid)
                tval = 0
                if pos not in tgrid["black"] and pos not in tgrid["white"]:
#                    print("not in")
                    child = tgrid
                    child["black"].add(pos) # Not always black!!!
                    # value := max(value, minimax(child, depth − 1, FALSE))
#                    val = max(val, minimax(child, depth - 1, False))
#                    tval, gmove = minimax(child, depth - 1, False)
                    tval = minimax(child, depth - 1, False)
                    if val < tval:
                        val = tval
                        move = pos
#                    print("val = ", val)
#                    val[0] = max(val[0], minimax(child, depth - 1, True))  # Not always 0!!!
        # return value
        return val, move
    # else (* minimizing player *)
    else:
        # value := +∞
        val = float("inf")
        # for each child of node do
#        tgrid = grid
#        tgrid = copy.deepcopy(grid)
#        val = 0
        for digit in letter_range('1'):
#        print("digit = ", digit) # DEBUG
            for letter in letter_range('a'):
#                print("letter = ", letter) # DEBUG
#                pos = letter + digit
                pos = letter + str((6 - int(digit)))  # Hacky fix
                tgrid = copy.deepcopy(grid)
                tval = 0
                if pos not in tgrid["black"] and pos not in tgrid["white"]:
#                    print("not in")
                    child = tgrid
#                    child.add(pos)
                    child["white"].add(pos) # Not always white!!!
                    # value := min(value, minimax(child, depth − 1, TRUE))
#                    val = max(val, minimax(child, depth - 1, True))
#                    val = max(val[0], minimax(child, depth - 1, True))  # Not always 0!!!
#                    tval = minimax(child, depth - 1, False)
                    tval, gmove = minimax(child, depth - 1, False)
                    if val < tval:
                        val = tval
                        move = pos
        # return value
        return val, move

#def score(player):
def score(me, opp):
#    print("\nscore()")
#    print(player)
#    return len(grid[player])
    return len(grid[me]), len(grid[opp])

def value(state):
#    print("\nvalue()")
#    print(state)
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
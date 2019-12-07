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
#       - Fix not working on depth > 1
#   - Fix making illegal moves that would lower score X
#       - Implement captures X
#   - Fix handling end of game.
#   - Add option to gracefully exit the game
#   - Implement better evaluator (extra)
import copy

import gthclient
import random
import sys
#import pydevd_pycharm
#if sys.argv[5] == "debug":
#    pydevd_pycharm.settrace('10.0.0.12', port=12345, stdoutToServer=True, stderrToServer=True)

# Source: gthrandom.py from gothello-libclient-python3
def letter_range(letter):
    for i in range(5):
        yield chr(ord(letter) + i)

def show_position(grid):
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

# Source: gthrandom.py from gothello-libclient-python3
def main():
    print("Welcome to Gothello Player 1.0")

    for i in range(1, len(sys.argv)):
        print(sys.argv[i]) # DEBUG

    # Source: gthrandom.py from gothello-libclient-python3
    board = {letter + digit
             for letter in letter_range('a')
             for digit in letter_range('1')}

    # Source: gthrandom.py from gothello-libclient-python3
    grid = {"white": set(), "black": set()} # Global?

    imove = set() # Tracks illegal moves to avoid repete calculations

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
    client = gthclient.GthClient(me, ip, servernum)
    opp = gthclient.opponent(me)

    side = "black" # Black goes first
    while True:
        print("-----")
        show_position(grid)
        curscore = score(grid, me, opp)
        print("curscore = ", curscore) # DEBUG
        cval = value(grid)[me] # Bug: NOT ALWAYS 0!!!
        print("cval = ", cval)
        if side == me :
#            userin = input("Your move: ")
#            move = userin
            val, move = minimax(grid, grid, depth, True, cval, me, imove)
            print("My move: ", move)
            try:
                client.make_move(move)
                if move != "pass":
                    grid[me].add(move)
                    board.remove(move)
                    nstate = captures(grid)
                    print("nstate = ", nstate)
                    grid = nstate

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
                minimax(grid, depth, False, cval, me, imove)
                client.make_move("pass")
                break
            else:
                if not cont:
                    break
                board.remove(move)
                grid[opp].add(move)
                nstate = captures(grid)
                print("nstate = ", nstate)
                grid = nstate

        side = gthclient.opponent(side)

# Algorithm source: https://en.wikipedia.org/wiki/Minimax
# function minimax(node, depth, maximizingPlayer) is
def minimax(grid, node, depth, maxPlayer, cval, me, imove):
#    print("\nminimax()") # DEBUG
#    print("depth = ", depth) # DEBUG
#    print("maxPlayer = ", maxPlayer) # DEBUG
#    print() # DEBUG
    # if depth = 0 or node is a terminal node then
    pos = 0
    move = "pass"
    if depth == 0:
        # return the heuristic value of node
        val = value(node)
#        print("val = ", val) # DEBUG
        return val[me]  # Bug: Not Always me?
    # if maximizingPlayer then
    if maxPlayer:
        # value := −∞
        val = -26
    # else (* minimizing player *)
    else:
        # value := +∞
        val = 26
    # for each child of node do
    for digit in letter_range('1'):
#        print("digit = ", digit) # DEBUG
        for letter in letter_range('a'):
#            print("letter = ", letter) # DEBUG
            pos = letter + digit
            tgrid = copy.deepcopy(grid)
            tval = 0
            if pos not in tgrid["black"] and pos not in tgrid["white"] and pos not in imove:
                child = copy.deepcopy(tgrid)
                child[me].add(pos) # Bug: Not always me?
                child = captures(child)
                # value := max(value, minimax(child, depth − 1, FALSE)) if maxPlayer
                tval = minimax(grid, child, depth - 1, not maxPlayer, cval, me, imove)
                if val < tval:
                    if tval > cval:
                        val = tval
                        print("val = ", val) # DEBUG
                        move = pos
                        print("move = ", move) # DEBUG
                    elif tval <= cval or len(grid) >= 24:
                        print("imove pos = ", pos)
                        imove.add(pos)
    # return value
    return val, move

#def score(me, opp): # Needed since I have  value()?
def score(grid, me, opp): # Needed since I have  value()?
#    print("\nscore()")
#    print(player)
    return len(grid[me]), len(grid[opp])

def value(state):
#    print("\nvalue()")
#    print(state)
    return {"white": len(state["white"]), "black": len(state["black"])}

# When a stone is placed in such a way that stones of the player on move plus the outer wall completely enclose, with
# no gaps, a group of the opponent's stones horizontally and vertically, the opponent's group is captured.
def captures(state):
#    print("captures()")
#    print("state = ", state)
    nstate = copy.deepcopy(state)
    visited = set()
    for letter in letter_range('a'):
#        print("letter = ", letter) # DEBUG
        for digit in letter_range('1'):
#            print("digit = ", digit) # DEBUG
            group = list()
            pos = letter + digit
#            print("pos = ", pos)
            if pos in state["white"]:
                gcolor = "white"
                ccolor = "black"
            elif pos in state["black"]:
                gcolor = "black"
                ccolor = "white"
            if pos in state["white"] or pos in state["black"]:
#                print("gcolor = ", gcolor)
    #            print("ccolor = ", ccolor)
                if pos not in visited:
                    if pos not in group:
                        group.append(pos)
                        group.sort()

                    visited.add(pos)
                    group = getneighbors(state, pos, gcolor) # Getting non-neighbors
                    group.sort()
                    print("group = ", group)
                    capneeded = capneed(group, state, gcolor)
                    print("capneeded = ", capneeded)

                    for i in group:
                        visited.add(i)

                    captured = True

                    for i in capneeded:
                        if i not in state[ccolor]:
                            captured = False
                            break

                    if captured:
                        print("---CAPTURE!!!---")
                        print("gcolor = ", gcolor)
                        print("ccolor = ", ccolor)
                        for i in group:
                            nstate[ccolor].add(i)
                            if i in nstate[gcolor]:
                                nstate[gcolor].remove(i)
                        print("nstate = ", nstate)
    return nstate

def getneighbors(state, pos, side):
#    print("getneighbors()")
#    print("state = ", state)
#    print("pos = ", pos)
#    print("side = ", side)

    group = list()
    if pos not in group:
        group.append(pos)
    for letter in letter_range(pos[0]):
#        print("letter = ", letter)  # DEBUG
        for digit in letter_range("1"):
#            print("digit = ", digit)  # DEBUG
            pos = letter + digit
            if pos in state[side]:
                if pos not in group and checkneigbors(pos, group):
                    group.append(pos)
    return group

def capneed(group, state, side):
#    print("capneed()")
#    print("group = ", group)
#    print("state = ", state)

    startpos = group[0]
#    print("startpos = ", startpos)

    if side == "black":
        oside = "white"
    else:
        oside = "black"

    capneeded = list()

    for letter in letter_range('a'):
#        print("digit = ", digit) # DEBUG
        for digit in letter_range('1'):
#            print("letter = ", letter) # DEBUG
            pos = letter + digit
#            print("pos = ", pos)

            if pos not in group:
                if checkneigbors(pos, group):
                    capneeded.append(pos)
#                print("pos added")

    return capneeded

def checkneigbors(pos, group):
#    print("checkneighbors()")
#    print("pos = ", pos)
#    print("group = ", group)

    letter = pos[0]
#    print("letter = ", letter)
    digit = pos[1]
#    print("digit = ", digit)

    up = letter + str(int(digit) + 1)
#    print("up = ", up)

    down = letter + str(int(digit) - 1)
#    print("down = ", down)

    right = chr(ord(letter) + 1) +digit
#    print("right = ", right)

    left = chr(ord(letter) - 1) + digit
#    print("left = ", left)

    if up in group or down in group or right in group or left in group:
        return True

    return False

main()
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
#   - Fix making illegal moves that would lower score
#       - Implement board state
#       - Implement captures
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
        print("-----")
        show_position()
#        myscore = score(me)
#        print("myscore = ", myscore) # DEBUG
#        oppscore = score(opp)
#        print("oppscore = ", myscore) # DEBUG
        curscore = score(me, opp)
        print("curscore = ", curscore) # DEBUG
#        print(value(grid)) # DEBUG
#        cval = value(grid)[0] # Bug: NOT ALWAYS 0!!!
        cval = value(grid)[me] # Bug: NOT ALWAYS 0!!!
        print("cval = ", cval)
        if side == me :
#            userin = input("Your move: ")
#            move = userin
#            minimax(grid, depth, True)
#            val, move = minimax(grid, depth, True)
#            val, move = minimax(grid, depth, True, value(grid))
#            val, move = minimax(grid, depth, True, cval)
            val, move = minimax(grid, depth, True, cval, me)
#            move = "pass"
            print("My move: ", move)
            try:
                client.make_move(move)
                if move != "pass":
                    grid[me].add(move)
                    board.remove(move)
            except gthclient.MoveError as e:
                print(e)
                if e.cause == e.ILLEGAL:
                    print("You made illegal move, passing")
#                    client.make_move("pass")
                    return # Temp end game
        else:
            cont, move = cont, move = client.get_move()
            print("Opponents move: ", move)
            if cont and move == "pass":
                print("me: pass to end game")
#                minimax(grid, depth, False, cval)
                minimax(grid, depth, False, cval, me)
                client.make_move("pass")
                break
            else:
                if not cont:
                    break
                board.remove(move)
                grid[opp].add(move)
                nstate = captures(grid)
#                grid = captures(grid)
                print("nstate = ", nstate)

        side = gthclient.opponent(side)

# Algorithm source: https://en.wikipedia.org/wiki/Minimax
# function minimax(node, depth, maximizingPlayer) is
#def minimax(node, depth, maxPlayer):
def minimax(node, depth, maxPlayer, cval, me):
#    print("\nminimax()") # DEBUG
#    print("depth = ", depth) # DEBUG
#    print("maxPlayer = ", maxPlayer) # DEBUG
#    print() # DEBUG
    # if depth = 0 or node is a terminal node then
    pos = 0
#    move = random.choice(list(board))
    move = "pass"
    if depth == 0:
        # return the heuristic value of node
#        return value(node)
        val = value(node)
#        print("val = ", val) # DEBUG
#        return val
#        return val[0] # Bug: NOT ALWAYS 0!!!
#        return val["black"]  # Bug: Not Always black!!!
        return val[me]  # Bug: Not Always black!!!
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
                pos = letter + digit
#                pos = letter + str((6 - int(digit)))  # Hacky fix
                tgrid = copy.deepcopy(grid)
                tval = 0
                if pos not in tgrid["black"] and pos not in tgrid["white"] and pos not in imove:
#                    print("not in")
#                    child = tgrid
                    child = copy.deepcopy(tgrid)
#                    child["black"].add(pos) # Bug: Not always black!!!
                    child[me].add(pos) # Bug: Not always black!!!
#                    child = captures(child)
                    # value := max(value, minimax(child, depth − 1, FALSE))
#                    val = max(val, minimax(child, depth - 1, False))
#                    tval, gmove = minimax(child, depth - 1, False)
#                    tval = minimax(child, depth - 1, False)
#                    tval = minimax(child, depth - 1, False, cval)
                    tval = minimax(child, depth - 1, False, cval, me)
#                    if val < tval:
#                    if val < tval and tval >= cval:
                    if val < tval:
                        if tval >= cval:
                            val = tval
                            print("val = ", val) # DEBUG
                            move = pos
                            print("move = ", move) # DEBUG
                        else: # tval never < cval
                            imove.add(pos)
                            print("imove pos = ", pos)
#                    elif tval < cval:
#                        imove.add(pos)
#                        print("imove pos = ", pos)
#                    print("val = ", val)
#                    val[0] = max(val[0], minimax(child, depth - 1, True))  # Bug: Not always 0!!!
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
                pos = letter + digit
#                pos = letter + str((6 - int(digit)))  # Hacky fix
                tgrid = copy.deepcopy(grid)
                tval = 0
                if pos not in tgrid["black"] and pos not in tgrid["white"] and pos not in imove:
#                    print("not in")
                    child = tgrid
#                    child.add(pos)
                    child["white"].add(pos) # Bug: Not always white!!!
#                    child = captures(child)
                    # value := min(value, minimax(child, depth − 1, TRUE))
#                    val = max(val, minimax(child, depth - 1, True))
#                    val = max(val[0], minimax(child, depth - 1, True))  # Bug: Not always 0!!!
#                    tval = minimax(child, depth - 1, False)
#                    tval, gmove = minimax(child, depth - 1, False)
#                    tval, gmove = minimax(child, depth - 1, False, cval)
                    tval, gmove = minimax(child, depth - 1, False, cval, me)
#                    if val < tval:
                    if val < tval and tval >= cval:
                        val = tval
                        move = pos
                    elif tval < cval:
                        imove.add(pos)
                        print("imove pos = ", pos)
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
#    return len(grid["white"]), len(grid["black"])
    return {"white": len(grid["white"]), "black": len(grid["black"])}

# When a stone is placed in such a way that stones of the player on move plus the outer wall completely enclose, with
# no gaps, a group of the opponent's stones horizontally and vertically, the opponent's group is captured.
def captures(state):
#    print("captures()")
#    print("state = ", state)

    nstate = copy.deepcopy(state)

#    group = set()
    group = list()
    visited = set()

#    for digit in letter_range('1'):
    for letter in letter_range('a'):
#        print("digit = ", digit) # DEBUG
#        for letter in letter_range('a'):
        for digit in letter_range('1'):
#            print("letter = ", letter) # DEBUG
            pos = letter + digit
#            pos = letter + str((6 - int(digit)))  # Hacky fix
            if pos in state["white"] and pos not in visited:
#                group.add(pos)
                visited.add(pos)
                gcolor = "white"
#                getneighbors(state, pos, gcolor)
                group = getneighbors(state, pos, gcolor)
#                print("white group = ", group)
                capneeded = capneed(group, state, gcolor)
#                print("capneeded = ", capneeded)

                captured = True

                for i in capneeded:
                    if i not in state["black"]:
#                        return state
                        captured = False
                        break
#                    else:
#                        nstate["white"].add(i)
#                        nstate["black"].add(i)
#                        nstate["black"].remove(i)
#                        nstate["white"].remove(i)

                if captured:
                    for i in group:
#                        nstate["white"].add(i)
                        nstate["black"].add(i)
#                        nstate["black"].remove(i)
                        nstate["white"].remove(i)

#                nstate["black"].add(group) # Bug: wrong order?
#                nstate["white"].remove(group)
#                return nstate
            elif pos in state["black"] and pos not in visited:
#                group.add(pos)
                if pos not in group:
                    group.append(pos)
                visited.add(pos)
                gcolor = "black"
#                getneighbors(state, pos, gcolor)
                group = getneighbors(state, pos, gcolor)
#                print("black group = ", group)
                capneeded = capneed(group, state, gcolor)
#                print("capneeded = ", capneeded)

                captured = True

                for i in capneeded:
                    if i not in state["white"] or len(state["white"]) < len(capneeded):
#                        return state
                        captured = False
                        break
#                    else:
#                        nstate["black"].add(i)
#                        nstate["white"].add(i)
#                        nstate["white"].remove(i)
#                        nstate["black"].remove(i)

                if captured:
                    for i in group:
#                        nstate["white"].add(i)
                        nstate["black"].add(i)
#                        nstate["black"].remove(i)
                        nstate["white"].remove(i)
#                nstate["white"].add(group) # Bug: wrong order?
#                nstate["black"].remove(group)

#                return nstate
    return nstate

def getneighbors(state, pos, side):
#    print("getneighbors()")
#    print("state = ", state)
#    print("pos = ", pos)
#    print("side = ", side)

#    group = set()
    group = list()
#    group.add(pos)
    if pos not in group:
        group.append(pos)
#    for digit in letter_range(pos[1]):
#        print("digit = ", digit)  # DEBUG
    for letter in letter_range(pos[0]):
#    for letter in letter_range("a"):
    #    for digit in letter_range(str(int(pos[0]) + 1)):
#        print("letter = ", letter)  # DEBUG
#        for letter in letter_range(str(int(pos[1]) + 1)):
#            print("letter = ", letter)  # DEBUG
#        for digit in letter_range(pos[1]):
        for digit in letter_range("1"):
#            print("digit = ", digit)  # DEBUG
            pos = letter + digit
#            pos = letter + str((6 - int(digit)))  # Hacky fix
            if pos in state[side]:
#                group.add(pos)
                if pos not in group:
                    group.append(pos)
            else:
                break
#                return group
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

    for letter in letter_range(startpos[0]):
#        print("digit = ", digit) # DEBUG
#        for letter in letter_range('a'):
        for digit in letter_range('1'):
#            print("letter = ", letter) # DEBUG
            pos = letter + digit
#            print("pos = ", pos)

            if pos not in group:
#                if pos in state[oside]:
                if checkneigbors(pos, group):
                    capneeded.append(pos)
#                print("pos added")
#                else:

    return capneeded

def checkneigbors(pos, group):
#    print("checkneighbors()")
#    print("pos = ", pos)
#    print("group = ", group)

    letter = pos[0]
#    letter = chr(ord(pos[0]))
#    print("letter = ", letter)
#    digit = int(pos[1])
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
imove = set()

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
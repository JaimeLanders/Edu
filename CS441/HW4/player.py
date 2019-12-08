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
#       - Implement captures X
#           - Fix captures not updating when depth = 3
#       - Fix making illegal moves
#           - Fix for depth = 1 X
#           - Fix for depth = 2 X
#           - Fix for depth = 3 X
#           - Fix considering illgal move a gain
#       - Fix not working on depth > 1
#       - Fix losing every game
#   - Increase efficiency
#       - Time = ~48 seconds @ depth 3
#       - Time = ~7.5 seconds @ depth 1
#       - Only traverse unvisited nodes
#       - Implement AB Pruning
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

    imove = set() # Tracks illegal moves to avoid repeate calculations

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
        print("\n-----\n")
        show_position(grid)
        curscore = score(grid, me, opp)
        print("curscore = ", curscore) # DEBUG
        cval = value(grid)[me] # Bug: NOT ALWAYS 0!!!
#        cval = value(grid) # Bug: NOT ALWAYS 0!!!
        print("cval = ", cval)
        if side == me :
#            userin = input("Your move: ")
#            move = userin
            val, move = minimax(grid, grid, depth, True, cval, me, imove)
            print("My move: ", move)
#            if val < cval:
#                move = "pass"
            if move != "pass":
                imove.add(move)
            print("imove = ", imove)

#            board.remove(move)
            try:
                client.make_move(move)
                if move != "pass":
                    grid[me].add(move)
#                    board.remove(move)
                    nstate = docaptures(grid)
                    print("nstate = ", nstate)
                    grid = nstate

            except gthclient.MoveError as e:
                print(e)
                if e.cause == e.ILLEGAL:
                    print("You made illegal move, passing")
#                    board.remove(move)
#                    client.make_move("pass")
                return #temp
        else:
            cont, move = cont, move = client.get_move()
            if move != "pass":
                imove.add(move)
            print("imove = ", imove)
            print("Opponents move: ", move)
            if cont and move == "pass":
                print("me: pass to end game")
                minimax(grid, depth, False, cval, me, imove)
                client.make_move("pass")
                break
            else:
                if not cont:
                    break
#                board.remove(move)
                grid[opp].add(move)
                nstate = docaptures(grid)
                print("nstate = ", nstate)
                grid = nstate

        side = gthclient.opponent(side)

# Algorithm source: https://en.wikipedia.org/wiki/Minimax
# function minimax(node, depth, maximizingPlayer) is
    # if depth = 0 or node is a terminal node then
        # return the heuristic value of node
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

# function minimax(node, depth, maximizingPlayer) is
def minimax(grid, node, depth, maxPlayer, cval, me, imove):
    print("\nminimax()") # DEBUG

    print("depth = ", depth) # DEBUG
#    print("maxPlayer = ", maxPlayer) # DEBUG
#    print() # DEBUG
    pos = 0
    move = "pass"
    if me == "black":
        opp = "white"
    else:
        opp = "black"

    # if depth = 0 or node is a terminal node then
#    if depth == 0 or len(grid) > 23: # Bug
    if depth == 0 or len(imove) > 23:  # Bug
        # return the heuristic value of node
        val = value(node)
#        print("val = ", val) # DEBUG
        return val[me], "pass"  # Bug: Not Always me?
#        return val, "pass"  # Bug: Not Always me?
    # if maximizingPlayer then
    if maxPlayer:
        # value := −∞
        ival = -26
#        ival = -26, 0
    # else (* minimizing player *)
    else:
        # value := +∞
        ival = 26
#        ival = 26, 0
    # for each child of node do
#    for digit in letter_range('1'):
    for letter in letter_range('a'):
        #        print("digit = ", digit) # DEBUG
#        for letter in letter_range('a'):
        for digit in letter_range('1'):
    #            print("letter = ", letter) # DEBUG
            pos = letter + digit
#            if pos in imove:
#                break
#            tgrid = copy.deepcopy(grid)
            tgrid = copy.deepcopy(node)
#            tval = 0
            if pos not in tgrid["black"] and pos not in tgrid["white"] and pos not in imove:
#            if pos not in tgrid["black"] and pos not in tgrid["white"]:
                child = copy.deepcopy(tgrid)
                child[me].add(pos) # Bug: Not always me?

                # Check if illegal move before doing captures
                tgroup = list()
                tgroup.append(pos)
                tcap = capneed(tgroup, child, opp)
                if iscaptured(child, opp, tcap):
                    imove.add(pos)
                    break

                child = docaptures(child)
#                if value(child)[me] <= cval:
#                if value(child)[me] <= cval[me]:
#                    print("illegal move detected")
#                    imove.add(pos)
#                    break
                # value := max(value, minimax(child, depth − 1, FALSE)) if maxPlayer
                tval, tmove = minimax(grid, child, depth - 1, not maxPlayer, cval, me, imove)

                #if maxPlayer
                if(maxPlayer):
                    if tval > ival:
#                    if tval[me] > ival[me]:
                        if tval > cval:
#                        if tval[me] > cval[me]:
                            ival = tval
                            print("ival = ", ival) # DEBUG
                            move = pos
                            print("move = ", move) # DEBUG
#                        elif tval <= cval or len(grid) >= 24:
#                        elif tval[me] <= cval[me] or len(grid) >= 24:
#                            print("illegal move detected")
#                            print("imove pos = ", pos)
#                            imove.add(pos)
                # if minPlayer
                # value := min(value, minimax(child, depth − 1, TRUE))
                else:
                    min(tval, ival)
#                    min(tval[minplayer], ival[minplayer])

    # return value
    return ival, move

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
def docaptures(state):
#    print("docaptures()")
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
#                print("ccolor = ", ccolor)
                if pos not in visited:
                    if pos not in group:
                        group.append(pos)
                        group.sort()

                    visited.add(pos)

#                    tgroup = list()
#                    tgroup.append(pos)
#                    tcap = capneeded(tgroup, state, gcolor)
#                    if iscaptured(state, ccolor, tcap):
#                        imove.add(pos)
#                        break

                    group = getneighbors(state, pos, gcolor)
                    group.sort()
                    print("group = ", group)
                    capneeded = capneed(group, state, gcolor)
                    print("capneeded = ", capneeded)

                    for i in group:
                        visited.add(i)

                    if iscaptured(state, ccolor, capneeded): #and len(group) < 24:
    #                    if captured and len(state) < 24:
                        print("---CAPTURE!!!---")
                        print("gcolor = ", gcolor)
                        print("ccolor = ", ccolor)
                        print("pos = ", pos)
                        for i in group:
                            nstate[ccolor].add(i)
                            if i in nstate[gcolor]:
                                nstate[gcolor].remove(i)
                        print("nstate = ", nstate)
                        return nstate
#                        break
#                    elif len(group) >= 24:
#                        return nstate
    return nstate

def iscaptured(state, color, capneed):
    print("iscaptured()")
#    print("state = ", state)
#    print("color = ", color)
#    print("capneed = ", capneed)

    captured = True

    for i in capneed:
        if i not in state[color]:
            captured = False

    return captured


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
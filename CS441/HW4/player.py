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
#           - Fix considering illegal move a gain X
#       - Fix not working on depth > 1 X
#       - Fix losing every game/making dumb moves
#           - Fix never making move when depth 3 white side X
#           - Fix not getting neigbors in collumns before pos in getneighbors X
#           - Fix adding valid moves to imove X
#           - Fix passing always when starting with random move when black X
#           - Fix bug in getneighbors
#           - Fix base case/terminal node logic
#   - Increase efficiency
#       - Implement AB Pruning X
#       - Only traverse unvisited nodes X
#       - Only traverse valid nodes
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
    print("board = ", board)

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
    mdepth = depth
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
        cval = value(grid)
        print("cval = ", cval)
        if side == me:
#            userin = input("Your move: ")
#            move = userin
#            if len(board) == 25: # Open with random move if on the play (black)
#                move = random.choice(list(board))
#            else:
            val, move = minimax(grid, depth, True, -26, 26, me, opp, imove, board, mdepth)
            print("My move: ", move)
            if move != "pass":
                imove.add(move)
                board.remove(move)
                print("board = ", board)
            print("imove = ", imove)
            try:
                client.make_move(move)
                if move != "pass":
                    grid[me].add(move)
                    nstate = docaptures(grid)
                    print("nstate = ", nstate)
                    grid = nstate

            except gthclient.MoveError as e:
                print(e)
                if e.cause == e.ILLEGAL:
                    print("You made illegal move, passing")
#                    client.make_move("pass")
                    return #temp
        else:
            cont, move = client.get_move()
            print("Opponents move: ", move)
            if move != "pass":
                imove.add(move)
                board.remove(move)
                print("board = ", board)
            print("imove = ", imove)
            if cont and move == "pass" and len(imove) == 25:
                print("me: pass to end game")
                client.make_move("pass")
                break
            else:
                if not cont:
                    break
                grid[opp].add(move)
                nstate = docaptures(grid)
                print("nstate = ", nstate)
                grid = nstate

        side = gthclient.opponent(side)


# Algorithm source: https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
# function alphabeta(node, depth, α, β, maximizingPlayer) is
    # if depth = 0 or node is a terminal node then
        # return the heuristic value of node
    # if maximizingPlayer then
        # value := −∞
        # for each child of node do
            # value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            # α := max(α, value)
            # if α ≥ β then
                # break (* β cut-off *)
        # return value
    # else
        # value := +∞
        # for each child of node do
            # value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            # β := min(β, value)
            # if α ≥ β then
                # break (* α cut-off *)
        # return value
def minimax(node, depth, alpha, beta, maxPlayer, me, opp, imove, board, mdepth):

    print("\nminimax()") # DEBUG

    print("depth = ", depth) # DEBUG
#    print("maxPlayer = ", maxPlayer) # DEBUG
#    print() # DEBUG
    pos = 0
    move = "pass"

    # Base case: when there are no more valid moves left to make
    # if depth = 0 or node is a terminal node then
    if depth == 0 or len(imove) >= 24:  # Bug: not sure if correct terminal node
        # return the heuristic value of node
        val = eval(node)
        return val, move
    # if maximizingPlayer then
    if maxPlayer:
        # value := −∞
        val = -26
    # else (* minimizing player *)
    else:
        # value := +∞
        val = 26
    # for each child of node do
    for pos in board:
        child = copy.deepcopy(node)
        if pos not in child["black"] and pos not in child["white"] and pos not in imove:

            if maxPlayer:
                child[me].add(pos) # Bug: Not always me?
            else:
                child[opp].add(pos)  # Bug: Not always me?

            # Check if illegal move before doing captures
            if maxPlayer:
                tgroup = set()
                sgroup = set()
                sgroup.add(pos) # Only checks position by itself, not group
                scap = capneed(sgroup, opp)
                if iscaptured(child, opp, scap):
                    if depth == mdepth:
                        imove.add(pos)
                    break

                tgroup.add(pos) # Only checks position by itself, not group
                visited = set()
                tgroup = getneighbors(child, pos, me, tgroup, visited) # Bug: Not returning all members of group
                print("tgroup = ", tgroup)
                tcap = capneed(tgroup, opp)
                print("tcap = ", tcap)
                if iscaptured(child, opp, tcap):
                    if depth == mdepth:
                        imove.add(pos)
                    break

            child = docaptures(child)
            tval, tmove = minimax(child, depth - 1, not maxPlayer, alpha, beta, me, opp, imove, board, mdepth)

            #if maxPlayer
            # value := max(value, minimax(child, depth − 1, FALSE)) if maxPlayer
            if(maxPlayer):
                if tval > val:
                    val = tval
                    print("val = ", val) # DEBUG
                    move = pos
                    print("move = ", move) # DEBUG
                    alpha = max(alpha, tval)
                    if (alpha >= beta):
                        break
            # if minPlayer
            # value := min(value, minimax(child, depth − 1, TRUE))
            else:
                min(tval, val)
                beta = min(beta, tval)
                if (alpha >= beta):
                    break
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


def eval(state):
    print("eval()")
    diff = len(state["black"]) - len(state["white"])
    print("diff = ", diff)
    return diff


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
            group = set()
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
                        group.add(pos)

                    visited.add(pos)
                    tvisited = set()

                    group = getneighbors(state, pos, gcolor, group, tvisited)
                    print("group = ", group)
                    visited.update(group)
                    capneeded = capneed(group, gcolor)
                    print("capneeded = ", capneeded)

                    if iscaptured(state, ccolor, capneeded):
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
    return nstate


def iscaptured(state, color, capneed):
#    print("iscaptured()")
#    print("state = ", state)
#    print("color = ", color)
#    print("capneed = ", capneed)

    captured = True

    for i in capneed:
        if i not in state[color]:
            captured = False

    return captured


def getneighbors(state, pos, side, group, visited):
#    print("getneighbors()")
    letter = pos[0]
#    print("letter = ", letter)
    digit = pos[1]
#    print("digit = ", digit)

    if pos in state[side] and pos not in visited:
        upletter = chr(ord(letter) + 1)
        downletter = chr(ord(letter) - 1)
        upnumber = str(int(digit) + 1)
        downnumber = str(int(digit) - 1)

        up = letter + upnumber
        down = letter + downnumber
        left = downletter + digit
        right = upletter + digit

        group.add(pos)
        visited.add(pos)
        if int(upnumber) <= 5:
            posup = getneighbors(state, up, side, group, visited)
            if posup != None:
                group.update(posup)
        if int(downnumber) >= 1:
            posdown = getneighbors(state, down, side, group, visited)
            if posdown != None:
                group.update(posdown)
        if ord(downletter) >= ord('A'):
            posleft = getneighbors(state, left, side, group, visited)
            if posleft != None:
                group.update(posleft)
        if ord(upletter) <= ord('E'):
            posright = getneighbors(state, right, side, group, visited)
            if posright != None:
                group.update(posright)

    return group


def capneed(group, side):
#    print("capneed()")
#    print("group = ", group)
#    print("state = ", state)

    group = list(group)
    group.sort()
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


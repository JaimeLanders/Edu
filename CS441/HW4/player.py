import copy
import gthclient
import sys

# Source: gthrandom.py from gothello-libclient-python3
def letter_range(letter):
    for i in range(5):
        yield chr(ord(letter) + i)

# Source: gthrandom.py from gothello-libclient-python3
def show_position(grid):
    for digit in letter_range('1'):
        for letter in letter_range('a'):
            pos = letter + str((6 - int(digit))) # Hacky fix
            if pos in grid["white"]:
                piece = "w"
            elif pos in grid["black"]:
                piece = "b"
            else:
                piece = "."
            print(piece, end="")
        print()

# Main function which makes and recieves moves and determines when game is over
def main():
    print("Welcome to Gothello Player 1.0")

    if len(sys.argv) != 5:
        print("\nError: missing command line arguments.")
        print("\nUsage: python3 player.py black|white server_ip server_number search_depth")
        return

    # Source: gthrandom.py from gothello-libclient-python3
    board = {letter + digit
             for letter in letter_range('a')
             for digit in letter_range('1')}

    # Source: gthrandom.py from gothello-libclient-python3
    grid = {"white": set(), "black": set()} # Global?

    imoves= set() # Tracks illegal moves to avoid repeate calculations

    me = sys.argv[1]
    ip = sys.argv[2]
    servernum = int(sys.argv[3])
    depth = int(sys.argv[4])
    mdepth = depth
    client = gthclient.GthClient(me, ip, servernum)
    opp = gthclient.opponent(me)

    side = "black" # Black goes first
    while True:
        show_position(grid)
        print("\n", score(grid, me, opp))
        print()
        if side == me:
            val, move = minimax(grid, depth, True, float("-inf"), float("inf"),
                                me, opp, imoves, board, mdepth)

            print("My move: ", move)
            if move != "pass":
                imoves.add(move)
                board.remove(move)
            try:
                client.make_move(move)
                if move != "pass":
                    grid[me].add(move)
                    nstate = docaptures(grid)
                    grid = nstate

            except gthclient.MoveError as e:
                print(e)
                if e.cause == e.ILLEGAL:
                    print("You made illegal move, passing")
                    client.make_move("pass")
        else:
            try:
                cont, move = client.get_move()
                print("Opponents move: ", move)
                if move != "pass":
                    imoves.add(move)
                    board.remove(move)
                if cont and move == "pass" and len(imoves) == 25:
                    print("me: pass to end game")
                    client.make_move("pass")
                    break
                else:
                    if not cont:
                        break
                    if move != "pass":
                        grid[opp].add(move)
                        nstate = docaptures(grid)
                        grid = nstate
            except gthclient.MoveError as e:
                print("Game over...")
                return #tempError as e:
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
# Minimax function used to calculate best moves
def minimax(node, depth, alpha, beta, maxPlayer, me, opp, imoves, board, mdepth):
    pos = 0
    move = "pass"

    if depth == mdepth:
        tmoves = copy.deepcopy(imoves)
    else:
        tmoves = imoves

    # Base case: when there are no more valid moves left to make
    # if depth = 0 or node is a terminal node then
    if depth == 0 or len(tmoves) == 25:  # Bug: not sure if correct terminal node
        # return the heuristic value of node
        if maxPlayer:
            val = eval(node, me, opp)
        else:
            val = eval(node, opp, me)
        return val, move
    # if maximizingPlayer then
    if maxPlayer:
        # value := −∞
        val = float("-inf")
    # else (* minimizing player *)
    else:
        # value := +∞
        val = float("inf")

    vmove = board - tmoves
    # for each child of node do
    for pos in vmove:
        child = copy.deepcopy(node)

        if maxPlayer:
            child[me].add(pos)
        else:
            child[opp].add(pos)

        # Check if illegal move before doing captures
        if maxPlayer:
            tgroup = set()
            sgroup = set()
            sgroup.add(pos)
            scap = capneed(sgroup, opp)
            if iscaptured(child, opp, scap):
                if depth == mdepth:
                    imoves.add(pos)
                tmoves.add(pos)
                continue

            tgroup.add(pos) # Only checks position by itself, not group
            visited = set()
            tgroup = getneighbors(child, pos, me, tgroup, visited)
            tcap = capneed(tgroup, opp)
            if iscaptured(child, opp, tcap):
                if depth == mdepth:
                    imoves.add(pos)
                tmoves.add(pos)
                continue

        child = docaptures(child)
        tval, tmove = minimax(child, depth - 1, not maxPlayer, alpha, beta,
                              me, opp, tmoves, board, mdepth)

        #if maxPlayer
        # value := max(value, minimax(child, depth − 1, FALSE)) if maxPlayer
        if(maxPlayer):
            if tval > val:
                val = tval
                move = pos
                alpha = max(alpha, tval)
                if (alpha >= beta):
                    break
#                    continue
        # if minPlayer
        # value := min(value, minimax(child, depth − 1, TRUE))
        else:
            val = min(tval, val)
            beta = min(beta, val)
            if (alpha >= beta):
                break
#                continue
    # return value
    return val, move

# Used to print score in (me, opponent) format
def score(grid, me, opp): # Needed since I have  value()?
    return len(grid[me]), len(grid[opp])


# Evaluation function used to determine the value of the current state for a
# player
def eval(state, a, b) :
    diff = len(state[a]) - len(state[b])
    return diff

# Used to redo the board after a move and flip pieces that have been captured.
def docaptures(state):
    nstate = copy.deepcopy(state)
    visited = set()
    for letter in letter_range('a'):
        for digit in letter_range('1'):
            group = set()
            pos = letter + digit
            if pos in state["white"]:
                gcolor = "white"
                ccolor = "black"
            elif pos in state["black"]:
                gcolor = "black"
                ccolor = "white"
            if pos in state["white"] or pos in state["black"]:
                if pos not in visited:
                    if pos not in group:
                        group.add(pos)

                    visited.add(pos)
                    tvisited = set()

                    group = getneighbors(state, pos, gcolor, group, tvisited)
                    visited.update(group)
                    capneeded = capneed(group, gcolor)

                    if iscaptured(state, ccolor, capneeded):
                        for i in group:
                            nstate[ccolor].add(i)
                            if i in nstate[gcolor]:
                                nstate[gcolor].remove(i)
                        return nstate
    return nstate

# Helper function to determine illegal moves
def iscaptured(state, color, capneed):
    captured = True

    for i in capneed:
        if i not in state[color]:
            captured = False

    return captured

# Returns group a position is included in
def getneighbors(state, pos, side, group, visited):
    letter = pos[0]
    digit = pos[1]

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
        if ord(downletter) >= ord('a'):
            posleft = getneighbors(state, left, side, group, visited)
            if posleft != None:
                group.update(posleft)
        if ord(upletter) <= ord('e'):
            posright = getneighbors(state, right, side, group, visited)
            if posright != None:
                group.update(posright)

    return group

# Returns positions needed to capture a group
def capneed(group, side):
    group = list(group)
    group.sort()

    capneeded = list()

    for letter in letter_range('a'):
        for digit in letter_range('1'):
            pos = letter + digit

            if pos not in group:
                if checkneigbors(pos, group):
                    capneeded.append(pos)

    return capneeded

# Checks if position has like neighbors
def checkneigbors(pos, group):
    letter = pos[0]
    digit = pos[1]
    up = letter + str(int(digit) + 1)
    down = letter + str(int(digit) - 1)
    right = chr(ord(letter) + 1) +digit
    left = chr(ord(letter) - 1) + digit

    if up in group or down in group or right in group or left in group:
        return True

    return False

main()
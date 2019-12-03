# TODO:
#   - Setup project including all modules needed to run the game: X
#       - Official server daemon (gthd) X
#       - Grossthello player X
#       - Python client X
#       - My submission X
#   - Make manual player to test connections and understand client
#       - Import gthclient.py X
#       - Connect to server X
#       - Display current state
#       - Make moves using user input
#       - Get opponents moves
#       - Play until complete
#   - Implement minimax player
#   - Implement better evaluator ?


import sys
import gthclient

def main():
    print("Welcome to Gothello Player 1.0")
#    me = sys.argv[1]
    me = "black"
    client = gthclient.GthClient(me, "localhost", 0)
#    client.make_move("pass")
#    client.make_move("a1")
    while(True):
        show_position()
        userin = input("Your move: ")
        client.make_move(userin)
        cont, move = client.get_move()

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
        for letter in letter_range('a'):
            pos = letter + digit
            if pos in grid["white"]:
                piece = "O"
            elif pos in grid["black"]:
                piece = "*"
            else:
                piece = "."
            print(piece, end="")
        print()

main()
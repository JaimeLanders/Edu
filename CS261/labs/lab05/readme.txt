Overview
--------

For this lab you will examine and modify two different versions of the Zuul
program from the book. The objective is to observe design and architecture
problems and identify ways to fix them.

Details
-------

First copy all of the files from the lab directory into your directory. You
will be editing these files so they need to be in a writeable location for
you.

Zuul-bad

Go into the zuul-bad directory and compile the entire program using this
command:

javac *.java

You can now run the program using this command:

java Zuul

This is a very sipmle text adventure game somewhat like the classic game
Zork. You can play an online version of Zork here:
http://textadventures.co.uk/games/view/5zyoqrsugeopel3ffhz_vq/zork

Play around with the Zuul game until you feel like you understand how the game
works. The only valid commands are "help", "go", "quit". The "go" command
requires a direction of "east", "west", "north", or "south".

After playing with the game edit the various java files to add a new room
"meeting room" that you can get to by going "up" from the "pub". You will also
need to add support for the "up" direction to the "go" command.  Once you have
edited the program, make sure you can compile and run the program. Be sure to
try to get to the new room.

Zuul-good

Go into the zuul-good directory and compile the entire program using this
command:

javac *.java

You can now run the program using this command:

java Zuul

Just like you did for zuul-bad, add the new "meeting" room and make sure you
can get to it.

Reflection
----------

Using your text editor edit the questions.txt file and answer the questions.

Turning in the assignment
-------------------------

Use the turnin program to turn in the questions.txt file. The command is
~mike.noel/bin/turnin cs261 questions.txt.


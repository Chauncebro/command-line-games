lab 2 Chauncey Hill

at first my program could not take proper input and could only accept input seperated by whitespace
but then I was able to fix this by replacing the comma in the input with a space

Then I realized that I had switched the row input and column input when i parsed the users input for a 
move.  This was easily fixed by switching the row and column variables around

For testing I just made sure that it could detect wins, losses, and draws correctly and that it did not allow
the player to play over a previous move

for the extra credit portion I designed an auto player that goes first.  It always plays in the middle square
on its first turn then after that it checks for moves that make it win and plays that, then it checks for moves
that make the opponent not be able to win (interupt potential three in a rows).  If neither of those are available
it plays the move oppossite of the opponents move (the optimal strategy).  If this is not available the computer plays
the first available move (move does not matter in this case).  This strategy will always result in either a 
win for the computer or a draw (that is the best the computer can do).

When implementing the auto player I ran into some issues, firstly I initially did not check to make sure the
move the autoplayer was making was valid, secondly I implmented checking the opponents potential moves incorectly
by accidentally making the piece that I inserted into the board the wrong colour, causing the autoplayer to be unable
to check if the opponent would win properly, as my done() method compares the colors of pieces to determine if the game is over
or not.

to test the autoplayer I played against it and tried every strategy I could think of to beat it, but could not
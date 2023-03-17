HOMEWORK 6 CONTEST: INVERSE WORD SEARCH


NAME: Christopher Villanueva


OPTIMIZATIONS:
What did you do?
There were 2 major optimizations I did on the program. The first is I sorted the words by size
before I recursed through them. This meant that the largest words were attempted for recursion first,
and the short words that exploded the number of iterations of recursion were kept until the end when
there were fewer cells. The larger words meant that more cells were taken up and fewer cells needed to be
randomly placed with the smaller words to check for proper outputs. This decreased runtimes in some cases
by up to 3x! The second optimization was to take out any single characters forbidden words from my
alphabet list for adding in random letters to empty cells. This was very helpful for the test case that
had a lot of single character forbidden letters, since it changed the amount of recursion for that step from
26^n to (26-x)^n, where n is the number of empty cells. This greatly reduced runtime in that specific case.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?
Same program is used for the main submission and the contest, so the same
writeup is used for the solutions

Puzzle 1 - 2ms
Puzzle 2 - 4ms
Puzzle 3 - 73ms
Puzzle 4 - 44ms
Puzzle 5 - 13ms
Puzzle 6 - 18ms
Puzzle 7 - 1012ms
Puzzle 8 - 21532ms

Custom 1 (352 Solutions) - 23ms
Custom 2 (8 Solutions) - 81ms
Custom 3 (8 Solutions) - 2938ms

Custom 1 was a test case with a long word (recursion)
Custom 2 and custom 3 dealt with cases where there werent enough
spaces for every word, and the only solutions is where one of the words
is created by being inside other words

HOMEWORK 6: INVERSE WORD SEARCH


NAME: Christopher Villanueva


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
O(8whl^r + whs + 16whlf + swh(26-x)^a)
w is the number of columns
h is the number of rows
l is the number of characters in a word
r is the number of required words
f is the nubmer of forbidden words
x is the number of words exluded that are single characters
a is the number of empty cells after all words have been added
s is the number of solutions
My algorithm is split into multiple parts. The first is the 
creation of the solutions through recursion. This takes
O(8whl^r) time because for each square in the board, 8 directions are 
checked to see which words can be added there in that direction.
Any successful words are then added as new boards and recursed through 
the same function. After all the words are added, blank spaces are filled,
which takes O(swh(26-x)^a) time because it checks through all spaces 
in all solutions for empty spaces, fills it, and recurses. The O(whs)
comes into play with palendromes, and it removes duplicate solutions.
Finally, the O(16whl^f) is for using the standard recursive search to
see if any of the forbidden words are in the grid. This is very similar
to how words are originally added to the grids and solutions are created.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?
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

MISC. COMMENTS TO GRADER:  
Optional, please be concise!

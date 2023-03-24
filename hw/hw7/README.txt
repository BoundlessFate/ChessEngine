HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME: Christopher Villanueva


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

No collaborators used

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 10



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:
	m is not used because there are 7 moves, which reduces to O(1) which is negligible time compared to the log time complexities
-q (specific move): O(log(f) + m)
	O(log(f)) because that is how long it takes to find the correct fighter in the map and check for a valid move. Everything else is O(1)
-q (all): O(log(f) + m)
	O(log(f)) because that is how long it takes to find the correct fighter in the map and check for a valid move. Everything else is O(1)
-f: O(f(log(f) + m)
	O(f(log(f)) because all of the indexes have to be added one by one to a set and checked for a valid move, which takes log(f) time for each addition
-s: O(f(log(f) + m)
	O(f(log(f)) because the code is virtually identical from -f apart from a different sort function for the set
-d: O(f(log(f) + m + t)
	O(f(log(f) + m + t) because the list has to be sorted and then iterated for every move 
	with the same frame, and also have the move checked to see if it is valid

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)







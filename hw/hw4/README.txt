HOMEWORK 4: TOOL RENTAL LISTS


NAME: Christopher Villanueva


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Viane

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 25 Hours



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file:
	O(i^2)
	Loops through each line in the inventory file, and places it in the correct order by id
Rental event:
	O(i+c)
	Finds the item from the id, and rents the item for the customer that was parsed to find
Return event - no pending customer(s):
	O(2c+i)
	Finds the customer from the id, finds the item the same way, and returns the tool
Return event - with pending customer(s):
	O(c+i+2cpr)
	Finds the customer from the id, finds the item the same way, returns the tool, and rents tools for those in pending
Entire program:
	O(i^2+ei+eic+ec+ei+2ecpr+4ic^2+ic)
	Loads inventory file, rents and returns for all cases necessary, and prints to the inventory and customer files


MISC. COMMENTS TO GRADER:
(optional, please be concise!)
Took a while to finish, coded a rats nest, but eventually cleaned it up a bit

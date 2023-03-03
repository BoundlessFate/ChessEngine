HOMEWORK 5: LINKED TRAIN CARS


NAME: Christopher Villanueva


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Viane Matsibekker
Joshua Collins

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 30



DESCRIPTION OF IMPROVED SHIPFREIGHT ALGORITHM FOR EXTRA CREDIT 
Aiming for optimal (fastest train speed, most freight, fewest number
of engines used, and fewest resulting trains) for any input.  Note:
Student choice on how to prioritze between these goals.  Describe your
priorization and your implementation.



DESCRIPTION OF IMPROVED SEPARATE ALGORITHM FOR EXTRA CREDIT 
Aiming for optimally comfortable trains (smaller values for average
distance to dining and/or larger values for closest engine to sleeper)
and/or optimally handling cases with > 2 engines.  Student choice on how 
to prioritze between these goals.  Describe your priorization and your
implementation.
My code for separate can handle as many engines as it needs. I played around in desmos to find the formula where
given the original speed, it returns the number of engines and other cars needed in each of the two
trains for the speeds to match each other. Once I have these numbers, my separate function will find 
a spot in the original train where one of the two final trains can be met with 1 or 2 disconnects (one on either side).
It then sets the rest of the train equal to the other train.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


HOMEWORK 8: B+ TREES


NAME: Christopher Villanueva


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Joshua Collins

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  ~10 hours


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

To debug my program, I used gdb to go line by line through my program. 
I also drew out visual models of my trees to test if it was working properly.
I used the test file provided as well to see if my program worked, as my code
passed all the assert statements. For memory issues, I used Dr. Memory to verify 
I had no memory errors or leaks, and I made sure to add a deconstructor and keep
track of all my heap memory. To test corner cases, I drew out many test cases
on paper and went through my code by hand to make sure it would run properly
on edge cases.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


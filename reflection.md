# Description
My program reads a schedule from a txt file, determines whether it is indeed a valid schedule, and then compares that with a user inputted schedule to detmerine if there are conflicting timelines.Now it can determine which schedule order will maximize the amount of courses that can be taken. 
# Challenges encountered
The toughest part of this milestone was creating the logic for the best_schedule function. The use of permutation had me very confused initially and clarification we heavily needed to set the logic for it. I still had issues with the indexing of the courses since the array pointer started at 1 and the index for the courses started at 0. I was able to get the code to compile and the majority of the tests to pass, but the indexing issue ends up calling an area of memory that is not occupied. 

# Things I've learned
From this milestone I got a better understanding of how to allocate and de-allocate memory to avoid leaks. It did a good job at identifying my weak points before I go into the course final. 
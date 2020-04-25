# TuffyScheduler Milestone 6

This is milestone 6 of the [TuffyScheduler Project](https://docs.google.com/document/d/1439ruL-xNEz58-ND_3Li7nthr1om_dwXJ3zQlB42oPI/edit?usp=sharing).

# Requirements
Our **CourseSchedule** implementation from Milestone 5 does not perform very well when it does not get courses in a certain order. Consider the schedule file shown below. Adding the course `CPSC 362` first will result in both `CPSC 131` and `CPSC 481` to conflict with its schedule. This results in a schedule with only one course. However, if you added `CPSC 131` and `CPSC 481` before adding `CPSC 362` then you will have the optimal schedule that contains two courses.

```
CPSC 362
CS 101
MW
16:30
19:50
CPSC 131
EC 109
MW
16:00
17:15
CPSC 481
CS 408
MW
18:00
19:15
```

In this milestone we will create a **ScheduleManager** class that finds a schedule that accommodates the most courses provided in a schedule file. **ScheduleManager** will load **Courses** from a schedule file then creates multiple **CourseSchedule** objects and adds different permutations of **Courses** in each one. This process effectively creates different schedule variations and the **ScheduleManager** chooses the schedule with the most number of courses.

## Classes
### CourseSchedule
*Summary: Modify the CourseSchedule class to give options to check for conflicts when adding courses, add a Course through pointers, and retrieve a Course pointer*.

#### Data members
Add a boolean data member called *remove_conflicts_* that is used to indicate whether **CourseSchedule** checks for conflicting **Courses** before adding it to the **Course** pointer array.

#### Nondefault constructor
Create a nondefault constructor that accepts a boolean parameter that will be used to set the *remove_conflicts_* data member `true` or `false`. It should set *num_courses_* to `0`.

#### Default constructor
Modify the default constructor to call the nondefault constructor and set *remove_conflicts_* to `true`.

#### add
Modify your add member function so that it checks the *remove_conflicts_* data member to decide whether it should check for conflicts or not. If *remove_conflicts_* is `true`, then the member function should work the same way as Milestone 5 -- add the **Course** pointer if it does not conflict with any course already in the array of **Course** pointers, and delete the **Course** pointer otherwise.

However, if *remove_conflicts_* is `false` then it will add the **Course** pointer to the array of **Course** pointers without checking for conflicts.

#### add overload
Create a new *add* function that will overload the *add* function described above. This function should accept a **Course** pointer as a parameter and return a boolean value. The function should call the *add* function above and return whatever it returns. You can retrieve all the values required by your *add* function's parameters above by dereferencing the passed **Course** pointer.

#### course
Create a *course* function that accepts an integer as a parameter and returns a **Course** pointer. The member function should use the integer parameter to return the corresponding element of the array. For example, if the integer parameter was 3, then it should return the fourth **Course** pointer in the *courses_* array (take note that the indices begin with 0).

### ScheduleManager
*Summary: Create a ScheduleManager class that is used to load schedules from a file and find the best schedule. Make sure to include the fstream and algorithm header files to provide all the functionalities you need for this class.*

#### Data members
Create a **CourseSchedule** called *complete_schedule_*. This will contain all the **Course** objects from the file.

Create a **CourseSchedule** pointer called *best_schedule_*. This will contain the address of the best schedule.

#### Default constructor
Create a default constructor that does the following using an initialization list.

1. Initialize *complete_schedule_* by calling **CourseSchedule**'s nondefault constructor and passing `false` for *remove_conflicts_*
1. Initialize *best_schedule_* to `nullptr`

#### load_schedule
Move your global *load_schedule* function from Milestone 5 into the **ScheduleManager** class. This should now be a private member function that only accepts an *std::string* filename as a parameter and returns a boolan value. The member function works the same way, however, it should now use the *complete_schedule_* data member to add **Course** objects. Recall that in Milestone 5, we used a **CourseSchedule** object that was passed as a parameter, but we are now using a data member.

#### best_schedule
Create a *best_schedule* member function that accepts an *std::string* filename as a parameter and returns a **CourseSchedule** pointer. The member function performs the following operations.

1. Call the *load_schedule* function and pass the filename parameter passed to *best_schedule*.
1. If there is an error loading the file, the *best_schedule* member function should return `nullptr`.
1. If the file is loaded correctly:
    1. Create a local **Course** pointer array variable.
    1. Copy all the **Course** pointers from the *complete_schedule_* data member into the local **Course** pointer array. *Hint: CourseSchedule provides a course() member function that retrieves courses from a CourseSchedule object*.
    1. Use the *std::next_permutation* function from the Standard Template Library (STL) to generate all permutations of the **Course** pointer array. You can read more about the *std::next_permutation* function from: http://www.cplusplus.com/reference/algorithm/next_permutation/. Take note that it requires you to include the *algorithm* header. For each permutation (iteration of the loop), your local **Course** pointer array will contain **Course** pointer objects in a different sequence. Use a **CourseSchedule** object to add **Course** pointer objects in each iteration and take note of the number of courses successfully added.
    1. Identify the **CourseSchedule** object that contains the most number of courses and assign it to the *best_schedule_* data member. *Be very careful on how you allocate and deallocate objects here. Otherwise you will experience memory leaks.*
    1. Return the *best_schedule_* data member.

#### Destructor
Create a destructor that will deallocate the space in the heap occupied by the *best_schedule_* data member if it is not `nullptr`.

### main function (Driver)
Modify your *main* function so that it creates a **ScheduleManager** object. Call its *best_schedule* member function and pass the filename provided by the user. Store the result of the function into a **CourseSchedule** pointer. If the returned pointer is not `nullptr` then call the *display* function of the **CourseSchedule** pointer. You do not need to print anything otherwise.

The screen output should now show the most number of courses without conflicts from the schedule file.

# Sample output
Below are samples of the program's output given different cases.

## Valid file
<pre>
Welcome to Tuffy Scheduler!
Please enter the file name containing the list of classes: <b>sched.txt</b>
The schedule below accommodates the most number of courses without conflicts from the file you provided:

Course name: CPSC 131
Location: EC 109
Weekly schedule: MW
Start time: 16:00
End time: 17:15

Course name: CPSC 481
Location: CS 408
Weekly schedule: MW
Start time: 18:00
End time: 19:15

Thank you for using Tuffy Scheduler.
</pre>

## Start time happens after end time
<pre>
Welcome to Tuffy Scheduler!
Please enter the file name containing the list of classes: <b>sched.txt</b>
Error: The start time 17:15 should happen before the end time 16:00.
Invalid file.
Thank you for using Tuffy Scheduler.
</pre>

## Invalid weekly schedule
<pre>
Welcome to Tuffy Scheduler!
Please enter the file name containing the list of classes: <b>sched.txt</b>
Error: Invalid weekly schedule symbol MX.
Invalid file.
Thank you for using Tuffy Scheduler.
</pre>

# Submission checklist
1. Compiled and ran the driver (`main`).
1. Manually checked for compilation and logical errors.
1. Designed and tested your own test cases.
1. Ensured no errors on the unit test (`make test`).
1. Ensured no errors on the style check (`make stylecheck`).
1. Ensured no errors on the format check (`make formatcheck`).
1. Completed reflection file ([reflection.md](reflection.md))

# Code evaluation
Open the terminal and navigate to the folder that contains this exercise. Assuming you have pulled the code inside of `/home/student/ts06-tuffy` and you are currently in `/home/student` you can issue the following commands

```
cd ts06-tuffy
```

Use the `clang++` command to compile your code and the `./` command to run it. The sample code below shows how you would compile code save in `main.cpp` and into the executable file `main`. Make sure you use the correct filenames required in this problem.  Take note that if you make any changes to your code, you will need to compile it first before you see changes when running it.

```
clang++ -std=c++17 main.cpp scheduler.cpp -o main
./main
```

You can run one, two, or all the commands below to `test` your code, `stylecheck` your code's design, or `formatcheck` your work. Kindly make sure that you have compiled and executed your code before issuing any of the commands below to avoid errors.

```
make test
make stylecheck
make formatcheck
```

A faster way of running all these tests uses the `all` parameter.

```
make all
```

# Submission
1. When everything runs correctly,  let's copy your code into the Github repository. The first step is to add your code to what is called the staging area using git's `add` command. The parameter after `add` is the name of the file you want to add. There are cases when you have multiple changed files, so you can just type . (period) to add all modified files.

    ```
    git add main.cpp
    ```
1. Once everything is in the staging area, we use the `commit` command to tell git that we have added everything we need into the staging area.

    ```
    git commit
    ```

    Alternatively, you could add a comment to the `commit` command in order to s
kip the *nano* editor step described below.

    ```
    git commit -m "Finished milestone"
    ```
1. In case it asks you  to configure global variables for an email and name, just copy the commands it provides then replace the dummy text with your email and Github username.

    ```
    git config --global user.email "tuffy@csu.fullerton.edu"
    git config --global user.name "Tuffy Titan"
    ```
    When you're done, make sure you type `git commit` again.    
1. Git will ask you to describe what you have added to the staging area. By default, you will use a command-line based editor called *nano*. Go ahead and provide a description then press <kbd>Ctrl</kbd> + <kbd>x</kbd> to exit. Press <kbd>Y</kbd> to confirm that you want to make changes and then press <kbd>Enter</kbd>.
1. Let's push all changes to the Github repository using git's `push` command. Provide your Github username and password when you are asked.

    ```
    git push
    ```
1. When you finish the exercise, go back to Titanium and click on the `Add submission` button in the lab exercise page. Provide a short message in the text area such as "finished lab exercise" and click on `Save changes`. Finally click on `Submit assignment` to inform your instructor that you are done.

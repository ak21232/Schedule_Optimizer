#include <fstream>
#include <iostream>
#include <string>
#include "scheduler.hpp"

int main()
{
  int num_courses = 0;
  const int max_courses = 100;
  bool valid_format = true;
  std::string file_name;
  std::string display;
  // Updated based on Milestone 5
  CourseSchedule * course_sched;
  ScheduleManager sched_manager;

  std::cout << "Welcome to Tuffy Scheduler!\n";
  std::cout << "Please enter the file name containing the list of classes: ";
  std::cin >> file_name;
  course_sched = sched_manager.best_schedule(file_name);
  if (course_sched != nullptr)
  {
    std::cout << "The schedule below accommodates the most number of courses "
                 "without conflicts from the file you provided:\n";
    course_sched->display();
  }
  else
  {
    std::cout << "Invalid file.\n";
  }
  std::cout << "Thank you for using Tuffy Scheduler.\n";
  return 0;
}

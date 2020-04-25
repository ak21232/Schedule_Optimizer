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
  CourseSchedule course_sched;

  std::cout << "Welcome to Tuffy Scheduler!\n";
  std::cout << "Please enter the file name containing the list of classes: ";
  std::cin >> file_name;
  // Updated based on Milestone 5
  valid_format = load_schedule(file_name, course_sched);
  if (valid_format)
  {
    std::cout << "Schedule file loaded. Displaying contents ...\n";
    // Updated based on Milestone 5
    course_sched.display();
  }
  else
  {
    std::cout << "Invalid file.\n";
  }
  std::cout << "Thank you for using Tuffy Scheduler.\n";
  return 0;
}

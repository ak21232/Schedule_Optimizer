#include <fstream>
#include <iostream>
#include <string>
#include "scheduler.hpp"

// Updated based on Milestone 5
bool load_schedule(std::string file_name, CourseSchedule & course_sched)
{
  // define variables
  const int MAX_MINUTE = 59;
  const int MAX_HOUR = 24;
  bool valid_format = true;
  std::string filename;
  std::ifstream in_file;
  std::string course_name;
  std::string location;
  std::string day_of_week;
  int start_hour;
  int start_minute;
  int end_hour;
  int end_minute;
  int start_time;
  int end_time;
  // open file
  in_file.open(file_name);
  // validate file
  if (!in_file)
  {
    valid_format = false;
    std::cout << "Error: File does not exist - " << filename << ".\n";
  }
  else
  {
    while (getline(in_file, course_name) && valid_format)
    {
      // initialize the value for the colons in order to be able to verify
      // whether the colon is successfully read from the start and end times
      char start_colon = ' ';
      char end_colon = ' ';
      // validate contents
      if (course_name.empty())
      {
        valid_format = false;
        std::cout << "Error: Unable to get a course name.\n";
      }
      else if (!getline(in_file, location))
      {
        valid_format = false;
        std::cout << "Error: Unable to get a location.\n";
      }
      else if (location.empty())
      {
        valid_format = false;
        std::cout << "Error: Unable to get a location.\n";
      }
      else if (!getline(in_file, day_of_week))
      {
        valid_format = false;
        std::cout << "Error: Unable to get a weekly schedule.\n";
      }
      else if (day_of_week != "M" && day_of_week != "T" && day_of_week != "W" &&
               day_of_week != "H" && day_of_week != "F" && day_of_week != "S" &&
               day_of_week != "MW" && day_of_week != "MF" &&
               day_of_week != "TH")
      {
        valid_format = false;
        std::cout << "Error: Invalid weekly schedule symbol " << day_of_week
                  << std::endl;
      }
      // read the start time into 3 variables in order to check for valid hour
      // and minutes
      else if (!(in_file >> start_hour >> start_colon >> start_minute))
      {
        valid_format = false;
        std::cout << "Error: Unable to get a valid start time.\n";
      }
      else if (start_colon != ':' || start_hour < 0 || start_hour > MAX_HOUR ||
               start_minute < 0 || start_minute > MAX_MINUTE)
      {
        valid_format = false;
        std::cout << "Error: " << start_hour << start_colon
                  << ((start_minute < 10 && start_minute >= 0) ? "0" : "")
                  << start_minute << " is an invalid start time.\n";
      }
      // read the end time into 3 variables in order to check for valid hour
      // and minutes
      else if (!(in_file >> end_hour >> end_colon >> end_minute))
      {
        valid_format = false;
        std::cout << "Error: Unable to get a valid end time.\n";
      }
      else if (end_colon != ':' || end_hour < 0 || end_hour > MAX_HOUR ||
               end_minute < 0 || end_minute > MAX_MINUTE)
      {
        valid_format = false;
        std::cout << "Error: " << end_hour << end_colon
                  << ((end_minute < 10 && end_minute >= 0) ? "0" : "")
                  << end_minute << " is an invalid end time.\n";
      }
      // make sure the start time comes before the end time
      else if ((end_hour == start_hour && end_minute < start_minute) ||
               end_hour < start_hour)
      {
        valid_format = false;
        std::cout << "Error: The start time " << start_hour << start_colon
                  << ((start_minute < 10 && start_minute >= 0) ? "0" : "")
                  << start_minute << " should happen before the end "
                  << "time " << end_hour << end_colon
                  << ((end_minute < 10 && end_minute >= 0) ? "0" : "")
                  << end_minute << std::endl;
      }
      // convert the start and end times
      start_time = (start_hour * 100) + start_minute;
      end_time = (end_hour * 100) + end_minute;
      dynamically allocate memory set each value of the array with corresponding
          value course_sched.add(course_name, location, day_of_week, start_time,
                                 end_time);
      // move file pointer to the next line after having read an int
      in_file.ignore();
    }
    in_file.close();
  }
  std::cout << (valid_format ? "Valid" : "Invalid") << " file.\n";
  return valid_format;
}

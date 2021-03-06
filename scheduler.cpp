#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "scheduler.hpp"

// Functions for TimeSpan
bool TimeSpan::operator<(const TimeSpan & right) const
{
  if (end_time_ < right.start_time())
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool TimeSpan::operator>(const TimeSpan & right) const
{
  if (start_time_ > right.end_time())
  {
    return true;
  }
  else
  {
    return false;
  }
}

void TimeSpan::display()
{
  if (start_time_ % 100 == 0)
  {
    std::cout << "Start time: " << (start_time_ / 100) << ":"
              << (start_time_ % 100) << "0" << '\n'
              << "End time: " << (end_time_ / 100) << ":" << (end_time_ % 100)
              << '\n';
  }
  else if (end_time_ % 100 < 10)
  {
    std::cout << "Start time: " << (start_time_ / 100) << ":"
              << (start_time_ % 100) << '\n'
              << "End time: " << (end_time_ / 100) << ":0" << (end_time_ % 100)
              << '\n';
  }
  else if (end_time_ % 100 == 0)
  {
    std::cout << "Start time: " << (start_time_ / 100) << ":"
              << (start_time_ % 100) << '\n'
              << "End time: " << (end_time_ / 100) << ":"
              << "00" << '\n';
  }
  else if (start_time_ % 100 == 0 && end_time_ % 100 == 0)
  {
    std::cout << "Start time: " << (start_time_ / 100) << ":"
              << (start_time_ % 100) << "0" << '\n'
              << "End time: " << (end_time_ / 100) << ":"
              << "00" << '\n';
  }
  else
  {
    std::cout << "Start time: " << (start_time_ / 100) << ":"
              << (start_time_ % 100) << '\n'
              << "End time: " << (end_time_ / 100) << ":" << (end_time_ % 100)
              << '\n';
  }
}

// Functions for Course
void Course::display()
{
  if ((time_.start_time() % 100 == 0) && (time_.end_time() % 100 == 0))
  {
    std::cout << "Course name: " << course_name_ << '\n'
              << "Location: " << location_ << '\n'
              << "Weekly schedule: " << weekly_schedule_ << '\n'
              << "Start time: " << (time_.start_time() / 100) << ":"
              << (time_.start_time() % 100) << "0" << '\n'
              << "End time: " << (time_.end_time() / 100) << ":00" << '\n';
  }
  else if (time_.start_time() % 100 == 0)
  {
    std::cout << "Course name: " << course_name_ << '\n'
              << "Location: " << location_ << '\n'
              << "Weekly schedule: " << weekly_schedule_ << '\n'
              << "Start time: " << (time_.start_time() / 100) << ":"
              << (time_.start_time() % 100) << "0" << '\n'
              << "End time: " << (time_.end_time() / 100) << ":"
              << (time_.end_time() % 100) << '\n';
  }
  else if (time_.end_time() % 100 < 10)
  {
    std::cout << "Course name: " << course_name_ << '\n'
              << "Location: " << location_ << '\n'
              << "Weekly schedule: " << weekly_schedule_ << '\n'
              << "Start time: " << (time_.start_time() / 100) << ":"
              << (time_.start_time() % 100) << '\n'
              << "End time: " << (time_.end_time() / 100) << ":0"
              << (time_.end_time() % 100) << '\n';
  }
  else if (time_.end_time() % 100 == 0)
  {
    std::cout << "Course name: " << course_name_ << '\n'
              << "Location: " << location_ << '\n'
              << "Weekly schedule: " << weekly_schedule_ << '\n'
              << "Start time: " << (time_.start_time() / 100) << ":"
              << (time_.start_time() % 100) << '\n'
              << "End time: " << (time_.end_time() / 100) << ":00" << '\n';
  }
  else
  {
    std::cout << "Course name: " << course_name_ << '\n'
              << "Location: " << location_ << '\n'
              << "Weekly schedule: " << weekly_schedule_ << '\n'
              << "Start time: " << (time_.start_time() / 100) << ":"
              << (time_.start_time() % 100) << '\n'
              << "End time: " << (time_.end_time() / 100) << ":"
              << (time_.end_time() % 100) << '\n';
  }
}

bool Course::intersects(Course * other) const
{
  bool overlap = false;

  // check whether the two courses have a day in common
  // e.g. MW course and W course have W in common
  for (char ch1 : weekly_schedule_)
  {
    for (char ch2 : other->weekly_schedule())
    {
      if (ch1 == ch2)
      {
        overlap = true;
        break;
      }
    }
  }
  // if the courses are have a day in common, check whether their times
  // overlap
  if (overlap)
  {
    if (time_ < other->time() || time_ > other->time())
    {
      overlap = false;
    }
  }
  return overlap;
}

// Functions for CourseSchedule
bool CourseSchedule::add(std::string course_name, std::string course_location,
                         std::string day, int start_time, int end_time)
{
  bool valid = false;

  courses_[num_courses_] = new Course;
  (*(courses_ + num_courses_))->set_course_name(course_name);
  (*(courses_ + num_courses_))->set_location(course_location);
  (*(courses_ + num_courses_))->set_weekly_schedule(day);
  (*(courses_ + num_courses_))->set_time(TimeSpan(start_time, end_time));
  if (!remove_conflicts_ || !(has_conflict(*(courses_ + num_courses_))))
  {
    num_courses_++;
    valid = true;
  }
  else
  {
    delete courses_[num_courses_];
    courses_[num_courses_] = nullptr;
    valid = false;
  }
  return valid;
}

void CourseSchedule::display()
{
  if ((*(courses_)) != nullptr)
  {
    for (int i = 0; i < num_courses_; i++)
    {
      ((*(courses_ + i)))->display();
    }
  }
}

// Functions for ScheduleManager

bool ScheduleManager::load_schedule(std::string file_name)
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
      // dynamically allocate memory set each value of the array with
      // corresponding value
      complete_schedule_.add(course_name, location, day_of_week, start_time,
                             end_time);

      // move file pointer to the next line after having read an int
      in_file.ignore();
    }
    in_file.close();
  }
  std::cout << (valid_format ? "Valid" : "Invalid") << " file.\n";
  return valid_format;
}

CourseSchedule * ScheduleManager::best_schedule(std::string file_name)
{
  bool loaded = load_schedule(file_name);
  if (!loaded)
  {
    return nullptr;
  }
  else
  {
    int number_of_courses = complete_schedule_.num_courses();
    Course * arr[number_of_courses];
    int track = 0;
    if (best_schedule_ != nullptr)
    {
      track = best_schedule_->num_courses();
    }
    for (int i = 0; i < number_of_courses; i++)
    {
      arr[i] = complete_schedule_.course(i);
    }
    do
    {
      CourseSchedule * obj = new CourseSchedule;
      for (int k = 0; k < number_of_courses; k++)
      {
        obj->add(arr[k]);
      }
      if (track < obj->num_courses())
      {
        track = obj->num_courses();
        delete best_schedule_;
        best_schedule_ = obj;
      }
      else
      {
        delete obj;
        obj = nullptr;
      }
    } while (std::next_permutation(arr, arr + number_of_courses));
  }
  return best_schedule_;
}

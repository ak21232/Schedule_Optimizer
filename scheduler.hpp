#include <iostream>
#include <iomanip>

// Updated class based on Milestone 5
class TimeSpan
{
protected:
  int start_time_;
  int end_time_;

public:
  TimeSpan() : start_time_(0000), end_time_(0000) {}

  TimeSpan(int start_time, int end_time)
      : start_time_(start_time), end_time_(end_time)
  {
  }
  void set_start_time(int start_time) { start_time_ = start_time; }
  void set_end_time(int end_time) { end_time_ = end_time; }
  int start_time() { return start_time_; }
  int end_time() { return end_time_; }
  bool operator<(TimeSpan right)
  {
    if (end_time_ < right.start_time())
    {
      return true;
    }
    else
    {
      return false;
    };
  }
  bool operator>(TimeSpan right)
  {
    if (start_time_ > right.end_time())
    {
      return true;
    }
    else
    {
      return false;
    };
  }

  void display()
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
                << "End time: " << (end_time_ / 100) << ":0"
                << (end_time_ % 100) << '\n';
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
};

// Updated class based on Milestone 5
class Course
{
protected:
  std::string course_name_;
  std::string location_;
  std::string weekly_schedule_;

  TimeSpan time_;
  int start_hour_;
  int start_minute_;
  int end_hour_;
  int end_minute_;

public:
  Course()
      : course_name_(""), location_(""), weekly_schedule_(""), time_(TimeSpan())
  {
  }

  Course(std::string course_name, std::string location,
         std::string weekly_schedule, TimeSpan time_span)
  {
    course_name_ = course_name;
    location_ = location;
    weekly_schedule_ = weekly_schedule;
    time_ = time_span;
  }
  void set_course_name(std::string course_name) { course_name_ = course_name; }
  void set_location(std::string location) { location_ = location; }
  void set_weekly_schedule(std::string weekly_schedule)
  {
    weekly_schedule_ = weekly_schedule;
  }

  void set_time(TimeSpan time) { time_ = time; }
  std::string course_name() { return course_name_; }
  std::string location() { return location_; }
  std::string weekly_schedule() { return weekly_schedule_; }

  TimeSpan time() { return time_; }
  void display()
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
    };
  }

  bool intersects(Course * course)
  {
    bool intersects = false;
    if ((time_.start_time() <= course->time().start_time()) &&
        (course->time().start_time() <= time_.end_time()) &&
        (course->weekly_schedule() == weekly_schedule_))
    {
      intersects = true;
    }
    else if ((time_.start_time() <= course->time().end_time()) &&
             (course->time().end_time() <= time_.end_time()) &&
             (course->weekly_schedule() == weekly_schedule_))
    {
      intersects = true;
    }
    return intersects;
  }
};

// Updated class based on Milestone 5
class CourseSchedule
{
private:
  Course * courses_[100];
  int num_courses_;
  bool has_conflict(Course * course)
  {
    bool conflict = false;
    for (int i = 0; i < num_courses_; i++)
    {
      if ((*(courses_ + i))->intersects(course))
      {
        conflict = true;
      }
    }
    return conflict;
  }
  bool remove_conflicts_;

public:
  CourseSchedule() : CourseSchedule(true) {}
  CourseSchedule(bool remove_conflicts) :remove_conflicts_(remove_conflicts), num_courses_(0) {}
  int num_courses() { return num_courses_; }
  bool add(std::string course_name, std::string course_location,
           std::string day, int start_time, int end_time)
  {
    if (remove_conflicts_)
    {
      courses_[num_courses_] = new Course;
      (*(courses_ + num_courses_))->set_course_name(course_name);
      (*(courses_ + num_courses_))->set_location(course_location);
      (*(courses_ + num_courses_))->set_weekly_schedule(day);
      (*(courses_ + num_courses_))->set_time(TimeSpan(start_time, end_time));
      if (!(has_conflict(*(courses_ + num_courses_))))
      {
        num_courses_++;
        return true;
      }
      else
      {
        delete courses_[num_courses_];
        return false;
      }
    }
    else if (!remove_conflicts_)
    {
      courses_[num_courses_] = new Course;
      (*(courses_ + num_courses_))->set_course_name(course_name);
      (*(courses_ + num_courses_))->set_location(course_location);
      (*(courses_ + num_courses_))->set_weekly_schedule(day);
      (*(courses_ + num_courses_))->set_time(TimeSpan(start_time, end_time));
      num_courses_++;
      return true;
    }

  }
  bool add(Course * cptr)
  {
    cptr.add(cptr->course_name(), cptr->location(), cptr->weekly_schedule(),cptr->time().start_time(),cptr->time().end_time());
  }
  Course * course(int array_element)
  {
    return courses_array_[array_element + 1];
  }
  void display()
  {
    for (int i = 0; i < num_courses_; i++)
    {
      courses_[i]->display();
    }
  }
  ~CourseSchedule()
  {
    for (int i = 0; i < num_courses_; i++)
    {
      delete courses_[i];
    }
  }
};

// Milestone 6 Schedule Manager
class ScheduleManager
{
private:
  CourseSchedule complete_schedule_;
  CourseSchedule best_schedule_;
  bool load_schedule(std::string file_name);
public:
  ScheduleManager() : complete_schedule_(CourseSchedule(false)), best_schedule_(nullptr) {}
  CourseSchedule * best_schedule(std::string file_name);
  ~CourseSchedule()
  {
    if (best_schedule_ != nullptr)
    {
      delete best_schedule_;
    }
  }
}


// Updated class based on Milestone 5

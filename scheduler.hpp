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
  int start_time() const { return start_time_; }
  int end_time() const { return end_time_; }
  bool operator<(const TimeSpan & right) const;
  bool operator>(const TimeSpan & right) const;
  void display();
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
  void display();
  bool intersects(Course * other) const;
};

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
  CourseSchedule(bool remove_conflicts)
      : remove_conflicts_(remove_conflicts), num_courses_(0)
  {
  }
  CourseSchedule() : CourseSchedule(true) {}
  int num_courses() { return num_courses_; }
  bool add(std::string course_name, std::string course_location,
           std::string day, int start_time, int end_time);
  bool add(Course * cptr)
  {
    bool check;
    check = add((cptr)->course_name(), (cptr)->location(),
                (cptr)->weekly_schedule(), (cptr)->time().start_time(),
                (cptr)->time().end_time());
    return check;
  }
  Course * course(int array_element) { return courses_[array_element]; }
  void display();
  ~CourseSchedule()
  {
    for (int i = 0; i < num_courses_; i++)
    {
      delete courses_[i];
    }
  }
};

class ScheduleManager
{
private:
  CourseSchedule complete_schedule_;
  CourseSchedule * best_schedule_;
  bool load_schedule(std::string file_name);

public:
  ScheduleManager() : complete_schedule_(false), best_schedule_(nullptr) {}
  CourseSchedule * best_schedule(std::string file_name);
  ~ScheduleManager()
  {
    if (best_schedule_ != nullptr)
    {
      delete best_schedule_;
    }
  }
};

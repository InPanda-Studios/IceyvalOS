struct Task
{
      int priority;
      int taskid;
      char ca1[256];
      char text[256];
      int i1;
      char equater[2];
      int (*function) (int);

};
struct Task tasks[256];
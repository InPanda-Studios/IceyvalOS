#include "graphics.hpp"
extern "C" int start()
{
    VBEInfoBlock* VBE = (VBEInfoBlock* )VBEInfoAddress;
    mx = VBE->x_resolution /2;
    my = VBE->y_resolution /2;
    char str[] = "Welcome To IceValley OS,\nMade By Filip And Xing!";
    char* p = str;
    char charbuffer[1000] = "\0";
    char* charbuffpointer = charbuffer;
    int charbufflen = 0;
    base = (unsigned int) &isr1;
    base12 = (unsigned int) &isr12;
    InitialiseMouse();
    InitialiseIDT();
    mainFile.isDir = false;
    mainFile.openable = true;
    tasks[TasksLength].priority = 0;
    tasks[TasksLength].function = &ClearScreenTask;
    TasksLength++;
    tasks[TasksLength].priority = 0;
    tasks[TasksLength].function = &TaskBarTask;
    tasks[TasksLength].taskid = TasksLength;
    iparams[TasksLength * task_params_length + 0] = 0;
    iparams[TasksLength * task_params_length + 1] = VBE->y_resolution - 40;
    iparams[TasksLength * task_params_length + 2] = VBE->x_resolution;
    iparams[TasksLength * task_params_length + 3] = 40;
    iparams[TasksLength * task_params_length + 4] = 1;
    TasksLength++;
    tasks[TasksLength].priority = 5;
    tasks[TasksLength].function = &DrawMouseTask;
    TasksLength++;
    while(1)
    {
        ProcessTasks();
        Flush();
    }
}
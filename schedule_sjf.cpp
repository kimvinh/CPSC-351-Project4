/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 4: Scheduling Algorithms
*/

#include <iostream>
#include <tuple>
#include <list>
#include <vector>
#include "schedulers.h"

using std::cout;
using std::endl;

void ScheduleSJF::schedule(CPU *cpu) {
  cout << "ScheduleSJF::schedule()" << endl;

  const int numberOfTasks = tasks[0]->size();

  // Initialize the integer vector to store the value of each task's burst in the list
  vector<int> burstTime;

  // Run and show tasks from the list
  while(!tasks[0]->empty()) {
    Task *taskToRun = pickNextTask();
    cpu->run(taskToRun, taskToRun->burst);

    // Store the burst time of the task into the array
    burstTime.push_back(taskToRun->burst);

    for (list<Task *> *queue : tasks)
        for (Task *task : *queue)
          if(task == taskToRun)
            delete task;
    tasks[0]->remove(taskToRun);
  }

  // Initialize the integer vector to store the value of eack task's waiting time in the list
  vector<int> waitingTime;
  // The waiting time of the first task is always equal to 0
  waitingTime.push_back(0);
  int totalWaitingTime = 0;
  double avgWaitingTime;

  // Initialize the integer vector to store the value of eack task's turnaround time in the list
  vector<int> turnAroundTime;
  int totalTurnAroundTime = 0;
  double avgTurnAroundTime;

  // Calculate the waiting time of each task in the list
  // and store it into the vector
  for (int i = 1; i < numberOfTasks; i++) {
    waitingTime.push_back(burstTime[i - 1] + waitingTime[i - 1]);
  }

  // Calculate the turnaround time of each task in the list
  // and store it into the vector
  for (int i = 0; i < numberOfTasks; i++) {
    turnAroundTime.push_back(burstTime[i] + waitingTime[i]);
  }

  for (int i = 0; i < numberOfTasks; i++) {
    // Calculate the total of waiting times of all tasks in the list
    totalWaitingTime += waitingTime[i];
    // Calculate the total of turnaround times of all tasks in the list
    totalTurnAroundTime += turnAroundTime[i];
  }

  // Initialize the total response time of all tasks in the list
  // Since the arrival time of all task is 0, SJF in this case is non-preemptive.
  // Therefore, total response time is equal to total waiting time
  int totalResponseTime = totalWaitingTime;
  double avgResponseTime;

  // Calculate the average waiting time
  avgWaitingTime = (double) totalWaitingTime / (double) numberOfTasks;
  // Calculate the average turnaround time
  avgTurnAroundTime = (double) totalTurnAroundTime / (double) numberOfTasks;
  // Calculate the average response time
  avgResponseTime = (double) totalResponseTime / (double) numberOfTasks;
  // Display the average values on the screen
  cout << "Average Waiting Time = " << avgWaitingTime << endl;
  cout << "Average Turnaround Time = " << avgTurnAroundTime << endl;
  cout << "Average Response Time = " << avgResponseTime << endl;
}

Task *ScheduleSJF::pickNextTask() {
  int lowest_burst = tasks[0]->front()->burst;

  Task *taskToReturn;

  // Find the lowest burst time from tasks in the list
  for (list<Task *> *queue : tasks) {
    for (Task *task : *queue) {
      if (task->burst < lowest_burst) {
        lowest_burst = task->burst;
      }
    }
  }

  // Get the lowest burst time task in the list
  for (list<Task *> *queue : tasks) {
    for (Task *task : *queue) {
      if(task->burst == lowest_burst) {
        taskToReturn = task;
        break;
      }
    }
  }
  return taskToReturn;
}

Scheduler *create() {
  return new ScheduleSJF;
}

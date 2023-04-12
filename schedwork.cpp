#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fill(const AvailabilityMatrix& avail,
              const size_t dailyNeed,
              const size_t maxShifts,
              DailySchedule& sched,
              vector<Worker_T>& numShifts,
              const size_t day,
              const size_t number);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //constructs the schedule 2d array
    for (size_t i = 0; i < avail.size(); i++) {
      vector<Worker_T> toAdd(dailyNeed);
      sched.push_back(toAdd);
    }


    //this will keep track of the number of shifts
    //each worker has done so far
    vector<Worker_T> numShifts(avail[0].size());
    for (size_t i = 0; i < avail[0].size(); i++) {
      numShifts[i] = 0;
    }

  return fill(avail, dailyNeed, maxShifts, sched, numShifts, 0, 0);
}

bool fill(const AvailabilityMatrix& avail,
          const size_t dailyNeed,
          const size_t maxShifts,
          DailySchedule& sched,
          vector<Worker_T>& numShifts,
          const size_t day,
          const size_t number) {
    //true if everything is filled up and the day is out of bounds
    if (day == avail.size()) {
      return true;
    }

    //iterates through availability for that day
    //i represents the worker ID
    for (size_t i = 0; i < avail[day].size(); i++) {
      if (avail[day][i] && numShifts[i] < maxShifts) {
        sched[day][number] = i;
        numShifts[i] = numShifts[i] + 1;
        bool status = false;

        if (number == dailyNeed - 1) {
          status = fill(avail, dailyNeed, maxShifts, sched, numShifts, day + 1, 0);
        }
        else {
          status = fill(avail, dailyNeed, maxShifts, sched, numShifts, day, number + 1);
        }

        if (status) {
          return true;
        }

        sched[day][number] = -1;
        numShifts[i] = numShifts[i] - 1;
      }
    }

    return false;
}




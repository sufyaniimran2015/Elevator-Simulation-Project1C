#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <queue>

// This is one request made by a person using the elevator
struct Request {
    int timeRequested;     // The time they pushed the button
    int sourceFloor;       // What floor they are on
    int destinationFloor;  // Where they want to go
    bool goingUp;          // Are they going up?
    int id;                // ID number to keep track

    Request(int t, int src, int dst, int reqId)
        : timeRequested(t), sourceFloor(src), destinationFloor(dst),
          goingUp(dst > src), id(reqId) {}
};

// Elevator class to handle one elevator
class Elevator {
public:
    Elevator(int id, int startFloor = 0);       // Constructor to set ID and start floor
    void addRequest(const Request& req);        // Add a new request to the queue
    void step(int currentTime);                 // Move elevator and check requests
    bool isIdle() const;                        // Returns true if nothing to do
    int getWaitingTimeSum() const;              // Total waiting time for all users

private:
    int id;                                     // Elevator number
    int currentFloor;                           // Where the elevator is
    int direction;                              // 1 = up, -1 = down, 0 = idle
    std::queue<Request> queue;                  // All waiting requests
    std::vector<Request> inside;                // Users currently inside the elevator
    int totalWaitingTime;                       // Total wait time counter

    void handleInside(int currentTime);         // Handles drop-offs and direction
};

#endif

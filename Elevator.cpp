#include "Elevator.h"
#include <iostream>

using namespace std;

Elevator::Elevator(int id, int startFloor)
    : id(id), currentFloor(startFloor), direction(0), totalWaitingTime(0) {}

void Elevator::addRequest(const Request& req) {
    queue.push(req);
}

// Checks if elevator is doing nothing
bool Elevator::isIdle() const {
    return queue.empty() && inside.empty();
}

// One time step - move and process
void Elevator::step(int currentTime) {
    if (isIdle()) return;

    // If new request waiting, move them inside
    if (!queue.empty()) {
        inside.push_back(queue.front());
        queue.pop();
    }

    handleInside(currentTime);
}

// Handles the movement and dropping off users
void Elevator::handleInside(int currentTime) {
    if (inside.empty()) return;

    // Go to the first user's destination
    int target = inside.front().destinationFloor;
    direction = (target > currentFloor) ? 1 : (target < currentFloor ? -1 : 0);

    currentFloor += direction; // Move elevator

    vector<Request> stillInside;
    for (Request& r : inside) {
        if (r.destinationFloor == currentFloor) {
            totalWaitingTime += currentTime - r.timeRequested;
            cout << "[Elevator " << id << "] Delivered user " << r.id
                 << " to floor " << currentFloor << " at time " << currentTime << "\n";
        } else {
            stillInside.push_back(r);
        }
    }
    inside = stillInside;

    if (inside.empty() && queue.empty()) direction = 0;
}

int Elevator::getWaitingTimeSum() const {
    return totalWaitingTime;
}


#include "Elevator.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Simulate elevators running over time
void simulate(int totalTime, int numElevators, int numFloors, int requestChancePercent) {
    vector<Elevator> elevators;
    for (int i = 0; i < numElevators; ++i)
        elevators.emplace_back(i);

    int requestId = 0;

    for (int time = 0; time < totalTime; ++time) {
        // Randomly create a new request
        if (rand() % 100 < requestChancePercent) {
            int from = rand() % numFloors;
            int to;
            do {
                to = rand() % numFloors;
            } while (to == from);

            Request req(time, from, to, requestId++);

            // Give it to an idle elevator if possible
            int best = 0;
            for (int i = 1; i < elevators.size(); ++i) {
                if (elevators[i].isIdle()) {
                    best = i;
                    break;
                }
            }

            elevators[best].addRequest(req);
            cout << "[Time " << time << "] New request " << req.id << ": Floor "
                 << from << " -> " << to << " assigned to Elevator " << best << "\n";
        }

        // Each elevator moves
        for (Elevator& e : elevators) {
            e.step(time);
        }
    }

    // Final stats
    int totalWait = 0;
    for (Elevator& e : elevators)
        totalWait += e.getWaitingTimeSum();

    cout << "\n--- Simulation Done ---\n";
    cout << "Total waiting time: " << totalWait << "\n";
    cout << "Average wait per request: " << (requestId ? totalWait / requestId : 0) << "\n";
}

int main() {
    srand(time(0)); // Make random work differently each time

    // Run the simulation: 100 seconds, 2 elevators, 10 floors, 20% chance of new request
    simulate(100, 2, 10, 20);

    return 0;
}

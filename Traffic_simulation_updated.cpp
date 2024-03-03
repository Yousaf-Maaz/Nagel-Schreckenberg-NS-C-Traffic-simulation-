/*
Explanation of Changes:

1.Increased the acceleration probability (new_acceleration_p) to make vehicles accelerate faster.
2.Increased the randomization probability (new_p) to make vehicles change speed more frequently.
3.Adjusted the acceleration values to reflect the increased acceleration probability.

Results:

-The vehicles should accelerate more quickly and change speeds more frequently,
 resulting in a more dynamic and potentially chaotic traffic flow.
-Observe how the changes affect the traffic pattern, speed fluctuations,
and overall behavior of vehicles in the simulation.



*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

const int length = 20;
const double density = 0.3;
const int v_max = 5;
const double p = 0.1;
const int iterations = 20;

// Increase acceleration and randomization probabilities
const double new_p = 0.2;
const double new_acceleration_p = 0.8;

void initializeRoad(vector<int> &road)
{
    int numCars = static_cast<int>(length * density);

    for (int i = 0; i < numCars; ++i)
    {
        int position = rand() % length;
        road[position] = rand() % (v_max + 1);
    }
}

void printRoad(const vector<int> &road)
{
    for (int cell : road)
    {
        if (cell == -1)
        {
            cout << ".";
        }
        else
        {
            cout << cell;
        }
    }
    cout << endl;
}

void updateRoad(vector<int> &road)
{
    for (int i = 0; i < length; ++i)
    {
        if (road[i] != -1)
        {
            // Increase acceleration probability
            if ((rand() / static_cast<double>(RAND_MAX)) < new_acceleration_p)
            {
                road[i] = min(road[i] + 2, v_max); // Increase acceleration
            }
            else
            {
                road[i] = min(road[i] + 1, v_max); // Standard acceleration
            }

            // Deceleration
            for (int j = 1; j <= road[i]; ++j)
            {
                if (road[(i + j) % length] != -1)
                {
                    road[i] = j - 1;
                    break;
                }
            }

            // Increase randomization probability
            if ((rand() / static_cast<double>(RAND_MAX)) < new_p)
            {
                road[i] = max(road[i] - 2, 0); // Increase randomization
            }
        }
    }

    // Move vehicles
    vector<int> newRoad(length, -1);
    for (int i = 0; i < length; ++i)
    {
        if (road[i] != -1)
        {
            newRoad[(i + road[i]) % length] = road[i];
        }
    }
    road = newRoad;
}

void sleepMilliseconds(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void simulateTraffic()
{
    vector<int> road(length, -1);
    initializeRoad(road);

    for (int i = 0; i < iterations; ++i)
    {
        printRoad(road);
        updateRoad(road);
        sleepMilliseconds(500);
        clearConsole();
    }
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    simulateTraffic();
    return 0;
}

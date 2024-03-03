/*
The program simulates traffic flow on a one-dimensional road using
the Nagel-Schreckenberg model. The output consists of a series of lines representing
the state of the road at each iteration. Each cell on the road
is either empty (denoted by a dot .) or contains a vehicle with a velocity.

During each iteration, vehicles accelerate, decelerate based on the distance to the nearest vehicle,
and occasionally randomize their speed. The simulation provides a visual representation of how traffic
evolves over time.

You can observe changes in the traffic pattern, speed fluctuations, and interactions
between vehicles as the simulation progresses.

*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Platform-specific includes
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
            // Acceleration
            road[i] = min(road[i] + 1, v_max);

            // Deceleration
            for (int j = 1; j <= road[i]; ++j)
            {
                if (road[(i + j) % length] != -1)
                {
                    road[i] = j - 1;
                    break;
                }
            }

            // Randomization
            if ((rand() / static_cast<double>(RAND_MAX)) < p)
            {
                road[i] = max(road[i] - 1, 0);
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
    usleep(milliseconds * 1000); // Convert milliseconds to microseconds
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
        sleepMilliseconds(500); // Sleep for 500 milliseconds
        clearConsole();         // Clear console (platform-specific)
    }
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    simulateTraffic();
    return 0;
}

/*
Last Date Modified: 1/9/2024

Description:

This file includes the functions in the derived class, including calculating the electric field in x, y , and z direction
, assigning jobs to threads, and acquiring the final result of the electric field for the object.

*/
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <mutex>
#include <pthread.h>
#include <atomic>
#include <cmath>
#include "ECE_ElectricField.h"

using namespace std;

void ECE_ElectricField::computeFieldAt(double x, double y, double z, int i)
{
    // Compute the value of the electric filed, and it will accumulated. 
    double r = sqrt(((x * x) + (y * y) + (z * z)));
    double r1 = r * r * r; 
    out1[i] = ((kConstant*(x))/(r1)) + out1[i]; // For Electric field in x-direction 
    out2[i] = ((kConstant*(y))/(r1)) + out2[i]; // For Electric field in y-direction 
    out3[i] = ((kConstant*(z))/(r1)) + out3[i]; // For Electric field in z-direction 
}

void ECE_ElectricField::getElectricField(double &Ex, double &Ey, double &Ez)
{
    // This function can help the object to get the value of the electric field.
    outputEx = Ex;
    outputEy = Ey;
    outputEz = Ez;
}

void ECE_ElectricField::calculationElectricField(int n)
{
    Ex = 0;
    Ey = 0;
    Ez = 0;

    n = n -1;
    int totalPoints = getTotalQ();
    int pointsPerThread = totalPoints / n; // Number of points to be processed by each thread
    int remainingPoints = totalPoints % n; // Remaining data points
    kConstant = k * getCharge();

    // Clear the temporary space for the calculation of the electric field.
    for (int j = 0; j < n; j++)
    {
        out1.push_back(0);
        out2.push_back(0);
        out3.push_back(0);
    }

    vector<thread> threads;
    // Here, we average the number of charge points to each thread, and if there is more, they will be put to last thread.
    int startIndex = 0;
    for (int i = 0; i < n; ++i)
    {
        int extraPoint = (i < remainingPoints) ? 1 : 0;
        int endIndex = startIndex + pointsPerThread + extraPoint;

        threads.emplace_back([this, startIndex, endIndex, i]() 
        {
            for (int j = startIndex; j < endIndex; ++j)
            {
                computeFieldAt(v1[j], v2[j], getDirectionZ(), i);
            }
        });

        for (thread& t : threads) 
        {
            if (t.joinable()) 
            {
                t.join();
            }
        }

        startIndex = endIndex;
    }
    
    // Add up all values of the electric field in x, y, and z direction.
    for (int i = 0; i < n; i++)
    {
        Ex = out1[i] + Ex;
        Ey = out2[i] + Ey;
        Ez = out3[i] + Ez;
    }
    
    getElectricField(Ex,Ey,Ez);
}


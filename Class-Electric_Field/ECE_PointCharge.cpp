/*
Last Date Modified: 1/9/2024

Description:

This file includes the functions in base class, including set the location of all charges,
setting and getting the value iof charge, checking whether the target point is at one of charges, 
setting the variables of N, M, separation of x-direction and y-direction, and the total charges.

*/
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ECE_PointCharge.h"

using namespace std;

void ECE_PointCharge::setLocation(double x, double y, double z)
{
    double positionX = 0;
    double positionY = 0;
    double positionZ = 0;
    zDirection = z;
    // x is N, y is M
    v1.clear();
    v2.clear();


    // This 2-level for-loop will calculate the position of the charge, 
    // and then it calculate the difference between the charge and target points in x and y direction.
    // This function will split the position into x and y direction respectively.
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            // For if-statement, if it is even number, need to use this part to get the x value of top-left point, 
            // and it will go through the whole row using (separationX * j).
            // For else-statement, if it is odd number, use this part to get the x value of top-left point, 
            // and it will go through the whole row using (separationX * j).
            if (N % 2 == 0)
            {
                positionX = (-1)*((((N / 2) - 1) * separationX) + (separationX/2)) + (separationX * j);
            }
            else
            {
                positionX = (-1)*((((N - 1) / 2) * separationX)) + (separationX * j);
            }

            positionX = x - positionX;
            
            // For if-statement, if it is even number, need to use this part to get the y value of top-left point, 
            // and it will go through the whole row using (separationY * i).
            // For else-statement, if it is odd number, use this part to get the x value of top-left point, 
            // and it will go through the whole row using (separationY * i).
            if (M % 2 == 0)
            {
                positionY = ((((M / 2) - 1) * separationY) + (separationY/2)) - (separationY * i);
            }
            else
            {
                positionY = (((M - 1) / 2) * separationY) - (separationY * i);
            }

            positionY = y - positionY;


            // Check whether any charge has the same value as the target point.
            positionZ = z;
            if(checkPositionMatch(positionX, positionY, positionZ) == 1)
            {
                break;
            }

            // Save the postion of x and y coordinates, which are already deducted with target point, in vector respectively.
            v1.push_back(positionX);
            v2.push_back(positionY);


        }
        if(checkPositionMatch(positionX, positionY, positionZ) == 1)
        {
            break;
        }
    }
}

void ECE_PointCharge::setSizeSeparation(int sizeN, int sizeM, double dX, double dY)
{
    // Save the value of variables from main.cpp 
    N = sizeN;
    M = sizeM;
    separationX = dX;
    separationY = dY;
}

double ECE_PointCharge::getDirectionZ()
{
    // Use this function to return the value of z-coordinate
    return zDirection;
}

void ECE_PointCharge::setCharge(double q)
{
    // Save the value of charge from main.cpp and change it into mC.
    qCharge = q * pow(10, -6);
}

double ECE_PointCharge::getCharge()
{
    // Get the value of charge
    return qCharge;
}

int ECE_PointCharge::getTotalQ()
{
    // Get the total number of charge.
    totalCharge = N * M;
    return totalCharge;
}

int ECE_PointCharge::checkPositionMatch(double x, double y, double z)
{
    // If all positions in x, y ,and z are no difference, which equals to 0 and return true, and that means 
    // the target point has same coordinates of a charge.
    double alpha = 1e-6;
    qPositionMatch = 0;
    if ((abs(x) < alpha) && (abs(y) < alpha) && (abs(z) < alpha))
    { 
        qPositionMatch = 1;
        return 1;
    }
    return 0;
}

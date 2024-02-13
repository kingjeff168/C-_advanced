/*
Last Date Modified: 1/9/2024

*/
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <cctype>

#include "ECE_ElectricField.h"

using namespace std;

vector<string> vInputChargeDimension;
vector<string> vInputSeparationCharge;
vector<string> vInputCharge;
vector<string> vInputTargetLocation;


void splitInput(const string& input, char space, vector<string>& results)
{
    // This function splits the input through detecting the space, and it puts every piece of string in the vector.
    bool isInteger = true;
    if (input.empty())
    {
        isInteger = false;
    }
    else
    {
        string token;
        istringstream tokenStream(input);

        while (getline(tokenStream, token, space)) 
        {
            results.push_back(token);
        }
    }

}
bool isPositiveInteger(const string& str) 
{
    // This for-loop is to check if the input is an integer.
    for (char c : str) 
    {
        if (!isdigit(c)) 
        {
            return false;
        }
    }
    return true;
}

bool isValidInput(const string& str) 
{
    // This for-loop is to check if the input has char or other invalid things than numbers.      
    istringstream iss(str);
    double value;
    
    if (str.empty()) 
    {
        return false;
    }

    iss >> noskipws >> value;

    if (!iss.fail() && iss.eof()) 
    {
        return true;
    }
    return false;
}


void convertToScientificNotation(double input, double & number, int & exponent) 
{
    exponent = 0;
    number = input;

    // This function is to convert numbers to scientific notation.
    // It will check the number, if it is bigger than 10, it will be divided, and the exponent will be added up until it is smaller than 10.
    // if input is zero, all variable should be 0.
    // If the number is smaller than 1, it will be multiplied, and the exponent will be deducted until it is bigger than 1.
    if (abs(input) >= 1) 
    {
        while (abs(number) >= 10.0) 
        {
            number /= 10.0;
            exponent++;
        }
    }
    else if (input == 0)
    {
        number = 0;
    }
    else 
    {
        while (abs(number) < 1.0) 
        {
            number *= 10.0;
            exponent--;
        }
    }

    number = round(number * 10000) / 10000;
}


int main()
{
    string inputArray, inputSeparation, inputCharge, inputLocation, inputYesNo;
    double numberX, numberY, numberZ, numberTotal, dX, dY, xPosition, yPosition, zPosition;
    double sCharge;
    int exponentX, exponentY, exponentZ, exponentTotal;
    uint64_t N, M;
    char cSpace = ' ';
    ECE_ElectricField e1;


    unsigned int n = thread::hardware_concurrency();
    cout << "Your computer supports " << n << " concurrent threads." << endl;

// From here, users enter the variables they want.

    while (1)
    {
        while (1)
        {
            // This while loop is to check if the user enter right number of arguments of N and M.
            cout << "Please enter the number of rows and columns in the N x M array: ";
            getline(cin, inputArray);
            if (inputArray.length() == 0)
            {
                cout << "Invalid input!" << endl; 
            }
            else
            {
                splitInput(inputArray, cSpace, vInputChargeDimension);
                if (vInputChargeDimension.size() == 2)
                {
                    if ((isPositiveInteger(vInputChargeDimension[0]) == true) && (isPositiveInteger(vInputChargeDimension[1]) == true))
                    {
                        // If the input is passed, it will check whether the N or M is 0 because it is invalid.
                        N = stoi(vInputChargeDimension[0]);
                        M = stoi(vInputChargeDimension[1]);
                        if ((N == 0) || (M == 0))
                        {
                            vInputChargeDimension.clear();
                            inputArray.clear();
                            cout << "Invalid input!" << endl; 
                        }
                        else
                        {
                            // If the input is passed all, it will leave the loop.
                            break;
                        }
                    }
                    else
                    {
                        vInputChargeDimension.clear();
                        inputArray.clear();
                        cout << "Invalid input!" << endl;
                    }
                }
                else
                {
                    vInputChargeDimension.clear();
                    inputArray.clear();
                    cout << "Invalid input!" << endl;
                }
            }
        }

        while (1)
        {
            cout << "Please enter the x and y separation distances in meters: ";
            getline(cin, inputSeparation);
            if (inputSeparation.length() == 0)
            {
                cout << "Invalid input!" << endl; 
            }
            else
            {
                splitInput(inputSeparation, cSpace, vInputSeparationCharge);
                if (vInputSeparationCharge.size() == 2)
                {
                    // If the input is passed, it will check whether the x or y separation is smaller than 0 because it is invalid.
                    if ((isValidInput(vInputSeparationCharge[0]) == true) && (isValidInput(vInputSeparationCharge[1]) == true))
                    {
                        dX = stod(vInputSeparationCharge[0]);
                        dY = stod(vInputSeparationCharge[1]);
                        if ((dX <= 0) || (dY <= 0))
                        {
                            vInputSeparationCharge.clear();
                            inputSeparation.clear();
                            cout << "Invalid input!" << endl;
                        }
                        else
                        {
                            // If the input is passed all, it will leave the loop.
                            break;
                        }
                    }
                    else
                    {
                        vInputSeparationCharge.clear();
                        inputSeparation.clear();
                        cout << "Invalid input!" << endl;
                    }
                }
                else
                {
                    vInputSeparationCharge.clear();
                    inputSeparation.clear();
                    cout << "Invalid input!" << endl;
                }
            }
        }
        
        while (1)
        {
            cout << "Please enter the common charge on the points in micro C: ";
            getline(cin, inputCharge);
            if (inputCharge.length() == 0)
            {
                inputCharge.clear();
                cout << "Invalid input!" << endl; 
            }
            else
            {
                splitInput(inputCharge, cSpace, vInputCharge);
                if (vInputCharge.size() == 1)
                {
                    sCharge = stod(vInputCharge[0]);
                    if ((isValidInput(vInputCharge[0]) == true) && (sCharge != 0))
                    {
                        // If the input is passed, it will leave the loop.
                        cout << endl;
                        break;
                    }
                    else
                    {
                        // If the input isn't passed, it will let the user enter new values again.
                        vInputCharge.clear();
                        inputCharge.clear();
                        cout << "Invalid input!" << endl; 
                    }
                }
                else
                {
                    // If there is unexpected error, it will come here, and it will let the user enter new values again.
                    vInputCharge.clear();
                    inputCharge.clear();
                    cout << "Invalid input!" << endl; 
                }
            }
        }
        
        while (1)
        {
            while(1)
            {
                vInputTargetLocation.clear();
                inputLocation.clear();
                e1.v1.clear();
                e1.v2.clear();
                e1.out1.clear();
                e1.out2.clear();
                e1.out3.clear();
                cout << "Please enter the location in space to determine the electric field (x y z) in meters: ";
                getline(cin, inputLocation);
                if (inputLocation.length() == 0)
                {
                    inputLocation.clear();
                    cout << "Invalid input!" << endl; 
                }
                else
                {
                    splitInput(inputLocation, cSpace, vInputTargetLocation);
                    if(vInputTargetLocation.size() == 3)
                    {
                        if ((isValidInput(vInputTargetLocation[0]) == true) && (isValidInput(vInputTargetLocation[1]) == true) && (isValidInput(vInputTargetLocation[2]) == true))
                        {
                            // If the inputs are passed, we will start to set up the value for calculation of the electric field.
                            xPosition = stod(vInputTargetLocation[0]);
                            yPosition = stod(vInputTargetLocation[1]);
                            zPosition = stod(vInputTargetLocation[2]);
                            e1.setSizeSeparation(N, M, dX, dY);
                            e1.setCharge(sCharge);
                            e1.setLocation(xPosition, yPosition, zPosition);

                            // Once the position of charges are calculated, we will check whether the target point is at the charge.

                            if ((e1.qPositionMatch) == 1)
                            {
                                vInputTargetLocation.clear();
                                inputLocation.clear();
                                cout << "Invalid location! Location matches a point charge position!" << endl;
                            }
                            else
                            {
                                // If the target point is not at the charge, then it will leave the loop.
                                break;
                            }
                        }
                        else
                        {
                            vInputTargetLocation.clear();
                            inputLocation.clear();
                            cout << "Invalid input!" << endl; 
                        }
                    }
                    else
                    {
                        vInputTargetLocation.clear();
                        inputLocation.clear();
                        cout << "Invalid input!" << endl; 
                    }
                }
            }
        
            // Here is to calculate the time and electric field.
            auto startTime = chrono::high_resolution_clock::now();
            e1.calculationElectricField(n);
            auto endTime = chrono::high_resolution_clock::now();
            auto totalTime = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

            // From here, the program will output the results.    
            cout << "The electric field at (" << xPosition << ", " << yPosition << ", " << zPosition << ") in V/m is " << endl;

            convertToScientificNotation(e1.outputEx, numberX, exponentX);
            convertToScientificNotation(e1.outputEy, numberY, exponentY); 
            convertToScientificNotation(e1.outputEz, numberZ, exponentZ);
            double eTotal = sqrt(((e1.outputEx * e1.outputEx) + (e1.outputEy * e1.outputEy) + (e1.outputEz * e1.outputEz)));
            convertToScientificNotation(eTotal, numberTotal, exponentTotal);
            
            cout << "Ex = " << numberX << " * 10^" << exponentX << endl;
            cout << "Ey = " << numberY << " * 10^" << exponentY << endl;
            cout << "Ez = " << numberZ << " * 10^" << exponentZ << endl;
            cout << "|E| = " << numberTotal << " * 10^" << exponentTotal << endl;

            cout << "The calculation took "<< totalTime.count() << " microsec!" << endl;

            while (1)
            {
                // This loop is to check whether the user wants to calculate the electric field again.
                cout << "Do you want to enter a new location (Y/N)? ";
                getline(cin, inputYesNo);
                if (inputYesNo == "y" || inputYesNo == "Y")
                {
                    // If the user says yes, then it will do it again.
                    inputYesNo.clear();
                    vInputTargetLocation.clear();
                    inputLocation.clear();
                    cout << endl;
                    break;
                }
                else if (inputYesNo == "n" || inputYesNo == "N")
                {
                    // If the user says no, it will break out the loop and terminate the program.
                    cout << "Bye!" << endl;
                    break;
                }
                else
                {
                    inputYesNo.clear();
                    cout << "Invalid input!" << endl;
                }
            }
            if (inputYesNo == "n" || inputYesNo == "N")
            {
                break;
            }
        }
        if (inputYesNo == "n" || inputYesNo == "N")
        {
            break;
        }
    }
    return 0;
}
/*
Last Date Modified: 1/9/2024

Description:

Here is to define the member variables and member functions for the electric field.
It includes the values of Ex, Ey, Ez in the derived class.
More information of the member functions can be found in ECE_ElectricField.cpp.

*/
#include "ECE_PointCharge.h"
#include <cmath>
#include <atomic>
using namespace std;

class ECE_ElectricField: public ECE_PointCharge
{
protected:
    double Ex; // Electric field in the x-direction.
    double Ey; // Electric field in the y-direction.
    double Ez; // Electric field in the z-direction.
    double k;  // Coulomb's constant

public:
    ECE_ElectricField()
    {
        Ex = 0;
        Ey = 0;
        Ez = 0;
        k = 9 * pow(10, 9);
    }
    double outputEx; // Electric field in the x-direction for derived class.
    double outputEy; // Electric field in the y-direction for derived class.
    double outputEz; // Electric field in the z-direction for derived class.
    vector<double> out1; // Save the temporary value of the electric field in x-direction.
    vector<double> out2; // Save the temporary value of the electric field in y-direction.
    vector<double> out3; // Save the temporary value of the electric field in z-direction.
    double kConstant; // Coulomb's constant multiply with charge because it would be a constant after setting up by the user.
    
    void computeFieldAt(double x, double y, double z, int i);
    void getElectricField(double &Ex, double &Ey, double &Ez);
    void calculationElectricField(int n);
};

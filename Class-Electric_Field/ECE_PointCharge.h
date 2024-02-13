/*
Last Date Modified: 1/4/2029

Description:

Here is to define the member variables and member functions for point charges.
It includes target points and other parameters for the basic class. Also, they can be inherited by derived classes.
More information of the member functions can be found in ECE_PointCharge.cpp.

*/
#include <cmath>
#include <vector>
using namespace std;

class ECE_PointCharge
{
protected:
    double x; // x-coordinate.
    double y; // y-coordinate.
    double z; // z-coordinate.
    double q; // charge of the point.
    int N; // number of points in x.
    int M; // number of points in y.
    double separationX; // separation of the point in x direction.
    double separationY; // separation of the point in y direction.

public:
    ECE_PointCharge()
    {
        x = 0;
        y = 0;
        z = 0;
        q = 0;
        N = 0;
        M = 0;
        separationX = 0;
        separationY = 0;
    }
    double qCharge; // Get the value of the charge.
    double zDirection; // Get the value of z-direction.
    int totalCharge; // Total number of charges.
    int qPositionMatch; // Check if the target point is on the charge.
    vector<double> v1; // Save the difference between charges and the target point in x-direction.
    vector<double> v2; // Save the difference between charges and the target point in y-direction.
    void setLocation(double x, double y, double z);
    void setCharge(double q);
    double getCharge();
    double getDirectionZ();
    void setSizeSeparation(int sizeN, int sizeM, double dX, double dY);
    int getTotalQ();
    int checkPositionMatch(double x, double y, double z);
};
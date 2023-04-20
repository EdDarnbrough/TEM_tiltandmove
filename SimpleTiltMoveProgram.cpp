#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cmath>
//#include <stdio.h>
#include <conio.h>

#include<numeric>
#include<vector>
using namespace std;

void crossProduct(double v_A[3], double v_B[3], double c_P[3]) {
   c_P[0] = v_A[1] * v_B[2] - v_A[2] * v_B[1];
   c_P[1] = -(v_A[0] * v_B[2] - v_A[2] * v_B[0]);
   c_P[2] = v_A[0] * v_B[1] - v_A[1] * v_B[0];
}

void dotProduct(double v_A[3], double v_B[3], double v_P[3], double d_P) {
   v_P[0] = v_A[0] * v_B[0];
   v_P[1] = v_A[1] * v_B[1];
   v_P[2] = v_A[2] * v_B[2];
   d_P = v_P[0]+v_P[1]+v_P[2];
}

void Centre_and_Axes(double X_centre,double Y_centre,double x_axis[3],double y_axis[3] ) {
    X_centre = 0.0; 
    Y_centre = 0.0;
    x_axis[0] = 1; x_axis[1] = 1; x_axis[2] = 0;
    y_axis[0] = 1; y_axis[2] = -1; y_axis[3] = 0; 
    cout << "\nDo you want to use the standard center and tilt axes? (y/n)" << endl;
	char ch_display = getch(); 
	cout << ch_display << endl;
	if(ch_display=='n'){ cout << "In future you will be able to do this if you ask Ed Darnbrough"; Sleep(1000);} 
	//if(ch_display!='y'){ cout << "Think you are clever trying to pick a secret option? \nNot this time buddy you just get the default."; Sleep(200);}
}

void Calculation_loop(double X_centre,double Y_centre,double x_axis[3],double y_axis[3]) {

cout << "What is your x location?\t"; double x_now; cin >> x_now; ; cout << "You entered " << x_now << endl;
cout << "What is your y location?\t"; double y_now; cin >> y_now; ; cout << "You entered " << x_now << endl;  
double v_position[3]; v_position[0] = X_centre - x_now; v_position[1] = Y_centre-y_now; v_position[2]=0; 
cout << "Your feature vector is: "; 
for (int i = 0; i < 3; i++)
    cout << v_position[i] << " " ;
cout << "How much do you want to tilt in degrees?\t"; double tilt; cin >> tilt; ; cout << "You entered " << tilt << " degrees." << endl;
cout << "Do you want to tilt in x or y?";
char ch_display = getch(); 
cout << ch_display << endl;
double Rot_axis[3];
if(ch_display=='x'){  Rot_axis[0] = x_axis[0];Rot_axis[1] = x_axis[1];Rot_axis[2] = x_axis[2]; }
if(ch_display=='y'){  Rot_axis[0] = y_axis[0];Rot_axis[1] = y_axis[1];Rot_axis[2] = y_axis[2];}
// Based on Rodrigues' rotation formula wiki
double c_P[3]; double v_P[3]; double d_P;
crossProduct(v_position, Rot_axis, c_P);
dotProduct(v_position, Rot_axis, v_P, d_P);
double v_rot[3];
double tilt_rad = 3.14*tilt/180; 
v_rot[0] = v_position[0]*cos(tilt_rad) + c_P[0]*sin(tilt_rad) + Rot_axis[0]*d_P*(1-cos(tilt_rad));
v_rot[1] = v_position[1]*cos(tilt_rad) + c_P[1]*sin(tilt_rad) + Rot_axis[1]*d_P*(1-cos(tilt_rad));
v_rot[2] = v_position[2]*cos(tilt_rad) + c_P[2]*sin(tilt_rad) + Rot_axis[2]*d_P*(1-cos(tilt_rad));
double delta_x; delta_x = v_position[0]-v_rot[0]; 
double delta_y; delta_y = v_position[1]-v_rot[1]; 
double delta_z; delta_z = v_position[2]-v_rot[2]; 

cout << "Your feature of interest has moved: " << delta_x << " in the x,\t" << delta_y << " in the y, and\t" << delta_z << " in the z." << endl << endl ; 
}

int main() {
	// Introduce self to user
	cout << "\t !!! WARNING !!! \n This software will only work if it and the Mechtest.exe are run as Administrators. \n Use of this 'software' is not recommended without the support of Dr Ed Darnbrough. \n Do you wish to continue [y/n]? " << endl;
	char ch_display = getch(); 
	cout << ch_display << endl;
	if(ch_display=='n'){ cout << "Goodbye!"; Sleep(1000); return 1;} 
	if(ch_display!='y'){ cout << "Think you are clever trying to pick a secret option? \nNot this time buddy, Goodbye!"; Sleep(200); return 1;}
    // cout << "This program does nothing right now." << endl;

    // Something to ask if you want standard rotation axis or to include your own
    double X_centre; double Y_centre; double x_axis[3]; double y_axis[3];
    Centre_and_Axes(X_centre,Y_centre,x_axis,y_axis);

    // Loop to take x, y and tilt values and return new locations 
    Calculation_loop(X_centre,Y_centre,x_axis,y_axis);
    char ch=0;
    cout << "\nIf finished press 'q' or press 'g' to go again." << endl;
    do{
    if (_kbhit()!=0) 
		{
			ch = _getch();
			ch = tolower(ch);

			// Respond to the key press
			switch (ch)
			{ 
                case 'g': Calculation_loop(X_centre,Y_centre,x_axis,y_axis);
                default: cout << "\nIf finished press 'q' or press 'g' to go again." << endl; break;
            }
        }

    } while (ch!='q');
    double v_A[3] = { 7.0, 6, 4 };
    double v_B[3] = { 2, 1, 3 };
    double c_P[3]; double v_P[3]; double d_P;
    cout << "Cross product:";
    crossProduct(v_A, v_B, c_P);
    for (int i = 0; i < 3; i++)
      cout << c_P[i] << " ";
    cout << "\nDot product:";
    dotProduct(v_A, v_B, v_P, d_P);
    cout << " " << d_P << " ";




    Sleep(1000); return 1;
 }
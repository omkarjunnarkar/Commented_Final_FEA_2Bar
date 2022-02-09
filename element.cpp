/*
***********************************************************************************************************************************************************

												Finite Element Code for 2 Bar Problem
															Element Routine

Author: Omkar Junnarkar, Semester-3 MSc. Computational Material Science
Matriculation Nr.: 66157	Email: omkar.junnarkar@student.tu-freiberg.de
IDE : Microsoft Visual Studio 2019

Objective : Handle the Element Level Operations for the Geometry considered in the Finite Element Problem

Libraries Included :

iostream: For Input-Output of the C++ Program
Eigen/Dense: For Using Dense Matrix Interface of Linear Algebra Library Eigen
iomanip: To manipulate the number of decimal places in output
fstream: To create the stream of file and write
element.h: Element Routine header file

*/

#include<iostream>
#include<Eigen/Dense>
#include<iomanip>
#include<fstream>
#include"element.h"

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
	To reduce the effort of specifying libraries/class for each command/data type
*/

using namespace std;
using namespace Eigen;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
	Arguments : Element Length, type : double
	Ouput : B-Matrix of format [ -1/L  1/L ] , type : Eigen Matrix
	
	B-Matrix is derived from the Partial Differentiation of Shape Function w.r.t Co-ordinate length ( dN/dX = dN/dZi * dZi/dX )
	[ Refer Report/Manual for more Details ]

*/
MatrixXd B_mat(double le) {

	MatrixXd b(1, 2);
	b(0, 0) = -1 / le;
	b(0, 1) = 1 / le;
	
	return b;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
	Arguments: any number, type: double
	Ouput : 'Sign' of the number

	If input is a Non-Negetive number, returns +1
	else returns -1

	Replicates Signum Function
*/
int signum(double x) {
	if (x >= 0) return 1;
	else return -1;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*
	Arguments: Index of the Element According to C++, Total Number of Elements
	Output : The assignment matrix for each element
	
	Assignment Matrix is Used to map local element matrices to global geomerty .
	[ Refer Report/Manual for more Details ]

	Note : In C++, the indexing starts with '0'. Thus, the Nth element physically, would be (N-1)th element numerically.
*/
MatrixXd assign(int ele_index_cpp, int numele) {

	MatrixXd a_element = MatrixXd::Zero(2, numele + 1);
	a_element(0, ele_index_cpp) = 1;
	a_element(1, ele_index_cpp + 1) = 1;
	return a_element;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
	tuple : template from 'std' class. Ties and Passes values together ; Used to output multiple values at once

	Arguments : 
			elements : Number of elements
			ar_1 : Area of Left Bar
			ar_2 : Area of Right Bar
			len_1 : Length of Left Bar
			len_2 : Length of Right Bar

	Output :
			After Meshing -
			List of Areas, type Eigen Matrix
			List of Lengths, type Eigen Matrix

*/

tuple<MatrixXd, MatrixXd>get_areas_lengths(int elements, double ar_1, double ar_2, double len_1, double len_2) {
	MatrixXd areas(elements, 1);
	MatrixXd lengths(elements, 1);
	for (int i = 0; i < elements; i++) {
		if (i < elements / 2) {
			areas(i, 0) = ar_1;
			lengths(i, 0) = len_1 / (elements / 2);
		}
		else {
			areas(i, 0) = ar_2;
			lengths(i, 0) = len_2 / (elements - (elements / 2));
		}
	}
	
	return { areas,lengths };
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/




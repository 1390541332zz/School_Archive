/*
 * Purpose for program: This program calculates compound interest.
 *
 * Programmer: Jacob Abel
 * Date: January 23, 2017
 *
 * Honor Code: I have neither given nor received any unauthorized assistance
 * with this program.
 */

#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::pow;

//A=P*pow((1+(r/n)), (n*t))
int main() {

    double discreteValue = 0;    // Final Value when compounded discretely
    double continuousValue = 0;  // Final Value when compounded continuously
    double principal = 0;        // Initial Investment
    double interestRate = 0;     // Interest Rate in decimal notation
    double timespan = 0;         // Timespan in years
    int evaluationRate = 0;      // Number of evaluations per year

    cout << "Principal Investment: ";
    cin  >> principal;
    cout << "Interest Rate: ";
    cin  >> interestRate;
    cout << "Number of Interest Evaluations per Year: ";
    cin  >> evaluationRate;
    cout << "Number of Years to Invest: ";
    cin  >> timespan;


    discreteValue = principal * pow((1 + interestRate/evaluationRate), \
    (timespan * evaluationRate));

    continuousValue = principal * pow(M_E, (timespan * interestRate));

    // Outputs the discretely compounded interest.
    cout << "After " << timespan << " years, the principal investment " \
    << principal << " will accrue into " << discreteValue \
    << " when compounded " << evaluationRate << " times per year." << endl;

    //Outputs the continuously compounded interest.
    cout << "After " << timespan << " years, the principal investment " \
    << principal << " will accrue into " << continuousValue \
    << " when compounded continuously." << endl;

    return 0;
}

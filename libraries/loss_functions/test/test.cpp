// test.cpp

#include "HingeLoss.h"
using loss_functions::HingeLoss;

#include "LogLoss.h"
using loss_functions::LogLoss;

#include "SquaredLoss.h"
using loss_functions::SquaredLoss;

// stl
#include <iostream>
using std::cout;
using std::endl;

#include<string>
using std::string;

#include <cmath>
using std::log;
using std::exp;

bool testFailed = false;

/// checks if two doubles are equal, up to a small numerical error
///
bool isEqual(double a, double b, double tolerance = 1.0e-8)
{
    if (a - b < tolerance && b - a < tolerance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// Prints the results of a test and sets the global testFailed flag if appropriate
///
void processTest(const string& testName, bool success)
{
    cout << "Testing " << testName << " ... ";

    if (success)
    {
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed\n";
        testFailed = true;
    }
}

void hingeLossTest()
{
    HingeLoss hingeLoss;
    processTest("HingeLoss::Evaluate(2,1)", isEqual(hingeLoss.Evaluate(2, 1), 0));
    processTest("HingeLoss::Evaluate(-2,-1)", isEqual(hingeLoss.Evaluate(-2, -1), 0));
    processTest("HingeLoss::Evaluate(2,-1)", isEqual(hingeLoss.Evaluate(2, -1), 3));
    processTest("HingeLoss::Evaluate(-2,1)", isEqual(hingeLoss.Evaluate(-2, 1), 3));
    processTest("HingeLoss::Evaluate(0,1)", isEqual(hingeLoss.Evaluate(0, 1), 1));
    processTest("HingeLoss::Evaluate(0,-1)", isEqual(hingeLoss.Evaluate(0, -1), 1));

    processTest("HingeLoss::GetDerivative(2,1)", isEqual(hingeLoss.GetDerivative(2, 1), 0));
    processTest("HingeLoss::GetDerivative(-2,-1)", isEqual(hingeLoss.GetDerivative(-2, -1), 0));
    processTest("HingeLoss::GetDerivative(2,-1)", isEqual(hingeLoss.GetDerivative(2, -1), 1));
    processTest("HingeLoss::GetDerivative(-2,1)", isEqual(hingeLoss.GetDerivative(-2, 1), -1));
    processTest("HingeLoss::GetDerivative(0,1)", isEqual(hingeLoss.GetDerivative(0, 1), -1));
    processTest("HingeLoss::GetDerivative(0,-1)", isEqual(hingeLoss.GetDerivative(0, -1), 1));
}

void logLossTest()
{
    LogLoss logLoss;
    processTest("LogLoss::Evaluate(2,1)", isEqual(logLoss.Evaluate(2, 1), log(1 + exp(-2))));
    processTest("LogLoss::Evaluate(-2,-1)", isEqual(logLoss.Evaluate(-2, -1), log(1 + exp(-2))));
    processTest("LogLoss::Evaluate(2,-1)", isEqual(logLoss.Evaluate(2, -1), log(1 + exp(2))));
    processTest("LogLoss::Evaluate(-2,1)", isEqual(logLoss.Evaluate(-2, 1), log(1 + exp(2))));
    processTest("LogLoss::Evaluate(0,1)", isEqual(logLoss.Evaluate(0, 1), log(2)));
    processTest("LogLoss::Evaluate(0,-1)", isEqual(logLoss.Evaluate(0, -1), log(2)));

    processTest("LogLoss::GetDerivative(2,1)", isEqual(logLoss.GetDerivative(2, 1), -1/(1+exp(2))));
    processTest("LogLoss::GetDerivative(-2,-1)", isEqual(logLoss.GetDerivative(-2, -1), 1/(1 + exp(2))));
    processTest("LogLoss::GetDerivative(2,-1)", isEqual(logLoss.GetDerivative(2, -1), 1/(1 + exp(-2))));
    processTest("LogLoss::GetDerivative(-2,1)", isEqual(logLoss.GetDerivative(-2, 1), -1/(1 + exp(-2))));
    processTest("LogLoss::GetDerivative(0,1)", isEqual(logLoss.GetDerivative(0, 1), -1/2.0));
    processTest("LogLoss::GetDerivative(0,-1)", isEqual(logLoss.GetDerivative(0, -1), 1/2.0));
}

void squaredLossTest()
{
    SquaredLoss squaredLoss;
    processTest("SquaredLoss::Evaluate(4,4)", isEqual(squaredLoss.Evaluate(4, 4), 0));
    processTest("SquaredLoss::Evaluate(4,2)", isEqual(squaredLoss.Evaluate(4, 2), 2));
    processTest("SquaredLoss::Evaluate(2,4)", isEqual(squaredLoss.Evaluate(2, 4), 2));

    processTest("SquaredLoss::GetDerivative(4,4)", isEqual(squaredLoss.GetDerivative(4, 4), 0));
    processTest("SquaredLoss::GetDerivative(4,2)", isEqual(squaredLoss.GetDerivative(4, 2), 2));
    processTest("SquaredLoss::GetDerivative(2,4)", isEqual(squaredLoss.GetDerivative(2, 4), -2));
}

/// Runs all tests
///
int main()
{
    hingeLossTest();
    logLossTest();
    squaredLossTest();

    if(testFailed)
    {
        return 1;
    }

    return 0;
}





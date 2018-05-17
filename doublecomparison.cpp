#include "doublecomparison.h"
#include <cmath>

bool Less(double lhs, double rhs)
{
    return lhs + EPS < rhs;
}

bool Greater(double lhs, double rhs)
{
    return Less(rhs, lhs);
}

bool LessEqual(double lhs, double rhs)
{
    return Less(lhs, rhs) || Equal(lhs, rhs);
}

bool GreaterEqual(double lhs, double rhs)
{
    return Greater(lhs, rhs) || Equal(lhs, rhs);
}

bool Equal(double lhs, double rhs)
{
    return std::abs(lhs - rhs) < EPS;
}

bool NotEqual(double lhs, double rhs)
{
    return !Equal(lhs, rhs);
}

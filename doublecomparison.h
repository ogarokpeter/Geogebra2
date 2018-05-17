#pragma once
constexpr double EPS = 1e-8;

bool Less(double lhs, double rhs);
bool Greater(double lhs, double rhs);
bool LessEqual(double lhs, double rhs);
bool GreaterEqual(double lhs, double rhs);

bool Equal(double lhs, double rhs);
bool NotEqual(double lhs, double rhs);

using RealNumber = double;

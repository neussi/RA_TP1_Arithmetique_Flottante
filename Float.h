#pragma once
#include <cmath>
#include <limits>
#include <cstdint>
#include <cstring>
#include <algorithm>

namespace NkMath {

    // Constantes
    constexpr double kEps = 1e-9;
    constexpr float kFEps = 1e-6f;

    // Valide : ni NaN, ni Inf
    inline bool isFiniteValid(double x) { return std::isfinite(x); }
    inline bool isFiniteValid(float x) { return std::isfinite(x); }

    // Proche de zéro
    inline bool nearlyZero(double x, double eps = kEps) { return std::abs(x) < eps; }
    inline bool nearlyZero(float x, float eps = kFEps) { return std::abs(x) < eps; }

    // Égalité relative
    inline bool approxEq(double a, double b, double eps = kEps) {
        if (a == b) return true;
        double maxAB = std::max(std::abs(a), std::abs(b));
        return std::abs(a - b) <= eps * std::max(1.0, maxAB);
    }

    // Sommation de Kahan
    inline double kahanSum(const double* data, int n) {
        double sum = 0.0;
        double comp = 0.0;
        for (int i = 0; i < n; i++) {
            double y = data[i] - comp;
            double t = sum + y;
            comp = (t - sum) - y;
            sum = t;
        }
        return sum;
    }

} // namespace NkMath

#pragma once
#include <cmath>
#include <limits>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <vector>

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

    // 1.1 Extraction bits
    inline uint32_t floatBits(float f) {
        uint32_t bits;
        std::memcpy(&bits, &f, sizeof(float));
        return bits;
    }

    // 1.2 Sommation de Kahan
    inline float kahanSum(const float* data, int n) {
        float sum = 0.0f;
        float comp = 0.0f;
        for (int i = 0; i < n; i++) {
            float y = data[i] - comp;
            float t = sum + y;
            comp = (t - sum) - y;
            sum = t;
        }
        return sum;
    }

    // 1.2 Variance de Welford
    inline float varianceWelford(const std::vector<float>& data) {
        float mean = 0.0f, M2 = 0.0f;
        int n = data.size();
        if (n < 2) return 0.0f;
        for (int i = 0; i < n; i++) {
            float delta = data[i] - mean;
            mean += delta / (i + 1);
            float delta2 = data[i] - mean;
            M2 += delta * delta2;
        }
        return M2 / (n - 1);
    }

    // 1.3 Machine Epsilon
    inline float measureEpsilon() {
        float eps = 1.0f;
        while (1.0f + eps / 2.0f != 1.0f) {
            eps /= 2.0f;
        }
        return eps;
    }

} // namespace NkMath

#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <numeric>
#include <vector>
#include <limits>

// --- TP 1.1: inspectFloat ---

uint32_t floatBits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(float));
    return bits;
}

void inspectFloat(float f) {
    uint32_t bits = floatBits(f);
    uint32_t sign = (bits >> 31) & 0x1;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    printf("float %.10f\n", f);
    printf("  Bits     : %08X\n", bits);
    printf("  Signe    : %u\n", sign);
    printf("  Exposant : %u (biais=127 -> 2^%d)\n", exponent, (int)exponent - 127);
    printf("  Mantisse : %06X (1.%06X en hex)\n", mantissa, mantissa);
}

// --- TP 1.2: Kahan et Welford ---

float kahanSum(const float* data, int n) {
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

float varianceNaive(const std::vector<float>& data) {
    float sum = 0.0f, sum2 = 0.0f;
    int n = data.size();
    for (float x : data) {
        sum += x;
        sum2 += x * x;
    }
    float mean = sum / n;
    return (sum2 - (sum * sum / n)) / (n - 1);
}

float varianceWelford(const std::vector<float>& data) {
    float mean = 0.0f, M2 = 0.0f;
    int n = data.size();
    for (int i = 0; i < n; i++) {
        float delta = data[i] - mean;
        mean += delta / (i + 1);
        float delta2 = data[i] - mean;
        M2 += delta * delta2;
    }
    return M2 / (n - 1);
}

float measureEpsilon() {
    float eps = 1.0f;
    while (1.0f + eps / 2.0f != 1.0f) {
        eps /= 2.0f;
    }
    return eps;
}

int main() {
    printf("=== TP1: IEEE 754 & Arithmetique Flottante ===\n\n");

    // 1. inspectFloat tests
    printf("1. Tests de inspectFloat :\n");
    inspectFloat(0.1f);  // Pourquoi n'est-il pas exact ?
    inspectFloat(1.0f);  // signe=0, exposant=127, mantisse=0
    inspectFloat(1.0f / 0.0f); // +Inf
    inspectFloat(std::sqrt(-1.0f)); // NaN
    inspectFloat(-0.0f); // comparer avec +0.0f
    inspectFloat(std::numeric_limits<float>::min()); // subnormal / min normal
    printf("\n");

    // 2. Kahan et Welford
    printf("2. Demonstation de precision :\n");
    int n = 1000000;
    std::vector<float> data(n, 0.1f);
    float sumStd = std::accumulate(data.begin(), data.end(), 0.0f);
    float sumKahan = kahanSum(data.data(), n);
    printf("  Somme de 1,000,000 de 0.1f :\n");
    printf("    Theorique      : 100000.00\n");
    printf("    std::accumulate: %.2f (erreur: %.2f)\n", sumStd, std::abs(100000.0f - sumStd));
    printf("    kahanSum       : %.2f (erreur: %.2f)\n", sumKahan, std::abs(100000.0f - sumKahan));

    std::vector<float> dataVar = {1e8f, 1e8f, 1.0f, 2.0f};
    printf("\n  Variance de {1e8, 1e8, 1, 2} :\n");
    printf("    Naive   : %.2f\n", varianceNaive(dataVar));
    printf("    Welford : %.2f\n", varianceWelford(dataVar));

    // 3. Epsilon
    printf("\n3. Epsilon machine :\n");
    float eps = measureEpsilon();
    printf("    Mesure par boucle : %e\n", eps);
    printf("    std::numeric_limits: %e\n", std::numeric_limits<float>::epsilon());

    return 0;
}

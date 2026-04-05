#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include "Float.h"

using namespace NkMath;

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

int main() {
    printf("=== TP1: IEEE 754 & Arithmetique Flottante ===\n\n");

    // 1. inspectFloat tests
    printf("1. Tests de inspectFloat :\n");
    inspectFloat(0.1f);  
    inspectFloat(1.0f);  
    inspectFloat(1.0f / 0.0f); // +Inf
    inspectFloat(-0.0f); 
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
    printf("    Welford : %.2f\n", varianceWelford(dataVar));

    // 3. Epsilon
    printf("\n3. Epsilon machine :\n");
    float eps = measureEpsilon();
    printf("    Mesure par boucle : %e\n", eps);

    return 0;
}

#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>
#include "../Float.h"
#include <vector>

using namespace NkMath;

TEST_CASE(TP1, FloatBits) {
    ASSERT_EQUAL(floatBits(1.0f), 0x3F800000u);
    ASSERT_EQUAL(floatBits(0.0f), 0x00000000u);
}

TEST_CASE(TP1, KahanSummation) {
    std::vector<float> data(1000000, 0.1f);
    float sumStd = 0.0f;
    for(float f : data) sumStd += f;
    
    float sumKahan = kahanSum(data.data(), (int)data.size());
    
    // Kahan should be much closer to 100000.0 than naive sum
    ASSERT_TRUE(std::abs(100000.0f - sumKahan) < std::abs(100000.0f - sumStd));
}

TEST_CASE(TP1, WelfordVariance) {
    std::vector<float> data = {1e8f, 1e8f, 1.0f, 2.0f};
    float var = varianceWelford(data);
    ASSERT_TRUE(var > 0.0f);
    // Exact variance for {1, 2} is 0.5. For {1e8, 1e8, 1, 2}, it's more complex but should be stable.
}

TEST_CASE(TP1, MachineEpsilon) {
    float eps = measureEpsilon();
    ASSERT_TRUE(eps > 0.0f);
    ASSERT_TRUE(1.0f + eps > 1.0f);
    ASSERT_EQUAL(1.0f + eps/2.0f, 1.0f);
}

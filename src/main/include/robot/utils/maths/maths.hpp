#pragma once

// std
#include <vector>

namespace robot {
namespace utils {
namespace maths {

// Returns normalised data from the input, 0 to 1 range
extern std::vector<float> Normalise(std::vector<float> data);
// Maps data from a value range to another value range
extern float Map(float data, int inputStart, int inputEnd, int outputStart, int outputEnd);

} // namespace maths
} // namespace utils
} // namespace robot
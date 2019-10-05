#include "robot/utils/maths/maths.hpp"

namespace robot {
namespace utils {
namespace maths {

std::vector<float> Normalise(std::vector<float> data) {
    float min{ 0 };
    float max{ 0 };

    for (int i = 0; i<data.size(); ++i) {
        if (data[i] < min) {
            min = data[i];
        }
        else if (data[i] > max) {
            max = data[i];
        }
    }

    std::vector<float> normalisedData;

    for (int i = 0; i<data.size(); ++i) {
        normalisedData.push_back((data[i] - min)/(max - min));
    }

    return(normalisedData);
}

float Map(float data, int inputStart, int inputEnd, int outputStart, int outputEnd) {
    double slope = 1.0 * (outputEnd - outputStart) / (inputEnd - inputStart);
    return (outputStart + slope * (data - inputStart));
}

} // namespace maths
} // namespace utils
} // namespace robot
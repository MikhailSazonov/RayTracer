#include "PPMManager.hpp"

namespace Files {

PPMManager::PPMManager(const std::string& filename, size_t width, size_t height, Method method, size_t maxcolor)
    : ofs(filename), data(height, std::vector<size_t>(width)), width_(width), height_(height), method_(method) {
        ofs << "P3\n";
        ofs << height << ' ' << width << '\n';
        ofs << maxcolor << '\n';
    }

PPMManager& PPMManager::operator<<(uint32_t color) {
    ofs << ((color >> 16) & 0xFF) << ' ';
    ofs << ((color >> 8) & 0xFF) << ' ';
    ofs << (color & 0x0000FF) << '\n';
    return *this;
}

std::vector<size_t>& PPMManager::operator[](size_t idx) {
    return data[idx];
}

PPMManager::~PPMManager() {
    if (method_ == Method::DUMP) {
        for (size_t j = 0; j < width_; ++j) {
            for (size_t i = 0; i < height_; ++i) {
                ofs << ((data[i][width_ - j - 1] >> 16) & 0xFF) << ' ';
                ofs << ((data[i][width_ - j - 1] >> 8) & 0xFF) << ' ';
                ofs << (data[i][width_ - j - 1] & 0x0000FF) << '\n';
            }
        }
    }
}

}

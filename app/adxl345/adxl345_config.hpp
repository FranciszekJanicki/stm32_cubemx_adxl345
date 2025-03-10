#ifndef ADXL345_CONFIG_HPP
#define ADXL345_CONFIG_HPP

#include "adxl345_registers.hpp"
#include "vector3d.hpp"
#include <cstdint>

namespace ADXL345 {

    template <typename T>
    using Vec3D = Utility::Vector3D<T>;

    enum struct RA : std::uint8_t {
        DEVID = 0x00,
        THRESH_TAP = 0x1D,
        OFSX = 0x1E,
        OFSY = 0x1F,
        OFSZ = 0x20,
        DUR = 0x21,
        LATENT = 0x22,
        WINDOW = 0x23,
        THRESH_ACT = 0x24,
        THRESH_INACT = 0x25,
        TIME_INACT = 0x26,
        ACT_INACT_CTL = 0x27,
        THRESH_FF = 0x28,
        TIME_FF = 0x29,
        TAP_AXES = 0x2A,
        ACT_TAP_STATUS = 0x2B,
        BW_RATE = 0x2C,
        POWER_CTL = 0x2D,
        INT_ENABLE = 0x2E,
        INT_MAP = 0x2F,
        INT_SOURCE = 0x30,
        DATA_FORMAT = 0x31,
        DATA_X0 = 0x32,
        DATA_X1 = 0x33,
        DATA_Y0 = 0x34,
        DATA_Y1 = 0x35,
        DATA_Z0 = 0x36,
        DATA_Z1 = 0x37,
        FIFO_CTL = 0x38,
        FIFO_STATUS = 0x39,
    };

    enum struct DataRate : std::uint8_t {
        RATE_3200HZ = 0b1111,
        RATE_1600HZ = 0b1110,
        RATE_800HZ = 0b1101,
        RATE_400HZ = 0b1100,
        RATE_200HZ = 0b1011,
        RATE_100HZ = 0b1010,
        RATE_50HZ = 0b1001,
        RATE_25HZ = 0b1000,
        RATE_12HZ5 = 0b0111,
        RATE_6HZ25 = 0b0110,
        RATE_3HZ125 = 0b0101,
        RATE_1HZ563 = 0b0100,
        RATE_0HZ782 = 0b0011,
        RATE_0HZ39 = 0b0010,
        RATE_0HZ195 = 0b0001,
        RATE_0HZ098 = 0b0000,
    };

    enum struct Range : std::uint8_t {
        FS_2G = 0b00,
        FS_4G = 0b01,
        FS_8G = 0b10,
        FS_16G = 0b11,
    };

    enum struct WakeUpRate : std::uint8_t {
        RATE_8HZ = 0b00,
        RATE_4HZ = 0b01,
        RATE_2HZ = 0b10,
        RATE_1HZ = 0b11,
    };

    std::uint8_t constexpr CHIP_ID = 0U;

    inline float range_to_scale(Range const range) noexcept
    {
        switch (range) {
            case Range::FS_2G:
                return 0.01916F;
            case Range::FS_4G:
                return 0.03823F;
            case Range::FS_8G:
                return 0.07664F;
            case Range::FS_16G:
                return 0.15328F;
        }
    }

    inline float config_to_scale(Config const& config) noexcept
    {
        return range_to_scale(static_cast<Range>(config.data_format.range));
    }

}; // namespace ADXL345

#endif // ADXL345_CONFIG_HPP
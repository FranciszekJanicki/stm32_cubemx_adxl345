#ifndef ADXL345_HPP
#define ADXL345_HPP

#include "adxl345_config.hpp"
#include "adxl345_registers.hpp"
#include "i2c_device.hpp"

namespace ADXL345 {

    struct ADXL345 {
    public:
        using I2CDevice = Utility::I2CDevice;

        ADXL345() noexcept = default;
        ADXL345(I2CDevice&& i2c_device, Config const& config) noexcept;

        ADXL345(ADXL345 const& other) = delete;
        ADXL345(ADXL345&& other) noexcept = default;

        ADXL345& operator=(ADXL345 const& other) = delete;
        ADXL345& operator=(ADXL345&& other) noexcept = default;

        ~ADXL345() noexcept;

        float get_acceleration_x_scaled() const noexcept;
        float get_acceleration_y_scaled() const noexcept;
        float get_acceleration_z_scaled() const noexcept;
        Vec3D<float> get_acceleration_scaled() const noexcept;

    private:
        std::uint8_t read_byte(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const reg_address) const noexcept;

        void write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const reg_address, std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void initialize(Config const& config) noexcept;

        void deinitialize() noexcept;

        bool is_valid_device_id() const noexcept;

        std::uint8_t get_device_id() const noexcept;

        std::int16_t get_acceleration_x_raw() const noexcept;
        std::int16_t get_acceleration_y_raw() const noexcept;
        std::int16_t get_acceleration_z_raw() const noexcept;
        Vec3D<std::int16_t> get_acceleration_raw() const noexcept;

        DEVID get_devid_register() const noexcept;

        THRESH_TAP get_thresh_tap_register() const noexcept;
        void set_thresh_tap_register(THRESH_TAP const thresh_tap) const noexcept;

        OFSX get_ofsx_register() const noexcept;
        void set_ofsx_register(OFSX const ofsx) const noexcept;

        OFSY get_ofsy_register() const noexcept;
        void set_ofsy_register(OFSY const ofsy) const noexcept;

        OFSZ get_ofsz_register() const noexcept;
        void set_ofsz_register(OFSZ const ofsz) const noexcept;

        DUR get_dur_register() const noexcept;
        void set_dur_register(DUR const dur) const noexcept;

        LATENT get_latent_register() const noexcept;
        void set_latent_register(LATENT const latent) const noexcept;

        WINDOW get_window_register() const noexcept;
        void set_window_register(WINDOW const window) const noexcept;

        THRESH_ACT get_thresh_act_register() const noexcept;
        void set_thresh_act_register(THRESH_ACT const thresh_act) const noexcept;

        THRESH_INACT get_thresh_inact_register() const noexcept;
        void set_thresh_inact_register(THRESH_INACT const thresh_inact) const noexcept;

        TIME_INACT get_time_inact_register() const noexcept;
        void set_time_inact_register(TIME_INACT const time_inact) const noexcept;

        ACT_INACT_CTL get_act_inact_ctl_register() const noexcept;
        void set_act_inact_ctl_register(ACT_INACT_CTL const act_inact_ctl) const noexcept;

        THRESH_FF get_thresh_ff_register() const noexcept;
        void set_thresh_ff_register(THRESH_FF const thresh_ff) const noexcept;

        TIME_FF get_time_ff_register() const noexcept;
        void set_time_ff_register(TIME_FF const time_ff) const noexcept;

        TAP_AXES get_tap_axes_register() const noexcept;
        void set_tap_axes_register(TAP_AXES const tap_axes) const noexcept;

        ACT_TAP_STATUS get_act_tap_status_register() const noexcept;

        BW_RATE get_bw_rate_register() const noexcept;
        void set_bw_rate_register(BW_RATE const bw_rate) const noexcept;

        POWER_CTL get_power_ctl_register() const noexcept;
        void set_power_ctl_register(POWER_CTL const power_ctl) const noexcept;

        INT_ENABLE get_int_enable_register() const noexcept;
        void set_int_enable_register(INT_ENABLE const int_enable) const noexcept;

        INT_MAP get_int_map_register() const noexcept;
        void set_int_map_register(INT_MAP const int_map) const noexcept;

        INT_SOURCE get_int_source_register() const noexcept;

        DATA_FORMAT get_data_format_register() const noexcept;
        void set_data_format_register(DATA_FORMAT const data_format) const noexcept;

        DATA_X get_data_x_registers() const noexcept;

        DATA_Y get_data_y_registers() const noexcept;

        DATA_Z get_data_z_registers() const noexcept;

        DATA get_data_registers() const noexcept;

        FIFO_CTL get_fifo_ctl_register() const noexcept;
        void set_fifo_ctl_register(FIFO_CTL const fifo_ctl) const noexcept;

        FIFO_STATUS get_fifo_status_register() const noexcept;

        bool initialized_{false};

        float scale_{};

        I2CDevice i2c_device_{};
    };

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, SIZE> ADXL345::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_bytes<SIZE>(reg_address);
    }

    template <std::size_t SIZE>
    inline void ADXL345::write_bytes(std::uint8_t const reg_address,
                                     std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->i2c_device_.write_byte(reg_address, bytes);
    }

}; // namespace ADXL345

#endif // ADXL345_HPP
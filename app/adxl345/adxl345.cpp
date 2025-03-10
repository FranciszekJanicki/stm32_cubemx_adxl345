#include "adxl345.hpp"
#include "adxl345_config.hpp"
#include "adxl345_registers.hpp"

namespace ADXL345 {

    ADXL345::ADXL345(I2CDevice&& i2c_device, Config const& config) noexcept :
        scale_{config_to_scale(config)}, i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(config);
    }

    ADXL345::~ADXL345() noexcept
    {
        this->deinitialize();
    }

    float ADXL345::get_acceleration_x_scaled() const noexcept
    {
        return static_cast<float>(this->get_acceleration_x_raw()) * this->scale_;
    }

    float ADXL345::get_acceleration_y_scaled() const noexcept
    {
        return static_cast<float>(this->get_acceleration_y_raw()) * this->scale_;
    }

    float ADXL345::get_acceleration_z_scaled() const noexcept
    {
        return static_cast<float>(this->get_acceleration_z_raw()) * this->scale_;
    }

    Vec3D<float> ADXL345::get_acceleration_scaled() const noexcept
    {
        return static_cast<Vec3D<float>>(this->get_acceleration_scaled()) * this->scale_;
    }

    std::uint8_t ADXL345::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_byte(reg_address);
    }

    void ADXL345::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->i2c_device_.write_byte(reg_address, byte);
    }

    void ADXL345::initialize(Config const& config) noexcept
    {
        if (this->is_valid_device_id()) {
            this->set_thresh_tap_register(config.thresh_tap);
            this->set_ofsx_register(config.ofsx);
            this->set_ofsy_register(config.ofsy);
            this->set_ofsz_register(config.ofsz);
            this->set_dur_register(config.dur);
            this->set_latent_register(config.latent);
            this->set_window_register(config.window);
            this->set_thresh_act_register(config.thresh_act);
            this->set_thresh_inact_register(config.thresh_inact);
            this->set_time_inact_register(config.time_inact);
            this->set_act_inact_ctl_register(config.act_inact_ctl);
            this->set_thresh_ff_register(config.thresh_ff);
            this->set_time_ff_register(config.time_ff);
            this->set_tap_axes_register(config.tap_axes);
            this->set_bw_rate_register(config.bw_rate);
            this->set_power_ctl_register(config.power_ctl);
            this->set_int_enable_register(config.int_enable);
            this->set_int_map_register(config.int_map);
            this->set_data_format_register(config.data_format);
            this->set_fifo_ctl_register(config.fifo_ctl);
            this->initialized_ = true;
        }
    }

    void ADXL345::deinitialize() noexcept
    {
        if (this->is_valid_device_id()) {
            this->initialized_ = false;
        }
    }

    bool ADXL345::is_valid_device_id() const noexcept
    {
        return this->get_device_id() == CHIP_ID;
    }

    std::uint8_t ADXL345::get_device_id() const noexcept
    {
        return std::bit_cast<std::uint8_t>(this->get_devid_register());
    }

    std::int16_t ADXL345::get_acceleration_x_raw() const noexcept
    {
        return std::bit_cast<std::int16_t>(this->get_data_x_registers());
    }

    std::int16_t ADXL345::get_acceleration_y_raw() const noexcept
    {
        return std::bit_cast<std::int16_t>(this->get_data_y_registers());
    }

    std::int16_t ADXL345::get_acceleration_z_raw() const noexcept
    {
        return std::bit_cast<std::int16_t>(this->get_data_z_registers());
    }

    Vec3D<std::int16_t> ADXL345::get_acceleration_raw() const noexcept
    {
        auto const data = this->get_data_registers();
        return Vec3D<std::int16_t>{std::byteswap(std::bit_cast<std::int16_t>(data.data_x)),
                                   std::byteswap(std::bit_cast<std::int16_t>(data.data_y)),
                                   std::byteswap(std::bit_cast<std::int16_t>(data.data_z))};
    }

    DEVID ADXL345::get_devid_register() const noexcept
    {
        std::bit_cast<DEVID>(this->read_byte(std::to_underlying(RA::DEVID)));
    }

    THRESH_TAP ADXL345::get_thresh_tap_register() const noexcept
    {
        std::bit_cast<THRESH_TAP>(this->read_byte(std::to_underlying(RA::THRESH_TAP)));
    }

    void ADXL345::set_thresh_tap_register(THRESH_TAP const thresh_tap) const noexcept
    {
        this->write_byte(std::to_underlying(RA::THRESH_TAP), std::bit_cast<std::uint8_t>(thresh_tap));
    }

    OFSX ADXL345::get_ofsx_register() const noexcept
    {
        return std::bit_cast<OFSX>(this->read_byte(std::to_underlying(RA::OFSX)));
    }

    void ADXL345::set_ofsx_register(OFSX const ofsx) const noexcept
    {
        this->write_byte(std::to_underlying(RA::OFSX), std::bit_cast<std::uint8_t>(ofsx));
    }

    OFSY ADXL345::get_ofsy_register() const noexcept
    {
        return std::bit_cast<OFSY>(this->read_byte(std::to_underlying(RA::OFSY)));
    }

    void ADXL345::set_ofsy_register(OFSY const ofsy) const noexcept
    {
        this->write_byte(std::to_underlying(RA::OFSY), std::bit_cast<std::uint8_t>(ofsy));
    }

    OFSZ ADXL345::get_ofsz_register() const noexcept
    {
        return std::bit_cast<OFSZ>(this->read_byte(std::to_underlying(RA::OFSZ)));
    }

    void ADXL345::set_ofsz_register(OFSZ const ofsz) const noexcept
    {
        this->write_byte(std::to_underlying(RA::OFSZ), std::bit_cast<std::uint8_t>(ofsz));
    }

    DUR ADXL345::get_dur_register() const noexcept
    {
        return std::bit_cast<DUR>(this->read_byte(std::to_underlying(RA::DUR)));
    }

    void ADXL345::set_dur_register(DUR const dur) const noexcept
    {
        this->write_byte(std::to_underlying(RA::DUR), std::bit_cast<std::uint8_t>(dur));
    }

    LATENT ADXL345::get_latent_register() const noexcept
    {
        return std::bit_cast<LATENT>(this->read_byte(std::to_underlying(RA::LATENT)));
    }

    void ADXL345::set_latent_register(LATENT const latent) const noexcept
    {
        this->write_byte(std::to_underlying(RA::LATENT), std::bit_cast<std::uint8_t>(latent));
    }

    WINDOW ADXL345::get_window_register() const noexcept
    {
        return std::bit_cast<WINDOW>(this->read_byte(std::to_underlying(RA::WINDOW)));
    }

    void ADXL345::set_window_register(WINDOW const window) const noexcept
    {
        this->write_byte(std::to_underlying(RA::WINDOW), std::bit_cast<std::uint8_t>(window));
    }

    THRESH_ACT ADXL345::get_thresh_act_register() const noexcept
    {
        return std::bit_cast<THRESH_ACT>(this->read_byte(std::to_underlying(RA::THRESH_ACT)));
    }

    void ADXL345::set_thresh_act_register(THRESH_ACT const thresh_act) const noexcept
    {
        this->write_byte(std::to_underlying(RA::THRESH_ACT), std::bit_cast<std::uint8_t>(thresh_act));
    }

    THRESH_INACT ADXL345::get_thresh_inact_register() const noexcept
    {
        return std::bit_cast<THRESH_INACT>(this->read_byte(std::to_underlying(RA::THRESH_INACT)));
    }

    void ADXL345::set_thresh_inact_register(THRESH_INACT const thresh_inact) const noexcept
    {
        this->write_byte(std::to_underlying(RA::THRESH_INACT), std::bit_cast<std::uint8_t>(thresh_inact));
    }

    TIME_INACT ADXL345::get_time_inact_register() const noexcept
    {
        return std::bit_cast<TIME_INACT>(this->read_byte(std::to_underlying(RA::TIME_INACT)));
    }

    void ADXL345::set_time_inact_register(TIME_INACT const time_inact) const noexcept
    {
        this->write_byte(std::to_underlying(RA::TIME_INACT), std::bit_cast<std::uint8_t>(time_inact));
    }

    ACT_INACT_CTL ADXL345::get_act_inact_ctl_register() const noexcept
    {
        return std::bit_cast<ACT_INACT_CTL>(this->read_byte(std::to_underlying(RA::ACT_INACT_CTL)));
    }

    void ADXL345::set_act_inact_ctl_register(ACT_INACT_CTL const act_inact_ctl) const noexcept
    {
        this->write_byte(std::to_underlying(RA::ACT_INACT_CTL), std::bit_cast<std::uint8_t>(act_inact_ctl));
    }

    THRESH_FF ADXL345::get_thresh_ff_register() const noexcept
    {
        return std::bit_cast<THRESH_FF>(this->read_byte(std::to_underlying(RA::THRESH_FF)));
    }

    void ADXL345::set_thresh_ff_register(THRESH_FF const thresh_ff) const noexcept
    {
        this->write_byte(std::to_underlying(RA::THRESH_FF), std::bit_cast<std::uint8_t>(thresh_ff));
    }

    TIME_FF ADXL345::get_time_ff_register() const noexcept
    {
        return std::bit_cast<TIME_FF>(this->read_byte(std::to_underlying(RA::TIME_FF)));
    }

    void ADXL345::set_time_ff_register(TIME_FF const time_ff) const noexcept
    {
        this->write_byte(std::to_underlying(RA::TIME_FF), std::bit_cast<std::uint8_t>(time_ff));
    }

    TAP_AXES ADXL345::get_tap_axes_register() const noexcept
    {
        return std::bit_cast<TAP_AXES>(this->read_byte(std::to_underlying(RA::TAP_AXES)));
    }

    void ADXL345::set_tap_axes_register(TAP_AXES const tap_axes) const noexcept
    {
        this->write_byte(std::to_underlying(RA::TAP_AXES), std::bit_cast<std::uint8_t>(tap_axes));
    }

    ACT_TAP_STATUS ADXL345::get_act_tap_status_register() const noexcept
    {
        return std::bit_cast<ACT_TAP_STATUS>(this->read_byte(std::to_underlying(RA::ACT_TAP_STATUS)));
    }

    BW_RATE ADXL345::get_bw_rate_register() const noexcept
    {
        return std::bit_cast<BW_RATE>(this->read_byte(std::to_underlying(RA::BW_RATE)));
    }

    void ADXL345::set_bw_rate_register(BW_RATE const bw_rate) const noexcept
    {
        this->write_byte(std::to_underlying(RA::BW_RATE), std::bit_cast<std::uint8_t>(bw_rate));
    }

    POWER_CTL ADXL345::get_power_ctl_register() const noexcept
    {
        return std::bit_cast<POWER_CTL>(this->read_byte(std::to_underlying(RA::POWER_CTL)));
    }

    void ADXL345::set_power_ctl_register(POWER_CTL const power_ctl) const noexcept
    {
        this->write_byte(std::to_underlying(RA::POWER_CTL), std::bit_cast<std::uint8_t>(power_ctl));
    }

    INT_ENABLE ADXL345::get_int_enable_register() const noexcept
    {
        return std::bit_cast<INT_ENABLE>(this->read_byte(std::to_underlying(RA::INT_ENABLE)));
    }

    void ADXL345::set_int_enable_register(INT_ENABLE const int_enable) const noexcept
    {
        this->write_byte(std::to_underlying(RA::INT_ENABLE), std::bit_cast<std::uint8_t>(int_enable));
    }

    INT_MAP ADXL345::get_int_map_register() const noexcept
    {
        return std::bit_cast<INT_MAP>(this->read_byte(std::to_underlying(RA::INT_MAP)));
    }

    void ADXL345::set_int_map_register(INT_MAP const int_map) const noexcept
    {
        this->write_byte(std::to_underlying(RA::INT_MAP), std::bit_cast<std::uint8_t>(int_map));
    }

    INT_SOURCE ADXL345::get_int_source_register() const noexcept
    {
        return std::bit_cast<INT_SOURCE>(this->read_byte(std::to_underlying(RA::INT_SOURCE)));
    }

    DATA_FORMAT ADXL345::get_data_format_register() const noexcept
    {
        return std::bit_cast<DATA_FORMAT>(this->read_byte(std::to_underlying(RA::DATA_FORMAT)));
    }

    void ADXL345::set_data_format_register(DATA_FORMAT const data_format) const noexcept
    {
        this->write_byte(std::to_underlying(RA::DATA_FORMAT), std::bit_cast<std::uint8_t>(data_format));
    }

    DATA_X ADXL345::get_data_x_registers() const noexcept
    {
        return std::bit_cast<DATA_X>(this->read_bytes<sizeof(DATA_X)>(std::to_underlying(RA::DATA_X0)));
    }

    DATA_Y ADXL345::get_data_y_registers() const noexcept
    {
        return std::bit_cast<DATA_Y>(this->read_bytes<sizeof(DATA_X)>(std::to_underlying(RA::DATA_Y0)));
    }

    DATA_Z ADXL345::get_data_z_registers() const noexcept
    {
        return std::bit_cast<DATA_Z>(this->read_bytes<sizeof(DATA_Z)>(std::to_underlying(RA::DATA_Z0)));
    }

    DATA ADXL345::get_data_registers() const noexcept
    {
        return std::bit_cast<DATA>(this->read_bytes<sizeof(DATA)>(std::to_underlying(RA::DATA_X0)));
    }

    FIFO_CTL ADXL345::get_fifo_ctl_register() const noexcept
    {
        return std::bit_cast<FIFO_CTL>(this->read_byte(std::to_underlying(RA::FIFO_CTL)));
    }

    void ADXL345::set_fifo_ctl_register(FIFO_CTL const fifo_ctl) const noexcept
    {
        this->write_byte(std::to_underlying(RA::FIFO_CTL), std::bit_cast<std::uint8_t>(fifo_ctl));
    }

    FIFO_STATUS ADXL345::get_fifo_status_register() const noexcept
    {
        return std::bit_cast<FIFO_STATUS>(this->read_byte(std::to_underlying(RA::FIFO_STATUS)));
    }

}; // namespace ADXL345
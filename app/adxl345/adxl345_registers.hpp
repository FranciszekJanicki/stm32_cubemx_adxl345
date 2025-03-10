#ifndef ADXL345_REGISTERS_HPP
#define ADXL345_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace ADXL345 {

    struct DEVID {
        std::uint8_t devid : 8;
    } PACKED;

    struct THRESH_TAP {
        std::uint8_t thresh_tap : 8;
    } PACKED;

    struct OFSX {
        std::uint8_t ofsx : 8;
    } PACKED;

    struct OFSY {
        std::uint8_t ofsy : 8;
    } PACKED;

    struct OFSZ {
        std::uint8_t ofsz : 8;
    } PACKED;

    struct DUR {
        std::uint8_t dur : 8;
    } PACKED;

    struct LATENT {
        std::uint8_t latent : 8;
    } PACKED;

    struct WINDOW {
        std::uint8_t window : 8;
    } PACKED;

    struct THRESH_ACT {
        std::uint8_t thresh_act : 8;
    } PACKED;

    struct THRESH_INACT {
        std::uint8_t thresh_inact : 8;
    } PACKED;

    struct TIME_INACT {
        std::uint8_t time_inact : 8;
    } PACKED;

    struct ACT_INACT_CTL {
        std::uint8_t act_ac_dc : 1;
        std::uint8_t act_x_en : 1;
        std::uint8_t act_y_en : 1;
        std::uint8_t act_z_en : 1;
        std::uint8_t inact_ac_dc : 1;
        std::uint8_t inact_x_en : 1;
        std::uint8_t inact_y_en : 1;
        std::uint8_t inact_z_en : 1;
    } PACKED;

    struct THRESH_FF {
        std::uint8_t thresh_ff : 8;
    } PACKED;

    struct TIME_FF {
        std::uint8_t time_ff : 8;
    } PACKED;

    struct TAP_AXES {
        std::uint8_t : 4;
        std::uint8_t suppress : 1;
        std::uint8_t tap_x_en : 1;
        std::uint8_t tap_y_en : 1;
        std::uint8_t tap_z_en : 1;
    } PACKED;

    struct ACT_TAP_STATUS {
        std::uint8_t : 1;
        std::uint8_t act_x_src : 1;
        std::uint8_t act_y_src : 1;
        std::uint8_t act_z_src : 1;
        std::uint8_t asleep : 1;
        std::uint8_t tap_x_src : 1;
        std::uint8_t tap_y_src : 1;
        std::uint8_t tap_z_src : 1;
    } PACKED;

    struct BW_RATE {
        std::uint8_t : 3;
        std::uint8_t low_power : 1;
        std::uint8_t rate : 4;
    } PACKED;

    struct POWER_CTL {
        std::uint8_t : 2;
        std::uint8_t link : 1;
        std::uint8_t auto_sleep : 1;
        std::uint8_t measure : 1;
        std::uint8_t sleep : 1;
        std::uint8_t wakeup : 2;
    } PACKED;

    struct INT_ENABLE {
        std ::uint8_t data_ready : 1;
        std::uint8_t single_tap : 1;
        std::uint8_t double_tap : 1;
        std::uint8_t activity : 1;
        std::uint8_t inactivity : 1;
        std::uint8_t free_fall : 1;
        std::uint8_t watermark : 1;
        std::uint8_t overrun : 1;
    } PACKED;

    struct INT_MAP {
        std::uint8_t data_ready : 1;
        std::uint8_t single_tap : 1;
        std::uint8_t double_tap : 1;
        std::uint8_t activity : 1;
        std::uint8_t inactivity : 1;
        std::uint8_t free_fall : 1;
        std::uint8_t watermark : 1;
        std::uint8_t overrun : 1;
    } PACKED;

    struct INT_SOURCE {
        std::uint8_t data_ready : 1;
        std::uint8_t single_tap : 1;
        std::uint8_t double_tap : 1;
        std::uint8_t activity : 1;
        std::uint8_t inactivity : 1;
        std::uint8_t free_fall : 1;
        std::uint8_t watermark : 1;
        std::uint8_t overrun : 1;
    } PACKED;

    struct DATA_FORMAT {
        std::uint8_t self_test : 1;
        std::uint8_t spi : 1;
        std::uint8_t int_invert : 1;
        std::uint8_t : 1;
        std::uint8_t full_res : 1;
        std::uint8_t justify : 1;
        std::uint8_t range : 2;
    } PACKED;

    struct DATA_X {
        std::uint16_t data_x : 16;
    } PACKED;

    struct DATA_Y {
        std::uint16_t data_y : 16;
    } PACKED;

    struct DATA_Z {
        std::uint16_t data_z : 16;
    } PACKED;

    struct DATA {
        DATA_X data_x;
        DATA_Y data_y;
        DATA_Z data_z;
    } PACKED;

    struct FIFO_CTL {
        std::uint8_t fifo_mode : 2;
        std::uint8_t trigger : 1;
        std::uint8_t samples : 5;
    } PACKED;

    struct FIFO_STATUS {
        std::uint8_t fifo_trig : 1;
        std::uint8_t : 1;
        std::uint8_t entries : 6;
    } PACKED;

    struct Config {
        THRESH_TAP thresh_tap{};
        OFSX ofsx{};
        OFSY ofsy{};
        OFSZ ofsz{};
        DUR dur{};
        LATENT latent{};
        WINDOW window{};
        THRESH_ACT thresh_act{};
        THRESH_INACT thresh_inact{};
        TIME_INACT time_inact{};
        ACT_INACT_CTL act_inact_ctl{};
        THRESH_FF thresh_ff{};
        TIME_FF time_ff{};
        TAP_AXES tap_axes{};
        BW_RATE bw_rate{};
        POWER_CTL power_ctl{};
        INT_ENABLE int_enable{};
        INT_MAP int_map{};
        DATA_FORMAT data_format{};
        FIFO_CTL fifo_ctl{};
    };

}; // namespace ADXL345

#undef PACKED

#endif // ADXL345_REGISTERS_HPP
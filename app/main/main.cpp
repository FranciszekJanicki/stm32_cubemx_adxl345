#include "main.h"
#include "adxl345.hpp"
#include "gpio.h"
#include "i2c.h"
#include "i2c_device.hpp"
#include "usart.h"

namespace {

    volatile auto interrupt = false;

};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    interrupt = true;
}

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_USART2_UART_Init();
    MX_GPIO_Init();
    MX_I2C1_Init();

    using namespace Utility;
    using namespace ADXL345;

    auto adxl345 = ADXL345::ADXL345{};

    while (true) {
        if (interrupt) {
            auto const& [x, y, z] = adxl345.get_acceleration_scaled().value();
            std::printf("acceleration x: %f, y: %f, z: %f\n\r", x, y, z);
            interrupt = false;
        }
    }

    return 0;
}

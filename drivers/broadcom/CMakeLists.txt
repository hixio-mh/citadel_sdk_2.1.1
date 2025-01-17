zephyr_library_include_directories(${ZEPHYR_BASE}/include/broadcom/drivers)
zephyr_library_include_directories(${ZEPHYR_BASE}/boards/arm/${BOARD})
# To allow drivers to access other private driver apis
zephyr_library_include_directories(${ZEPHYR_BASE}/drivers/broadcom)

add_subdirectory(clock_control)
add_subdirectory(pinmux)
add_subdirectory(timer)

add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_ADC adc)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_BBL bbl)
IF (${CONFIG_BRCM_DRIVER_BBL} OR ${CONFIG_BRCM_DRIVER_RTC})
add_subdirectory(spru)
ENDIF()
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_CRYPTO crypto)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_CRYPTO pka)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_DMA dma)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_DMU dmu)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_FT flextimer)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_GPIO gpio)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_I2C i2c)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_KEYPAD keypad)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_ADC msr)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_LCD lcd)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_PM pm)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_PRINTER printer)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_PWM pwm)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_QSPI qspi_flash)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_RTC rtc)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SCC sc)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SDIO sdio)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SMAU smau)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SMC smc)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SOTP sotp)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SPI spi)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_SPL spl)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_UNICAM unicam)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_USB usb)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_WDT wdt)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_USBD usbd)
add_subdirectory_ifdef(CONFIG_BRCM_DRIVER_USBH usbh)

#Zephyr v1.9 to v1.14 function name changes
zephyr_compile_definitions(-D_timer_cycle_get_32=z_timer_cycle_get_32)
zephyr_compile_definitions(-D_sys_clock_driver_init=z_clock_driver_init)
zephyr_compile_definitions(-Dmin=MIN -Dmax=MAX)
zephyr_compile_definitions(-DUSBD_CB_HAS_PARAM)

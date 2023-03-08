![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Network Application Examples for SAM A7G5 Family v3.0.0
The applications demonstrate the typical usage of Harmony 3 TCP/IP Stack on a hardware board with SAMA7G54 device.
- All applications use MCC for configuration.
- All applications created with TCP/IP Configurator Plugin (beta).

### New Features
- None

### Known Issues
- TCP/IP Configurator plugin fails to open when TCP/IP heap type is selected as 'TCPIP_STACK_HEAP_TYPE_EXTERNAL_HEAP'.
- "JLink failed to write" error when programming SAMA7G54_EK with MPLAB X IDE v6.05. We do not see this issue when programming the board with MPLAB X IDE v6.00
- PC-Lint reports following MISRA violations:
    - Variable 'tx_frame_state' (line 691) may not have been initialized [MISRA 2012 Rule 9.1, mandatory] in driver/gmac/src/dynamic/drv_gmac_lib_samA7G5.c(736)
    - Symbol 'args' (line 320) not initialized [MISRA 2012 Rule 9.1, mandatory] in system/console/src/sys_console.c(340)

### Development Tools

- [MPLAB® X IDE v6.05](https://www.microchip.com/mplab/mplab-x-ide) or later
- [MPLAB® XC32 C/C++ Compiler v4.20](https://www.microchip.com/mplab/compilers) or later
- MPLAB® Code Configurator (MCC), 5.2.1 or later


### Development Kit Support

This release supports applications for the following development kit.

| Development Kits |
| --- |
| [SAMA7G54-EK](https://www.microchip.com/en-us/development-tool/EV21H18A) |



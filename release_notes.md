![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Network Application Examples for SAM A7G5 Family, v3.1.0

### New Features
- Support for MAC RX/TX Checksum offload feature.
- Support for GMAC RGMII/GMII 10/100 speed.


### Improvements and Bug Fixes
- IPERF throughput improvement.
- Fix for GMAC driver critical section access issue.
- ETHPHY driver write function.
- Fix for bind operation in berkeley module.
- Fix for 'IntegerSymbol not found' MCC failure.
- Updated demo documentation.

### Known Issues
- wolfssl_tcp_client with FreeRTOS fails during TLS Handshake.


### Development Tools

- [MPLAB® X IDE, v6.15](https://www.microchip.com/mplab/mplab-x-ide) or later
- [MPLAB® XC32 C/C++ Compiler, v4.35](https://www.microchip.com/mplab/compilers) or later
- [MPLAB® Code Configurator(MCC) Plugin, v5.3.7](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator) or later
- [MPLAB® Harmony v3 net repository, v3.11.0](https://github.com/Microchip-MPLAB-Harmony/net/tree/v3.11.0)
- [MPLAB® Harmony v3 net\_apps\_sam\_a7g5 demo apps repository, v3.1.0](https://github.com/Microchip-MPLAB-Harmony/net_apps_sam_a7g5/tree/v3.1.0)

### Development Kit Support

This release supports applications for the following development kit.

| Development Kits |
| --- |
| [SAMA7G54-EK](https://www.microchip.com/en-us/development-tool/EV21H18A) |


## Net Release Notes

- See the [Net 3.11.0 Release Notes](https://github.com/Microchip-MPLAB-Harmony/net/tree/v3.11.0)

---

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



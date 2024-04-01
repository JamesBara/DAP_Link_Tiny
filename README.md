# DAP_Link_Tiny

Customized Port of CMSIS-DAP for STM32L412.

CMSIS-DAP can be found here https://github.com/ARM-software/CMSIS-DAP

CMSIS-DAP has been stripped down to only 2 pin Serial Wire Debugging. 
The bare minimum Microsoft OS 2.0 descriptor has been added to provide pnp capabilities on Windows 10 and above devices.

The project has been minimally tested on Windows 10. Seems to Work fine with OpenOCD and gdb.

Untested stuff:
Downloading or Uploading firmware to a target device, ergo double buffer transfers.
Hardware Reset pin.

May have some inconsistencies in style.

@todo:
main.c file double buffer transfer functions.
Comments, documentation, etc.
User options for pinout.








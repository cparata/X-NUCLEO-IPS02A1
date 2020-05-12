# X-NUCLEO-IPS02A1

The X-NUCLEO-IPS02A1 provides an affordable and easy-to-use solution for driving grounded loads
(i.e. heating elements, solenoid driver, LED driver, light bulb driver, pumps relay replacement, and fans)
in STM32 Nucleo projects. The X-NUCLEO-IPS02A1 expansion board is based on the VPS2535H a double channel
High Side Driver through a 3 V and 5 V CMOS-compatible interface and with multisense analog feedback and protections.
The device VPS2535H integrates advanced protective functions such as the load current limitation protects the device
in overload conditions. The device latches off in case of overload or thermal shutdown.

## Examples

There is 1 example with the X-NUCLEO-IPS02A1 library.
* X_NUCLEO_IPS02A1_HelloWorld: This application provides a simple example of usage of the X-NUCLEO-IPS02A1 
24V Intelligent Power Switch Expansion Board. The example performs current measurements on output Channel 1 (Ch1)
and Channel 2 (Ch2), continuously, in several conditions. For each configuration, the current for each channel is
displayed over an opened console (use Hyperterminal or whatever, set 115200 as bauds, 8-bit data, no parity).

## Documentation

You can find the source files at  
https://github.com/stm32duino/X-NUCLEO-IPS02A1

The VPS2535H datasheet is available at  
https://www.st.com/content/st_com/en/products/automotive-analog-and-power/high-and-low-side-drivers-switches/high-side-switches/vps2535h.html

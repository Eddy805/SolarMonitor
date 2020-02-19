# SolarMonitor
Monitor solar system

test: :tokyo_tower: 

Arduino monitors:
* Battery voltage
* Battery current (charge/discharge)
* ~~Solarpanel(s) voltage~~
* Solarpanel(s) current
* ~~Load voltage~~
* Load current

_Unfortunately, when using a common positive system, like the used solar charger, other voltages than it's supplying voltage, cannot be measured (with a simple voltage divider sensor). Maybe later..._

_Think about: measure current over known resistance will provide voltage? Efficiency? Smaller current more efficient, but more difficult to measure?_

_The standard +/- 2A current sensor has a resolution of ~ 4 mA. 12V would need (R=V/I) 3k resistor (disipating V*I = 48 mW). 18V would show up as (I=V/R) 6mA -- not enough resolution, higher current is needed, resulting in too high wattage to be efficient for a coninuous measuring._



Needs ~~6~~ 4 analog inputs -> Arduino Mega for future expansion (temp, other voltages, etc.)

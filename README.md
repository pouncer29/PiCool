# PiCool
A very simple service to cool my raspi when it needs cooling.

## Getting Started
To Use PiCool

1. Clone the repo
2. Run the Configure script


## The Configure script
### Usage
```
BEGIN PICOOL CONFIG
usage
config <dangerTemp> <pollTime> <ouputPin>
dangerTemp - The temperature in degrees Celcius at which if crossed, fan is activated
pollTime - the time in seconds to check the pi's temperature
outputPin - The pin that is hooked up to the power for the fan
```
**NOTE**: You'll want to have your outputPin set to a `GPIO` (See more in Misc)

### Whats Going on?
The Configure script...
1. Creates a configued python script that will poll every `<PollTime>` seconds to see if
the temperature has surpassed `<DangerTemp>` and if so, start a fan connected to pin `<OutputPin>`.
2. Creates a Linux service to run the script on startup.
3. May create an alias that will tell you what the current status of the fan/ temp of the pi is (If you ask nice)

### Reconfiguring
To Reconfigure the script, you'll need to...
1. Call configure again with new parameters...
2. There will be a message about the fan service already exisiting. This can be ignored.

### Logs
The Execution and activation of the Logs is logged with the Service. The configure script will create an alias that lists the last log message containing the temperature if you choose it in the `configure` script.

## Misc
### My Cooling Aparatus
[This is the cooling aparatus I got](https://www.amazon.ca/gp/product/B07MW3GM1T/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1) but the script will work for anything that depends on temperature and is hooked up to the configured pin.

### Speaking Of Pins...
Here are the [pinouts for Raspi's](https://maker.pro/raspberry-pi/tutorial/raspberry-pi-4-gpio-pinout) (3 and 4 I think)

This is just a test for commit or something. Does Pull need creds?


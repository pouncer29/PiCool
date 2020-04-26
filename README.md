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
### Whats Going on?
The Configure script...
1. Creates a configued python script that will poll every `<PollTime>` seconds to see if
the temperature has surpassed `<DangerTemp>` and if so, start a fan connected to pin `<OutputPin>`.
2. Creates a Linux service to run the script on startup.

### Reconfiguring
To Reconfigure the script, you'll need to...
1. Call configure again with new parameters. 
2. **NOTE** you will not be able to reconfigure the service (which you shouldn't anyway) unless you go to 
`/etc/systemd/system` and remove the `FanService.service`. Then Call reconfigure again.

### Logs
The Execution and activation of the Logs is logged in `../PiCool/Logs/piTempLog.csv`

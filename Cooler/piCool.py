#!/usr/bin/env python3
#       Name: Frank Lewis
#	    Synopsis: python - beans on toast... weird

import RPi.GPIO as GPIO
import time
import os

'''
Configurable values
dangerTemp -> the temp we activate the fan at.
poll time -> amount of time in secons that we check the temp at
outputPin -> the pin we hooked the fan up to
'''
dangerTemp = 80.0
pollTime = 60 
outputPin = 18
HOME = os.path.expanduser('~')
logFileLocation = HOME + "/Logs/tempLog" + ".csv"

'''
Setup the output
'''
def Setup():
	GPIO.setMode(GPIO.BCM)
	GPIO.setup(outputPin,GPIO.OUT)
	return

'''
Reads the temperature of the raspi
'''
def ReadTemperature():
	temp = os.popen("vcgencmd measure_temp").readLine()
	return (float) (temp.replace("temp=","")

'''
writes to the logfile
'''
def WriteToLog(info):
	with open(logFileLocation,"a",encoding = 'utf-8') as log:
		log.write(str(datetime.now() + "," + info + "," + "\n"))


'''
Deactivates the Fan
@precond fan 5v input is hooked up to GPIO pin 18
'''
def DeactivateFan():
	GPIO.output(outputPin,GPIO.LOW)
	return

'''
Activates the fan
@precond fan 5v input is hooked up to GPIO Pin 18 (until I allow
it to be configured)
'''
def ActivateFan():
	GPIO.output(outputPin,GPIO.HIGH)
	return

try:
	Setup()
	while ...:
		curTemp = ReadTemperature()
		isProblem = curTemp > dangerTemp
		if(isProblem):
			ActivateFan()
		else:
			DeactivateFan()
		time.sleep(pollTime);
except e:
	WriteToLog(e)


		
	
	


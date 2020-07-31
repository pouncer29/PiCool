#!/usr/bin/env python3
#       Name: Frank Lewis
#	    Synopsis: python - beans on toast... weird

import RPi.GPIO as GPIO
from systemd import journal
import time
import random
import sys
import os

'''
Configurable values
dangerTemp -> the temp we activate the fan at.
poll time -> amount of time in secons that we check the temp at
outputPin -> the GPIO pin we hooked the fan up to
logFileLocation -> where the logs go
'''
dangerTemp = 55
pollTime = 30
outputPin = 18
reader = "landscape-sysinfo"

'''
Setup the output
'''
def Setup():
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(outputPin,GPIO.OUT)
	WriteToLog("Setup Fan Control on Pin: " + str(outputPin))
	return

'''
Reads the temperature of the raspi
'''
def ReadTemperature():
	temp = "0.0"
	if reader is 'vgencmd':
		temp = os.popen("vcgencmd measure_temp").readline()
		temp = temp.replace("'C","")
		temp = temp.replace("temp=","")
	elif reader is 'landscape-sysinfo':
		temp = os.popen("landscape-sysinfo --sysinfo-plugins=Temperature").readline()
		temp = temp.replace("C","")
		temp = temp.replace("Temperature:","")
		temp = temp.strip()
	else:
		WriteToLog("No suitable method of reading temperature found. See documentation")

	return (float) (temp)

'''
	Writes to the service log
'''
def WriteToLog(info,firstEntry=False):
	logEntry = str(info) + "\n"
	journal.write(logEntry)
	#print(logEntry)
	return

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
	WriteToLog("Beginning Script: " +
	"Initial temp is: " + str(ReadTemperature()) + "C. " +
	"OutputPin is: "+ str(outputPin) +
	" Polling Time: "+ str(pollTime) + "s. " +
	"Danger Temp: " + str(dangerTemp) + "C. ",True)
	
	Setup()
	DeactivateFan()
	wasActive = False
	counter = 0;

	while ...:
		curTemp = ReadTemperature()
		isProblem = curTemp > dangerTemp
		logMessage = ""

		# If it's been awhile, we should show what's going on.
		if(not wasActive and not isProblem and counter > 10):
			logMessage = "MAINTAINED INACTIVE"	

		if(isProblem):
			ActivateFan()
			logMessage = "ACTIVATED FAN"
			if(wasActive):
				logMessage = "MAINTAINTED FAN"
			wasActive = True
		elif(wasActive and  not isProblem):
			DeactivateFan()
			logMessage = "DEACTIVATED FAN"
			wasActive = False

		if(logMessage != ""):
			WriteToLog(logMessage + "," + str(curTemp));

		counter += 1
		time.sleep(pollTime);
except Exception as e:
	WriteToLog(e)
finally:
	GPIO.cleanup()
		
GPIO.cleanup()
	
	


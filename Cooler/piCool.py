#!/usr/bin/env python3
#       Name: Frank Lewis
#	    Synopsis: python - beans on toast... weird

import RPi.GPIO as GPIO
import time
import random
from datetime import datetime
import os

'''
Configurable values
dangerTemp -> the temp we activate the fan at.
poll time -> amount of time in secons that we check the temp at
outputPin -> the pin we hooked the fan up to
logFileLocation -> where the logs go
'''
dangerTemp = 40
pollTime = 15
outputPin = 18
logFileLocation = "/home/pi/Projects/PiCool/Logs/piTempLog.csv"

#HOME = os.path.expanduser('~')
#logFileLocation = HOME + "/Logs/piTempLog" + ".csv"


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
	temp = os.popen("vcgencmd measure_temp").readline()
	temp = temp.replace("'C","")
	temp = temp.replace("temp=","")
	#print("Read Temp is" + temp);
	return (float) (temp)

'''
	writes to the logfile
'''
def WriteToLog(info,firstEntry=False):
	logEntry = str(datetime.now()) + "," + str(info) + "\n"
	mode = "a"
	#print(logEntry)
	if(firstEntry):
		mode = "w"
	else:
		mode = "a"

	with open(logFileLocation,mode,encoding = 'utf-8') as log:
		log.write(logEntry)
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
	wasActive = False
	counter = 0;

	while ...:
		curTemp = ReadTemperature()
		#curTemp = random.uniform(50,100)
		isProblem = curTemp > dangerTemp
		logMessage = ""
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
		
		# If it's been awhile, we should show what's going on.
		if(not wasActive and not isProblem and counter > 10):
			logMessage = "MAINTAINED INACTIVE"	

		if(logMessage != ""):
			WriteToLog(logMessage + "," + str(curTemp));

		counter += 1
		time.sleep(pollTime);
except Exception as e:
	WriteToLog(e)
finally:
	GPIO.cleanup()


		
GPIO.cleanup()
	
	


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
dangerTemp = <DANGERTEMP>
pollTime = <POLLTIME>
outputPin = <OUTPUTPIN>
logFileLocation = <LOGLOCATION>

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
def WriteToLog(info):
	logEntry = str(datetime.now()) + "," + str(info) + "\n"
	#print(logEntry)
	with open(logFileLocation,"a",encoding = 'utf-8') as log:
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
	"Danger Temp: " + str(dangerTemp) + "C. ")
	
	Setup()
	wasActive = False
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

		if(logMessage != ""):
			WriteToLog(logMessage + "," + str(curTemp));

		time.sleep(pollTime);
except Exception as e:
	WriteToLog(e)
finally:
	GPIO.cleanup()


		
GPIO.cleanup()
	
	


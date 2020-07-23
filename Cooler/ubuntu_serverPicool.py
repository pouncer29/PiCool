#!/usr/bin/env python3
#       Name: Frank Lewis
#	    Synopsis: python - beans on toast... weird
import logging
import time
import random
import sys
import os
from systemd import journal

'''
Configurable values
dangerTemp -> the temp we activate the fan at.
poll time -> amount of time in secons that we check the temp at
outputPin -> the GPIO pin we hooked the fan up to
'''
dangerTemp = 60
pollTime = 60
outputPin = 18
sysfs_root = "/sys/class/gpio"
control_root = "/sys/class/gpio/"+"gpio"+str(outputPin)

'''
Setup the output
'''
def Setup():
	sysfs_root = "/sys/class/gpio"
	#Setup Sysfile
	WriteToLog("sysfs_root: " + sysfs_root)
	sysfs_setup = open(sysfs_root+"/export","w",2)
	sysfs_setup.write(str(outputPin))
	
	#change root
	control_root = sysfs_root + "/gpio" + str(outputPin)
	
	WriteToLog("control_root: " + control_root)
	sysfs_handle = open(control_root+"/direction", "w")

	# setup handle 
	if(sysfs_handle):
		sysfs_handle.write("out")
		WriteToLog("Setup Fan Control on Pin: " + str(outputPin))
	else:
		WriteToLog("Could not setup fan control. Are you root?",level="E")
	return

'''
Reads the temperature of the raspi
'''
def ReadTemperature():
	temp = os.popen("landscape-sysinfo --sysinfo-plugins=Temperature").readline()
	temp = temp.replace("C","")
	temp = temp.replace("Temperature:","")
	temp = temp.strip()
	return (float) (temp)

'''
	Writes to the service log
'''
def WriteToLog(info,firstEntry=False,level='I'):
	logEntry = str(info) + "\n"
	journal.write(logEntry)
	print(logEntry)

'''
Deactivates the Fan
@precond fan 5v input is hooked up to GPIO pin 18
'''
def DeactivateFan():
	sysfs_handle = open(control_root+"/value", "w")
	if(sysfs_handle):
		sysfs_handle.write("0")
	else:
		WriteToLog("Could not Deactiate fan",level="E");

	return

'''
Activates the fan
@precond fan 5v input is hooked up to GPIO Pin 18 (until I allow
it to be configured)
'''
def ActivateFan():
	sysfs_handle = open(control_root+"/value", "w")
	if(sysfs_handle):
		sysfs_handle.write("1")
	else:
		WriteToLog("Could not Activate fan",level="E");

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
	
	


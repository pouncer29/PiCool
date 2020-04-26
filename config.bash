#! /bin/bash

function usage () {
	echo "usage"
	echo "config <dangerTemp> <pollTime> <ouputPin>"
	echo "dangerTemp - The temperature at which if crossed, fan is activated"
	echo "pollTime - the time in seconds to check the pi's temperature"
	echo "outputPin - The pin that is hooked up to the power for the fan"
}


#Lets Go
echo "BEGIN PICOOL CONFIG"

if [ $# -ne 3 ]; then
	usage
	exit 1
fi

#Check Params are what we expect
egrep -q "^[0-9]*$" <<< $1$2$3
if [ $? -ne 0 ]; then
	usage
	exit 1
fi

LOGPATH="`pwd`/Logs/piTempLog.csv"
TEMPLATE="`pwd`/Cooler/unconfigured.txt"
echo "LOGPATH: $LOGPATH"
echo "TEMPLATE: $TEMPLATE"

#Preform Replacement
sed -i "s/<DANGERTEMP>/$1/g" $TEMPLATE
sed -i "s/<POLLTIME>/$2/g" $TEMPLATE
sed -i "s/<OUTPUTPIN>/$3/g" $TEMPLATE
sed -i "s|<LOGLOCATION>|\"$LOGPATH\"|g" $TEMPLATE
echo "RESULT IS"
head -n 21 $TEMPLATE
## TODO
#1. Configure the Script
#a. poll time
#b. danger temp
#c. outPin

#2. Configure the Service
#a. Add Path to pyScript in service
#b. If Service Exists, don't do it.
#c. But if it doesn't, link it


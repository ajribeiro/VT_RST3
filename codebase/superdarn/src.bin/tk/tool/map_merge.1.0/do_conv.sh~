#!/bin/bash -x

rm /rst/output_files.mconv.txt

#iterate through a certain number of days
for (( i = 0 ; i < 365; i++ ))
do

	#target start date, day before, and day after
	today=$((`date --date="1 Jan 2010 +$i days" +%Y%m%d`))

	#now, filter the data, change this fitex to fitacf, bfc=box car filter combined (camping beams)

	#check if filtered file exists
	if [ -e "/data/raw/merge/${today}.bks.fhe.merge" ] && [ -s "/data/raw/merge/${today}.bks.fhe.merge" ]
	then
		#if file does not exist, create it
		map_merge /data/raw/merge/${today}.bks.fhe.merge
	fi

done
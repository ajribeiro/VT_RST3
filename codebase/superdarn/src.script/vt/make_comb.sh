#!/bin/bash -x
cd /data/fit/aj/temp_files
for (( i = 0 ; i < 365; i++ ))
do
	date=$((`date --date="1 Jan 2010 +$i days" +%Y%m%d`))
	SD_RADAR=/rst/tables/superdarn/radar.dat
	export SD_RADAR
	SD_HDWPATH=/rst/tables/superdarn/hdw/
	export SD_HDWPATH

	if [ -e "/data/raw/pscat/$date.bks.pscat" ] && [ -s "/data/raw/pscat/$date.bks.pscat" ] && [ -e "/data/raw/pscat/$date.fhe.pscat" ] && [ -s "/data/raw/pscat/$date.fhe.pscat" ]
	then
		merge_vec -vb -nogs /data/raw/pscat/$date.bks.pscat /data/raw/pscat/$date.fhe.pscat > /data/raw/merge/$date.bks.fhe.merge
		FILESIZE=$(stat -c%s "/data/raw/merge/$date.bks.fhe.merge")
		echo $FILESIZE
		if [[ $FILESIZE -eq 0 ]]
		then
			rm /data/raw/merge/$date.bks.fhe.merge
		fi
	fi
done
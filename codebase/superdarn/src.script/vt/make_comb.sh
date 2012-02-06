#!/bin/bash -x
cd /data/fit/aj/temp_files
for (( i = 0 ; i < 365; i++ ))
do
	date=$((`date --date="1 Jan 2010 +$i days" +%Y%m%d`))
	SD_RADAR=/rst/tables/superdarn/radar.dat
	export SD_RADAR
	SD_HDWPATH=/rst/tables/superdarn/hdw/
	export SD_HDWPATH

	if [ -e "/data/pscat/$date.bks.pscat" ] && [ -s "/data/pscat/$date.bks.pscat" ] && [ -e "/data/pscat/$date.fhe.pscat" ] && [ -s "/data/pscat/$date.fhe.pscat" ]
	then
		merge_vec -vb -nogs -botrng 10 -toprng 45 /data/pscat/$date.bks.pscat /data/pscat/$date.fhe.pscat > /data/merge/$date.bks.fhe.pscat.merge
		FILESIZE=$(stat -c%s "/data/merge/$date.bks.fhe.pscat.merge")
		echo $FILESIZE
		if [[ $FILESIZE -eq 0 ]]
		then
			rm /data/merge/$date.bks.fhe.pscat.merge
		fi
	fi
done
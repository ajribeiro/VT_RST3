rm /rst/output_files/v_w_scat.txt
for (( i = 0 ; i < 365; i++ ))
do
	date=$((`date --date="1 Jan 2010 +$i days" +%Y%m%d`))
	SD_RADAR=/rst/tables/superdarn/radar.dat
	export SD_RADAR
	SD_HDWPATH=/rst/tables/superdarn/hdw/
	export SD_HDWPATH

	if [ -e "/data/merge/$date.bks.fhe.pscat.merge" ]
	then
		read_merge /data/merge/$date.bks.fhe.pscat.merge >> /rst/output_files/v_w_scat.txt
	fi
done
date=$1
sthr=$2
edhr=$3
bot=$4
top=$5

SD_RADAR=/rst/tables/superdarn/radar.dat
export SD_RADAR
SD_HDWPATH=/rst/tables/superdarn/hdw/
export SD_HDWPATH

merge_vec -vb -sthr $sthr -edhr $edhr -toprng $top -botrng $bot /data/fit/$date.bks.fitexbfc /data/fit/$date.fhe.fitexbfc > /data/raw/merge/$date.bks.fhe.merge

FILESIZE=$(stat -c%s "/data/raw/merge/$date.bks.fhe.merge")
echo $FILESIZE
if [[ $FILESIZE -eq 0 ]]
then
	rm /data/raw/merge/$date.bks.fhe.merge
fi

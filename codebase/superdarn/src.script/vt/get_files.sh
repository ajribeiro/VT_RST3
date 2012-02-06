#!/bin/bash -x

yr=$1
mon=$2
day=$3
rad=$4

cp /sd-data/${yr}/rawacf/${rad}/${yr}${mon}${day}*${rad}*rawacf* /data/tmp
bunzip2 /data/tmp/${yr}${mon}${day}*${rad}*rawacf.bz2
gunzip /data/tmp/${yr}${mon}${day}*${rad}*rawacf.gz

cat /data/tmp/${yr}${mon}${day}*${rad}*rawacf > /data/raw/${yr}${mon}${day}.${rad}.rawacf

make_fitex2 -new /data/raw/${yr}${mon}${day}.${rad}.rawacf > /data/fit/${yr}${mon}${day}.${rad}.fitex

/data/fit/aj/fan_data/fan_data /data/fit/${yr}${mon}${day}.${rad}.fitex > /data/raw/fan/${yr}${mon}${day}.${rad}.fandat

fitexfilter /data/fit/${yr}${mon}${day}.${rad}.fitex > /data/fit/${yr}${mon}${day}.${rad}.fitexbfc

/data/fit/aj/fan_data/fan_data /data/fit/${yr}${mon}${day}.${rad}.fitexbfc > /data/raw/fan/${yr}${mon}${day}.${rad}.fandatf

fitexfilter -nocomb /data/fit/${yr}${mon}${day}.${rad}.fitex > /data/fit/${yr}${mon}${day}.${rad}.fitexbfnc


rm /data/tmp/${yr}${mon}${day}*${rad}*




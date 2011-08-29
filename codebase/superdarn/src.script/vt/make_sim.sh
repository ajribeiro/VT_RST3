#!/bin/bash -x
echo > /data/raw/100.rawacf
vel=1550
noise=25
t=50
make_sim -vel $vel -t_d $t -amp 100 -nocri -n_good 1  -noise $noise > /data/raw/1000002.rawacf
for (( i = 1 ; i < 100000; i++ ))
do
  c=$[ $i % 500 ]
  if test $c -eq 0
  then
		t=$[$t+10]
		if test $t -gt 100
		then
			t=10
		fi
  fi
  c=$[ $i % 5000 ]
  if test $c -eq 0
  then
    vel=$[$vel+100]
  fi
  make_sim -vel $vel -t_d $t -amp 100 -nocri -n_good 1  -noise $noise >> /data/raw/1000002.rawacf
done
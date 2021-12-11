#!/bin/bash
#dht11经常犯病，写个脚本检测一下避免犯病

ret=`/usr/bin/python3 /home/pi/Weather-Pi/indoor/getIndoorT.py | grep I`

if [[ -n $ret ]];then
    echo $ret > /home/pi/Weather-Pi/indoor/data
    echo $ret
else
    cat /home/pi/Weather-Pi/indoor/data
fi

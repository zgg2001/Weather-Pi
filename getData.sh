#!/bin/bash

#室外天气与气温
cat /home/pi/work/outdoor/data
#室内温湿度
/usr/bin/python3 /home/pi/work/indoor/getIndoorT.py
#ip获取 优先检测wlan0随后检测eth0
wlan=`ifconfig wlan0 | grep inet | awk 'NR==1{print $2}'`
eth=`ifconfig eth0 | grep inet | awk 'NR==1{print $2}'`
if [ -n "$wlan" ];then
    echo "wlan0: $wlan"
elif [ -n "$eth" ];then
    echo "eth0: $eth"
else
    echo "No internet connection"
fi


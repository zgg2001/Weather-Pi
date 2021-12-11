#!/bin/bash

curl -sS wttr.in/ZhengZhou | awk 'NR>2&&NR<7{print}' > /home/pi/Weather-Pi/outdoor/weather
weather=`cat /home/pi/Weather-Pi/outdoor/weather | awk 'NR==1{print}' | grep -o [A-Z].*[a-z]`
temp=`cat /home/pi/Weather-Pi/outdoor/weather | awk 'NR==2{print}' | grep -o "\+[0-9]*"`
echo "Weather: $weather" > /home/pi/Weather-Pi/outdoor/data
echo "O TEMP: $temp °C" >> /home/pi/Weather-Pi/outdoor/data

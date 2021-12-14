# SPDX-FileCopyrightText: 2017 Tony DiCola for Adafruit Industries
# SPDX-FileCopyrightText: 2017 James DeVito for Adafruit Industries
# SPDX-License-Identifier: MIT

# This example is for use on (Linux) computers that are using CPython with
# Adafruit Blinka to support CircuitPython libraries. CircuitPython does
# not support PIL/pillow (python imaging library)!

import time
import subprocess
import os
import signal

from board import SCL, SDA
import busio
from PIL import Image, ImageDraw, ImageFont
import adafruit_ssd1306

signal.signal(signal.SIGPIPE, signal.SIG_DFL)

# Create the I2C interface.
i2c = busio.I2C(SCL, SDA)

# Create the SSD1306 OLED class.
# The first two parameters are the pixel width and pixel height.  Change these
# to the right size for your display!
disp = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c)

# Clear display.
disp.fill(0)
disp.show()

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = disp.width
height = disp.height
image = Image.new("1", (width, height))

# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)

# Draw a black filled box to clear the image.
draw.rectangle((0, 0, width, height), outline=0, fill=0)

# Draw some shapes.
# First define some constants to allow easy resizing of shapes.
padding = -2
top = padding
bottom = height - padding
# Move left to right keeping track of the current x position for drawing shapes.
x = 0


# Load default font.
font = ImageFont.load_default()

# Alternatively load a TTF font.  Make sure the .ttf font file is in the
# same directory as the python script!
# Some other nice fonts to try: http://www.dafont.com/bitmap.php
# font = ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf', 9)

for num in range(1,8):    
    draw.rectangle((0, 0, width, height), outline=0, fill=0)
    draw.text((x, top + 0), "Zhao's PI", font=font, fill=255)
    draw.text((x, top + 8), "Starting up...", font=font, fill=255)
    draw.text((x, top + 16), "...init...", font=font, fill=255)
    draw.text((x, top + 25), "Time: " + str(12 - num), font=font, fill=255)
    disp.image(image)
    disp.show()
    time.sleep(1)

#开机自启后尝试更新天气
os.system('/usr/bin/bash /home/pi/Weather-Pi/outdoor/getOutdoor.sh &')

for num in range(8,12):    
    draw.rectangle((0, 0, width, height), outline=0, fill=0)
    draw.text((x, top + 0), "Zhao's PI", font=font, fill=255)
    draw.text((x, top + 8), "Starting up...", font=font, fill=255)
    draw.text((x, top + 16), "...update...", font=font, fill=255)
    draw.text((x, top + 25), "Time: " + str(12 - num), font=font, fill=255)
    disp.image(image)
    disp.show()
    time.sleep(1)

while True:

    # Draw a black filled box to clear the image.
    draw.rectangle((0, 0, width, height), outline=0, fill=0)

    # Shell scripts for system monitoring from here:
    # https://unix.stackexchange.com/questions/119126/command-to-display-memory-usage-disk-usage-and-cpu-load
    cmd = "/bin/bash /home/pi/Weather-Pi/getData.sh &"
    re = os.popen(cmd).readlines()
    result = []
    for i in range(0, len(re)):  # 由于原始结果需要转换编码，所以循环转为utf8编码并且去除\n换行
        res = re[i].strip('\n')
        result.append(res)

    # Write four lines of text.
    draw.text((x, top + 0), result[0], font=font, fill=255)
    draw.text((x, top + 8), result[1], font=font, fill=255)
    draw.text((x, top + 16), result[2], font=font, fill=255)
    draw.text((x, top + 25), result[3], font=font, fill=255)

    # Display image.
    disp.image(image)
    disp.show()
    time.sleep(0.1)

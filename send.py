#!/usr/bin/env python
import serial
import fileinput
import time
import sys

ser = serial.Serial('/dev/cu.usbserial-DA00XHOO', 115200, timeout=1, xonxoff=1)

for line in fileinput.input():
  line = line.strip()
  if len(line):
    print line
    ser.write(line)
    ser.write('\n')
    time.sleep(3)

print "Keepalive"
while True:
  sys.stdout.write('.')
  sys.stdout.flush()
  ser.write('\n')
  time.sleep(10)

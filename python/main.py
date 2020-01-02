#!/usr/bin/python3
import serial
import time

while True:
    try:
        ser = serial.Serial("/dev/ttyACM0", 9600)
        print("Opening serial connection to port /dev/tty/ACM0")
        break
    except(serial.serialutil.SerialException):
        print("Waiting for device at port /dev/ttyACM0 . . .")
        time.sleep(10)
        continue

ser.flushInput()
ser.flushOutput()
while True:
    line = ser.readline().decode("ASCII").split(",")
    if line[0] == "debug":
        print(line[1])

    elif line[0] == "data":
        angle = line[1]
        distance = line[2]
        print("angle = " + angle + ", distance = " + distance)
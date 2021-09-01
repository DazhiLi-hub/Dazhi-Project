import RPi.GPIO as GPIO
import time

def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(24, GPIO.IN)
    GPIO.setup(22,GPIO.OUT)
 
while True:
    setup()
    print (GPIO.input(24))
    if (GPIO.input(24)==1):
        GPIO.output(22,GPIO.HIGH)
    else:
        GPIO.output(22,GPIO.LOW)
    time.sleep(0.1)
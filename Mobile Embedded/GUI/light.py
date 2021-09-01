import RPi.GPIO as GPIO
import time

Trig_Pin_back = 23
Echo_Pin_back = 17

def whole_setup():
        
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    #initialize the ultrasound pin
    GPIO.setup(Trig_Pin_back, GPIO.OUT, initial = GPIO.LOW)
    GPIO.setup(Echo_Pin_back, GPIO.IN)
    GPIO.setup(24, GPIO.IN)
    GPIO.setup(22,GPIO.OUT)

def check_light():
    if (GPIO.input(24)==1):
        GPIO.output(22,GPIO.HIGH)
        return 1
    else:
        GPIO.output(22,GPIO.LOW)
        return 0

def LED_status():
    return 1
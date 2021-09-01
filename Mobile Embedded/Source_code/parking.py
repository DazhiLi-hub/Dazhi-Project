import RPi.GPIO as GPIO
import time


#distance detection
#define the ultrasound pin's number
Trig_Pin = 23
Echo_Pin = 17

def checkdist():
    
    GPIO.output(Trig_Pin, GPIO.HIGH) #send the ultrasound signal

    time.sleep(0.00015)

    GPIO.output(Trig_Pin,GPIO.LOW)

        #according to the time difference between the ultrasound signal's leave and back

        #calculate the distance, and return it.

    while not GPIO.input(Echo_Pin):
        pass

    t1 = time.time()
        
    while GPIO.input(Echo_Pin):
        pass

    t2 = time.time()
    return (t2 - t1)*340*100/2

def checklight():
    if (GPIO.input(24)==1):
        GPIO.output(22,GPIO.HIGH)
    else:
        GPIO.output(22,GPIO.LOW)
    time.sleep(0.1)

def main():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(24, GPIO.IN)
    GPIO.setup(22,GPIO.OUT)
    #initialize the ultrasound pin
    GPIO.setup(Trig_Pin, GPIO.OUT, initial = GPIO.LOW)
    GPIO.setup(Echo_Pin, GPIO.IN)
    while True:
        distance = checkdist()
        print ('Distance Estimation is :%0.2f cm' % distance)
        checklight()
if __name__ == "__main__":
    main()
import RPi.GPIO as GPIO
import time
#import cv2

#distance detection
#define the ultrasound pin's number
Trig_Pin_back = 23
Echo_Pin_back = 17
Trig_Pin_left = 25
Echo_Pin_left = 21

def back_checkdist():
    
    GPIO.setup(Trig_Pin_back, GPIO.OUT, initial = GPIO.LOW)
    GPIO.setup(Echo_Pin_back, GPIO.IN)
    
    GPIO.output(Trig_Pin_back, GPIO.HIGH) #send the ultrasound signal

    time.sleep(0.00015)

    GPIO.output(Trig_Pin_back,GPIO.LOW)

        #according to the time difference between the ultrasound signal's leave and back

        #calculate the distance, and return it.

    while not GPIO.input(Echo_Pin_back):
        pass

    t1 = time.time()
        
    while GPIO.input(Echo_Pin_back):
        pass

    t2 = time.time()
    return (t2 - t1)*340*100/2

def left_checkdist():
    
    GPIO.setup(Trig_Pin_left, GPIO.OUT, initial = GPIO.LOW)
    GPIO.setup(Echo_Pin_left, GPIO.IN)
    
    GPIO.output(Trig_Pin_left, GPIO.HIGH) #send the ultrasound signal

    time.sleep(0.00015)

    GPIO.output(Trig_Pin_left,GPIO.LOW)

        #according to the time difference between the ultrasound signal's leave and back

        #calculate the distance, and return it.

    while not GPIO.input(Echo_Pin_left):
        pass

    t1 = time.time()
        
    while GPIO.input(Echo_Pin_left):
        pass

    t2 = time.time()
    return (t2 - t1)*340*100/2



def main():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    

    #initialize the ultrasound pin
    GPIO.setup(Trig_Pin_back, GPIO.OUT, initial = GPIO.LOW)
    GPIO.setup(Echo_Pin_back, GPIO.IN)
    while True:
        distance = checkdist()
        print ('Distance Estimation is :%0.2f cm' % distance)
if __name__ == "__main__":
    main()
from Tkinter import *
import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import cv2
from PIL import Image,ImageTk

def camera_setup():
    camera=PiCamera()
    camera.resolution=(640,480)
    camera.framerate=30
    rawCapture=PiRGBArray(camera,size=(640,480))
    time.sleep(0.1)
'''
for frame in camera.capture_continuous(rawCapture,format="bgr",use_video_port=True):
        image=frame.array
        cv2.imshow("Frame",image)
        key=cv2.waitKey(1) & 0xFFF
        rawCapture.truncate(0)
        if key == ord("q"):
                break
'''
def video_loop():
    success, image = frame.array  
    if success:
        cv2.waitKey(1) & 0xFFF
        #cv2image = cv2.cvtColor(image, cv2.COLOR_BGR2RGBA)
        current_image = Image.fromarray(image)
        imgtk = ImageTk.PhotoImage(image=current_image)
        panel.imgtk = imgtk
        panel.config(image=imgtk)
        root.after(1, video_loop)


camera = cv2.VideoCapture(0)    

root = Tk()
root.title("opencv + tkinter")
#root.protocol('WM_DELETE_WINDOW', detector)

panel = Label(root)  # initialize image panel
panel.pack(padx=10, pady=10)
root.config(cursor="arrow")

video_loop()

root.mainloop()
camera.release()
cv2.destroyAllWindows()

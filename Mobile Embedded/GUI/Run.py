import Tkinter as tk
import threading
import distance
import light
import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import cv2
from PIL import Image,ImageTk

def camera_start():
	camera=PiCamera()
	camera.resolution=(640,480)
	camera.framerate=30
	rawCapture=PiRGBArray(camera,size=(640,480))
	time.sleep(0.1)
	for frame in camera.capture_continuous(rawCapture,format="bgr",use_video_port=True):
		image=frame.array
		cv2.imshow("Frame",image)
		key=cv2.waitKey(1) & 0xFFF
		rawCapture.truncate(0)
		if key == ord("q"):
			break 

def LED_update():
	if light.check_light()==1:
		LED_status="ON"
		LED_label.configure(text=""+LED_status,fg="green")
	else:
		LED_status="OFF"
		LED_label.configure(text=""+LED_status,fg="red")
	LED_label.after(125,LED_update)
	

def dist_update():
	dist=distance.checkdist()
	if dist >= 400:
		pass
	elif dist <=2:
		pass
	else:
		if dist < 20:
			Dist_label.configure(text="%0.2f cm \n Warning " % dist,fg="red")
		else:
			Dist_label.configure(text="%0.2f cm \n Safe" % dist,fg="green")
	Dist_label.after(125,dist_update)

def Video_update():
	success, image = camera.capture_continuous(rawCapture,format="bgr",use_video_port=True)  
	if success:
		cv2.waitKey(1) & 0xFFF
		#cv2image = cv2.cvtColor(image, cv2.COLOR_BGR2RGBA)
		current_image = Image.fromarray(image)
		imgtk = ImageTk.PhotoImage(image=current_image)
		Camera_label.imgtk = imgtk
		Camera_label.config(image=imgtk)
		root.after(1, video_loop)

def open_camera():
	camera_thread=threading.Thread(target=camera_start)
	camera_thread.start()

def close_camera():
	camera_thread.stop()

global dist
global LED_status
LED_status=light.LED_status()
light.whole_setup()
'''
camera=PiCamera()
camera.resolution(640,480)
camera.framerate=30
rawCapture=PiRGBArray(camera,size=(640,480))
time.sleep(0.1)
'''
dist=distance.checkdist()

'''
def LED_manually_on():
	btn=tk.Button.config(top,text="Manually close LED",command=LED_manually_off)
	LED_status="on"
'''

GUI=tk.Tk()
GUI.title("Parking Assistance")
GUI.geometry("300x400")

LED_information=tk.LabelFrame(GUI,text="LED status",padx=10,pady=10,height=128,width=128)
LED_information.place(x=110,y=100)
LED_label=tk.Label(LED_information,text="OFF",fg="red")
LED_label.after(125,LED_update)
LED_label.pack()

Dist_information=tk.LabelFrame(GUI,text="Distance",padx=10,pady=10,height=128,width=128)
Dist_information.place(x=65,y=200)
Print_label=tk.Label(Dist_information,text="Distance Estimation is :")
Print_label.pack()
Dist_label=tk.Label(Dist_information,text="%0.2f cm" % dist)
Dist_label.after(125,dist_update)
Dist_label.pack()

'''
Camera_window=tk.LabelFrame(GUI,text="Video",height=600,width=1024)
Camera_window.place(x=250,y=20)
Camera_label=tk.Label(Camera_window)
Camera_label.after(33,Video_update)
Camera_label.pack()
'''

camera_btn=tk.Button(GUI,text="Open Camera",command=open_camera)
camera_btn.pack()

GUI.mainloop()

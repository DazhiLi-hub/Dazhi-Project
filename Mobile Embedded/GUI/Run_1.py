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
	

def back_dist_update():
	back_dist=distance.back_checkdist()
	if back_dist >= 400:
		pass
	elif back_dist <=2:
		pass
	else:
		if back_dist < 20:
			Back_Dist_label.configure(text="%0.2f cm \n Warning " % back_dist,fg="red")
		else:
			Back_Dist_label.configure(text="%0.2f cm \n Safe" % back_dist,fg="green")
	Back_Dist_label.after(125,back_dist_update)

def left_dist_update():
	left_dist=distance.left_checkdist()
	if left_dist >= 400:
		pass
	elif left_dist <=2:
		pass
	else:
		if left_dist < 20:
			Left_Dist_label.configure(text="%0.2f cm \n Warning " % left_dist,fg="red")
		else:
			Left_Dist_label.configure(text="%0.2f cm \n Safe" % left_dist,fg="green")
	Left_Dist_label.after(125,left_dist_update)

'''
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
'''

def open_camera():
	camera_thread=threading.Thread(target=camera_start)
	camera_thread.start()

global back_dist
global left_dist
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
back_dist=distance.back_checkdist()
left_dist=distance.left_checkdist()

GUI=tk.Tk()
GUI.title("Parking Assistance")
GUI.geometry("750x750")

LED_information=tk.LabelFrame(GUI,text="LED status",padx=10,pady=10,height=128,width=128)
LED_information.place(x=335,y=30)
LED_label=tk.Label(LED_information,text="OFF",fg="red")
LED_label.after(125,LED_update)
LED_label.pack()

Dist_back=tk.LabelFrame(GUI,text="Back Distance",padx=10,pady=10,height=128,width=128)
Dist_back.place(x=270,y=640)
Back_Print_label=tk.Label(Dist_back,text="Back Distance Estimation is :")
Back_Print_label.pack()
Back_Dist_label=tk.Label(Dist_back,text="%0.2f cm" % back_dist)
Back_Dist_label.after(125,back_dist_update)
Back_Dist_label.pack()

Dist_left=tk.LabelFrame(GUI,text="Left Distance",padx=10,pady=10,height=128,width=128)
Dist_left.place(x=50,y=300)
Left_Print_label=tk.Label(Dist_left,text="Left Distance\nEstimation is :")
Left_Print_label.pack()
Left_Dist_label=tk.Label(Dist_left,text="%0.2f cm" % left_dist)
Left_Dist_label.after(125,left_dist_update)
Left_Dist_label.pack()

Car_window=tk.LabelFrame(GUI,text="Overview",height=1188,width=578)
Car_window.place(x=190,y=100)
img_open=Image.open('car.png')
img_png=ImageTk.PhotoImage(img_open)
label_img=tk.Label(Car_window,image=img_png)
label_img.pack()
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

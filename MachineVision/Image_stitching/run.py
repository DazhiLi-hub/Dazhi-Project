import cv2
import numpy as np
import matplotlib.pyplot as plt
import imageio
'''
Important Correspondence:
opencv-python-3.4.2.16
opencv-contrib-python-3.4.2.16
matplotlib-3.3.0
'''
cv2.ocl.setUseOpenCL(False)
#Train image preprocessing to gray  depth image
trainImg=cv2.imread('./Input_images/right.jpg')
trainImg=cv2.cvtColor(trainImg,cv2.COLOR_BGR2RGB)
train_gray=cv2.cvtColor(trainImg,cv2.COLOR_RGB2GRAY)

#query image preprocessing to gray depth images
queryImg = cv2.imread('./Input_images/left.jpg')
queryImg=cv2.cvtColor(queryImg,cv2.COLOR_BGR2RGB)
query_gray=cv2.cvtColor(queryImg,cv2.COLOR_RGB2GRAY)

fig, (ax1, ax2) = plt.subplots(nrows=1, ncols=2, constrained_layout=False, figsize=(16,9))
ax1.imshow(queryImg, cmap="gray")
ax1.set_xlabel("Query image", fontsize=14)

ax2.imshow(trainImg, cmap="gray")
ax2.set_xlabel("Train image (Image to be transformed)", fontsize=14)

plt.savefig("./Output_images/input_img.jpeg", bbox_inches='tight', dpi=300, optimize=True, format='jpeg')

plt.show()

#Catching SIFT features in both two images
descriptor_train=cv2.xfeatures2d.SIFT_create()
(key_points_train,features_train)=descriptor_train.detectAndCompute(train_gray,None)
descriptor_query=cv2.xfeatures2d.SIFT_create()
(key_points_query,features_query)=descriptor_query.detectAndCompute(query_gray,None)

fig, (ax1,ax2) = plt.subplots(nrows=1, ncols=2, figsize=(20,8), constrained_layout=False)
ax1.imshow(cv2.drawKeypoints(query_gray,key_points_query,None,color=(0,255,0)))
ax1.set_xlabel("Query_SIFT_features", fontsize=14)
ax2.imshow(cv2.drawKeypoints(train_gray,key_points_train,None,color=(0,255,0)))
ax2.set_xlabel("Train_SIFT_features", fontsize=14)

plt.savefig("./Output_images/SIFT_features_img"+'.jpeg', bbox_inches='tight',
            dpi=300, optimize=True, format='jpeg')
plt.show()

#We are using Brute force matching for matching image features

fig = plt.figure(figsize=(20,8))
bf=cv2.BFMatcher(cv2.NORM_L2,crossCheck=True)
best_matches=bf.match(features_query,features_train)
matches=sorted(best_matches,key=lambda x:x.distance)
print("Raw matches (Brute force):", len(matches))
feature_matching_image = cv2.drawMatches(queryImg,key_points_query,trainImg,key_points_train,matches[:100],
                           None,flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
plt.imshow(feature_matching_image)
plt.axis('off')
plt.savefig("./Output_images/BruteForce_matching_img.jpeg", bbox_inches='tight',
            dpi=300, optimize=True, format='jpeg')
plt.show()

best_matches=bf.match(features_train,features_query)
matches=sorted(best_matches,key=lambda x:x.distance)
#Do image stitching, which is creating a homography
key_points_train = np.float32([kp.pt for kp in key_points_train])
key_points_query = np.float32([kp.pt for kp in key_points_query])
if len(matches)>4:
    points_train = np.float32([key_points_train[m.queryIdx] for m in matches])
    points_query = np.float32([key_points_query[m.trainIdx] for m in matches])
    (H, status) = cv2.findHomography(points_train, points_query, cv2.RANSAC, 4)
else:
    print("Error,not so many matches found in your pics")
    exit(0)
print(H)
#Horizontal panorama stitching
width = queryImg.shape[1] + trainImg.shape[1]
height = max(queryImg.shape[0], trainImg.shape[0])

result = cv2.warpPerspective(trainImg, H,
    (width, height))
result[0:queryImg.shape[0], 0:queryImg.shape[1]] = queryImg
plt.figure(figsize=(20,10))
plt.axis('off')
plt.imshow(result)
imageio.imwrite("./Output_images/horizontal_panorama.jpeg", result)
plt.show()
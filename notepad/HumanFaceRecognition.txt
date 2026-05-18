#!/usr/bin/env python
# coding: utf-8

# In[1]:


get_ipython().system('pip install opencv-python')


# In[2]:


import cv2


# In[3]:


face_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades +
    'haarcascade_frontalface_default.xml'
)

print("Face Detection Model Loaded")


# In[4]:


cap = cv2.VideoCapture(0)

# Check webcam
if not cap.isOpened():
    print("Cannot Open Webcam")
else:
    print("Webcam Started Successfully")


# In[5]:


while True:

    # Read frame from webcam
    ret, frame = cap.read()

    
    # If frame not captured
    if not ret:
        print("Failed to capture image")
        break


    # Convert image to grayscale
    gray = cv2.cvtColor(
        frame,
        cv2.COLOR_BGR2GRAY
    )


    # Detect faces
    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30,30)
    )


    # Draw rectangle around face
    for (x, y, w, h) in faces:

        cv2.rectangle(
            frame,
            (x, y),
            (x+w, y+h),
            (0,255,0),
            2
        )


        # Add label
        cv2.putText(
            frame,
            "Human Face",
            (x, y-10),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (0,255,0),
            2
        )


    # Display output window
    cv2.imshow(
        "Human Face Recognition",
        frame
    )


    # Press q to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# In[6]:


cap.release()

cv2.destroyAllWindows()

print("Webcam Closed")


# In[ ]:


#to see webcam check taskbar for webcam window
#to stop webcan click on webcam window first then press q


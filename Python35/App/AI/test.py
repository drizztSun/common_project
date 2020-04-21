import cv2

path = "file path"

# load picture
image = cv2.imread(path)

capture = cv2.VideoCapture(0) # pause


# load face mode
face_model = cv2.CascadeClassifier('~/Download/pic/facemode.xml')

# Capture video from web cam
while True: # capture picture by fps of video

    # read each frame
    res, image = capture.read()

    # gray the frame
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

    # check the face
    faces = face_model.detectMultiScale(gray, 1.1, 3, 0, (120, 120))

    # sign the face
    for (x, y, w, h) in faces:
        # rectangle origin pic, left-top, right-bottom, line color, line width
        cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 10)

        cv2.imshow('tupian', image)

        # quit the loop or wait 3ms
        if cv2.waitKey(3) & 0xFF == ord('q'):
            break


# release capture video
capture.release()

# destroy window
cv2.destoryAllWIndwos()

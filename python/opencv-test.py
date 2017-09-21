import os
import cv2
import numpy as np

"""
This is an OpenCV Python Test application.

This app showcases various OpenCV methods, highlighting GUI usage and
basic image processing methods.

Command-Line: python3 opencv-test.py
"""
class TestApp:
    frame = None
    preEdgedFrame = None

    resizeFrame = True
    maxThreshold = 100
    edgeThreshold = 0

    def __init__(self):
        """ Default constructor for TestApp. """
        self.resizeFrame = True

    def init(self):
        """ Initializes a pre-computed and edge-computed windows to display. """
        cv2.namedWindow('preEdgedFrame')
        cv2.moveWindow('preEdgedFrame', 0, 0)

        cv2.namedWindow('edgeImage')
        cv2.moveWindow('edgeImage', 500, 0)
        cv2.createTrackbar('EdgeThreshold', 'edgeImage', 0, self.maxThreshold, self.edgeThresholdCallback)

    def edgeThresholdCallback(self, value):
        """ This is a callback for whenever the edge threshold is changed. """
        self.edgeThreshold = value

        processedFrame = self.processFrame(self.frame)
        cv2.imshow('edgeImage', processedFrame)

    def processFrame(self, frame):
        """ Edge detects a frame. It gray-scales, resizes, and blurs before detecting. """
        self.frame = frame

        imageGray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        if self.resizeFrame:
            imageGrayResized = cv2.resize(imageGray, (300, 300))
        else:
            imageGrayResized = imageGray

        self.preEdgedFrame = imageGrayResized

        imageGrayResizedBlurred = cv2.blur(imageGrayResized, (3, 3))

        return cv2.Canny(imageGrayResizedBlurred, self.edgeThreshold, self.edgeThreshold * 3)


    def runVideoCapture(self):
        """ Main run method for processing frames captured via a webcam. """
        self.resizeFrame = True
        videoCaptureDevice = cv2.VideoCapture(0)

        while(True):
            frameOkay, frame = videoCaptureDevice.read()

            if frameOkay:
                resultFrame = self.processFrame(frame)

                cv2.imshow('preEdgedFrame', self.preEdgedFrame)
                cv2.imshow('edgeImage', resultFrame)

            key = cv2.waitKey(1) & 0xFF
            if key == 27:
                break

        videoCaptureDevice.release()

    def runStillImage(self, testImageFilePath):
        """ Displays the results for a test image. """

        self.resizeFrame = False
        stillImage = cv2.imread(testImageFilePath, 1)

        resultFrame = self.processFrame(stillImage)

        cv2.imshow('preEdgedFrame', self.preEdgedFrame)
        cv2.imshow('edgeImage', resultFrame)
        cv2.waitKey(0)

    def close(self):
        """ Does some clean up! """
        cv2.destroyAllWindows()

if __name__ == '__main__':
    app = TestApp()

    app.init()

    app.runVideoCapture()
    # app.runStillImage('test.png')

    app.close()

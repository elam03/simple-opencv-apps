#include <iostream>

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

/**
 * Here's a little test application that you can use. It loads up an image and shows the original image alongside an
 * edge-detected image. You can move the little slider bar around to change the size of the canny filter. I incorporated
 * a little bit of C++ into it, so you can sort of get a feel of what useful C++ code might look like. I encapsulated all
 * of the data into this MyApp class. You can re-use the class for the most part, maybe use it as a template for future
 * projects or tests.
 *
 * The project setup is in CMakeLists.txt. It's relatively easy to get setup.
 *
 * You can run in by pressing the play button. You can also run it from the command line. It can take an argument of an
 * image file to load.
 *
 * The original example is here: http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_gcc_cmake/linux_gcc_cmake.html
 */
class MyApp {
public:
    MyApp() {
    }

    virtual ~MyApp() {
    }

    bool init(string imageFilename) {
        imageOriginal = imread(imageFilename, 1);

        if (imageOriginal.data == nullptr) {
            return false;
        }

        cout << "MyApp::init()..." << endl;

        namedWindow("Original Image", WINDOW_AUTOSIZE);
        moveWindow("Original Image", 20, 53);

        namedWindow("Edge map", WINDOW_AUTOSIZE);
        moveWindow("Edge map", 20 + imageOriginal.cols, 20);

        imshow("Original Image", imageOriginal);

        colorEdgeImage.create(imageOriginal.size(), imageOriginal.type());
        cvtColor(imageOriginal, grayImage, COLOR_BGR2GRAY);

        createTrackbar("Canny threshold", "Edge map", nullptr, 100, MyApp::onTrackbarStatic, this);

        // Set initial value
        onTrackbar(0);

        return true;
    }

    void run() {
        waitKey(0);
    }

    void close() {
        cout << "MyApp::close..." << endl;
    }

    void onTrackbar(int value) {
        blur(grayImage, edgeImage, Size(3, 3));

        // Run the edgeImage detector on grayscale
        Canny(edgeImage, edgeImage, value, value * 3, 3);

        colorEdgeImage = Scalar::all(0);

        imageOriginal.copyTo(colorEdgeImage, edgeImage);

        imshow("Edge map", colorEdgeImage);
    }

    static void onTrackbarStatic(int value, void* callbackData)
    {
        ((MyApp *)callbackData)->onTrackbar(value);
    }

protected:
    Mat imageOriginal;
    Mat grayImage;
    Mat edgeImage;
    Mat colorEdgeImage;
};



int main(int argc, char** argv) {
    MyApp myApp;
    string imageFilename = "../test.png";

    if (argc > 1) {
        imageFilename = argv[1];
    }

    if (!myApp.init(imageFilename)) {
        cout << "I couldn't load the imageOriginal!" << endl;
        return -1;
    }

    myApp.run();

    myApp.close();

    return 0;
}

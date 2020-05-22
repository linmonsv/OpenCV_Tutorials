#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
int main(void)
{
    //Adding (blending) two images using OpenCV
    {
        double alpha = 0.5; double beta; double input;
        Mat src1, src2, dst;
        cout << " Simple Linear Blender " << endl;
        cout << "-----------------------" << endl;
        cout << "* Enter alpha [0.0-1.0]: ";
        input = 0.3;
        //cin >> input;
        // We use the alpha provided by the user if it is between 0 and 1
        if (input >= 0 && input <= 1)
        {
            alpha = input;
        }
        src1 = imread("LinuxLogo.jpg");
        src2 = imread("WindowsLogo.jpg");
        if (src1.empty()) { cout << "Error loading src1" << endl; return -1; }
        if (src2.empty()) { cout << "Error loading src2" << endl; return -1; }
        beta = (1.0 - alpha);
        addWeighted(src1, alpha, src2, beta, 0.0, dst);
        //imshow("Linear Blend", dst);
        //waitKey(0);
    }

    //Changing the contrast and brightness of an image!
    {
        Mat image = imread("../../data/lena.jpg");
        if (image.empty())
        {
            cout << "Could not open or find the image!\n" << endl;
            //cout << "Usage: " << argv[0] << " <Input image>" << endl;
            return -1;
        }
        Mat new_image = Mat::zeros(image.size(), image.type());
        double alpha = 0.8; /*< Simple contrast control */
        int beta = 30;       /*< Simple brightness control */
        cout << " Basic Linear Transforms " << endl;
        cout << "-------------------------" << endl;
        //cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
        //cout << "* Enter the beta value [0-100]: ";    cin >> beta;
        for (int y = 0; y < image.rows; y++) {
            for (int x = 0; x < image.cols; x++) {
                for (int c = 0; c < image.channels(); c++) {
                    new_image.at<Vec3b>(y, x)[c] =
                        saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
                }
            }
        }
    }

    return 0;
}

#include<opencv2/opencv.hpp>
#include<ctime>
#include<cstdlib>
using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    // init
    FileStorage fs("test.yaml", FileStorage::WRITE);

    // start to write
    fs << "frameCount" << 5;
    time_t rawtime;
    time(&rawtime);
    fs << "calibrationDate" << asctime(localtime(&rawtime));
    Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240);
    Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
    fs << "features" << "[";
    for(int i = 0; i < 3; i++) {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;

        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
        for(int j = 0; j < 8; j++)
            fs << ((lbp >> j) & 1);
        fs << "]" << "}";
    }
    fs << "]";
    fs.release();
    return 0;
}

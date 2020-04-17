#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
int main()
{
    Mat  dstImage_Erode, dstImage_Dilate, dstImage_Open, dstImage_Close;
    cv::Mat binaryMat;
    cv::Mat srcMat = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.4.17/2/2.png", 0);
    cv::Mat labelMat;
    cv::Mat statsMat;
    cv::Mat centrMat;
    cv::Mat resultMat;

    Mat invertImage;
    srcMat.copyTo(invertImage);

    cv::threshold(invertImage, binaryMat, 0, 255, THRESH_OTSU);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
    morphologyEx(binaryMat, dstImage_Open, MORPH_OPEN, kernel, Point(-1, -1), 1);

    int nComp = cv::connectedComponentsWithStats(dstImage_Open,labelMat,statsMat,centrMat,8,CV_32S);

    resultMat = cv::Mat::zeros(srcMat.size(), CV_8UC3);
    std::vector<cv::Vec3b> colors(nComp);
    colors[0] = cv::Vec3b(0, 0, 0);
    for (int i = 1; i < nComp; i++)
    {
        Rect bndbox;
        bndbox.x = statsMat.at<int>(i, 0);
        bndbox.y = statsMat.at<int>(i, 1);
        bndbox.width = statsMat.at<int>(i, 2);
        bndbox.height = statsMat.at<int>(i, 3);
        rectangle(srcMat, bndbox, CV_RGB(255,255,255), 1, 8, 0);
    }


    imshow("binaryMat", binaryMat);
    imshow("frame", srcMat);
    waitKey(0);

    return 0;
}

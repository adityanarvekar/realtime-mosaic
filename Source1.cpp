#include "opencv2/opencv.hpp"
#include<cmath>
#include <windows.h>
#include <ctime>
#include "iostream"
#include <chrono>



using namespace cv;
using namespace std;



Point pa, pb;
int stretch = 0;
Rect rect;
Mat bigImage, croppedImage;
int select_flag = 0;
int blurD = 5;
bool blur_keyPressOn = false;
bool disableBlur = true;
vector<Rect> blurredArea;

int red, green, blue;
int redSum = 0;
int greenSum = 0;
int blueSum = 0;

static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int stringLength = sizeof(alphanum) - 1;

char genRandom() {

	return alphanum[rand() % stringLength];
}


void mouseHandler(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN && !stretch)
	{
		/* left button clicked. ROI selection begins */
		pa = Point(x, y);
		stretch = 1;
		printf("Starting Point: (%d, %d)", x, y);
	}

	if (event == CV_EVENT_MOUSEMOVE && stretch)
	{
		/* mouse dragged. ROI being selected */
		Mat img1 = bigImage.clone();
		pb = Point(x, y);
		rectangle(img1, pa, pb, CV_RGB(255, 0, 0), 3, 8, 0);
		imshow("Webcam", img1);
	}

	if (event == CV_EVENT_LBUTTONUP && stretch)
	{
		pb = Point(x, y);
		rect = Rect(pa.x, pa.y, x - pa.x, y - pa.y);
		stretch = 0;
		croppedImage = bigImage(rect);
	}

	if (event == CV_EVENT_LBUTTONUP)
	{
		select_flag = 1;
		stretch = 0;
		blurredArea.push_back(rect);
		printf("\nEnding Point: (%d, %d)", x, y);
		blur_keyPressOn = true;
		disableBlur = false;
	}
}

void doMosaic(int bd, Mat imageToBeBlurred) {
	int bdsquare = bd * bd;
	int rowsToBeCalc = imageToBeBlurred.rows / bd;
	int colsToBeCalc = imageToBeBlurred.cols / bd;



	for (int i = 0; i < rowsToBeCalc; i++) {
		for (int j = 0; j < colsToBeCalc; j++) {
			redSum = 0;
			greenSum = 0;
			blueSum = 0;
			for (int rows = 0; rows < bd; rows++) {

				for (int cols = 0; cols < bd; cols++) {
					int x = (i*bd) + rows;
					int y = (j*bd) + cols;

					if ((x < imageToBeBlurred.cols &&  y < imageToBeBlurred.rows)) {
						redSum += imageToBeBlurred.ptr<uchar>(y)[3 * x + 2];
						greenSum += imageToBeBlurred.ptr<uchar>(y)[3 * x + 1];
						blueSum += imageToBeBlurred.ptr<uchar>(y)[3 * x + 0];
					}

				}
			}
			red = redSum / bdsquare;
			green = greenSum / bdsquare;
			blue = blueSum / bdsquare;
			for (int rows = 0; rows < bd; rows++) {

				for (int cols = 0; cols < bd; cols++) {
					int x = (i*bd) + rows;
					int y = (j*bd) + cols;
					if (x < imageToBeBlurred.cols &&  y < imageToBeBlurred.rows) {
						
						imageToBeBlurred.ptr<uchar>(y)[3 * x + 2] = red;
						imageToBeBlurred.ptr<uchar>(y)[3 * x + 1] = green;
						imageToBeBlurred.ptr<uchar>(y)[3 * x + 0] = blue;

					}


				}

			}
		}
	

	}


}
void resetClick(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		croppedImage = NULL;
		rect = Rect(pa.x, pa.y, 0, 0);
		blurredArea.clear();
		printf("Left Click: (%d, %d)", x, y);
	}
}


int main(int, char**)
{
	int k;
	VideoCapture cap = VideoCapture(0);
	while (1)
	{
		cap >> bigImage;
		cvSetMouseCallback("Webcam", mouseHandler, NULL);

		k = waitKey(10);
		if (select_flag == 1)
		{
			if (!disableBlur) {
				cvSetMouseCallback("Webcam", resetClick, NULL);
				rectangle(bigImage, pa, pb, CV_RGB(0, 155, 0), 0, 8, 0);
				croppedImage = bigImage(rect);
				doMosaic(blurD, croppedImage);
			}
		}
		else {
			rectangle(bigImage, rect, CV_RGB(255, 0, 0), 3, 8, 0);
		}
		imshow("Webcam", bigImage);
		if (k == 27)
		{
			break;
		}
		else if ((k == 'i' || k == 'I') && blur_keyPressOn == true) {
			blur_keyPressOn = true;
			if (blurD >= 0 && blurD < 5) {
				blurD = blurD + 1;
			}
			else {
				blurD = blurD + 5;
			}
			if (blurD > 100) {
				blurD = 100;
			}
			doMosaic(blurD, croppedImage);
		}
		else if ((k == 'd' || k == 'D') && blur_keyPressOn == true) {
			blur_keyPressOn = true;
			if (blurD >= 0 && blurD <= 5) {
				blurD = blurD - 1;
			}
			else {
				blurD = blurD - 5;
			}
			if (blurD < 0 || blurD ==0) {
				blurD = 1;
			}
			doMosaic(blurD, croppedImage);
		}
		else if ((k == 's' || k == 'S')) {
			String randomString;
			for (unsigned int i = 0; i < 10; ++i) {
				randomString += genRandom();
			}
			randomString = randomString + ".jpg";
			imwrite(randomString, bigImage);
			printf("\nImage Saved");
		}
		else if ((k == 'r' || k == 'R')) {
			croppedImage = NULL;
			rect = Rect(pa.x, pa.y, 0, 0);
			blurredArea.clear();
			disableBlur = true;
		}
	}
	return 0;
}

// Open CV 2.4.13

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
using namespace cv;
using namespace std;

#if _DEBUG
#pragma comment(lib, "opencv_core2413d.lib")
#pragma comment(lib, "opencv_features2d2413d.lib")
#pragma comment(lib, "opencv_highgui2413d.lib")
#pragma comment(lib, "opencv_imgproc2413d.lib")
#pragma comment(lib, "opencv_nonfree2413d.lib")
#else
#pragma comment(lib, "opencv_core2413.lib")
#pragma comment(lib, "opencv_features2d2413.lib")
#pragma comment(lib, "opencv_highgui2413.lib")
#pragma comment(lib, "opencv_imgproc2413.lib")
#pragma comment(lib, "opencv_nonfree2413.lib")
#endif

int main(void)
{
	// 入力画像の取得
	Mat color_image = imread("input.jpg", 1);
	if (color_image.empty()) {
		return -1;
	}

	// カラー画像をグレースケールに変換
	Mat gray_image;
	cvtColor(color_image, gray_image, CV_RGB2GRAY);
	normalize(gray_image, gray_image, 0, 255, NORM_MINMAX);

	// SIFT特徴点の抽出
	vector<KeyPoint> keypoints;
	vector<KeyPoint>::iterator itk;
	double threshold = 0.05;
	double edge_threshold = 10.0;
	SiftFeatureDetector detector(threshold, edge_threshold);
	detector.detect(gray_image, keypoints);

	// キーポイントの数を表示
	int keypoint_num = keypoints.size();
	cout << "keypoint_num :" << keypoint_num << endl;

	// 結果を表示
	Mat output_image_1, output_image_2;
	drawKeypoints(color_image, keypoints, output_image_1, Scalar(0, 255, 0), 0);
	drawKeypoints(color_image, keypoints, output_image_2, Scalar(0, 255, 0), 4);
	imshow("Result Keypoint", output_image_1);
	imshow("Result Keypoint Size and Direction", output_image_2);

	// 結果を保存
	imwrite("output_image_1.png", output_image_1);
	imwrite("output_image_2.png", output_image_2);

	waitKey(0);
}
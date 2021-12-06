#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
	string imageFileName, txtFileName;
	Mat resizedImage, grayImage;
	int size;
	ofstream txt;
	char ascii[] = "@$B%&M#*oahkbdpqwmZOQLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,^'. ";

	cout << "image location: ";
	cin >> imageFileName;
	Mat image = imread(imageFileName, IMREAD_COLOR); // получаем изображение
	if (image.empty()) 
	{
		cout << "something wrong!";
		return -1; 
	} 

	cout << "text file: ";
	cin >> txtFileName;
	txt.open(txtFileName + ".txt"); // создаем txt файл
 
	cout << "image compression (min 5x): ";
	cin >> size;
	if (size < 5) 
	{
		cout << "compression must be less then 5x!";
		return -1;
	}

 	resize(image, resizedImage, Size(floor(image.cols/size), floor(image.rows/size)), INTER_LINEAR); // изменение разрешения изображения

	cvtColor(resizedImage, grayImage, COLOR_BGR2GRAY); // перевод в чернобелый формат

 	for (int i = 0; i < resizedImage.rows; i++) // цикл перевода в ascii
 	{
 		for (int j = 0; j < resizedImage.cols; j++)
		{
			uchar intensity = grayImage.at<uchar>(i, j); // получаем яркость символа
			txt << ascii[(intensity+1)/4]; 
  		}
		txt << endl;
 	}
	txt.close();
}
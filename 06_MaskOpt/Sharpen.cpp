#include <cv.h>

using namespace std;
using namespace cv;

void Sharpen(const Mat& myImage, Mat& Result)
{
	// accept only uchar images
	CV_Assert(myImage.depth() == CV_8U);

	//myImage.copyTo(Result);
	Result.create(myImage.size().height, myImage.size().width, myImage.type());
	const int nChannels = myImage.channels();

	for(int j=1; j<myImage.rows-1; j++)
	{
		const uchar* previous = myImage.ptr<uchar>(j-1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j+1);

		uchar* output = Result.ptr<uchar>(j);

		for(int i=nChannels; i<nChannels*(myImage.cols-1); ++i)
		{
			*output++ = saturate_cast<uchar>(5*current[i] - current[i+nChannels]
				- current[i-nChannels] - previous[i] - next[i]);
		}

		Result.row(0).setTo(Scalar(0));
		Result.row(Result.rows-1).setTo(Scalar(0));
		Result.col(0).setTo(Scalar(0));
		Result.col(Result.cols-1).setTo(Scalar(0));
	}
}

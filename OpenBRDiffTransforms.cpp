/*
* Following program shows transform effects on images
*/

#include <openbr/openbr_plugin.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(int argc, char *argv[])
{

    br::Context::initialize(argc, argv);
    br::Globals->enrollAll = true;

//     QSharedPointer<br::Transform> transform =  br::Transform::fromAlgorithm("Open");//all untrainable transforms
    QSharedPointer<br::Transform> transform =  br::Transform::fromAlgorithm("Open+Cvt(Gray)");//all untrainable transforms
//     QSharedPointer<br::Transform> transform =  br::Transform::fromAlgorithm("Open+Cvt(Gray)+Sobel");//all untrainable transforms
//     QSharedPointer<br::Transform> transform =  br::Transform::fromAlgorithm("Open+SkinMask+Cvt(Gray)+DrawGridLines");//all untrainable transforms
//     QSharedPointer<br::Transform> transform =  br::Transform::fromAlgorithm("Open+DrawGridLines+SkinMask+Sobel+Cvt(Gray)+Draw(lineThickness=3)");//all untrainable transforms

    VideoCapture cap("rtsp://admin:password@ip/h264/ch1/main/av_stream?tcp");

    cv::namedWindow( "Win1", WINDOW_NORMAL /* WINDOW_AUTOSIZE*/ );

    if(!cap.isOpened())
        return -1;
   
    for(;;)
    {
        Mat frame;
        cap >> frame;

        if( frame.empty() )
            break; // end of video stream

        br::Template t1(frame);
        t1 >> *transform;
        cv::imshow("Win1", t1); 
            cv::waitKey(1);
       
    }
   
    br::Context::finalize();

    return 0;
}

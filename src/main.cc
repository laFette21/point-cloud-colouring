#include "matrixreaderwriter/MatrixReaderWriter.hh"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

static constexpr const char* WINDOW_NAME = "Point Cloud Colouring";

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <input path> <output path>" << std::endl;
        return 0;
    }

    cv::Mat canvas = cv::imread("../data/elte_logo/Dev0_Image_w960_h600_fn92.jpg");

    cv::namedWindow(WINDOW_NAME);
    cv::imshow(WINDOW_NAME, canvas);
    cv::waitKey(0);

    // Input
    MatrixReaderWriter stream;
    stream.setMaxColNum(3);
    stream.load(argv[1]);

    auto data = stream.getData();
    std::vector<cv::Point3d> pointCloudPoints(data.size() / 3);

    for (std::size_t i = 0; i < pointCloudPoints.size(); ++i)
    {
        pointCloudPoints[i].x = data[i * 3];
        pointCloudPoints[i].y = data[i * 3 + 1];
        pointCloudPoints[i].z = data[i * 3 + 2];
    }

    // Cameras
    cv::Mat leftR = cv::Mat::zeros(3, 3, CV_64F);
    cv::Mat centerR = cv::Mat::zeros(3, 3, CV_64F);
    cv::Mat rightR = cv::Mat::zeros(3, 3, CV_64F);

    cv::Mat leftT = cv::Mat::zeros(3, 1, CV_64F);
    cv::Mat centerT = cv::Mat::zeros(3, 1, CV_64F);
    cv::Mat rightT = cv::Mat::zeros(3, 1, CV_64F);

    leftR.at<double>(0, 0) = 0.9230;
    leftR.at<double>(0, 1) = -0.0066;
    leftR.at<double>(0, 2) = -0.3847;

    leftR.at<double>(1, 0) = 0.3848;
    leftR.at<double>(1, 1) = 0.0203;
    leftR.at<double>(1, 2) = 0.9228;

    leftR.at<double>(2, 0) = 0.0018;
    leftR.at<double>(2, 1) = -0.9998;
    leftR.at<double>(2, 2) = -0.0213;

    leftT.at<double>(0, 0) = -0.0397;
    leftT.at<double>(0, 1) = 0.1842;
    leftT.at<double>(0, 2) = -0.0944;

    centerR.at<double>(0, 0) = 0.9999;
    centerR.at<double>(0, 1) = 0.0086;
    centerR.at<double>(0, 2) = -0.0094;

    centerR.at<double>(1, 0) = 0.0095;
    centerR.at<double>(1, 1) = -0.0110;
    centerR.at<double>(1, 2) = 0.9999;

    centerR.at<double>(2, 0) = 0.0085;
    centerR.at<double>(2, 1) = -0.9999;
    centerR.at<double>(2, 2) = -0.0111;

    centerT.at<double>(0, 0) = -0.0463;
    centerT.at<double>(0, 1) = 0.0752;
    centerT.at<double>(0, 2) = 0.0932;

    rightR.at<double>(0, 0) = 0.9543;
    rightR.at<double>(0, 1) = 0.0319;
    rightR.at<double>(0, 2) = 0.2971;

    rightR.at<double>(1, 0) = -0.2969;
    rightR.at<double>(1, 1) = -0.0113;
    rightR.at<double>(1, 2) = 0.9548;

    rightR.at<double>(2, 0) = 0.0338;
    rightR.at<double>(2, 1) = -0.9994;
    rightR.at<double>(2, 2) = -0.0014;

    rightT.at<double>(0, 0) = 0.1000;
    rightT.at<double>(0, 1) = 0.1962;
    rightT.at<double>(0, 2) = -0.0663;

    cv::Mat K = cv::Mat::eye(3, 3, CV_64F);
    K.at<double>(0, 0) = 625;
    K.at<double>(1, 1) = 625;
    K.at<double>(0, 2) = 480;
    K.at<double>(1, 2) = 300;

    // Transform
    std::vector<cv::Mat> leftCameraPoints(pointCloudPoints.size());
    std::vector<cv::Vec3i> leftPointCloudColor(pointCloudPoints.size());

    for (std::size_t i = 0; i < pointCloudPoints.size(); ++i)
    {
        auto& point = leftCameraPoints[i];
        point = leftR.t() * cv::Mat(pointCloudPoints[i]) + leftT;
        point = K * point;

        if (point.at<double>(2, 0) < 0)
        {
            continue;
        }

        point /= point.at<double>(2, 0);

        int x = static_cast<int>(point.at<double>(0, 0));
        int y = static_cast<int>(point.at<double>(1, 0));

        if (x >= 0 && y >= 0 && x < canvas.cols && y < canvas.rows)
        {
            leftPointCloudColor[i] = canvas.at<cv::Vec3b>(y, x);

            cv::circle(
                canvas,
                cv::Point(x, y),
                2.0,
                leftPointCloudColor[i],
                2,
                8
            );
        }
    }

    cv::imshow(WINDOW_NAME, canvas);
    cv::waitKey(0);

    canvas = cv::imread("../data/elte_logo/Dev1_Image_w960_h600_fn92.jpg");

    cv::imshow(WINDOW_NAME, canvas);
    cv::waitKey(0);

    std::vector<cv::Mat> centerCameraPoints(pointCloudPoints.size());
    std::vector<cv::Vec3i> centerPointCloudColor(pointCloudPoints.size());

    for (std::size_t i = 0; i < pointCloudPoints.size(); ++i)
    {
        auto& point = centerCameraPoints[i];
        point = centerR.t() * cv::Mat(pointCloudPoints[i]) + centerT;
        point = K * point;

        if (point.at<double>(2, 0) < 0)
        {
            continue;
        }

        point /= point.at<double>(2, 0);

        int x = static_cast<int>(point.at<double>(0, 0));
        int y = static_cast<int>(point.at<double>(1, 0));

        if (x >= 0 && y >= 0 && x < canvas.cols && y < canvas.rows)
        {
            centerPointCloudColor[i] = canvas.at<cv::Vec3b>(y, x);

            cv::circle(
                canvas,
                cv::Point(x, y),
                2.0,
                centerPointCloudColor[i],
                2,
                8
            );
        }
    }

    cv::imshow(WINDOW_NAME, canvas);
    cv::waitKey(0);

    canvas = cv::imread("../data/elte_logo/Dev2_Image_w960_h600_fn92.jpg");

    cv::imshow(WINDOW_NAME, canvas);
    cv::waitKey(0);

    std::vector<cv::Mat> rightCameraPoints(pointCloudPoints.size());
    std::vector<cv::Vec3i> rightPointCloudColor(pointCloudPoints.size());

    for (std::size_t i = 0; i < pointCloudPoints.size(); ++i)
    {
        auto& point = rightCameraPoints[i];
        point = rightR.t() * cv::Mat(pointCloudPoints[i]) + rightT;
        point = K * point;

        if (point.at<double>(2, 0) < 0)
        {
            continue;
        }

        point /= point.at<double>(2, 0);

        int x = static_cast<int>(point.at<double>(0, 0));
        int y = static_cast<int>(point.at<double>(1, 0));

        if (x >= 0 && y >= 0 && x < canvas.cols && y < canvas.rows)
        {
            rightPointCloudColor[i] = canvas.at<cv::Vec3b>(y, x);

            cv::circle(
                canvas,
                cv::Point(x, y),
                2.0,
                rightPointCloudColor[i],
                2,
                8
            );
        }
    }

    cv::imshow(WINDOW_NAME, canvas);
    cv::waitKey(0);

    std::vector<cv::Vec3i> pointCloudPointColors(pointCloudPoints.size());

    for (std::size_t i = 0; i < pointCloudPoints.size(); ++i)
    {
        cv::Vec3i color;
        int count = 0;

        if (leftPointCloudColor[i] != cv::Vec3i{})
        {
            color += leftPointCloudColor[i];
            count++;
        }
        if (centerPointCloudColor[i] != cv::Vec3i{})
        {
            color += centerPointCloudColor[i];
            count++;
        }
        if (rightPointCloudColor[i] != cv::Vec3i{})
        {
            color += rightPointCloudColor[i];
            count++;
        }
        if (count != 0)
        {
            color /= count;
        }
        pointCloudPointColors[i] = color;
    }

    std::vector<double> coloredPointCloudPoints(pointCloudPoints.size() * 6);

    for (std::size_t i = 0; i < pointCloudPoints.size(); ++i)
    {
        coloredPointCloudPoints[i * 6]     = pointCloudPoints[i].x;
        coloredPointCloudPoints[i * 6 + 1] = pointCloudPoints[i].y;
        coloredPointCloudPoints[i * 6 + 2] = pointCloudPoints[i].z;
        coloredPointCloudPoints[i * 6 + 3] = pointCloudPointColors[i][2];
        coloredPointCloudPoints[i * 6 + 4] = pointCloudPointColors[i][1];
        coloredPointCloudPoints[i * 6 + 5] = pointCloudPointColors[i][0];
    }

    // Output
    stream.setData(coloredPointCloudPoints, coloredPointCloudPoints.size() / 6, 6);
    stream.save(argv[2]);

    return EXIT_SUCCESS;
}

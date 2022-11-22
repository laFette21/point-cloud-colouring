#include "matrixreaderwriter/MatrixReaderWriter.hh"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <fstream>
#include <iostream>

static constexpr unsigned HEIGHT = 500;
static constexpr unsigned WIDTH = 500;
static constexpr const char* WINDOW_NAME = "Point Cloud Colouring";

class Transformer
{
public:
    Transformer():
        _end(false)
    {
        cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

        _canvas = cv::Mat(HEIGHT, WIDTH, CV_8UC3);

        readCloudData("/Users/lafette21/Documents/ELTE/SEM_1/3DCV/TASKS/point-cloud-colouring/data/test");
        // readCloudData("/Users/lafette21/Documents/ELTE/SEM_1/3DCV/TASKS/point-cloud-colouring/data/elte_logo/test_fn92.xyz");

        cv::imshow(WINDOW_NAME, _canvas);

        cv::waitKey(0);
    }
    ~Transformer() = default;

    bool end() { return _end; }
    void readCloudData(const std::string& path)
    {
        MatrixReaderWriter reader;
        reader.setMaxColNum(3);
        reader.load(path);

        auto data = reader.getData();

        for (auto& e : data)
        {
            std::cout << e << ' ';
        }

        std::cout << std::endl;

        for (std::size_t i = 0; i < reader.rows(); ++i)
        {
            for (std::size_t j = 0; j < reader.cols(); ++j)
            {
                std::cout << data[i * reader.cols() + j] << ' ';
            }

            std::cout << std::endl;
        }

        std::cout << reader.rows() << ' ' << reader.cols() << std::endl;
    }
    void update()
    {
        cv::imshow(WINDOW_NAME, _canvas);

        cv::waitKey(0);
    }

private:
    cv::Mat _canvas;
    std::vector<cv::Point2d> _points;
    bool _end;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    Transformer model;

    while (not model.end())
    {
        model.update();
    }

    return EXIT_SUCCESS;
}

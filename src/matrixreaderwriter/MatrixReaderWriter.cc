#include "MatrixReaderWriter.hh"

namespace
{
    std::size_t countEntries(std::string& str)
    {
        bool lastWasSpace = true;
        std::size_t wordCount = 0;

        for (std::size_t i = 0; i < str.size(); ++i)
        {
            if (str[i] == ' ')
            {
                lastWasSpace = true;
            }
            else if (lastWasSpace)
            {
                lastWasSpace = false;
                ++wordCount;
            }
        }

        return wordCount;
    }
}

void MatrixReaderWriter::load(const std::string& path)
{
    std::ifstream dataFile(path);

    if (dataFile.is_open())
    {
        std::string line;
        std::getline(dataFile, line);

        _columnNum = countEntries(line);

        bool flag = _maxColNum >= 0;

        _rowNum = 1;

        std::stringstream ss;
        ss << line;

        for (std::size_t i = 0; i < _columnNum; ++i)
        {
            double x;
            ss >> x;
            if (flag && i < static_cast<std::size_t>(_maxColNum))
            {
                _data.push_back(x);
            }
        }

        while (std::getline(dataFile, line))
        {
            ss.clear();
            ss << line;

            for (std::size_t i = 0; i < _columnNum; ++i)
            {
                double x;
                ss >> x;
                if (flag && i < static_cast<std::size_t>(_maxColNum))
                {
                    _data.push_back(x);
                }
            }

            ++_rowNum;
        }

        if (flag)
        {
            _columnNum = static_cast<std::size_t>(_maxColNum);
        }

        dataFile.close();
    }
    else
    {
        std::cout << "Unable to open file: " << path << std::endl;
    }
}

void MatrixReaderWriter::save(const std::string& path) const
{
    std::ofstream dataFile(path);

    if (dataFile.is_open())
    {
        for (std::size_t i = 0; i < _rowNum; ++i)
        {
            for (std::size_t j = 0; j < _columnNum; ++j)
            {
                dataFile << _data[i * _columnNum + j] << ' ';
            }

            dataFile << std::endl;
        }

        dataFile.close();
    }
    else
    {
        std::cout << "Unable to open file: " << path << std::endl;
    }
}

void MatrixReaderWriter::setData(const std::vector<double>& data, std::size_t rows, std::size_t cols) {
    _rowNum = rows;
    _columnNum = cols;
    _data = data;
}

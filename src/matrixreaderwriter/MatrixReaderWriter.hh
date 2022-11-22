#ifndef MATRIX_READER_HH
#define MATRIX_READER_HH

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class MatrixReaderWriter
{
public:
    MatrixReaderWriter(): _columnNum(0), _rowNum(0), _maxColNum(-1) {}
    MatrixReaderWriter(const std::string& path) { load(path); }

    ~MatrixReaderWriter() = default;

    std::vector<double> getData() const { return _data; }
    std::size_t rows() const { return _rowNum; }
    std::size_t cols() const { return _columnNum; }

    void load(const std::string& path);
    void save(const std::string& path) const;
    void setData(const std::vector<double>& data, std::size_t rows, std::size_t cols);
    void setMaxColNum(int value) { _maxColNum = value; }

private:
    std::vector<double> _data;
    std::size_t _columnNum;
    std::size_t _rowNum;
    int _maxColNum;
};

#endif // MATRIX_READER_HH

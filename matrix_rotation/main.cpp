/**
    Assume that matrixes consists of several cycles, like this:

    AAAAA
    ABBBA
    ABCBA
    ABBBA
    AAAAA

    So, we have 3 cycles: A, B and C.

    So rotation problem now is a problem of rotating this cycles.
*/
#include <iostream>
#include <vector>


class RotatableMatrix
{
public:
    RotatableMatrix(size_t numRows, size_t numCols);

    static RotatableMatrix readFrom(std::istream& in, size_t numRows, size_t numCols);
    void printTo(std::ostream& out) const;

    size_t numRows() const { return data_.size() / numCols_; }
    size_t numCols() const { return numCols_; }

    int& at(size_t row, size_t col);
    const int& at(size_t row, size_t col) const;

    void rotate(size_t times);

private:
    class Cycle {
    public:
        Cycle(RotatableMatrix& matrix, size_t position)
            : parent_(matrix)
            , position_(position)
        { }

        void rotate(size_t times);
        size_t size() const;
        int& at(size_t i);

    private:
        RotatableMatrix& parent_;
        size_t position_;
    };

private:
    std::vector<Cycle> cycles();
    size_t numCycles() const;

private:
    std::vector<int> data_;
    size_t numCols_;
};

RotatableMatrix::RotatableMatrix(size_t numRows, size_t numCols)
    : data_(numRows * numCols, 0)
    , numCols_(numCols)
{ }

RotatableMatrix RotatableMatrix::readFrom(std::istream& in, size_t numRows, size_t numCols)
{
    auto matrix = RotatableMatrix(numRows, numCols);
    for (size_t i = 0; i < numRows; ++i)
    for (size_t j = 0; j < numCols; ++j)
        in >> matrix.at(i, j);
    return matrix;
}

const int& RotatableMatrix::at(size_t row, size_t col) const
{
    return data_.at(row * numCols_ + col);
}

int& RotatableMatrix::at(size_t row, size_t col)
{
    return const_cast<int&>(
        const_cast<const RotatableMatrix*>(this)->at(row, col));
}

void RotatableMatrix::printTo(std::ostream& out) const
{
    for (size_t i = 0; i < data_.size(); ++i) {
        if (i != 0 && i % numCols_ == 0) {
            out << "\n";
        } else if (i != 0) {
            out << " ";
        }
        out << data_.at(i);
    }
}

void RotatableMatrix::rotate(size_t times)
{
    for (auto& cycle: this->cycles()) {
        cycle.rotate(times);
    }
}

size_t RotatableMatrix::numCycles() const
{
    size_t minRowsCols = std::min(numRows(), numCols());
    return minRowsCols / 2 + minRowsCols % 2;
}

std::vector<RotatableMatrix::Cycle> RotatableMatrix::cycles()
{
    std::vector<RotatableMatrix::Cycle> result;
    for (size_t i = 0; i < numCycles(); ++i) {
        result.emplace_back(Cycle(*this, i));
    }

    return result;
}

void RotatableMatrix::Cycle::rotate(size_t times)
{
    std::vector<int> rotatedCycle(size(), 0);
    for (size_t i = 0; i < size(); ++i) {
        rotatedCycle[(i + times) % size()] = this->at(i);
    }
    for (size_t i = 0; i < size(); ++i) {
        this->at(i) = rotatedCycle[i];
    }
}

size_t RotatableMatrix::Cycle::size() const
{
    size_t rows = parent_.numRows() - 2*position_;
    size_t cols = parent_.numCols() - 2*position_;
    if (std::min(rows, cols) == 1) {
        return std::max(rows, cols);
    }
    return 2*rows + 2*cols - 4;
}

int& RotatableMatrix::Cycle::at(size_t i)
{
    size_t rows = parent_.numRows() - 2*position_;
    size_t cols = parent_.numCols() - 2*position_;
    i %= size();
    if (i < rows) {
        return parent_.at(position_ + i, position_);
    }
    i -= rows - 1;
    if (i < cols) {
        return parent_.at(parent_.numRows() - position_ - 1, position_ + i);
    }
    i -= cols - 1;
    if (i < rows) {
        return parent_.at(
            parent_.numRows() - position_ - i - 1,
            parent_.numCols() - position_ - 1);
    }
    i -= rows - 1;
    return parent_.at(position_, parent_.numCols() - position_ - i - 1);
}


int main()
{
    size_t numRows, numCols, numRotates;
    std::cin >> numRows >> numCols >> numRotates;
    RotatableMatrix data = RotatableMatrix::readFrom(std::cin, numRows, numCols);
    data.rotate(numRotates);
    data.printTo(std::cout);
    std::cout << std::endl;
    return 0;
}

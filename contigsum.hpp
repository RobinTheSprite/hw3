// contigsum.hpp
// Created by Mark on 10/8/2019.
//

#ifndef HW3_CONTIGSUM_HPP
#define HW3_CONTIGSUM_HPP
#include <numeric>
#include <algorithm>

struct valueTracker
{
    valueTracker(): gcs{0}, leftmost{0}, rightmost{0}, totalSum{0}
    {}

    explicit valueTracker(int i) : gcs{i}, leftmost{i}, rightmost{i}, totalSum{i}
    {}

    int gcs;
    int leftmost;
    int rightmost;
    int totalSum;
};

template<typename RAIter>
valueTracker contigSumRecursive(RAIter first, RAIter last, valueTracker values)
{
    int sizeOfRange = last - first;
    if (sizeOfRange <= 1)
    {
        if(*first < 0)
        {
            values = valueTracker();
            values.totalSum = *first;
        }
        else
        {
            values = valueTracker(*first);
        }
        return values;
    }

    RAIter middle = first + sizeOfRange/2;

    valueTracker firstHalfValues = contigSumRecursive(first, middle, values);
    valueTracker secondHalfValues = contigSumRecursive(middle, last, values);

    values.totalSum = firstHalfValues.totalSum + secondHalfValues.totalSum;

    values.leftmost = std::max({firstHalfValues.leftmost, firstHalfValues.totalSum,
                               firstHalfValues.totalSum + secondHalfValues.leftmost});

    values.rightmost = std::max({secondHalfValues.rightmost, secondHalfValues.totalSum,
                                 secondHalfValues.totalSum + firstHalfValues.rightmost});
    
    values.gcs = std::max({firstHalfValues.gcs, secondHalfValues.gcs,
                          firstHalfValues.rightmost + secondHalfValues.leftmost});

    return values;
}

template<typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    if (last - first <= 0)
    {
        return 0;
    }
    else
    {
        return contigSumRecursive(first, last, valueTracker()).gcs;
    }
}

#endif //HW3_CONTIGSUM_HPP

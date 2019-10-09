// inversion.h
// Created by Mark on 10/7/2019.
//

#ifndef HW3_INVERSIONS_HPP
#define HW3_INVERSIONS_HPP

// merge_sort.cpp
// Glenn G. Chappell
// 9 Oct 2015
//
// For CS 411/611 Fall 2015
// Merge Sort using Iterators

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;
#include <algorithm>
using std::copy;
#include <iterator>
using std::distance;
using std::advance;
using std::iterator_traits;
#include <type_traits>
using std::remove_reference;


// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// Post:
//     [first, last) contains the same items as it did initially, but
//      now sorted by < (in a stable manner).
template<typename FDIter>
size_t stableMerge(FDIter first, FDIter middle, FDIter last)
{
    // ** C++03:
    using Value = typename iterator_traits<FDIter>::value_type;
    // ** C++11:
    //    using Value = typename remove_reference<decltype(*first)>::type;
    // ** Is this really better?

    vector<Value> buffer(distance(first, last));
    // Buffer for temporary copy of data
    FDIter in1 = first;         // Read location in 1st half
    FDIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // ** auto! That *is* better than vector<Value>::iterator

    auto numOfSkips = 0u;
    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1)  // Must do comparison this way, to be stable.
        {
            numOfSkips += (in2 - first) - (out - buffer.begin());
            *out++ = *in2++;
        }
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    copy(in1, middle, out);
    copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    copy(buffer.begin(), buffer.end(), first);
    return numOfSkips;
}


// mergeSort
// Sorts a sequence, using Merge Sort.
// Recursive.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     The value type of FDIter has default ctor, dctor, copy=,
//      operator<.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template<typename FDIter>
size_t mergeSort(FDIter first, FDIter last)
{
    // Compute size of sequence
    size_t size = distance(first, last);

    // BASE CASE
    if (size <= 1)
        return 0;

    // RECURSIVE CASE
    FDIter middle = first;
    advance(middle, size / 2);  // middle is iterator to middle of range

    size_t numOfInversions = 0;
    // Recursively sort the two lists
    numOfInversions += mergeSort(first, middle);
    numOfInversions += mergeSort(middle, last);

    // And merge them
    numOfInversions += stableMerge(first, middle, last);

    return numOfInversions;
}

template<typename FDIter>
size_t inversions(FDIter first, FDIter last)
{
    auto check = mergeSort(first, last);
    return check;
}

#endif //HW3_INVERSIONS_HPP

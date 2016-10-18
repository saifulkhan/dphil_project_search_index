#ifndef ANALYSER_H
#define ANALYSER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;


template<typename TimeT = std::chrono::microseconds,
    typename ClockT=std::chrono::high_resolution_clock,
    typename DurationT=double>

class Stopwatch {

    private:
        std::chrono::time_point<ClockT> _start, _end;

    public:
        Stopwatch() {
            start();
        }

        void start() {
            _start = _end = ClockT::now();
        }

        DurationT stop() {
            _end = ClockT::now();
            return elapsed();
        }

        DurationT elapsed() {
            auto delta = std::chrono::duration_cast<TimeT>(_end-_start);
            return delta.count();
        }
};

void searchInIndexTime();

#endif // ANALYSER_H

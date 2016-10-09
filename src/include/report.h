#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <map>

#include "approximation.h"
#include "utility.h"

namespace report {

    class Report {


    private:
        Report() { }

        typedef std::map<approximation::Approximation, std::string> AppName;
        typedef std::pair<approximation::Approximation, std::string> approxpair;

        const static approxpair map_start_values[];
        const static size_t map_start_values_size = 6;

        static AppName approximationsName;


    };
    
} // namespace report


#endif /* REPORT_H */
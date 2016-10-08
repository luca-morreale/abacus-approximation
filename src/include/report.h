#ifndef REPORT_H
#define REPORT_H

#include <map>

#include "utility.h"
#include "approximation.h"

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
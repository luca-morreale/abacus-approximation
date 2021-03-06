#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <map>

#include "approximation.h"
#include "utility.h"

namespace approximation {
    // forward declaration
    typedef graph::Nodes (*Approximation)(graph::NodePtr node, int &mask);
}

namespace report {

    typedef struct {
        approximation::Approximation approx = NULL;
        double fitness;
        double accuracy;
        int mask;
    } Data;

    typedef Data* DataPtr;

    DataPtr newData(approximation::Approximation &approx, double fitness, double accuracy, int mask=-1);

    typedef std::map<std::string, int> Informations;
    typedef std::map<int, int> ShiftInformations;

    class Report {
    public:

        static void appendApproximation(DataPtr data);
        
        static std::string getApproximationName(approximation::Approximation app);
        static Informations getReport();
        static ShiftInformations getShiftReport();
        
        static void printReport(std::ostream &cout);
        static void printInCSVFormat(std::ostream &cout);

        static void reset();

    protected:
        static void appendShift(int mask);

    private:
        Report() { }

        static Informations info;
        static ShiftInformations shiftInfo;
        static double finalAccuracy;


        typedef std::map<approximation::Approximation, std::string> AppName;
        typedef std::pair<approximation::Approximation, std::string> approxpair;
        typedef std::pair<std::string, int> reportpair;

        const static approxpair map_start_values[];
        const static reportpair map_report_start_values[];
        const static size_t map_values_size = 5;

        static AppName approximationsName;


    };
    
} // namespace report


#endif /* REPORT_H */

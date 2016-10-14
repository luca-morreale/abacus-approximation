#include "include/report.h"


namespace report {

    const Report::approxpair Report::map_start_values[] = {
        Report::approxpair(&approximation::approximateSum, "sum"),
        Report::approxpair(&approximation::approximateMinus, "min"),
        Report::approxpair(&approximation::approximateMult, "mult"),
        Report::approxpair(&approximation::approximateDiv, "div"),
        Report::approxpair(&approximation::approximateValue, "value")
    };

    const Report::reportpair Report::map_report_start_values[] = {
        Report::reportpair("sum", 0),
        Report::reportpair("min", 0),
        Report::reportpair("mult", 0),
        Report::reportpair("div", 0),
        Report::reportpair("value", 0)
    };

    Report::AppName Report::approximationsName(map_start_values, map_start_values + map_values_size);
    Informations Report::info(map_report_start_values, map_report_start_values + map_values_size);
    ShiftInformations Report::shiftInfo;


    DataPtr newData(approximation::Approximation &approx, double fitness, double accuracy, int mask)
    {
        auto data = new Data;
        data->approx = approx;
        data->fitness = fitness;
        data->accuracy = accuracy;
        data->mask = mask;

        return data;
    }


    void Report::appendApproximation(DataPtr data)
    {
        std::string name = approximationsName[data->approx];
        info[name]++;
        appendShift(data->mask);
    }

    void Report::appendShift(unsigned int mask)
    {
        if(mask >= 0) {
            shiftInfo[mask]++;
        }
    }

    Informations Report::getReport()
    {
        return info;
    }

    ShiftInformations Report::getShiftReport()
    {
        return shiftInfo;
    }

    void Report::printReport(std::ostream &cout)
    {
        for(auto it = info.begin(); it != info.end(); it++) {
            cout << it->first << ": " << it->second << std::endl;
        }

        if(shiftInfo.size() != 0) {
            for(auto it = shiftInfo.begin(); it != shiftInfo.end(); it++) {
                cout << it->first << ": " << it->second << std::endl;
            }
        }
    }



} // namespace report
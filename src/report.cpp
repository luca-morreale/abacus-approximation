#include "include/report.h"


namespace report {

    Report::AppName Report::approximationsName(map_start_values, map_start_values + map_start_values_size);

    const Report::approxpair Report::map_start_values[] = {
            Report::approxpair(&approximation::approximateSum, "sum"),
            Report::approxpair(&approximation::approximateMinus, "min"),
            Report::approxpair(&approximation::approximateMult, "mult"),
            Report::approxpair(&approximation::approximateDiv, "div"),
            Report::approxpair(&approximation::approximateValue, "value")
        };




} // namespace report
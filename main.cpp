#include <chrono>
#include <iostream>
#include <date/date.h>
#include <date/chrono_io.h>

const std::string NORMAL = "\x1b[0m";
const std::string RED = "\x1b[31m";
const std::string YELLOW = "\x1b[33m";

auto main(int argc, char** argv) -> int {
    date::year current_y;
    date::sys_days current;
    date::year_month_day today = std::chrono::time_point_cast<date::days>(std::chrono::system_clock::now());

    if (argc == 1) {
        // Set current to the first day of the current year.
        // This seems obvious but took a long time to work out.
        current = std::chrono::time_point_cast<date::days>(floor<date::years>(std::chrono::system_clock::now()));
        current_y = date::year_month_day{current}.year();
    }
    else {
        current_y = date::year{std::stoi(argv[1])};
        current = date::sys_days{current_y/1/1};
    }
    date::year_month_day current_ymd = current_y/date::January/1;

    std::cout << "   ";
    for (int j = 1; j < 31+7; j++) {
        // I think this should be std::format(" {%a}", ...
        std::cout << format(" %a", date::weekday(j%7)).substr(0,3);
    }
    std::cout << "\n";

    while (current_ymd.year() == current_y) {
        std::cout << NORMAL;
        std::cout << current_ymd.month() << " ";
        auto padding = date::Monday;

        while (padding != date::weekday{current_ymd}) {
            padding++;
            std::cout << "   ";
        }

        date::month current_m = current_ymd.month();
        while (current_ymd.month() == current_m) {
            if (current_ymd == today) {
                std::cout << YELLOW;
            }
            else if (date::weekday{current_ymd} == date::Sunday ||
                     date::weekday{current_ymd} == date::Saturday) {             
                std::cout << RED;
            }
            else {
                std::cout << NORMAL;
            }
            std::cout << current_ymd.day() << " ";

            current += date::days{1};
            current_ymd = current;
        }

        std::cout << "\n";
    }
}

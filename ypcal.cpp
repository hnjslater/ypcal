#include <chrono>
#include <iostream>
#include <format>

const std::string NORMAL = "\x1b[0m";
const std::string RED = "\x1b[31m";
const std::string YELLOW = "\x1b[33m";

auto main(int argc, char** argv) -> int {
    std::chrono::year current_y;
    std::chrono::sys_days current;
    std::chrono::year_month_day today = std::chrono::time_point_cast<std::chrono::days>(std::chrono::system_clock::now());

    if (argc == 1) {
        // Set current to the first day of the current year.
        // This seems obvious but took a long time to work out.
        current = std::chrono::time_point_cast<std::chrono::days>(floor<std::chrono::years>(std::chrono::system_clock::now()));
        current_y = std::chrono::year_month_day{current}.year();
    }
    else {
        current_y = std::chrono::year{std::stoi(argv[1])};
        current = std::chrono::sys_days{current_y/1/1};
    }
    std::chrono::year_month_day current_ymd = current_y/std::chrono::January/1;

    std::cout << "   ";
    for (int j = 1; j < 31+7; j++) {
	// First two letters of each weekday name
        std::cout << std::format(" {:%a}", std::chrono::weekday(j%7)).substr(0,3);
    }
    std::cout << "\n";

    while (current_ymd.year() == current_y) {
        std::cout << NORMAL;
        std::cout << current_ymd.month() << " ";
        auto padding = std::chrono::Monday;

        while (padding != std::chrono::weekday{current_ymd}) {
            padding++;
            std::cout << "   ";
        }

        std::chrono::month current_m = current_ymd.month();
        while (current_ymd.month() == current_m) {
            if (current_ymd == today) {
                std::cout << YELLOW;
            }
            else if (std::chrono::weekday{current_ymd} == std::chrono::Sunday ||
                     std::chrono::weekday{current_ymd} == std::chrono::Saturday) {
                std::cout << RED;
            }
            else {
                std::cout << NORMAL;
            }
            std::cout << current_ymd.day() << " ";

            current += std::chrono::days{1};
            current_ymd = current;
        }

        std::cout << "\n";
    }
}

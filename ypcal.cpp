#include <chrono>
#include <iostream>
#include <format>
#include <map>

const std::string NORMAL = "\x1b[0m";
const std::string RED = "\x1b[31m";
const std::string YELLOW = "\x1b[33m";

auto main(int argc, char** argv) -> int {
    std::chrono::year_month_day today = std::chrono::time_point_cast<std::chrono::days>(std::chrono::system_clock::now());

    std::chrono::year current_y;
    if (argc == 1) {
        current_y = today.year();
    }
    else {
        current_y = std::chrono::year{std::stoi(argv[1])};
    }

    std::vector<int> padding;
    int num_columns = 0;
    for (auto current_ym = current_y/1; current_ym.year() == current_y; current_ym += std::chrono::months{1}) {
	int p = (std::chrono::weekday{current_ym/1}-std::chrono::Monday).count();
	padding.push_back(p);

	auto last_day_month = current_ym/std::chrono::last;
	auto month_length = static_cast<unsigned>(last_day_month.day());
	num_columns = std::max(num_columns, static_cast<int>(month_length)+p);
    }

    std::cout << "   ";
    for (int j = 1; j <= num_columns; j++) {
	// First two letters of each weekday name
        std::cout << std::format(" {:%a}", std::chrono::weekday(j%7)).substr(0,3);
    }
    std::cout << "\n";

    std::chrono::sys_days current = current_y/1/1;
    std::chrono::year_month_day current_ymd = current_y/1/1;
    auto current_padding = padding.begin();
    while (current_ymd.year() == current_y) {
        std::cout << NORMAL;
        std::cout << current_ymd.month() << " ";

        for (int p = 0; p < *current_padding; p++) {
            std::cout << "   ";
        }
	current_padding++;

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
    std::cout << NORMAL;
}

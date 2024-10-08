System Monitor Project - README
# System Monitor Project
This project implements a system monitor in C++ using the ncurses library. It mimics the functionality of utilities like htop and top, displaying system resource usage, running processes, and CPU statistics.
## Project Files
1. main.cpp:
- Entry point of the application. Initializes the system monitor, sets up ncurses display, and runs the
program loop.
2. linux_parser.cpp & linux_parser.h:
- These files define the LinuxParser class, responsible for reading system data from the /proc directory
on Linux systems. Functions include reading CPU statistics, memory usage, system uptime, and process information.
3. processor.cpp & processor.h:
- Implements the logic to gather and process CPU utilization data. Tracks and calculates CPU usage
over time by comparing active and idle time.
4. process.cpp & process.h:
- Represents a process running on the system. Gathers information such as process ID (PID), user,
CPU and memory usage, and uptime.

5. system.cpp & system.h:
- Manages system-wide statistics, including the total number of processes, running processes, and
overall CPU utilization. Acts as the central interface between the LinuxParser class and the UI.
6. ncurses_display.cpp & ncurses_display.h:
- Handles the display of system information using the ncurses library. Presents the system's CPU,
memory, and process information in a table-like format for real-time monitoring.
7. format.cpp & format.h:
- Contains utility functions for formatting data, such as converting time from seconds to human-readable
format (hours, minutes, seconds).
## How to Run the Project
### Prerequisites
- C++17 compiler (GCC or Clang).
- ncurses library (required for rendering the display). - CMake for project building.
### Steps to Run:
1. Clone the repository:
git clone https://github.com/SmilingBuddha95/System-Monitor.git cd System-Monitor
2. Install the ncurses library:
sudo apt-get install libncurses5-dev libncursesw5-dev

3. Build the project: mkdir build
cd build
cmake ..
make
4. Run the executable: ./monitor
## How It Works
- The program reads real-time system data from /proc/ to track CPU and memory usage.
- The data is displayed using the ncurses library in a terminal window.
- The system updates at regular intervals, providing a live view of system activity and performance.
## Future Improvements
- Add more advanced process management features like filtering and sorting.
- Support for non-Linux systems through platform-agnostic data gathering methods.
## License
This project is licensed under the MIT License.

#include <iostream.h>
#include <vector.h>
#include <string.h>
#include <map.h>
#include <iomanip.h> // Include the <iomanip> header

using namespace std;

// Event structure to store event details
struct Event {
    string name;
    string date;
    string time;
};

// Calendar class to manage events
class Calendar {
public:
    void addEvent(const string& date, const string& time, const string& name) {
        Event event = {name, date, time};
        events[date].push_back(event);
    }

    void displayEvents(const string& date) {
        if (events.find(date) == events.end()) {
            cout << "No events for the date: " << date << endl;
            return;
        }

        cout << "Events for the date: " << date << endl;
        for (const Event& event : events[date]) {
            cout << event.time << ": " << event.name << endl;
        }
    }

    void displayEventsForMonth(const string& month) {
        cout << "Events for the month: " << month << endl;
        for (const auto& pair : events) {
            if (pair.first.find(month) != string::npos) {
                cout << "Date: " << pair.first << endl;
                for (const Event& event : pair.second) {
                    cout << event.time << ": " << event.name << endl;
                }
            }
        }
    }

    void displayMonthCalendar(int year, int month) {
        cout << "Calendar for " << year << "-" << setw(2) << month << endl;
        cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

        struct tm timeinfo = {0};
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = 1;
        mktime(&timeinfo);

        int dayOfWeek = timeinfo.tm_wday;
        int daysInMonth = 31; // Assume 31 days by default

        if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
        }

        for (int i = 0; i < dayOfWeek; ++i) {
            cout << "    ";
        }

        for (int day = 1; day <= daysInMonth; ++day) {
            cout << setw(3) << day << " ";
            if (++dayOfWeek > 6) {
                dayOfWeek = 0;
                cout << endl;
            }
        }

        if (dayOfWeek != 0) {
            cout << endl;
        }
    }

private:
    map<string, vector<Event>> events;
};

int main() {
    Calendar myCalendar;

    while (true) {
        cout << "1. Display Month Calendar" << endl;
        cout << "2. Add Event" << endl;
        cout << "3. Display Events for a Date" << endl;
        cout << "4. Display Events for a Month" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            int year, month;
            cout << "Enter year and month (YYYY MM): ";
            cin >> year >> month;
            myCalendar.displayMonthCalendar(year, month);
        } else if (choice == 2) {
            string date, time, name;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter time (HH:MM): ";
            cin >> time;
            cin.ignore();
            cout << "Enter event name: ";
            getline(cin, name);

            myCalendar.addEvent(date, time, name);
            cout << "Event added successfully!" << endl;
        } else if (choice == 3) {
            string date;
            cout << "Enter date (YYYY-MM-DD) to display events: ";
            cin >> date;
            myCalendar.displayEvents(date);
        } else if (choice == 4) {
            string month;
            cout << "Enter month (YYYY-MM) to display events: ";
            cin >> month;
            myCalendar.displayEventsForMonth(month);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
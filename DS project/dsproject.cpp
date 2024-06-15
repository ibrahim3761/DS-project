#include <iostream>
#include <string>
#include <limits>

using namespace std; // Add using namespace std; for convenience

struct Appointment
{
    string description;
    string date; // format: YYYY-MM-DD
    string time; // format: HH:MM
    Appointment *next;
};

class AppointmentManager
{
private:
    Appointment *head;

public:
    AppointmentManager() : head(nullptr) {}

    // Function to add an appointment
    void addAppointment(const string &description, const string &date, const string &time)
    {
        Appointment *newAppointment = new Appointment{description, date, time, nullptr};

        if (!head || head->date > date || (head->date == date && head->time > time))
        {
            newAppointment->next = head;
            head = newAppointment;
        }
        else
        {
            Appointment *current = head;
            while (current->next && (current->next->date < date || (current->next->date == date && current->next->time <= time)))
            {
                current = current->next;
            }
            newAppointment->next = current->next;
            current->next = newAppointment;
        }
    }

    // Function to delete an appointment by description
    void deleteAppointment(const string &description)
    {
        if (!head)
            return;

        if (head->description == description)
        {
            Appointment *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Appointment *current = head;
        while (current->next && current->next->description != description)
        {
            current = current->next;
        }

        if (current->next)
        {
            Appointment *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Function to display all appointments
    void displayAppointments() const
    {
        if (!head)
        {
            cout << "No appointments found." << endl;
            return;
        }

        Appointment *current = head;
        while (current)
        {
            cout << "Description: " << current->description
                 << ", Date: " << current->date
                 << ", Time: " << current->time << endl;
            current = current->next;
        }
    }

    // Function to sort appointments by date and time
    void sortAppointments()
    {
        if (!head || !head->next)
            return; // No need to sort if list is empty or has only one element

        Appointment *current = head;
        Appointment *index = nullptr;
        Appointment *temp = nullptr;

        while (current)
        {
            index = current->next;

            while (index)
            {
                if (current->date > index->date || (current->date == index->date && current->time > index->time))
                {
                    // Swap data of current and index if index is smaller
                    temp = new Appointment{current->description, current->date, current->time, nullptr};
                    current->description = index->description;
                    current->date = index->date;
                    current->time = index->time;
                    index->description = temp->description;
                    index->date = temp->date;
                    index->time = temp->time;
                    delete temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    // Destructor to clean up allocated memory
    ~AppointmentManager()
    {
        while (head)
        {
            Appointment *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void displayMenu()
{
    cout << "1. Add Appointment" << endl;
    cout << "2. Delete Appointment" << endl;
    cout << "3. Display All Appointments" << endl;
    cout << "4. Sort Appointments" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    AppointmentManager manager;
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        // Handle invalid input for menu choice
        while (cin.fail() || choice < 1 || choice > 5)
        {
            cin.clear();                                                   // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 5: ";
            cin >> choice;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        switch (choice)
        {
        case 1:
        {
            string description, date, time;
            cout << "Enter description: ";
            getline(cin, description);
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            cout << "Enter time (HH:MM): ";
            getline(cin, time);
            manager.addAppointment(description, date, time);
            break;
        }
        case 2:
        {
            string description;
            cout << "Enter description of the appointment to delete: ";
            getline(cin, description);
            manager.deleteAppointment(description);
            break;
        }
        case 3:
            manager.displayAppointments();
            break;
        case 4:
            manager.sortAppointments();
            cout << "Appointments sorted." << endl;
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        }
        cout << endl;

    } while (choice != 5);

    return 0;
}

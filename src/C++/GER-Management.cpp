#include <iostream>
/*#include <externalfile>
because my program is oriented on "char", we can not put data until 500 emploeeys (limitation memory space),
 we will join external database (sorry Professor, i have not found better optimization)*/
using namespace std;

typedef struct // structure data of an employee
{
    char surname[255];
    char firstname[255];
    char dmy[255];
    char typeemployee[255];
} ListEmployees;

struct Hollydays_taken_list // structure of dates taken for days off by ONLY ONE EMPLOYEE
{
    char surname_dayoff[255];
    char firstname_dayoff[255];
    char dates_dayoff[255];
};

char bbb = 4; // initional number of emploeeys we have in database
unsigned int ddd = 0; // the total days off taken at the moment by ONLY ONE EMPLOYEE

int print_menu_choice()
{
    int choice; // menu variants
    cout << "Choose and type in the number of your action" << endl;
    cout << "1. List of employees" << endl;
    cout << "2. List of employees with additional information (sub classes)" << endl;
    cout << "3. Creating an employee" << endl;
    cout << "4. Deleting an employee" << endl;
    cout << "5. Entering the holiday days the employee wants" << endl;
    cout << "6. Checking the days off left" << endl;
    cout << "7. Searching for an employee" << endl << endl << endl;
    cout << "Number = ";
    cin >> choice;
    return choice;
}

int main()
{
    ListEmployees item[499]; //List of employees
    strcpy_s(item[0].surname, "Skrylnikov");
    strcpy_s(item[0].firstname, "Dmitry");
    strcpy_s(item[0].dmy, "23.01.1998");
    strcpy_s(item[0].typeemployee, "Manager-15%");
    strcpy_s(item[1].surname, "Arno");
    strcpy_s(item[1].firstname, "Yan");
    strcpy_s(item[1].dmy, "10.01.1989");
    strcpy_s(item[1].typeemployee, "Hourly-10$");
    strcpy_s(item[2].surname, "Olga");
    strcpy_s(item[2].firstname, "Agutina");
    strcpy_s(item[2].dmy, "12.12.1990");
    strcpy_s(item[2].typeemployee, "Annual-255000$");
    strcpy_s(item[3].surname, "Sava");
    strcpy_s(item[3].firstname, "Dorozh");
    strcpy_s(item[3].dmy, "25.11.1978");
    strcpy_s(item[3].typeemployee, "Annual-125000$");
    
    struct Hollydays_taken_list item2[29]; //List of taken days off by one employee (It is limitted by one only - because I didnt recognize another way to work)

    int a = print_menu_choice(); // main menu

    cout << "Number = ";

    if (a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6 || a == 7 || !cin >> a)
    {
        switch (a)
        {
        case 1: // 1. List of employees
            for (int i = 0; i < bbb; i++)
            {
                cout << "Surname: " << item[i].surname << endl << "Name: " << item[i].firstname << endl;
                cout << "Date of birth: " << item[i].dmy << endl << endl << endl;
            }
            break;
        case 2: // 2. List of employees with additional information (sub classes)
            for (int i = 0; i < bbb; i++)
            {
                cout << "Surname: " << item[i].surname << endl << "Name: " << item[i].firstname << endl;
                cout << "Date of birth: " << item[i].dmy << endl;
                cout << "Employee class: " << item[i].typeemployee << endl << endl << endl;
            }
            break;
        case 3: // 3. Creating an employee
            char surname2[255];
            char firstname2[255];
            char dmy2[255];
            char typeemployee2[255];
            int howmany;
            cout << "How much employees you want to enter?" << endl;
            cout << "The number: ";
            cin >> howmany;
            cout << endl << endl << endl;
            int overall;
            overall = howmany + bbb;
            if (overall <= 499)
            {
                for (int i = 0; i < howmany; i++)
                {
                    cout << "Surname: ";
                    cin >> surname2;
                    cout << endl;
                    cout << "Firstname: ";
                    cin >> firstname2;
                    cout << endl;
                    cout << "Attention! The format of date of birth - dd.mm.yyyy" << endl;
                    cout << "dd.mm.yyyy: ";
                    cin >> dmy2;
                    cout << endl;
                    cout << "Class of the employee: " << endl;
                    cout << "The format - Job possition-salary" << endl;
                    cout << "Possition-Salary: ";
                    cin >> typeemployee2;
                    strcpy_s(item[bbb].surname, surname2);
                    strcpy_s(item[bbb].firstname, firstname2);
                    strcpy_s(item[bbb].dmy, dmy2);
                    strcpy_s(item[bbb].typeemployee, typeemployee2);
                    bbb++;
                    for (int i = 0; i < bbb; i++)
                    {
                        cout << "Surname: " << item[i].surname << endl << "Name: " << item[i].firstname << endl;
                        cout << "Date of birth: " << item[i].dmy << endl;
                        cout << "Employee class: " << item[i].typeemployee << endl << endl << endl;
                    }
                }
            }
            else
            {
                cout << "The number of employees limitted by only 500 numbers!";
            }
            break;
        case 4: // 4. Deleting an employee
            cout << "How much employees you want to delete?" << endl;
            cout << "The number: ";
            int howmany2;
            cin >> howmany2;
            cout << endl << endl << endl;
            int overall2;
            overall2 = bbb - howmany2;
            if (overall2 >= 0)
                for (int i = 0; i < howmany2; i++)
                {
                    for (int i = 0; i < bbb; i++)
                    {
                        cout << "Surname: " << item[i].surname << "  " << "Name: " << item[i].firstname << endl << endl;
                    }
                    cout << "Enter the index of the employee (starting accounting with '0')" << endl;
                    cout << "Index: ";
                    int z;
                    cin >> z;
                    for (int i = 0; i < bbb; i++)
                    {
                        if (i == z)
                        {
                            strcat_s(item[i].surname, "  deleted");
                            strcat_s(item[i].firstname, "  deleted");
                            strcat_s(item[i].dmy, "  deleted");
                            strcat_s(item[i].typeemployee, "  deleted");
                        }
                    }
                    for (int i = 0; i < bbb; i++)
                    {
                        cout << "Surname: " << item[i].surname << endl << "Name: " << item[i].firstname << endl;
                        cout << "Date of birth: " << item[i].dmy << endl;
                        cout << "Employee class: " << item[i].typeemployee << endl << endl << endl;
                    }
                }
            else
            {
                cout << "You dont have the amount of your employee in your list!!";
            }
            break;
        case 5: // 5. Entering the holiday days the employee wants to take
            cout << "How many days off the employee wants to take?" << endl;
            int number_days_off;
            cin >> number_days_off;
            int tot_days;
            tot_days = ddd + number_days_off;
            if (tot_days < 30)
            {
                for (int i = 0; i < tot_days; i++)
                {
                    char surname_dayoff_added[255];
                    char firstname_dayoff_added[255];
                    char dates_dayoff_added[255];
                    cout << "Who wants to take a day off?" << endl;
                    cout << "Enter the surname: ";
                    cin >> surname_dayoff_added;
                    cout << endl;
                    cout << "Enter the first name: ";
                    cin >> firstname_dayoff_added;
                    cout << endl;
                    cout << "Enter the date (format - dd.mm.yyyy)" << endl;
                    cout << "dd.mm.yyyy: " << endl;
                    cin >> dates_dayoff_added;
                    cout << endl;
                    strcpy_s(item2[ddd].surname_dayoff, surname_dayoff_added);
                    strcpy_s(item2[ddd].firstname_dayoff, firstname_dayoff_added);
                    strcpy_s(item2[ddd].dates_dayoff, dates_dayoff_added);
                    for (int i = 0; i < tot_days; i++)
                    {
                        cout << "Surname: " << item2[i].surname_dayoff << endl;
                        cout << "Name: " << item2[i].firstname_dayoff << endl;
                        cout << "Date of day off: " << item2[i].dates_dayoff << endl << endl << endl;
                    }
                }
                ddd = ddd + number_days_off;
            }
            else
            {
                cout << "You achieved the max days off!";
            }
            break;
        case 6: // 6. Checking the days off left
            int days_left;
            days_left = 30 - ddd;
            cout << "This employee has: ";
            cout << days_left;
            cout << " days left.";
            break;
        case 7: // 7. Searching for an employee
            int index_employee;
            index_employee = 0;
            for (int i = 0; i < bbb; i++)
            {
                cout << index_employee << " " << item[i].surname << " " << item[i].firstname << endl;
                index_employee++;
            }
            cout << "Enter the index" << endl;
            cout << "Index = ";
            int ind;
            cin >> ind;
            for (int i = 0; i < bbb; i++)
                if (i == ind)
                {
                    {
                        cout << "Surname: " << item[i].surname << endl << "Name: " << item[i].firstname << endl;
                        cout << "Date of birth: " << item[i].dmy << endl;
                        cout << "Employee class: " << item[i].typeemployee << endl << endl << endl;
                    }
                }
            break;
        default:
            cout << "It is not a number, you have to type the number in!";
        }
    }
    else
    {
        cout << "You have to type the number in from the list!";
    }

    return 0;
}

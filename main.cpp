/*************************************************
Aufgabe Nr./Task No.: H4
Nachname/Last,Family Name: Abaza
Vorname/First,Given Name: Ahmed
Matrikelnummer/Matriculation number: 3035482
Uni-Email: ahmed.abaza@stud.uni-due.de
Studiengang/Course of Studies: ISE CE
*************************************************/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Time
{
private:
    unsigned int minutesOfDay;
public:
    Time(unsigned int);
    Time(unsigned int, unsigned int);
    void set_time(unsigned int, unsigned int);
    unsigned int get_hour();
    unsigned int get_minute();
    unsigned int get_minuteOfDay();
    Time operator+(unsigned int);
};

Time::Time(unsigned int initialTime = 0)
{
    minutesOfDay = initialTime;
}

Time::Time(unsigned int h, unsigned int m)
{
    set_time(h, m);
}

void Time::set_time(unsigned int h, unsigned int m)
{
    unsigned int timeCheck = (60 * h) + m;
    if(timeCheck >= 1440)
    {
        minutesOfDay = 0;
        cerr << "Please check time and try again! -- Time is set to 00:00" << endl;
    }
    else
    {
        minutesOfDay = timeCheck;
    }

}

unsigned int Time::get_hour()
{
    return (minutesOfDay / 60);
}

unsigned int Time::get_minute()
{
    return (minutesOfDay % 60);
}

unsigned int Time::get_minuteOfDay()
{
    return minutesOfDay;
}

Time Time::operator+(unsigned int add)
{
    Time sum;
    sum.minutesOfDay = minutesOfDay + add;
    if(sum.minutesOfDay >= 1440)
    {
        unsigned int o;
        o = sum.minutesOfDay - 1440;
        sum.minutesOfDay = o;
    }
    return sum;
}

istream& operator>>(istream& in, Time& z)
{
    unsigned int h, m;
    char c;
    in >> h >> c >> m;
    z.set_time(h, m);
    return in;
}

ostream& operator<<(ostream &out, Time y)
{
    int hour, minute;
    hour = y.get_hour();
    minute = y.get_minute();
    out << setfill('0') << setw(2) << hour  << ':' << setfill('0') << setw(2) << minute;
    return out;
}

class Train
{
private:
    string no, to, over;
public:
    Train(string, string, string);
   ~Train();
   string get_no();
   string get_to();
   string get_over();
};

Train::Train(string a, string b, string c)
{
    no = a;
    to = b;
    over = c;
}

Train::~Train()
{
    cout << "Train " << no << "to " << to << "over" << over << "deleted" << endl;
}

string Train::get_no()
{
    return no;
}

string Train::get_to()
{
    return to;
}

string Train::get_over()
{
    return over;
}

class Station
{
private:
    const string station;
    static const unsigned int platforms = 15;
    Train *schedule[24*60][platforms];
public:
    Station(string stationName) : station(stationName)
    {
        for(int i = 0; i < 1440; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                schedule[i][j] = nullptr;
            }
        }
    };
    ~Station()
    {
        for(unsigned int i = 0; i < 1440; i++)
        {
            for(unsigned int j = 0; j < 15; j++)
            {
                if(schedule[i][j] != nullptr)
                {
                    Train *p = schedule[i][j];
                    unsigned int x = i / 60;
                    unsigned int y = i % 60;
                    string a = p->get_no();
                    string b = p->get_to();
                    string c = p->get_over();
                    cout << right << setw(2) << setfill('0') << x << ":" << setw(2) << y << "\t" << setw(7) << left << setfill(' ') << a << "\t" << setw(50) << c << "\t" << setw(15) << b << "\t" << setw(2) << j+1 << " is deleted" << endl;
                }
            }
        }
        cout << "schedule for" << station << "completely deleted!";
    };
    void addDeparture(unsigned int, unsigned int, Train*);
    void showDepartures(Time, unsigned int);
};

void Station::addDeparture(unsigned int time, unsigned int platformNo, Train *p)
{
    unsigned int m, n;
    m = time;
    n = platformNo - 1;
    schedule[m][n] = p;
}

void Station::showDepartures(Time time, unsigned int addedTime)
{
    unsigned int x, y;
    Train *p;
    Time bis = time + addedTime;
    unsigned int t = time.get_minuteOfDay();
    unsigned int s = bis.get_minuteOfDay();
    cout << endl << station << endl;
    cout << "DEPARTURES " << time << "-" << bis << endl;
    cout << endl << "===========================" << endl;
    cout << left << setw(5) << setfill(' ') << "Time" << "\t" << setw(7) << "Train" << "\t" << setw(50) << "Over" << "\t" << setw(15) << "To" << "\t" << setw(2) << "Platform" << endl;
    if(t > s)
    {
        for(unsigned int i = t; i < 1440; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                if(schedule[i][j] != nullptr)
                {
                p = schedule[i][j];
                x = i / 60;
                y = i % 60;
                string a = p->get_no();
                string b = p->get_to();
                string c = p->get_over();
                cout << right << setw(2) << setfill('0') << x << ":" << setw(2) << y << "\t" << setw(7) << left << setfill(' ') << a << "\t" << setw(50) << c << "\t" << setw(15) << b << "\t" << setw(2) << j+1 << endl;
                }
            }
        }
        for(unsigned int i = 0; i <= s; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                if(schedule[i][j] != nullptr)
                {
                p = schedule[i][j];
                x = i / 60;
                y = i % 60;
                string a = p->get_no();
                string b = p->get_to();
                string c = p->get_over();
                cout << right << setw(2) << setfill('0') << x << ":" << setw(2) << y << "\t" << setw(7) << left << setfill(' ') << a << "\t" << setw(50) << c << "\t" << setw(15) << b << "\t" << setw(2) << j+1 << endl;
                }
            }
        }
    }
    else
    {
        for(unsigned int i = t; i <= s; i++)
        {
            for(unsigned int j = 0; j < 15; j++)
            {
                if(schedule[i][j] != nullptr)
                {
                    p = schedule[i][j];
                    x = i / 60;
                    y = i % 60;
                    string a = p->get_no();
                    string b = p->get_to();
                    string c = p->get_over();
                    cout << right << setw(2) << setfill('0') << x << ":" << setw(2) << y << "\t" << setw(7) << left << setfill(' ') << a << "\t" << setw(50) << c << "\t" << setw(15) << b << "\t" << setw(2) << j+1 << endl;
                }
            }
        }
    }
}

int main()
{
    Time ST;
    Time AT;
    unsigned int d, f, h, pl, m, z;
    string tr, to, over;
    Station duisburg("Duisburg Hbf");
    Train *S1 = new Train("S1", "Dortmund Hbf", "Muelheim(Ruhr)Styrum - Muelheim(Ruhr) - Essen");
    for(h = 0; h < 24; h++)
    {
        for(m = 7; m < 60; m = m + 20)
        {
            z = 60*h + m;
            duisburg.addDeparture(z, 9, S1);
        }
    }
    Train *S1b = new Train("S1", "Solingen Hbf", "Duisburg-Schlenk - Duesseldorf Flughafen");
    for(h = 0; h < 24; h++)
    {
        for(m = 15; m < 60; m = m + 20)
        {
            z = 60*h + m;
            duisburg.addDeparture(z, 5, S1b);
        }
    }
    Train *S2 = new Train("S2", "Dortmund Hbf", "Oberhausen - Gelsenkirchen - Wanne-Eickel");
    for(h = 0; h < 24; h++)
    {
        for(m = 35; m < 60; m = m + 60)
        {
            z = 60*h + m;
            duisburg.addDeparture(z, 2, S2);
        }
    }
    Train *RE1 = new Train("RE1", "Aachen Hbf", "Duesseldorf Flughafen - Duesseldorf - Koeln");
    for(h = 0; h < 24; h++)
    {
        for(m = 22; m < 60; m = m + 60)
        {
            z = 60*h + m;
            duisburg.addDeparture(z, 4, RE1);
        }
    }
    Train *RE2 = new Train("RE2", "Muenster Hbf", "Muelheim(Ruhr) - Essen - Gelsenkirchen");
    for(h = 0; h < 24; h++)
    {
        for(m = 24; m < 60; m = m + 60)
        {
            z = 60*h + m;
            duisburg.addDeparture(z, 10, RE2);
        }
    }
    char choice;
    do
   {
      cout << "0 End" << endl
           << "1 Schedule a Train" << endl
           << "2 Show Schedule" << endl
           << ">> ";
      cin >> choice;
      switch (choice)
      {
      case '0': break;
      case '1': {
                cout << "Time of departure? ";
                cin >> AT;
                cout << "Platform? ";
                cin >> pl;
                cout << "Train? ";
                cin.sync();
                getline(cin, tr);
                cout << "To? ";
                cin.sync();
                getline(cin, to);
                cout << "Over? ";
                cin.sync();
                getline(cin, over);
                Train *L = new Train(tr, to, over);
                f = AT.get_minuteOfDay();
                duisburg.addDeparture(f, pl, L);
                }
                break;
      case '2': cout << "Please enter time to search for: ";
                cin >> ST;
                cout << "Please enter time to search after: ";
                cin >> d;
                duisburg.showDepartures(ST, d);
                break;
      default:  cout << "sorry wrong choice" << endl;
      }
   } while(choice != '0');
   return 0;
}

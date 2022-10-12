/*
  Author:  Mohammad Seeam
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

template<typename T> // useful for getting user's keyboard input without crash or hang
T kbd_input(const string &prompt="Enter: ", const string &errmsg="  Oops! Try again.\n\n") {
  while (true) {
    cout << prompt; T ans;
    if (cin>>ans) return ans;
    else {
      cin.clear(); cin.ignore(INT_MAX, '\n'); cout<<errmsg;
    }
  }
}

class Day {
  private:
    int day_of_year; // limit day_of_year to positive numbers

  public:
    // month:
    static const int daysInMonth[12];
    static const int daysInMonth_accum[12];
    static const string monthsOfYear[12];  // Later initialized to: {"january", "february", "march", ... "december"};
    enum Month_t {JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

    // week
    static const string daysOfWeek[7];  // Initialized to: {"sunday", "monday", "tuesday", ... "saturday"};
    enum Weekday_t {SUN, MON, TUE, WED, THR, FRI, SAT}; // may be useful

    // day
    static const int BASE_YEAR=2022;
    static const Month_t BASE_MONTH=JAN;
    static const Weekday_t BASE_WEEKDAY=SAT; // January 1, 2022 was a Saturday
    static const int BASE_DAY=1;

    // default constructor that sets day_of_year to 1
    Day(){
      day_of_year=1;
    }

    // custom constructor that takes an input day_number and sets to day_of_year
    Day(int day_number){

      if(day_number<=0){day_number=BASE_DAY;}

      day_of_year = day_number;
    }

    // custom constructor that takes a month_name, converts the month nsme into int, 
    // then adds that int with day_number and sets to day_of_year
    Day(string month_name , int day_number){
      
      bool monthFound = false;

      for(int i=0; i<12 ; i++){
        if(monthsOfYear[i]==month_name){

          //set monthFound to true
          monthFound = true;

          //get the accum days for this month
          day_of_year=daysInMonth_accum[i];

          // now need to add day_number to the day_of_year.
          // before doing that, we need to check if day_number is bigger 
          // than possible number of days for that month
          if(day_number > daysInMonth[i]){
            day_of_year = day_of_year + daysInMonth[i];
          }else{
            day_of_year = day_of_year + day_number;
          }
        }
      }

      //final check to see if month_name passed was actually a valid month
      if(!monthFound){
        //month name provided was not a month so we will default to january
        //we will still try to keep day_number as long as it is smaller than maximum number of days in january that is 31 days
        cout << "WARNING! the month name you provided is not correct or maybe complete, defaulting to january for month." << endl;
        if(day_number > daysInMonth[0]){
            day_of_year = daysInMonth[0];
          }else{
            day_of_year = day_number;
          }
      }
    }

    friend ostream& operator<<(ostream& os, const Day& dt);
    //Overloading the prefix ++ operator
    Day operator++(){
      Day d;
      d.day_of_year = ++day_of_year;
      return d;
    }

    // Overloading the postfix ++ operator
    Day operator++(int){
      Day d;
      d.day_of_year = day_of_year++;
      return d;
    }

    // Overloading the prefix -- operator
    Day operator--(){
      Day d;
      d.day_of_year = --day_of_year;
    return d;
    }

    // Overloading the postfix -- operator
    Day operator--(int){
      Day d;
      d.day_of_year = day_of_year--;
      return d;
    }

    //setter
    void set_day_of_year(int dayOfYear){
      if(dayOfYear<0){
        day_of_year=BASE_DAY;
      }else{
        day_of_year=dayOfYear;
      }
      
    }

    //getter
    int get_day_of_year(){
      return day_of_year;
    }

    //returns the index of current day in the daysOfWeek array
    //sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"
    int indexOfCurrentDayOfWeek(){
      int remainder = ((day_of_year)%7);
      if(remainder==0){return 5;}  //index of friday in daysOfWeek array
      if(remainder==1){return 6;}  //index of saturday in daysOfWeek array
      //for other days
      return remainder-2;
    }

    //returns the index of current month in the monthsOfYear array
    int indexOfmonthsOfYear(){
      int dayOfYear = day_of_year % 365;

      //after mod, if remainder is 0, means today is december 31st so we return index of december in monthsOfYear array
      if (dayOfYear==0){
        return 11;
      }
      
      //if remainder is greater than 0, we need to check which month
      for(int i=0; i< 12-1; i++){

        //check for all months except december
        if( dayOfYear > daysInMonth_accum[i] && dayOfYear<=daysInMonth_accum[i+1]){
          return i;
        }
        
        //check for december month
        if(dayOfYear>daysInMonth_accum[11]){
          return 11;
        }
      }

      //dummy return
      return -1;
    }
    
    //return the day of month
    int dayOfMonth(){
      int dayOfYear = day_of_year % 365;

      //after mod, if remainder is 0, means today is december 31st so we return 31
      if (dayOfYear==0){
        return 31;
      }
      
      //if remainder is greater than 0, we need to check which month
      for(int i=0; i< 12-1; i++){

        //check for all months except december
        if( dayOfYear > daysInMonth_accum[i] && dayOfYear<=daysInMonth_accum[i+1]){
          return dayOfYear - daysInMonth_accum[i];
        }
        
        //check for december month
        if(dayOfYear>daysInMonth_accum[11]){
          return dayOfYear - daysInMonth_accum[11];
        }
      }

      //dummy return 
      return -1;
    }

    //returns the year from day_of_year
    int year(){
      int divResult = day_of_year/365;
      int remainder = day_of_year%365;
      
      //if remainder=0, meaning last day is dec 31st, so new year have not started yet
      if(remainder==0){
        return BASE_YEAR + divResult - 1;
      }else{
        return BASE_YEAR + divResult;
      }
    }

    void printDay(){
      cout << daysOfWeek[indexOfCurrentDayOfWeek() ] << " " << monthsOfYear[indexOfmonthsOfYear()] << " " << dayOfMonth() << " " << year();
    } 

};

ostream& operator<<(ostream& os, const Day& d){
  Day dd(d.day_of_year);
  dd.printDay();
  return os;
}

// Use these as needed
const int Day::daysInMonth[12]       = {31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30,  31};
const int Day::daysInMonth_accum[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
const string Day::monthsOfYear[12] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
const string Day::daysOfWeek[7] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
string monthsOfYearShort[12] = {"jan", "feb", "mar", "apr", "may",  "jun", "jul", "aug", "sep",  "oct", "nov", "dec"};


//verifies if parameter monthDays is in valid form, example of correct form is 'may 5' or 'may 15'
//if so then separates the month from day and sets them into the reference variables
void checkMonthDayInput(string monthDay, int &monthIndex, int &day, bool &inputValid, string &reason){

  bool validMonth = false;
  bool validDay = false;

  //check if monthDay is at least 5 characters long ex: 'may 5'
  if(monthDay.length()<5){
    inputValid=false;
    reason = "input not long enough";
    return;
  }

  //check if monthDay variable's first three char makes month
  string m = monthDay.substr(0, 3);

  //check if m belongs in monthsOfYearShort array
  for (int i=0; i<12; i++){
    if(m==monthsOfYearShort[i]){
      //month is valid
      monthIndex=i;
      validMonth=true;
    }
  }

  //check if month is not valid in that case return now
  if(!validMonth){
    inputValid=false;
    reason = "month is not valid";
    return;
  }

  //take the rest of monthDay string and put in string variable d
  string d = monthDay.substr(4);

  //check if d is numeric
  for(int i=0; i< d.length(); i++){
    if(!isdigit(d[i])){
      inputValid=false;
      reason = "day is not numeric";
      return;
    }
  }

  //coming here means day is numeric and valid
  day = std::stoi(d);
  validDay = true;

  //final check
  if(validMonth && validDay){
    inputValid=true;
  }
}

int main() {
  cout <<"Welcome to Mohammad Seeam's calendar helper!\n";

  Day day; // this is updated in the set day options, and is the 1st day displayed in the Display options.

  for (bool running=true; running; ) {

    cout<<"\nOptions: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: ";

    string option; 
    char option_letter; 
    cin>>option; 
    option_letter=tolower(option[0]);

    switch (option_letter) {
      case 'd': {
          cout<<endl;
          day.printDay();
          cout<<endl;
          break;
        }

      case 'w': {
        
          int copy = day.get_day_of_year();
          cout<<endl;
          for(int i=0; i<7; i++){
            day.set_day_of_year(copy+i);
            day.printDay();
            cout << ", ";
            cout<<endl;
          }
          day.set_day_of_year(copy);

          break;
        }
        
      case 'm': {
          int copy = day.get_day_of_year();
          cout<<endl;
          int daysInCurrMonth = Day::daysInMonth[day.indexOfmonthsOfYear()];
          for(int i=1; i<=daysInCurrMonth; i++){

            day.set_day_of_year(copy+i-1);
            day.printDay();
            cout << ", ";

            if(i%7==0){
              cout << endl;
            }
          }
          day.set_day_of_year(copy);
          cout<<endl;
          break;
        }
        
      case 's': // set day, test constructors: Day(), Day(int) constructor
        {
          char option = tolower(kbd_input<char>("  set day d)efault m)month,day n)umber v)ary: "));
          if (option=='q') break;

          switch(option) {
            case 'd': { // d=default: use default for an instance of class Day
              day.set_day_of_year(day.BASE_DAY);
              cout<<endl;
              cout << "day set to default: ";
              day.printDay();
              cout << endl;
              break;
            }

            case 'm': {  // m=month day: ask user for month and day of month, use user's input to construct a Day

              //take user input for month and day
              string monthDay;
              int monthIndex_;
              int day_;
              bool inputvalid=false;
              string reason;
              
              //keep taking input as long as input is not valid
              while(!inputvalid){
                cout << "mon day (3-letter-month number, like: jan 1): ";
                cin.clear();
                std::getline(std::cin >> std::ws, monthDay);
                checkMonthDayInput(monthDay, monthIndex_, day_, inputvalid, reason);
                if(!inputvalid){
                  cout << "Try again, " << reason << endl;
                }
              }
          
              //replace the old day object with new one
              string newMonth = Day::monthsOfYear[monthIndex_];
              day = Day(newMonth, day_);
              cout<<endl;
              cout << "day set to: ";
              day.printDay();
              cout<<endl;
              break;
            }

            case 'n': { 
              int dayInput=1;
              cout << "number day of year (1-365...): ";
              cin>>dayInput;
              while(dayInput<1 || dayInput>365){
                cout << "Invalid input, try again: ";
                cin.clear();
                cin >> dayInput;
              }
              day.set_day_of_year(dayInput);
              cout<<endl;
              cout << "day set to : ";
              day.printDay();
              cout<<endl;
              break;
            }

            case 'v': { 
              string varyAmount;
              cout << "Vary Amount [must be int, can be negative]: ";
              cin >> varyAmount;
              int VA = std::stoi(varyAmount);
              day.set_day_of_year(day.get_day_of_year() + VA);
              cout<<endl;
              cout << "day set to : ";
              day.printDay();
              cout << endl;
              break;
            }

            default: 
              cout<<"    set day Invalid option.\n"; break;// continue;
          }
          // cout<<"  day#=["<<day<<"] "<<day.to_string()<<endl; // generic output. Could be helpful.
          break;
        } // case 's' for set day

      case 't': {
          cout<<endl;
          char inputforT;
          cout << "---Select from below options---" << endl;
          cout << "d)default constructor" << endl;
          cout << "i)constructor that takes int" << endl;
          cout << "m)constructor that takes month day" << endl;
          cout << "w)test ++ operator " << endl;
          cout << "x)test -- operator " << endl;
          cout << "y)test << operator " << endl;
          cout << "q)quit " << endl;
          cout << "select: ";
          
          cin >> inputforT;
          while(inputforT!='d' && inputforT!='i' && inputforT!='m' && inputforT!='w' && inputforT!='x' && inputforT!='y' && inputforT!='q'){
            cout << "wrong input try again: ";
            cin.clear();
            cin >> inputforT;
          }

          if (inputforT=='q')break;

          if(inputforT=='d'){
            //use default constructor to set day
            day = Day();
            cout<<endl;
            cout << "day set using default constructor: ";
            day.printDay();
            cout << endl;
            break;
          }

          if(inputforT=='i'){
            //use default constructor to set day
            day = Day(121);
            cout<<endl;
            cout << "day set using constructor that takes int(121): ";
            day.printDay();
            cout << endl;
            break;
          }

          if(inputforT=='m'){
            //use default constructor to set day
            day = Day("july", 4);
            cout<<endl;
            cout << "day set using constructor constructor that takes month day(july 4): ";
            day.printDay();
            cout << endl;
            break;
          }

          if(inputforT=='w'){
            cout<<endl;
            cout << "automatically setting the day to July 31 before performing increment operations"<< endl;
            day = Day("july", 31);
            cout<<endl;
            cout << "Current date before performing (++day) operations: ";
            day.printDay();
            cout<<endl;
            for (int i=0; i<5; ++i) {cout<<"    "; (++day).printDay();} cout<<endl;
            cout << "Current date after performing (++day) operations: ";
            day.printDay();
            cout<< endl;


            cout << endl;
            cout << "Current date before performing (day++) operations: ";
            day.printDay();
            cout<<endl;
            for (int i=0; i<5; ++i) {cout<<"    "; (day++).printDay();} cout<<endl;
            cout << "Current date after performing (day++) operations: ";
            day.printDay();
            cout<< endl;
          }

          if(inputforT=='x'){
            cout<<endl;
            cout << "automatically setting the day to July 31 before performing decrement operations"<< endl;
            day = Day("july", 31);
            cout << endl;

            cout << "Current date before performing (--day) operations: ";
            day.printDay();
            cout<<endl;
            for (int i=0; i<5; ++i) {cout<<"    "; (--day).printDay();} cout<<endl;
            cout << "Current date after performing (--day) operations: ";
            day.printDay();
            cout<< endl;

            cout << endl;
            cout << "Current date before performing (day--) operations: ";
            day.printDay();
            cout<<endl;
            for (int i=0; i<5; ++i) {cout<<"    "; (day--).printDay();} cout<<endl;
            cout << "Current date after performing (day--) operations: ";
            day.printDay();
            cout<< endl;
          }

          if(inputforT=='y'){ //extra credit
            cout<<endl;
            cout << "Calling 'cout <<day' below..."<< endl;
            cout << day;
            cout<<endl;
          }

          //this break is to break from t option
          break;
        }
        
      case 'q':
        running=false;
        break;
        
      default:
        cout<<"  Invalid option, try again. q to quit.\n";
        break;
    }
  }
  cout<<"\nThanks for using Mohammad Seeam's calendar helper! Good-bye!";
}

/*
Welcome to Mohammad Seeam's calendar helper!

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: d

saturday january 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: w

saturday january 1 2022, 
sunday january 2 2022, 
monday january 3 2022, 
tuesday january 4 2022, 
wednesday january 5 2022, 
thursday january 6 2022, 
friday january 7 2022, 

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: m

saturday january 1 2022, sunday january 2 2022, monday january 3 2022, tuesday january 4 2022, wednesday january 5 2022, thursday january 6 2022, friday january 7 2022, 
saturday january 8 2022, sunday january 9 2022, monday january 10 2022, tuesday january 11 2022, wednesday january 12 2022, thursday january 13 2022, friday january 14 2022, 
saturday january 15 2022, sunday january 16 2022, monday january 17 2022, tuesday january 18 2022, wednesday january 19 2022, thursday january 20 2022, friday january 21 2022, 
saturday january 22 2022, sunday january 23 2022, monday january 24 2022, tuesday january 25 2022, wednesday january 26 2022, thursday january 27 2022, friday january 28 2022, 
saturday january 29 2022, sunday january 30 2022, monday january 31 2022, 

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: x
  Invalid option, try again. q to quit.

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: s
  set day d)efault m)month,day n)umber v)ary: d

day set to default: saturday january 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: s
  set day d)efault m)month,day n)umber v)ary: m
mon day (3-letter-month number, like: jan 1): dec 22

day set to: thursday december 22 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: s
  set day d)efault m)month,day n)umber v)ary: n
number day of year (1-365...): 155

day set to : saturday june 4 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: s
  set day d)efault m)month,day n)umber v)ary: v
Vary Amount [must be int, can be negative]: -4

day set to : tuesday may 31 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: s
  set day d)efault m)month,day n)umber v)ary: v
Vary Amount [must be int, can be negative]: 1

day set to : wednesday june 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: d

wednesday june 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: w

wednesday june 1 2022, 
thursday june 2 2022, 
friday june 3 2022, 
saturday june 4 2022, 
sunday june 5 2022, 
monday june 6 2022, 
tuesday june 7 2022, 

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: m

wednesday june 1 2022, thursday june 2 2022, friday june 3 2022, saturday june 4 2022, sunday june 5 2022, monday june 6 2022, tuesday june 7 2022, 
wednesday june 8 2022, thursday june 9 2022, friday june 10 2022, saturday june 11 2022, sunday june 12 2022, monday june 13 2022, tuesday june 14 2022, 
wednesday june 15 2022, thursday june 16 2022, friday june 17 2022, saturday june 18 2022, sunday june 19 2022, monday june 20 2022, tuesday june 21 2022, 
wednesday june 22 2022, thursday june 23 2022, friday june 24 2022, saturday june 25 2022, sunday june 26 2022, monday june 27 2022, tuesday june 28 2022, 
wednesday june 29 2022, thursday june 30 2022, 

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: s
  set day d)efault m)month,day n)umber v)ary: d

day set to default: saturday january 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: d

day set using default constructor: saturday january 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: i

day set using constructor that takes int(121): sunday may 1 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: m

day set using constructor constructor that takes month day(july 4): monday july 4 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: w

automatically setting the day to July 31 before performing increment operations

Current date before performing (++day) operations: sunday july 31 2022
    monday august 1 2022    tuesday august 2 2022    wednesday august 3 2022    thursday august 4 2022    friday august 5 2022
Current date after performing (++day) operations: friday august 5 2022

Current date before performing (day++) operations: friday august 5 2022
    friday august 5 2022    saturday august 6 2022    sunday august 7 2022    monday august 8 2022    tuesday august 9 2022
Current date after performing (day++) operations: wednesday august 10 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: x

automatically setting the day to July 31 before performing decrement operations

Current date before performing (--day) operations: sunday july 31 2022
    saturday july 30 2022    friday july 29 2022    thursday july 28 2022    wednesday july 27 2022    tuesday july 26 2022
Current date after performing (--day) operations: tuesday july 26 2022

Current date before performing (day--) operations: tuesday july 26 2022
    tuesday july 26 2022    monday july 25 2022    sunday july 24 2022    saturday july 23 2022    friday july 22 2022
Current date after performing (day--) operations: thursday july 21 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: y

Calling 'cout <<day' below...
thursday july 21 2022

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: t

---Select from below options---
d)default constructor
i)constructor that takes int
m)constructor that takes month day
w)test ++ operator 
x)test -- operator 
y)test << operator 
q)quit 
select: q

Options: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: q

Thanks for using Mohammad Seeam's calendar helper! Good-bye!% 
*/
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

class Date {
public:
	Date(){}
	Date(const int& y, const int& m, const int& d){
		year = y;
		if (m < 1 || m > 12){
			throw invalid_argument("Month value is invalid: " + to_string(m));
		}
		month = m;
		if (d < 1 || d > 31){
			throw domain_error("Day value is invalid: " + to_string(d));
		}
		day = d;
	}
  int GetYear() const{
  return year;
  }
  int GetMonth() const{
  return month;
  }
  int GetDay() const{
  return day;
  }
private:
  int year;
  int month;
  int day;
};
bool operator<(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() < rhs.GetYear()){
		return true;
	}else{
		if(lhs.GetYear() == rhs.GetYear()){
			if(lhs.GetMonth() < rhs.GetMonth()){
				return true;
			}else{
				if(lhs.GetMonth() == rhs.GetMonth()){
					if(lhs.GetDay() < rhs.GetDay()){
						return true;
					}
				}
			}
		}
	}
	return false;
}

istream& operator>>(istream& stream, Date& obj){
	int y, m, d;
	char c, f;
	string s;
	stream >> s;
	stringstream com(s);
	if (com >> y >> c >> m >> f >> d && com.eof() && c == '-' && f == '-'){
		obj = {y,m,d};
	}else{
		throw runtime_error("Wrong date format: " + s);
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Date& obj){
	stream << setw(4) << setfill('0') << obj.GetYear() << '-' <<
			setw(2) << setfill('0') <<
			obj.GetMonth() << '-' << setw(2) << setfill('0') <<
			obj.GetDay();
	return stream;
}


class Database {
public:
	Database(){}
  void AddEvent(const Date& date, const string& event){
  base[date].insert(event);
  };
  bool DeleteEvent(const Date& date, const string& event){
  if(base.count(date) > 0){
	  for (auto x : base[date]){
	  if (x == event){
		  base.at(date).erase(x);
		  return true;
	  }
  }
  }
  return false;
  };
  int  DeleteDate(const Date& date){
  if (base.count(date) > 0){
	  int tmp = base.at(date).size();
	  base.erase(date);
	  return tmp;
  }else{
	  return 0;
  }
  }

  void Find(const Date& date) const{
	  if (base.count(date) > 0){
	  for (auto x : base.at(date)){
		  cout << x << endl;
	  }
	  }
  }

  void Print() const{
	  for (auto x : base){
		  for (auto y : x.second){
			  cout << x.first << " " << y << endl;
		  }
	  }
  }
private:
  map<Date, set<string>> base;
};

int main() {
  Database db;
  Date d;
  string command, event, operation;
  try{
  while (getline(cin, command)){
	  stringstream com(command);
	  com >> operation;
	  if (com){
	  if (operation == "Add"){
		  com >> d >> event;
		  db.AddEvent(d, event);
	  } else if(operation == "Del"){
		  com >> d;
		  if (com >> event){
			  if (db.DeleteEvent(d, event)){
				  cout << "Deleted successfully" << endl;
			  } else{
				  cout << "Event not found" << endl;
			  }
		  }else{
			  cout << "Deleted " << db.DeleteDate(d) << " events" << endl;
		  }
	  }	else if(operation == "Find"){
		  com >> d;
		  db.Find(d);
	  } else if(operation == "Print"){
		  db.Print();
	  } else{
		  throw logic_error("Unknown command: " + operation);
	  }
  }
  }}
  	  catch(exception& ex){
  		  cout << ex.what();
  	  }
  return 0;
}

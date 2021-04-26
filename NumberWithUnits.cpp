#include <iostream>
#include"NumberWithUnits.hpp"
#include <map>
#include <fstream>

using namespace std;
const double E = 0.001;

namespace ariel {

    static map<std::string,map<std::string, double> > UnitsMap;//datasructure to store the NumWithunits data 

   

      NumberWithUnits::NumberWithUnits(double num,const std::string unit){
          if(UnitsMap.count(unit)==0){
              throw invalid_argument{"units not in the unitsmap"};
          }
          this->number=num;
          this->unit=unit;
      }


    //read from the file and declare the proportion between the units
    void NumberWithUnits::read_units(ifstream& units_file){
        string unit11, unit22, k;
        double x, y;
        while(units_file >> x >> unit11 >> k >> y >> unit22){//while we have what to read k some string
            UnitsMap[unit11][unit22] = y;
            UnitsMap[unit22][unit11] = 1/y;
         //for Deep converted
           for (auto map: UnitsMap[unit22]){
                double x = UnitsMap[unit11][unit22] * map.second;
                UnitsMap[unit11][map.first] = x;
                UnitsMap[map.first][unit11] = 1/x;
        }
          for (auto map: UnitsMap[unit11]){
                double x = UnitsMap[unit22][unit11] * map.second;
                UnitsMap[unit22][map.first] = x;
                UnitsMap[map.first][unit22] = 1/x;
        }
    }  
    }    
       
    
   
    double Check_Convert_Func(double x, const string &Isrc ,const string &Jdest){
        if(Isrc == Jdest) //if the same units return x and just do some operation
        {return x;}
        try {
            return x * UnitsMap.at(Isrc).at(Jdest);//mult by the proprtion
        }
        catch(const exception& ex) {
            throw invalid_argument{"Units not the same category the converted faild!" };
        }
    }


//in&&out
    ostream& operator<<(ostream& out, const NumberWithUnits& unit){
        out << unit.number << "[" << unit.unit << "]";
        return out;
    }



 std::istream &operator>>(std::istream &in, NumberWithUnits &x) {
        double v=0;
        std::string t;
        char ch=' ';
        in >> v;
        in >> ch ;
        while(ch!=']'){
            if(ch!='['){
                t.insert(t.end(),ch);
            }
            in>>ch;
        }
       if(UnitsMap[t].empty()){throw invalid_argument{"units doesnt exist in unitsmap"};};
        x.number=v;
        x.unit=t;
        return in;
    }
    
   
   //overloading arithmtic operators + ,+=,-=, -
  
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& x) {
        double t = Check_Convert_Func(x.number, x.unit, this->unit);
        return NumberWithUnits(this->number+t, this->unit);
    }
    NumberWithUnits NumberWithUnits::operator+(const double a) {
        return NumberWithUnits(this->number+a, this->unit);
    }
   NumberWithUnits& NumberWithUnits:: operator+=(const NumberWithUnits& x) {
        this->number +=Check_Convert_Func(x.number, x.unit, this->unit);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& x ) {
        double t = Check_Convert_Func(x.number, x.unit, this->unit);
        return NumberWithUnits(this->number-t, this->unit);
    }
    
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& x) {
        double t =Check_Convert_Func(x.number, x.unit, this->unit);
        this->number -=t;
        return *this;
    }

     //overloading comprasion <,>,<=,>=,!=
    bool operator>(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return compare(x,y)>0;
    
    }
    bool operator>=(const NumberWithUnits& x, const NumberWithUnits& y){
      
            return compare(x,y)>=0;
     
    }
    bool operator<(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return x.number < Check_Convert_Func(y.number, y.unit, x.unit);
   
    }
    bool operator<=(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return compare(x,y)<=0;
    
    }
    bool operator==(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return compare(x,y)==0;
        
      
    }
    bool operator!=(const NumberWithUnits& x, const NumberWithUnits& y){
       
            return compare(x,y)!=0;
        }



      //overloading ++,--

    NumberWithUnits& NumberWithUnits::operator++() {  
     (this->number) ++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int) {  
        return NumberWithUnits((this->number)++, this->unit);
    }
    NumberWithUnits& NumberWithUnits::operator--() {  
        --(this->number);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) {  
        return NumberWithUnits((this->number)--, this->unit);
    }

    int compare(const NumberWithUnits& x, const NumberWithUnits& y){
        
        double t = Check_Convert_Func(y.number, y.unit, x.unit);
        int res = 0;
        if(x.number-t > E){ res = 1;}
        else if(t-x.number> E) {res = -1;}
        return res;
    }



       
    
     //overloading multipliction *,*=
     NumberWithUnits operator*(const NumberWithUnits& x, double n) {
        return NumberWithUnits(x.number*n, x.unit);
    }
     NumberWithUnits operator*(double n ,const NumberWithUnits& x) {
        return NumberWithUnits(x.number*n, x.unit);
    }
     NumberWithUnits& NumberWithUnits:: operator*=(double n) {
        this->number *= n;
        return *this;
    }
        
    
}
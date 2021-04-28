#include <iostream>
#include <string>
#include <map>

//using namespace std;

namespace ariel {
    class NumberWithUnits{
        private:
       
        double number;
        std::string unit;//std in H file for the user
        //in&&out
        friend std::ostream& operator<<(std::ostream& OSout, const NumberWithUnits& unit);
        friend std::istream& operator>>(std::istream& OSin, NumberWithUnits& x);


    public:
       
        static void read_units(std::ifstream& file);
        NumberWithUnits(double num, const std::string &unit);
         ~NumberWithUnits(){}//discructor
       //static double Check_Convert_Func(double x, const std::string &Isrc ,const std::string &Jdest);
        //static void DeepConvert(const std::string &unit1,const  std::string &unit2);
         friend int compare(const NumberWithUnits& x, const NumberWithUnits& y);
        
        
        // declare the mult operation
        friend NumberWithUnits operator*(const NumberWithUnits& x, double n);
        friend NumberWithUnits operator*(double n,const NumberWithUnits& x);
        NumberWithUnits& operator*=( double n);
        

        // declare the comparison operators >,<,!=,<=,>=//
        friend bool operator>(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator<(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator>=(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator<=(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator!=(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator==(const NumberWithUnits& x, const NumberWithUnits& y);

        


         // declare the arithmetic operators +,-,+=,-=//
         NumberWithUnits operator+(const NumberWithUnits& x);
         NumberWithUnits operator+( double a);
         NumberWithUnits operator-(){
         return NumberWithUnits(-(this->number),this->unit);

             }
         NumberWithUnits operator+(){
             return NumberWithUnits(+this->number,this->unit);
        }
        NumberWithUnits& operator+=(const NumberWithUnits& x);
        // friend const NumberWithUnits operator-(const NumberWithUnits& x, const NumberWithUnits& y);
        NumberWithUnits operator-(const NumberWithUnits& x);
        NumberWithUnits& operator-=(const NumberWithUnits& x);

         // declare the --,++
        NumberWithUnits& operator++();
        NumberWithUnits& operator--();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);
        

    };
}

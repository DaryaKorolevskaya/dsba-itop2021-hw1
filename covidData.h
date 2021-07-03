#ifndef COVIDDATA_H
#define COVIDDATA_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <set>
#include <iterator>
#include <map>

class covidData{
public:
    int day;
    int month;
    int year;
    int cases;
    int deaths;
    std::string country;
    std::string code;
    int population;
    std::string continent;
    double rate;

    covidData(int day, int month, int year, int cases, int deaths, std::string country, std::string code,
                      int population, std::string continent, double rate);

    static std::vector<std::string> split(const std::string &s, char delimiter);

    static bool comp (covidData a, covidData b);

    static void fillMap(std::vector<covidData>& v, std::set<std::string>& c, std::string filename);

    static std::vector<std::vector<int>> convert_date(std::vector<std::vector<std::string>> date);

    static std::pair<std::map<std::string, int>, std::map<std::string, int>> computing(std::vector<covidData>& data, std::string d_from, std::string d_to,
                   std::string country, bool infected, bool died);

};






class covidInfo
{
public:
    std::vector<covidData> covid;
    std::set<std::string> countries;
    std::string date_from, date_to, selected_country;
    bool infected, died;
    std::pair<std::map<std::string, int>,std::map<std::string, int>> result;


    covidInfo ();


};







#endif // COVIDDATA_H


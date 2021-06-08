#ifndef COVIDDATA_H
#define COVIDDATA_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <set>
#include <iterator>

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
              int population, std::string continent, double rate){
        this->day = day;
        this->month = month;
        this->year = year;
        this->cases = cases;
        this->deaths = deaths;
        this->country = country;
        this->code = code;
        this->population = population;
        this->continent = continent;
        this->rate = rate;

    }

    static std::vector<std::string> split(const std::string &s, char delimiter)
        {
            std::vector<std::string> data;
            std::stringstream ss(s);
            std::string item;
            while (std::getline(ss, item, delimiter)) {
                data.push_back(item);
            }
            return data;
        }


};

bool comp (covidData a, covidData b){
    if (a.year != b.year)
        return a.year > b.year;
    else{
        if (a.month != b.month)
            return a.month > b.month;
    }
    return a.day > b.day;
}
void fillMap(std::vector<covidData>& v, std::set<std::string>& c, std::string filename){
    std::ifstream file;
    file.open(filename);

    std::string line;
    std::string word;
    int max_d, max_c;
    std::stringstream ss;
    std::vector<std::string>data;
    getline(file, line);
    std::vector<int> min_data = {0, 0, 0};
    std::string f;
    while (file.good()){
        getline(file, line);
        data = covidData::split(line, ';');
        c.insert(data[5]);
        covidData c1(stoi(data[0]), stoi(data[1]), stoi(data[2]), stoi(data[3]), stoi(data[4]), data[5],
                data[6], stoi(data[7]), data[8], stod(data[9]));
        v.push_back(c1);
    }
    file.close();
    std::sort(v.rbegin(), v.rend(), comp);
    return;
}

#endif // COVIDDATA_H

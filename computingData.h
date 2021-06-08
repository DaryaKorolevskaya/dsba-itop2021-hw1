#ifndef COMPUTINGDATA_H
#define COMPUTINGDATA_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <set>
#include <iterator>
#include "covidData.h"
#include <map>
#include <string>
#include <sstream>


std::vector<std::vector<int>> convert_date(std::vector<std::vector<std::string>> date)
{
    std::map<std::string, int> months;
    std::vector<std::vector<int>> ndate;
    int m1, m2;
    months = {
        {"янв.", 1}, {"февр.", 2}, {"марта", 3}, {"апр.", 4},
        {"мая", 5}, {"июня", 6}, {"июля", 7}, {"авг.", 8},
        {"сент.", 9}, {"окт.", 10}, {"нояб.", 11}, {"дек.", 12}
    };
    m1 = months[date[0][1]];
    m2 = months[date[1][1]];
    ndate.push_back({stoi(date[0][2]), m1, stoi(date[0][3])});
    ndate.push_back({stoi(date[1][2]), m2, stoi(date[1][3])});
    return ndate;
}

std::pair<std::map<std::string, int>, std::map<std::string, int>> computing(std::vector<covidData>& data, std::string d_from, std::string d_to,
               std::string country, bool infected, bool died){
    std::map<std::string, int> inf;
    std::map<std::string, int> die;
    std::string cur_d;
    std::ostringstream ostr;
    std::vector<std::vector<std::string>> date;
    std::vector<std::vector<int>> normal_date;
    date.push_back(covidData::split(d_from, ' '));
    date.push_back(covidData::split(d_to, ' '));
    normal_date = convert_date(date);

    for (unsigned long i = 0; i < data.size(); ++i){
        if (data[i].country == country){
            ostr.str("");
            if (data[i].day < 10)
                ostr << "0" << data[i].day << ".";
            else  ostr << data[i].day << ".";
            if (data[i].month < 10)
                ostr << "0" << data[i].month;
            else ostr << data[i].month;
            cur_d = ostr.str();
            if (normal_date[0][2] == 2019){
                if (data[i].year == 2019) {
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));
                }
                else if (data[i].month < normal_date[1][1]){
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));
                }
                else if (data[i].month == normal_date[1][1] && data[i].day <= normal_date[1][0]){
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));
                }

            }
            else {
                if (data[i].month > normal_date[0][1] && data[i].month < normal_date[1][1]){
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));
                }

                else if (data[i].month == normal_date[0][1] && data[i].month < normal_date[1][1]
                         && data[i].day >= normal_date[0][0]){
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));

                }
                else if (data[i].month > normal_date[0][1] && data[i].month == normal_date[1][1]
                         && data[i].day <= normal_date[1][0]){
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));
                }
                else if (data[i].month == normal_date[0][1] && data[i].month == normal_date[1][1]
                         && data[i].day >= normal_date[0][0] && data[i].day <= normal_date[1][0]){
                    if (infected)
                        inf.insert(std::pair<std::string, int>
                                        (cur_d, data[i].cases));
                    if (died)
                        die.insert(std::pair<std::string, int>
                                   (cur_d, data[i].deaths));
                }
            }
        }
    }
    for(auto it = inf.begin(); it != inf.end(); ++it)
      {
          std::cout << it->first << " : " << it->second << std::endl;///вывод на экран
      }


    return std::pair<std::map<std::string, int>, std::map<std::string, int>>(inf, die);
}






#endif // COMPUTINGDATA_H

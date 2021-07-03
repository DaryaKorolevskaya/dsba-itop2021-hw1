#include "covidData.h"


covidData::covidData(int day, int month, int year, int cases, int deaths, std::string country, std::string code,
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
covidInfo::covidInfo ()
{

}

std::vector<std::string> covidData::split(const std::string &s, char delimiter)
{
    std::vector<std::string> data;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        data.push_back(item);
    }
    return data;
}

bool covidData::comp (covidData a, covidData b){
    if (a.year != b.year)
        return a.year > b.year;
    else{
        if (a.month != b.month)
            return a.month > b.month;
    }
    return a.day > b.day;
}

void covidData::fillMap(std::vector<covidData>& v, std::set<std::string>& c, std::string filename){
    std::ifstream file;
    file.open(filename);

    std::string line;
    std::string word;
    std::stringstream ss;
    std::vector<std::string>data;
    getline(file, line);
    std::vector<int> min_data = {0, 0, 0};
    std::string f;
    c.insert("");
    while (file.good()){
        getline(file, line);
        data = split(line, ';');
        c.insert(data[5]);
        covidData c1(stoi(data[0]), stoi(data[1]), stoi(data[2]), stoi(data[3]), stoi(data[4]), data[5],
                data[6], stoi(data[7]), data[8], stod(data[9]));
        v.push_back(c1);
    }
    file.close();
    std::sort(v.rbegin(), v.rend(), comp);
}

std::vector<std::vector<int>> covidData::convert_date(std::vector<std::vector<std::string>> date)
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

std::pair<std::map<std::string, int>, std::map<std::string, int>> covidData::computing(std::vector<covidData>& data, std::string d_from, std::string d_to,
               std::string country, bool infected, bool died)
{
    std::map<std::string, int> inf;
    std::map<std::string, int> die;
    std::string cur_d;
    std::ostringstream ostr;
    std::vector<std::vector<std::string>> date;
    std::vector<std::vector<int>> normal_date;
    date.push_back(split(d_from, ' '));
    date.push_back(split(d_to, ' '));
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


    return std::pair<std::map<std::string, int>, std::map<std::string, int>>(inf, die);
}

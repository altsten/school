// Definition of Datastructure class, hw1 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

struct Person
{
    string name;
    int salary;
};

class Datastructure
{
public:
    Datastructure();
    ~Datastructure();

    void add_person(string name, int salary);

    unsigned int size();
    void clear();

    vector<Person*> personnel_alphabetically();
    vector<Person*> personnel_salary_order();

    Person* min_salary();
    Person* max_salary();

    Person* median_salary();
    Person* first_quartile_salary();
    Person* third_quartile_salary();

    //mergesorttia
    vector<Person*> merge_sort_alphabetically(vector<Person*> &personnel);
    vector<Person*> merge_alphabetically(vector<Person*> &left_part, vector<Person*> &right_part);
    vector<Person*> merge_sort_salary_wise(vector<Person*> &personnel);
    vector<Person*> merge_salary_wise(vector<Person*> &left_part, vector<Person*> &right_part);

private:
    vector<Person*> personnel_in_random_order;
    vector<Person*> personnel_in_alpha_order;
    vector<Person*> personnel_in_salary_order;
    bool alpha_order=false;
    bool salary_order=false;
};

#endif // DATASTRUCTURE_HPP

// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

// Helper function to return a random (enough) number in range start-end
// I.e. random_in_range(1,4) produces a random number between 1, 2, 3, or 4.
template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = rand() % range;
    return static_cast<Type>(start+num);
}


Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add_person(std::string name, int salary)
{
    Person *new_person = new Person;
    new_person->name=name;
    new_person->salary=salary;
    //lisätään henkilö peruslistaan
    personnel_in_random_order.push_back(new_person);
    //mikäli henkilöstö on jo aakkostettu tungetaan uusi tyyppi aakkoslistassa oikeaan paikkaan
    if (alpha_order){
        vector<Person*>::iterator alpha_iter = personnel_in_alpha_order.begin();
        bool place_found=false;
        while (!place_found && alpha_iter!=personnel_in_alpha_order.end()){
            if ((*alpha_iter)->name.compare(name)<0){
                alpha_iter++;
            } else {
                place_found=true;
            }
        }
        if (alpha_iter!=personnel_in_alpha_order.end()){
            personnel_in_alpha_order.insert(alpha_iter, new_person);
        } else {
            personnel_in_alpha_order.push_back(new_person);
        }
    }
    //mikäli henkilöstöstä on tehty jo palkkalistaus sijoitetaan uusi tyyppi siinä sopivaan koloon
    if (salary_order){
        vector<Person*>::iterator salary_iter = personnel_in_salary_order.begin();
        bool place_found=false;
        while (!place_found && salary_iter!=personnel_in_salary_order.end()){
            if ((*salary_iter)->salary<salary){
                salary_iter++;
            } else {
                place_found=true;
            }

        }
        if (salary_iter!=personnel_in_salary_order.end()){
            personnel_in_salary_order.insert(salary_iter, new_person);
        } else {
            personnel_in_salary_order.push_back(new_person);
        }
    }
}

unsigned int Datastructure::size()
{
    return(personnel_in_random_order.size());
}

void Datastructure::clear()
{
    //deletoidaan henkilöstön varaama muisti ja merkataan listat tyhjiksi
    while (personnel_in_random_order.size()!=0){
        delete personnel_in_random_order.back();
        personnel_in_random_order.pop_back();
    }
    personnel_in_alpha_order=personnel_in_random_order;
    personnel_in_salary_order=personnel_in_random_order;
    alpha_order=false;
    salary_order=false;
}

vector<Person *> Datastructure::personnel_alphabetically()
{
    //jos ei ole jo aakkosteltu aikaisemmin niin tehdään se mergesortilla
    if (!alpha_order){
        personnel_in_alpha_order=merge_sort_alphabetically(personnel_in_random_order);
        alpha_order=true;
    }
    return personnel_in_alpha_order;
}

vector<Person *> Datastructure::personnel_salary_order()
{
    //jos ei ole jo aikaisemmin laitettu henkilöstöä palkan mukaan järjestykseen niin tehdään se mergesortilla
    if (!salary_order){
        personnel_in_salary_order=merge_sort_salary_wise(personnel_in_random_order);
        salary_order=true;
    }
    return personnel_in_salary_order;
}

Person* Datastructure::min_salary()
{
    //jos ei ole jo aikaisemmin laitettu henkilöstöä palkan mukaan järjestykseen niin tehdään se mergesortilla
    if (!salary_order){
        personnel_in_salary_order=merge_sort_salary_wise(personnel_in_random_order);
        salary_order=true;
    }
    //pienipalkkaisin löytyy vektorin eka sijainnista
    return personnel_in_salary_order[0];

}

Person* Datastructure::max_salary()
{
    //jos ei ole jo aikaisemmin laitettu henkilöstöä palkan mukaan järjestykseen niin tehdään se mergesortilla
    if (!salary_order){
        personnel_in_salary_order=merge_sort_salary_wise(personnel_in_random_order);
        salary_order=true;
    }
    //suuripalkkaisin on vektorin perällä
    return personnel_in_salary_order.back();
}

Person* Datastructure::median_salary()
{
    //jos ei ole jo aikaisemmin laitettu henkilöstöä palkan mukaan järjestykseen niin tehdään se mergesortilla
    if (!salary_order){
        personnel_in_salary_order=merge_sort_salary_wise(personnel_in_random_order);
        salary_order=true;
    }
    return personnel_in_salary_order[personnel_in_salary_order.size()/2];
}

Person* Datastructure::first_quartile_salary()
{
    //jos ei ole jo aikaisemmin laitettu henkilöstöä palkan mukaan järjestykseen niin tehdään se mergesortilla
    if (!salary_order){
        personnel_in_salary_order=merge_sort_salary_wise(personnel_in_random_order);
        salary_order=true;
    }
    return personnel_in_salary_order[personnel_in_salary_order.size()/4];
}

Person* Datastructure::third_quartile_salary()
{
    //jos ei ole jo aikaisemmin laitettu henkilöstöä palkan mukaan järjestykseen niin tehdään se mergesortilla
    if (!salary_order){
        personnel_in_salary_order=merge_sort_salary_wise(personnel_in_random_order);
        salary_order=true;
    }
    return personnel_in_salary_order[personnel_in_salary_order.size()*3/4];
}

vector<Person *> Datastructure::merge_sort_alphabetically(vector<Person *> &personnel)
{
    //mikäli henkilöstöä on vain yksi on hän aakkosjärjestyksessä
    if (personnel.size()<=1){
        return personnel;
    } else {
        vector<Person*>::size_type mid_point = personnel.size()/2;
        vector<Person*> left_part (personnel.begin(), personnel.begin() + mid_point);
        vector<Person*> right_part (personnel.begin() + mid_point, personnel.end());
        //jos vasurista löytyy enemmän kuin yksi tyyppi kutsutaan sille rekursiivisesti mergesorttia
        if (left_part.size()>1){
            left_part = merge_sort_alphabetically(left_part);
        }
        if (right_part.size()>1){
            right_part = merge_sort_alphabetically(right_part);
        }
        //lopuksi yhdistetään järjestetyt jonot
        personnel = merge_alphabetically(left_part,
                             right_part);
        return personnel;
    }
}

vector<Person *> Datastructure::merge_alphabetically(vector<Person *> &left_part, vector<Person *> &right_part)
{

    vector<Person*>::size_type left_size = left_part.size();
    vector<Person*>::size_type right_size = right_part.size();
    vector<Person*> personnel;
    vector<Person*>::iterator left_part_beginning = left_part.begin();
    vector<Person*>::iterator left_part_ending = left_part.end();
    vector<Person*>::iterator right_part_beginning = right_part.begin();
    vector<Person*>::iterator right_part_ending = right_part.end();
    //jos jompikumpi vektori on tyhja palautetaan taysi vektori suoraan
    if (left_size!=0 && right_size!=0){
        //siirretaan personnel vektoriin kunnes oikea tai vasen osa loppuu
        while (left_part_beginning!=left_part_ending &&
                    right_part_beginning!=right_part_ending){
            if ((*left_part_beginning)->name.compare((*right_part_beginning)->name)<0){
                personnel.push_back(*left_part_beginning);
                ++left_part_beginning;
            } else {
                personnel.push_back(*right_part_beginning);
                ++right_part_beginning;
            }
        }
    } else if (left_size!=0){
        return left_part;
    } else{
        return right_part;
    }
    //lisätään vielä loput mille ei ole vertailukumppania toisessa osassa
    while(right_part_beginning!=right_part_ending){
        personnel.push_back(*right_part_beginning);
        ++right_part_beginning;
    }
    while(left_part_beginning!=left_part_ending){
        personnel.push_back(*left_part_beginning);
        ++left_part_beginning;
    }
    return personnel;
}

vector<Person *> Datastructure::merge_sort_salary_wise(vector<Person *> &personnel)
{
    //mikäli henkilöstöä on vain yksi on hän palkkajärjestyksessä
    //tämä salary-wise sorttaus toimii hyvin pitkälti samoin kuin tuo ylempi aakkosellinenkin
    if (personnel.size()<=1){
        return personnel;
    } else {
        vector<Person*>::size_type mid_point = personnel.size()/2;
        vector<Person*> left_part (personnel.begin(), personnel.begin() + mid_point);
        vector<Person*> right_part (personnel.begin() + mid_point, personnel.end());
        if (left_part.size()>1){
            left_part = merge_sort_salary_wise(left_part);
        }
        if (right_part.size()>1){
            right_part = merge_sort_salary_wise(right_part);
        }
        personnel = merge_salary_wise(left_part,
                             right_part);
        return personnel;
    }
}

vector<Person *> Datastructure::merge_salary_wise(vector<Person *> &left_part, vector<Person *> &right_part)
{

    vector<Person*>::size_type left_size = left_part.size();
    vector<Person*>::size_type right_size = right_part.size();
    vector<Person*> personnel;
    vector<Person*>::iterator left_part_beginning = left_part.begin();
    vector<Person*>::iterator left_part_ending = left_part.end();
    vector<Person*>::iterator right_part_beginning = right_part.begin();
    vector<Person*>::iterator right_part_ending = right_part.end();
    //jos jompikumpi vektori on tyhja palautetaan taysi vektori suoraan
    if (left_size!=0 && right_size!=0){
        //siirretaan personnel vektoriin kunnes oikea tai vasen osa loppuu
        while (left_part_beginning!=left_part_ending &&
                    right_part_beginning!=right_part_ending){
            //tässä verrataan palkkoja kun aakkosellisessa vertailtiin kirjaimia
            if ((*left_part_beginning)->salary<((*right_part_beginning)->salary)){
                personnel.push_back(*left_part_beginning);
                ++left_part_beginning;
            } else {
                personnel.push_back(*right_part_beginning);
                ++right_part_beginning;
            }
        }
    } else if (left_size!=0){
        return left_part;
    } else{
        return right_part;
    }
    //lisätään vielä loput mille ei ole vertailukumppania toisessa osassa
    while(right_part_beginning!=right_part_ending){
        personnel.push_back(*right_part_beginning);
        ++right_part_beginning;
    }
    while(left_part_beginning!=left_part_ending){
        personnel.push_back(*left_part_beginning);
        ++left_part_beginning;
    }
    return personnel;
}

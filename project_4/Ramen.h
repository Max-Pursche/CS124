//
// Created by mrgat on 9/12/2021.
//

#ifndef CS124_C___RAMEN_H
#define CS124_C___RAMEN_H
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using std::right;
using std::setw;
using std::string;
using std::vector;

class Ramen {
private:
    //fields
    std::string brand, variety, style, country;
    int number;
    float rating;

public:
    //constructors
    Ramen(){
        number = 0;
        rating = 1.0;
        brand = ' ';
        variety = ' ';
        style = ' ';
        country = ' ';
    }

    Ramen(int number, float rating, string brand, string variety, string style, string country) {
        this->number = number;
        this->rating = rating;
        this->brand = brand;
        this->variety = variety;
        this->style = style;
        this->country = country;
    }

    //getters
    int getNumber() const{
        return number;
    }

    float getRating() const{
        return rating;
    }


    string getBrand(){
        return brand;
    }

    string getVariety(){
        return variety;
    }

    string getStyle(){
        return style;
    }

    string getCountry(){
        return country;
    }

    //setters
    void setNumber(int number){
        this->number = number;
    }

    void setRating(float rating){
        this->rating = rating;
    }

    void setBrand(string brand){
        this->brand = brand;
    }

    void setVariety(string variety){
        this->variety = variety;
    }

    void setStyle(string style){
        this->style = style;
    }

    void setCountry(string country){
        this->country = country;
    }

    //overloaded operators
    friend std::ostream& operator << (std::ostream& outs, const Ramen &ram) {
        outs << std::left << setw(10) << ram.number;
        outs << std::left << setw(20) << ram.country;
        outs << std::left << setw(30) << ram.brand;
        outs << std::left << setw(10) << ram.style;
        outs << std::left << setw(40) << ram.variety;
        outs << "    "<< std::left << setw(500) << ram.rating;
        return outs;
    }

    /**
     * Overload < operator for object comparison
     */
    friend bool operator < (const Ramen& lhs, const Ramen& rhs) {
        return lhs.getRating() < rhs.getRating();
    }

    /**
     * Overload > operator for object comparison
     */
    friend bool operator > (const Ramen& lhs, const Ramen& rhs) {
        return lhs.getRating() > rhs.getRating();
    }

    /**
     * Overload <= operator for object comparison
     */
    friend bool operator <= (const Ramen& lhs, const Ramen& rhs) {
        return lhs.getRating() <= rhs.getRating();
    }

    /**
     * Overload >= operator for object comparison
     */
    friend bool operator >= (const Ramen& lhs, const Ramen& rhs) {
        return lhs.getRating() >= rhs.getRating();
    }

    /**
     * Overload == operator for object comparison
     */
    friend bool operator == (const Ramen& lhs, const Ramen& rhs) {
        return lhs.getRating() == rhs.getRating();
    }

    /**
     * Overload != operator for object comparison
     */
    friend bool operator != (const Ramen& lhs, const Ramen& rhs) {
        return lhs.getRating() != rhs.getRating();
    }


};

void getRamenStats(vector<Ramen> &ramenlist){
    int zero, one, two, three, four, five;
    float compare;
    int final_1, final_2, final_3, final_4, final_5, final_0;
    zero=0;
    one=0;
    two=0;
    three = 0;
    five = 0;
    four =0;
    // loop thru the file and specifically look for the star rating. depending on what integer number the star is
    // it will tick the respective variable
    for(int i=0; i< ramenlist.size(); ++i) {
        compare = ramenlist[i].getRating();
        if (compare == 5.0) {
            ++five;
        }
        if (compare >= 4.0 && compare < 5.0) {
            ++four;
        }
        if (compare >= 3.0 && compare < 4.0) {
            ++three;
        }
        if (compare >= 2.0 && compare < 3.0) {
            ++two;
        }
        if (compare >= 1.0 && compare < 2.0) {
            ++one;
        }
        if (0.0 == compare && compare < 1.0) {
            ++zero;
        }

    }
    //The variables will then be averaged out into percentages and then printed. It all has to be cast as a double in order to prevent integer division
    std::cout <<"%"<< ((double) five/2580)*100 << setw(10) <<"%of 5*"<< std::endl;
    std::cout <<"%"<< ((double) four/2580)*100 << setw(10) << "% of 4*"<< std::endl;
    std::cout <<"%"<< ((double) three/2580)*100 << setw(10) <<"% of 3*"<< std::endl;
    std::cout <<"%"<< ((double) two/2580)*100 << setw(10) <<"% of 2*"<< std::endl;
    std::cout <<"%"<< ((double) one/2580)*100 << setw(10) <<"% of 1*"<< std::endl;
    std::cout <<"%"<< ((double) zero/2580)*100 << setw(10) <<"% of 0*/unrated"<< std::endl;

}

vector<Ramen> ramenShuffle(vector<Ramen> &ramenlist){

}

// Use an ampersand (&) to pass the vector by reference. Instead of making a copy of the vector,
// it will pass the memory address of where the vector is located.
bool inline getRamenData(string filename, vector<Ramen> &ramenlist) {

    std::ifstream fIn;
    fIn.open(filename);

    if(!fIn) {
        return false;
    }

    string headers;
    if (fIn){
        getline(fIn, headers);
    }

    //declaring variables I want to read
    int number;
    float rating;
    string brand, variety, style, country, newLine, junk;
    char comma, quote;
    newLine = "";

    while (fIn && fIn.peek() != EOF) {

        // Read in number
        fIn >> number;
        fIn >> comma;

        // Read in brand
        getline(fIn, brand, ',');

        // Read in variety
        getline(fIn, variety, ',');

        // Read in style
        getline(fIn, style, ',');

        // Read in country
        getline(fIn, country, ',');

        // Read in rating
        fIn >> rating;
        if (!fIn) {
            // There was no rating for the ramen
            // Set a default value for rating
            getline(fIn, junk, ',');
            rating = 0;
            // Clear the stream so we can continue reading from the file
            fIn.clear();
        }
        else fIn >> comma;

        getline(fIn, newLine);
        // Create a ramen object and add it to the vector
        //Ramen(number , rating, topTenYr, brand, variety, style, country)
        ramenlist.push_back(Ramen(number, rating, brand, variety, style, country));
    }

    fIn.close();
    return true;
}

#endif //CS124_C___RAMEN_H

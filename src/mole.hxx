#pragma once

#include "ge211.hxx"
#include <iostream>

class Mole {
public:

    // the constructor used to create the mole character
    Mole(const std::string);

    // obtains an updated object in the next instance the on_frame function
    // is called -> used in test cases
    Mole next(double dt);

    // returns the state of the mole: whether it appears or disappears
    bool mole_status() {
        return appear_;
    }

    // returns the interval of time before the mole appears
    int pop_time_status() {
        return pop_time_;
    }

    // updates the pop_time field using the value that it passes
    void set_pop_time(double dt);

    // updates the status of the mole using the value that it passes: whether it
    // appears or disappears
    void set_status(bool boolean);

    // changes the pop time to the value that this function passes
    void change_pop(double dt);

    // checks whether two moles are the same by making sure they have the
    // same values in all their fields
    bool compare_moles(Mole const& a, Mole const& b);

private:

    // takes in a file that contains the animated mole character
    ge211::Image_sprite mole_;
    // Whether the mole is under the hole or popped out of the hole
    bool appear_;
    // Amount of time the mole stays hidden in the hole
    double pop_time_;
};
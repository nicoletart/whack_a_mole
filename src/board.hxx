#pragma once

#include <ge211.hxx>
#include <iostream>
#include "settings.hxx"
//#include <unordered_map>
//#include <unordered_set>
//#include <vector>

//Defining type aliases

// Dimensions will use `int` coordinates.
using Dimensions = ge211::Dims<int>;

// Positions will use `int` coordinates.
using Position = ge211::Posn<int>;

// Board rectangles will use `int` coordinates.
using Rectangle = ge211::Rect<int>;

//Hammer

struct Hammer {
    // Constructor
    Hammer(Settings const& pref = Settings());

    // location of the hammer
    Position location;

    //whether the hammer can hit the moles
    bool active;

    // whether the hammer is inside or outside the hole
    bool outside_of_hole;
};


// Board

class Board
{
public:

    // Defined and documented below.
    class reference;
    //
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    //
    // Constructs a board with the given dimensions.
    //
    explicit Board(Settings const& prefs = Settings());

    // Obtains the dimensions of the board with reference to the screen
    Dimensions board_dims() const;

    // Stores the holes in form of their bounding boxes in the board
    std::vector<Rectangle> hole_boxes;


private:
    //
    // PRIVATE DATA MEMBERS
    //

    //the settings to be used in the game
    Settings const prefs;

    //  the dimensions of the board
    Dimensions dims_;

    // the dimensions of the bounding box
    Dimensions box_dims;
};


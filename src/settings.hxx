#pragma once

#include <ge211.hxx>
struct Settings
{
    // Constructs an instance with the default parameters.
    Settings();

    // The dimensions of the whole window:
    ge211::Dims<int> screen;

    // The number of holes along the width and height of the board
    ge211::Dims<int> num_holes;

    // The number of pixels of space between each hole in the board:
    ge211::Dims<int> spacing;

    // Number of pixels from top and bottom of screen to top and bottom of
    // the board
    ge211::Dims<int> margin;

    // The dimensions of the board on the screen
    ge211::Dims<int> board_dims;

    // The dimensions of the bounding box of the hole
    ge211::Dims<int> box_dims;

    //The radius of the holes
    int radius;

    //gives the initial position of the hammer
    ge211::Posn<int> hammer_position;

    //gives the position of the start button on the screen
    ge211::Posn<int> button_position;

    //gives the position of the timer on the screen
    ge211::Posn<int> timer_position;

    //gives the position of the scores on the screen
    ge211::Posn<int> score_position;

};
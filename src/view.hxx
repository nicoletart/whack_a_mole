#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set, Position pos);

    //Returns the size of the window as given by `settings.screen`.
    ge211::Dims<int> initial_window_dimensions() const;

    // Returns the title of the game
    std::string initial_window_title() const;

private:
    Model const& model_;

    // Image of our mole
    ge211::Image_sprite mole;

    // Circle representing our hole
    ge211::Circle_sprite hole;

    // Image of the hammer
    ge211::Image_sprite hammer;

    // Start button
    ge211::Rectangle_sprite start;

    // "Start" text in start button
    ge211::Text_sprite start_text;

    // Scoreboard that displays the player's current score
    ge211::Rectangle_sprite scoreboard;

    // Text of the score in scoreboard
    ge211::Text_sprite scoreboard_text;

    // Timer that displays the amount of time the player has left in the game
    ge211::Rectangle_sprite timer;

    // Text that displays the current time in timer
    ge211::Text_sprite timer_text;

    // Background of our game
    ge211::Image_sprite grass;
};

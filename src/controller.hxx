#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    // The constructor for controller
    explicit Controller(const std::string);

protected:

    // implements the draw function in view
    void draw(ge211::Sprite_set& set) override;

    // moves the hammer on the screen hence updating its position
    void on_mouse_move(ge211::Posn<int>) override;

    // plays a move by implementing the hit function in model
    // also starts the game when the proper conditions are met
    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;

    // calls the on_frame function in model and implements it onto the screen
    void on_frame(double dt) override;

    // checks if the position of the mouse pos (really the hammer object) is
    // within the correct bounds to start the game
    bool in_bounds(Position pos);

    // implements the preferred title onto the window as defined in view
    std::string initial_window_title() const override;

    // implements the preferred window dimensions defined in settings
    Dimensions initial_window_dimensions() const override;



private:

    // the model to be used in controller
    Model model_;

    // the view to be used in controller
    View view_;

    // keeps track of the position of the pointer on the screen an uses it to
    // update the position of the hammer
    Position mouse_pos;
};

#pragma once

#include <ge211.hxx>

#include "mole.hxx"
#include "board.hxx"


class Model
{
public:

    // constructs a model using a given file name and default settings
    Model(const std::string, Settings const& prefs = Settings());

    // returns the board to be used
    Board board() const{
        return board_;
    }

    // returns the mole character used in model
    Mole mole() const{
        return mole_;
    }

    //returns the hammer object used in the game
    Hammer hammer() const{
        return hammer_;
    }

    //returns the hammer object used in the game -> to be used in test cases
    Hammer& hammer_ref(){
        return hammer_;
    }

    // returns the settings used in model
    Settings prefer() const {
        return prefs;
    }

    // Updates the state of the game for one frame
    void on_frame(double dt);

    // Check first that the position of the hammer is within the board
    // If so iterate through every position in the board and check whether it
    // is within either one of the bounding boxes
    bool check_bounds();

    // Launches the game by starting the timer
    void start();

    // update the score of the player in accordance to how they have played
    // to hit a mole earns the player one point
    void increase_score();

    // to hit an empty hole costs the player half a point
    void decrease_score();

    // checks that the hammer is within the bounds of the hole and a mole is
    // present and returns true if both conditions are true
    bool check_hit(int i);

    // plays an actual move by having a mole disappear once a player clicks
    // on it
    void hit(int i);

    // changes the rate at which the moles disappear to increase the
    // difficulty of the game
    void change_level();

    // ends the game if the game timer reaches 0
    void game_over();

    // returns a rectangle that contains the start button
    Rectangle button() const {
        return start_button;
    }

    // checks whether the game is over
    bool is_game_over() const
    {
        return (!hammer_.active && game_timer <= 0);
    }

    // stores the holes on the board in form of their bounding boxes
    std::vector <Rectangle> holes() const {
        return board_.hole_boxes;
    }

    // returns the current score
    double get_score() const {
        return points;
    }

    // returns the current time
    double get_time() const {
        return game_timer;
    }

    // returns a vector of moles for each hole on the board
    std::vector<Mole> moles() const{
        return moles_;
    }

    // returns a vector of moles for each hole on the board -> to be used in
    // test cases
    std::vector<Mole>& mole_ref() {
        return moles_;
    }

    //updates the time interval it takes before a mole appears and sets the
    //boolean variable appear to true once the time hits 0
    //Takes in the index of the mole within the mole vector and a double
    // which is used to update the time
    void change_pop_times(int i, double);

    //updates the time interval it takes before a mole disappears and sets the
    // boolean variable appear to false once the time hits 0
    //Takes in the index of the mole within the mole vector
    void mole_disappear(int i);

    //returns the number of times the player scores consequently
    int get_score_in_a_row(){
        return score_in_a_row;
    }

    // updates the location of the hammer on the screen
    void update_hammer(Position pos) {
        hammer_.location = pos;
    }

    // returns the index of whichever hole the hammer is in by checking
    // whether the hammer position is within bounds
    int retrieve_index();

    // returns a vector of the timers that determine how long it takes before
    // each mole appears -> to be used in test cases
    std::vector<double>& get_mole_timers(){
        return mole_timers;
    }

    // returns the constant time which is used to update the timers for each
    // mole
    double mole_time() {
        return mole_timer;
    }

private:

    // the settings of the game
    Settings prefs;

    // the game character - mole
    Mole mole_;

    // the game board containing the holes through which the moles appear and
    // disappear
    Board board_;

    // the hammer object used to hit the moles
    Hammer hammer_;

    // the constant interval of time a mole appears for each mole
    double mole_timer;

    // assigns the amount of time allowed for the whole game
    double game_timer;

    // keeps track of the time it takes before the level of difficulty
    // progresses
    double level_timer;

    // keeps track of the player's score
    double points;

    // keeps track of how many times a player hits moles in a row
    int score_in_a_row;

    //stores the moles that will appear on the board
    std::vector<Mole> moles_;

    // stores the interval of time a mole appears for each mole
    std::vector<double> mole_timers;

    // constructs a rectangle that contains the start button
    Rectangle start_button;
};



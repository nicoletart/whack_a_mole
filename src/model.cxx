#include "model.hxx"
#include <iostream>

Model::Model(const std::string file, Settings const& prefs)
        :   prefs(prefs),
            mole_(file),
            board_(prefs),
            hammer_(prefs),
            mole_timer(5),
            game_timer(120),
            level_timer(0),
            points(0),
            score_in_a_row(0),
            start_button(Rectangle ::from_top_left(prefs.button_position,
                                                         {100,
                                                          50}))
{
    for (int i = 0; i < 16; i++) {
        moles_.push_back(mole_);
        moles_.at(i).change_pop(rand()%10 +3);
        mole_timers.push_back(5);
    }
}
bool
Model::check_bounds()
{
    if (prefs.margin.width <= hammer_.location.x &&
        hammer_.location.x < board_.board_dims().width + prefs.margin.width &&
        prefs.margin.height <= hammer_.location.y &&
        hammer_.location.y < board_.board_dims().height + prefs.margin.height) {

        int i = 0;

        for (auto box: board_.hole_boxes) {

            if ((box.top_left().x <= hammer_.location.x &&
                hammer_.location.x <= box.width + box.top_left().x) &&
                (box.top_left().y <= hammer_.location.y &&
                hammer_.location.y <= box.height + box.top_left().y)) {


                int dx = hammer_.location.x - box.center().x;
                int dy = hammer_.location.y - box.center().y;
                double dist = dx * dx + dy * dy;

                return dist <= (prefs.radius * prefs.radius);
            }

            i++;
        }
    }

    return false;

}

int Model::retrieve_index()
{
    int i = 0;

    for (auto box: board_.hole_boxes) {

        if ((box.top_left().x <= hammer_.location.x &&
             hammer_.location.x <= box.width + box.top_left().x) &&
            (box.top_left().y <= hammer_.location.y &&
             hammer_.location.y <= box.height + box.top_left().y)) {

                return i;
        }

        i++;
    }
    return i;
}

void
Model::start() {
    hammer_.active = true;
}

bool
Model::check_hit(int i) {

    // check if the pointer is within the hole and the mole appears
    if (check_bounds() && moles_.at(i).mole_status()) {
        hammer_.outside_of_hole = false;
        return true;
    } else if (!check_bounds()){
        hammer_.outside_of_hole = true;
    }
    return false;
}

void Model::increase_score(){
    if (!hammer_.outside_of_hole){
        points+=1;
        score_in_a_row+= 1;
        if (score_in_a_row == 10){
            points +=5;
            score_in_a_row = 0;
        }
    }
}

void Model::decrease_score(){
    if(!hammer_.outside_of_hole){
        points -=0.5;
        score_in_a_row = 0;
    }
}


void
Model::hit(int i) {
    if (!is_game_over()) {
        if (check_hit(i)) {
            mole_disappear(i);
            increase_score();
        } else {
            decrease_score();
        }
        if (points < 0) {
            points = 0;
        }
        hammer_.outside_of_hole = false;
    }
}

void Model::change_level(){

    if (level_timer > 24) {
        --mole_timer;
        level_timer = 0;
    }
}

void
Model::game_over() {
    if (game_timer < 0) {
        hammer_.active = false;
        game_timer = 0;
    }
}

void
Model::change_pop_times(int i, double dt)
{
    if (moles_.at(i).pop_time_status() > 0){
        (moles_.at(i).set_pop_time(dt));
    }
    else{
        moles_.at(i).set_status(true);
        moles_.at(i).change_pop(0);
    }

    if (moles_.at(i).pop_time_status() <= 0){
        moles_.at(i).set_status(true);
        moles_.at(i).change_pop(0);
    }
}

void
Model::mole_disappear(int i){
    moles_.at(i).set_status(false);
    mole_timers.at(i) = mole_timer;
    moles_.at(i).change_pop(rand()%10 +3) ;
}

void Model::on_frame(double dt)
{
        game_timer -= dt;
        game_over();
        level_timer += dt;
        change_level();

        for (int i = 0; i < 16; i++) {
            change_pop_times(i, dt);

            if (moles_.at(i).mole_status()) {
                if (mole_timers.at(i) > 0) {
                    mole_timers.at(i) -= dt;
                } else {
                    mole_disappear(i);
                }
                if (mole_timers.at(i) <= 0){
                    mole_disappear(i);
                }
            }

        }

}
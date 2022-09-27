#include "view.hxx"


using Color = ge211::Color;
static Color const hole_color {139,69,19};
static Color const start_color {0,100,0};
static Color const scoreboard_color {0,0,0};
static Color const timer_color {0,0,0};
View::View(Model const& model)
        :   model_(model),
            mole("mole_image.png"),
            hole(model.prefer().radius,hole_color),
            hammer("hammer.png"),
            start(model.button().dimensions(), start_color),
            start_text(std::string("START"), {"sans.ttf", 30}),
            scoreboard({150, 60}, scoreboard_color),
            timer({170, 45}, timer_color),
            grass("grass.png")
{ }

void
View::draw(ge211::Sprite_set& set, Position pos)
{
    set.add_sprite(grass, {0, 0}, 0,
                   ge211::Transform {}.scale(2.0));
    set.add_sprite(hammer, pos, 4,
                   ge211::Transform {}.scale(0.2));
    set.add_sprite(scoreboard, model_.prefer().score_position, 1);
    set.add_sprite(timer, model_.prefer().timer_position, 1);

    scoreboard_text = ge211::Text_sprite(std::to_string(model_.get_score()),
                    {"sans.ttf", 50}),
    set.add_sprite(scoreboard_text, {875, 35}, 2);

    timer_text = ge211::Text_sprite(std::to_string(model_.get_time()),
               {"sans.ttf", 30}),
    set.add_sprite(timer_text, {40, 50}, 2);

    if (!model_.hammer().active && model_.get_time() == 120) {
        set.add_sprite(start, model_.button().top_left(), 1);
        set.add_sprite(start_text, model_.button().top_left(), 2);
    }

    for (int i = 0; i< 16; i++) {
        set.add_sprite(hole, model_.holes().at(i).top_left(), 2);
        if (model_.moles().at(i).mole_status()) {
                set.add_sprite(mole, model_.holes().at(i).top_left(),
                               3, ge211::Transform {}.scale(0.35));
        } else {
            set.add_sprite(mole, model_.holes().at(i).top_left(),
                           0, ge211::Transform {}.scale(0.35));
        }
    }

}


ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model_.prefer().screen;

}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Whack-a-mole Rewritten";
}
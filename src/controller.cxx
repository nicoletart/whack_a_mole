#include "controller.hxx"

Controller::Controller(const std::string file)
        :   model_(file),
            view_(model_),
            mouse_pos(model_.prefer().hammer_position)
{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse_pos);
}

void
Controller::on_mouse_move(ge211::Posn<int> pos)
{

    model_.update_hammer(pos);
    mouse_pos = pos;

}
bool
Controller::in_bounds(Position pos){
    return (((model_.button().top_left().x <= pos.x) && (pos.x < model_.button()
    .width + model_.button().top_left().x)) &&
        ((model_.prefer().screen.height - model_.button().height <= pos.y) &&
                (pos.y <= model_.prefer().screen.height)));
}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{
    // check position of the mouse is within the vicinity of the rectangle
    // that hold the start button
    if (!model_.is_game_over()) {

        if (!model_.hammer().active && in_bounds(pos)) {
            model_.start();
        }
        model_.hit(model_.retrieve_index());
    }
}

void
Controller::on_frame(double dt)
{
    if (model_.hammer().active) {
        model_.on_frame(dt);
    }
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}


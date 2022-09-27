#include "board.hxx"

Hammer::Hammer(Settings const& prefs)
        :   location(prefs.hammer_position),
            active(false),
            outside_of_hole(false)
{}

Board::Board(Settings const& prefs)
        :   prefs(prefs),
            dims_{prefs.board_dims},
            box_dims{prefs.box_dims}

{
    for (int i = 0; i < prefs.num_holes.width; i++) {
        for (int j = 0; j < prefs.num_holes.height; j++) {
            int dist_x = i * (box_dims.width +
                              prefs.spacing.width);
            int dist_y = j * (box_dims.height +
                              prefs.spacing.height);
            ge211::Posn<int> pos = {prefs.margin.width + dist_x,
                                    prefs.margin.height + dist_y};
            Rectangle hole_box = Rectangle::from_top_left(pos,
                                                          box_dims);
            hole_boxes.push_back(hole_box);

        }
    }

}

Dimensions
Board::board_dims() const
{
    return dims_;
}

#include "settings.hxx"

Settings::Settings()
        :   screen {1000, 800},
            num_holes {4,4},
            spacing {50, 50},
            margin {200, 100},
            board_dims {screen.width - (2 * margin.width),
                        screen.height - (2 * margin.height)},
            box_dims {(board_dims.width - (num_holes.width - 1) *
                        spacing.width) / num_holes.width,
                      (board_dims.height - (num_holes.height - 1) *
                      spacing.height) / num_holes.height},
            radius(box_dims.width/2),
            hammer_position {screen.width/2, screen.height/2},
            button_position {50 , screen.height - 50},
            timer_position{35, 50},
            score_position{screen.width - 150, 50}

{
}
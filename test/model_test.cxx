#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}


//
// These tests should demonstrate your functional requirements.
//

// Check for basic functionality of the game
TEST_CASE("Model Test 0")
{
    Model model("mole_image.png");

    CHECK(model.board().board_dims().width == 600);
    CHECK(model.board().board_dims().height == model.board().board_dims()
                                                    .width);

    CHECK_FALSE(model.hammer().active);

    model.start();

    CHECK(model.hammer().active);

    model.on_frame(10);

    CHECK_FALSE(model.is_game_over());
}


// Check if the hammer hits a hole with a mole, it disappears and score
// increases
TEST_CASE("Model Test 1")
{

    Model model("mole_image.png");

    CHECK(model.board().board_dims().width == 600);
    CHECK(model.board().board_dims().height == model.board().board_dims()
                                                    .width);

    CHECK_FALSE(model.hammer().active);

    model.start();
    CHECK(model.hammer().active);

    model.mole_ref()[5].change_pop(8);
    model.on_frame(7);
    CHECK(model.get_time() == 113);
    CHECK(model.mole_ref()[5].pop_time_status() == 1);
    model.on_frame(2);
    CHECK(model.mole_ref()[5].mole_status());
    CHECK(model.get_mole_timers()[5] == 3);

    model.update_hammer({412, 312});
    model.hit(5);

    CHECK_FALSE(model.mole_ref().at(5).mole_status());
    CHECK(model.get_mole_timers().at(5) == 5);
    CHECK(model.get_score() == 1);
}

// Check if hammer hits a hole without a mole, the score decreases by 0.5
TEST_CASE("Model Test 2")
{

    Model model("mole_image.png");

    CHECK(model.board().board_dims().width == 600);
    CHECK(model.board().board_dims().height == model.board().board_dims()
                                                    .width);

    CHECK_FALSE(model.hammer().active);

    model.start();
    CHECK(model.hammer().active);

    model.mole_ref()[5].change_pop(8);
    model.on_frame(7);
    CHECK(model.get_time() == 113);
    CHECK(model.mole_ref()[5].pop_time_status() == 1);
    model.on_frame(2);
    CHECK(model.mole_ref()[5].mole_status());
    CHECK(model.get_mole_timers()[5] == 3);

    model.update_hammer({412, 312});
    model.hit(5);

    CHECK_FALSE(model.mole_ref()[5].mole_status());
    CHECK(model.get_mole_timers().at(5) == 5);
    CHECK(model.get_score() == 1);

    model.hit(5);

    CHECK_FALSE(model.mole_ref()[5].mole_status());
    CHECK(model.get_mole_timers().at(5) == 5);
    CHECK(model.get_score() == 0.5);

    model.hit(5);

    CHECK(model.get_score() == 0);


    // Checks that the score won't go below 0 if it is already at 0
    model.hit(5);
    CHECK(model.get_score() == 0);

}

// Check if score increase by 5 points if player hits 10 moles in a row
TEST_CASE("Model Test 3")
{

    Model model("mole_image.png");

    CHECK(model.board().board_dims().width == 600);
    CHECK(model.board().board_dims().height == model.board().board_dims()
                                                    .width);

    CHECK_FALSE(model.hammer().active);

    model.start();
    CHECK(model.hammer().active);

    model.mole_ref()[5].change_pop(8);
    model.on_frame(7);
    CHECK(model.get_time() == 113);
    CHECK(model.mole_ref()[5].pop_time_status() == 1);
    model.on_frame(2);
    CHECK(model.mole_ref()[5].mole_status());
    CHECK(model.get_mole_timers()[5] == 3);

    model.update_hammer({412, 312});
    model.hit(5);

    CHECK_FALSE(model.mole_ref().at(5).mole_status());
    CHECK(model.get_mole_timers().at(5) == 5);
    CHECK(model.get_score() == 1);

    for (int i = 0; i < 8; i++){
        model.mole_ref()[5].change_pop(8);
        model.on_frame(1);
        CHECK(model.mole_ref().at(5).pop_time_status() == 7);
        model.on_frame(6);
        CHECK(model.mole_ref().at(5).pop_time_status() == 1);
        model.on_frame(1);
        CHECK(model.mole_ref()[5].mole_status());
        model.hit(5);
    }
    CHECK(model.get_score() == 9);

    model.mole_ref()[5].change_pop(8);
    model.on_frame(7);
    CHECK_FALSE(model.mole_ref()[5].mole_status());
    model.on_frame(1);
    CHECK(model.mole_ref()[5].mole_status());
    model.hit(5);

    //Checking here that the points increased by 5
    CHECK(model.get_score() == 15);
    CHECK(model.get_score_in_a_row() == 0);
}


// Player can't hit any more moles once game is over

TEST_CASE("Model Test 4")
{
    Model model("mole_image.png");

    CHECK(model.board().board_dims().width == 600);
    CHECK(model.board().board_dims().height == model.board().board_dims()
                                                    .width);

    CHECK_FALSE(model.hammer().active);

    model.start();
    CHECK(model.hammer().active);

    model.mole_ref()[1].change_pop(4);
    model.on_frame(1);
    CHECK(model.get_time() == 119);
    CHECK(model.mole_ref()[1].pop_time_status() == 3);
    model.on_frame(3);
    CHECK(model.mole_ref()[1].mole_status());
    CHECK(model.get_mole_timers()[5] == 5);

    model.update_hammer({250, 312});
    model.hit(1);

    CHECK_FALSE(model.mole_ref().at(1).mole_status());
    CHECK(model.get_mole_timers().at(1) == 5);
    CHECK(model.get_score() == 1);

    CHECK(model.get_time() == 116);

    model.on_frame(118);
    CHECK(model.get_time() == 0);

    model.mole_ref()[1].set_status(true);
    CHECK(model.mole_ref().at(1).mole_status());
    model.hit(1);
    CHECK_FALSE(model.hammer_ref().active);
    CHECK(model.mole_ref().at(1).mole_status());

}

// The level of difficulty increases as the game progresses by reducing the
// interval on which the mole appears
TEST_CASE("Model Test 5") {
    Model m("mole_image.png");

    m.start();

    double time_check = m.mole_time();

    m.on_frame(10);
    CHECK(m.get_time() == 110);
    CHECK(m.mole_time() == time_check);
    m.moles()[5].change_pop(0);
    m.moles()[5].set_status(true);
    m.on_frame(m.mole_time());
    CHECK_FALSE(m.moles()[5].mole_status());


    m.on_frame(21);
    CHECK(m.get_time() == 84);
    CHECK(m.mole_time() == (time_check - 1));
    m.moles()[10].change_pop(0);
    m.moles()[10].set_status(true);
    m.on_frame(m.mole_time());
    CHECK_FALSE(m.moles()[10].mole_status());


    m.on_frame(25);
    CHECK(m.get_time() == 55);
    CHECK(m.mole_time() == (time_check - 2));
    m.moles()[8].change_pop(0);
    m.moles()[8].set_status(true);
    m.on_frame(m.mole_time());
    CHECK_FALSE(m.moles()[8].mole_status());


    m.on_frame(17);
    CHECK(m.get_time() == 35);
    CHECK(m.mole_time() == (time_check - 2));
    m.moles()[2].change_pop(0);
    m.moles()[2].set_status(true);
    m.on_frame(m.mole_time());
    CHECK_FALSE(m.moles()[2].mole_status());

    m.on_frame(10);
    CHECK(m.get_time() == 22);
    CHECK(m.mole_time() == (time_check - 3));
    m.moles()[0].change_pop(0);
    m.moles()[0].set_status(true);
    m.on_frame(m.mole_time());
    CHECK_FALSE(m.moles()[0].mole_status());

    m.on_frame(9);
    CHECK(m.get_time() == 11);
    CHECK(m.mole_time() == (time_check - 3));
    m.moles()[7].change_pop(0);
    m.moles()[7].set_status(true);
    m.on_frame(m.mole_time());
    CHECK_FALSE(m.moles()[7].mole_status());

}

//Walk through on_frame and check that the moles appear randomly as
// predicted using the .next() function

TEST_CASE("Model Test 6") {

    Model model("mole_image.png");

    // start the game
    model.start();

    model.on_frame(10);

    CHECK_FALSE(model.is_game_over());

    // Checks that moles appear at random times

    for (int i = 0 ; i < 16; i++) {
        Mole expected_mole = model.mole_ref()[i].next(10);

        CHECK(model.mole_ref()[i].compare_moles(model.mole_ref()[i],
                                                expected_mole));

        if (!model.mole_ref()[i].mole_status()) {

            double dt1 = model.mole_ref()[i].pop_time_status();

            model.on_frame(dt1);

            Mole next1 = model.mole_ref()[i].next(dt1);

            CHECK(model.mole().compare_moles(model.mole_ref()[i],
                                             next1));
        } else {

            model.on_frame(model.get_mole_timers()[i]);

            Mole next2 = model.mole_ref()[i].next(model.get_mole_timers()[6]);

            CHECK(model.mole().compare_moles(model.mole_ref()[i],
                                             next2));
        }
    }

}




#include "mole.hxx"

Mole::Mole(const std::string file)
        :   mole_(file),
            appear_(false),
            pop_time_(0)
{}


Mole
Mole::next(double dt)
{
    Mole result(*this);
    return result;
}

void
Mole::set_pop_time(double dt){
     pop_time_-= dt;
}

void
Mole::change_pop(double dt){
    pop_time_= dt;
}

void
Mole::set_status(bool boolean){
    appear_ = boolean;
}

bool
Mole::compare_moles(Mole const& a, Mole const& b)
{
    if(a.appear_ == b.appear_ && a.pop_time_ == b.pop_time_){
        return true;
    }
    return false;
}
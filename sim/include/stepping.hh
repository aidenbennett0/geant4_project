#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "construction.hh"
#include "event.hh"

class MySteppingAction : public G4UserSteppingAction
{
 public:
    MySteppingAction(MyEventAction* event);
    ~MySteppingAction();

     void UserSteppingAction(const G4Step*) override;

 public:
    MyEventAction* fEventAction = nullptr;
};

#endif
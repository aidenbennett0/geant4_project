#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

#include "run.hh"

class MyEventAction : public G4UserEventAction
{
 public:
    MyEventAction(MyRunAction*);
    ~MyEventAction();

 public:
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

 private:
    G4double fEdep;
};

#endif
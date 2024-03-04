#pragma once

#include <memory>
#include <stack>

#include "State.h"

using namespace std;

namespace TP3 {

	typedef unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {};
		~StateMachine() {};

		void addState(StateRef newState, bool isReplacing = true);

		void removeState();

		void processStateChanges();

		StateRef& getActiveState();

	private:
		//Stack dans laquelle on stock les état du jeu (les states)
		stack<StateRef> states;

		//Variable pour stocker un nouvel état du jeu
		StateRef newState;

		//Booléens pour identifier l'action en cours
		bool isRemoving;
		bool isAdding;
		bool isReplacing;
	};

}

#include "StateMachine.h"

namespace TP3 {

	void StateMachine::addState(StateRef newState, bool isReplacing)
	{
		this->isAdding = true;
		this->isReplacing = isReplacing;

		this->newState = move(newState);
	}

	void StateMachine::removeState()
	{
		this->isRemoving = true;
	}

	void StateMachine::processStateChanges()
	{
		if (this->isRemoving && !this->states.empty())
		{
			this->states.pop();

			if (!this->states.empty())
			{
				this->states.top()->resume();
			}

			this->isRemoving = false;
		}

		if (this->isAdding)
		{
			if (!this->states.empty())
			{
				if (this->isReplacing)
				{
					this->states.pop();
				}
				else
				{
					this->states.top()->pause();
				}
			}

			this->states.push(move(this->newState));
			this->states.top()->init();
			this->isAdding = false;
		}
	}

	StateRef& StateMachine::getActiveState()
	{
		return this->states.top();
	}

}

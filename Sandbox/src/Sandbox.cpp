#include <iostream>
#include <limits>

#include "Gargantua/Engine.hpp"
#include "Gargantua/Core/Application.hpp"

#include "Time/TestTime.hpp"

class Sandbox : public Gargantua::Core::Application
{
public:
	void Execute() override
	{

	}
};



int main()
{
	Gargantua::Engine e{ []() {return new Sandbox{}; } };



	return 0;
}
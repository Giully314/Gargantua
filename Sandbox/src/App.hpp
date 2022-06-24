#pragma once
/*
Sandbox/src/App.hpp

PURPOSE:

CLASSES:


DESCRIPTION:

*/


#include <Gargantua/Types.hpp>

#include <Gargantua/Core/Application.hpp>
#include <Gargantua/Core/EngineSystems.hpp>
#include <Gargantua/Core/Pipeline.hpp>

#include <Gargantua/Renderer/Shader.hpp>
#include <Gargantua/Renderer/Program.hpp>


namespace Sandbox
{
	class App : public Gargantua::Core::Application
	{
	public:
		void Start() override;

		void Shutdown() override
		{
			pipeline.End();
		}
	};
} //namespace Sandbox
/*
Sandbox/src/App.hpp

PURPOSE:

CLASSES:


DESCRIPTION:

*/

export module sandbox.app;

import gargantua.types;
import gargantua.core.core;
import gargantua.render.shader;
import gargantua.render.program;



namespace sandbox
{
	export struct TestStage : public gargantua::core::Stage
	{
		/*TestStage(core::EngineSystems systems_) : systems(std::move(systems_))
		{

		}*/
	};

	export class App : public gargantua::core::Application
	{
	public:
		void Start() override;

		void Shutdown() override
		{
			pipeline.End();
		}
	};
} //namespace Sandbox
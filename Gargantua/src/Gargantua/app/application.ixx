/*
* gargantua/app/application.ixx
* 
* PURPOSE:
* CLASSES:
* DESCRIPTION:
*/

export module gargantua.app.application;


namespace gargantua::app
{
	export
	enum class ApplicationState
	{
		Running, // return this value if the application should continue running
		Close, // return this value if the application should be closed
	};

	export
	class Application
	{
	public:
		virtual ~Application() = default;
		
		// This function is called after the initialization of the engine systems.
		virtual auto Startup() -> void
		{

		}
		
		// This function is called before the shutdown of the engine systems.
		virtual auto Shutdown() -> void
		{

		}

		// Called every cycle before Run().
		virtual auto Begin() -> void
		{

		}

		// Called every cycle after Run().
		virtual auto End() -> void
		{

		}

		virtual auto Run() -> ApplicationState = 0;
	};
} // namespace gargantua::app
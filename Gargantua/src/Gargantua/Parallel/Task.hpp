#pragma once



namespace Gargantua
{
	namespace Parallel
	{
		/*
		Base class for all task that need be registered in the TaskSystem to be executed in parallel.
		TODO: i would like to implement coroutine inside the TaskSystem. If a task depends on another task,
		should put himself in the queue and resumed later. 
		But for now it's useless overwork, because the engine (and the game) doesn't need this.
		*/
		class Task
		{
		public:
			virtual ~Task();

			void operator()()
			{
				Execute();
			}

		protected:
			virtual void Execute() = 0;
		};
	} //namespace Parallel
} //namespace Gargantua
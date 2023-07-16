/*
* gargantua/log/mutex_console_stream.ixx
* 
* PURPOSE: thread safe console stream.
*/

export module gargantua.log.mutex_console_stream;

import <iostream>;
import <mutex>;
import <string_view>;


export namespace gargantua::log
{
	//To use ONLY for debug on local machine.
	class MutexConsoleStream
	{
	public:
		friend auto operator<<(MutexConsoleStream& os, std::string_view s) ->MutexConsoleStream&;

		auto Flush() -> MutexConsoleStream&
		{
			std::lock_guard l{ m };
			std::cout.flush();
			return *this;
		}

	private:
		std::mutex m;
	};

	inline auto operator<<(MutexConsoleStream& os, std::string_view s) -> MutexConsoleStream&
	{
		{
			std::lock_guard l{ os.m };
			std::cout << s;
		}
		return os;
	}

} //namespace gargantua::log
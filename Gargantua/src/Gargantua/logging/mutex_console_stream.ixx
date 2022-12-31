export module gargantua.logging.log:mutex_console_stream;

import <iostream>;
import <mutex>;
import <string_view>;

import :stream_type;

namespace gargantua::logging
{
	//To use ONLY for debug on local machine.
	export class MutexConsoleStream
	{
	public:
		using StreamType = OutputStreamTag;

		friend auto operator<<(MutexConsoleStream& os, std::string_view s) ->MutexConsoleStream&;

		auto Flush() -> MutexConsoleStream&
		{
			std::cout.flush();
			return *this;
		}

	private:
		std::mutex m;
	}; //class MutexConsoleStream&

	export inline auto operator<<(MutexConsoleStream& os, std::string_view s) -> MutexConsoleStream&
	{
		{
			std::lock_guard l{ os.m };
			std::cout << s;
		}
		return os;
	}

} //namespace gargantua::logging
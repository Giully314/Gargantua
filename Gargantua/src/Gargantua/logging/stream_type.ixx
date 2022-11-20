/*
Gargantua/Streams/StreamType.hpp

PURPOSE: Tag classes for streams.

CLASSES:
	BasicStream: Basic stream tag.
	OutputStream: Output stream tag.
	InputStream: Input stream tag.
	IOStream: I/O stream tag.

DESCRIPTION:

USAGE:

*/

export module gargantua.logging.log:stream_type;


export namespace gargantua::logging
{
	struct BasicStreamTag { };

	struct OutputStreamTag { };

	struct InputStreamTag { };

	struct IOStreamTag { };

} //namespace gargantua::logging
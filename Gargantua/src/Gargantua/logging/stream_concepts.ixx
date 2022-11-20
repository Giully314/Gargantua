/*
gargantua/logging/stream_concepts.ixx

PURPOSE: Check if a type is a Stream.

CLASSES:
	BasicStream: Concept for basic properties of a Stream.
	OutputStream: Concept for output stream.
	InputStream: Concept for input stream.
	IOStream: Concept for I/O stream.


DESCRIPTION:
	These concepts are used for custom stream type inside the Log directory (for now).
	Other possible future uses are stream serialization of objects inside the engine.

USAGE:
	template <typename MyStreamType, typename TObject>
	requires IOStream<MyStreamType, TObject>
	void f();
*/
module;


export module gargantua.logging.log:stream_concepts;

//import <iostream>;
import <concepts>;

import :stream_type;

export namespace gargantua::logging
{
	/*
		Note: i don't really like this design for stream concepts. Using a single "requirement" could lead
		to bad behavior. Concepts should describe general properties that a type must satisfy.
		A class could implements the operator << but this doesn't mean that the class is a stream.
		So for a good design, i should implement other concepts that describe what is a stream for me.
		*/

	template <typename T>
	concept BasicStream = requires(T s)
	{
		typename T::StreamType;
		{s.Flush()} -> std::same_as<T&>;
	};


	template <typename T, typename U>
	concept OutputStream = BasicStream<T> && requires(T s, U m)
	{
		std::same_as<typename T::StreamType, OutputStreamTag>;
		{s << m} -> std::same_as<T&>;
	};

	template <typename T, typename U>
	concept InputStream = BasicStream<T> && requires(T s, U m)
	{
		std::same_as<typename T::StreamType, InputStreamTag>;
		{s >> m} -> std::same_as<T&>;
	};


	template <typename T, typename U>
	concept IOStream = InputStream<T, U> && OutputStream<T, U>;
} //namespace gargantua::logging
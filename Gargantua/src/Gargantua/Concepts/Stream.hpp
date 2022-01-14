#pragma once

#include "Gargantua/Streams/StreamType.hpp"

#include <iostream>
#include <concepts>

namespace Gargantua
{
	namespace Concepts
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
			//{s.rdstate()} -> std::same_as<std::ios_base::iostate>;
			//{s.setstate(std::same_as<std::ios_base::iostate>) } -> std::same_as<void>;
			typename T::StreamType;
			{s.Flush()} -> std::same_as<T&>;
		};


		template <typename T, typename U>
		concept OutputStream = BasicStream<T> && requires(T s, U m)
		{
			std::same_as<typename T::StreamType, Streams::OutputStream>;
			{s << m} -> std::same_as<T&>;
		};

		template <typename T, typename U>
		concept InputStream = BasicStream<T> && requires(T s, U m)
		{
			std::same_as<typename T::StreamType, Streams::InputStream>;
			{s >> m} -> std::same_as<T&>;
		};


		template <typename T, typename U>
		concept IOStream = InputStream<T, U> && OutputStream<T, U>;
	} //namespace Concepts
} //namespace Gargantua
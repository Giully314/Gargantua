/*
* gargantua/ds/grid.ixx
* 
* PURPOSE: 2d grid.
* 
* CLASSES:
*	Grid: const 2d array with dimensions specified at runtime.
* 
* DESCRIPTION:
*/

export module gargantua.ds.grid;

import <concepts>;
import <vector>;
import <memory>;

import gargantua.types;


export namespace gargantua::ds
{
	template <std::default_initializable T, typename TAlloc = std::allocator<T>>
	class Grid
	{
	public:
		// TODO: this section is not completed.
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using iterator = typename std::vector<T, TAlloc>::iterator;
		using const_iterator = typename std::vector<T, TAlloc>::const_iterator;
		using difference_type = typename std::vector<T, TAlloc>::difference_type;
		using size_type = typename std::vector<T, TAlloc>::size_type;


		constexpr Grid() = default;
		

		/*
		* Construct a grid width * height.
		*/
		constexpr Grid(u32 width_, u32 height_) : data(width_* height_), w(width_), h(height_)
		{

		}

		/*
		* Construct a grid width * height.
		*/
		constexpr Grid(u32 width_, u32 height_, const T& default_value) : data(width_* height_, default_value), w(width_), h(height_)
		{

		}

		constexpr auto operator()(const u32 x, const u32 y) -> T&
		{
			return data[y * w + x];
		}

		constexpr auto operator()(const u32 x, const u32 y) const -> const T&
		{
			return data[y * w + x];
		}



		constexpr auto width() const noexcept -> u32
		{
			return w;
		}

		constexpr auto height() const noexcept -> u32
		{
			return h;
		}
	



		constexpr auto begin() -> iterator
		{
			return data.begin();
		}

		constexpr auto begin() const -> const_iterator
		{
			return data.cbegin();
		}

		constexpr auto end() -> iterator
		{
			return data.end();
		}

		constexpr auto end() const -> const_iterator
		{
			return data.cend();
		}


		constexpr auto cbegin() const -> const_iterator
		{
			return data.cbegin();
		}

		constexpr auto cend() const -> const_iterator
		{
			return data.cend();
		}
		

	private:
		std::vector<T, TAlloc> data;
		u32 w{ 0 };
		u32 h{ 0 };
		//const unique_res<T[]> data;
	};
} // namespace gargantua::ds



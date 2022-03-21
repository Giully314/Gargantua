#pragma once
/*
Gargantua/Renderer/OrtoCamera.hpp

PURPOSE: Orthographic Camera.


CLASSES:
	OrtoCamera:


DESCRIPTION:
	
*/
#include "Gargantua/Types.hpp"


#include "Gargantua/Math/Mat4d.hpp"
#include "Gargantua/Math/Vec3d.hpp"


namespace Gargantua
{
	namespace Renderer
	{
		class OrthoCamera
		{
		public:
			OrthoCamera(real_t l, real_t b, real_t r, real_t t, real_t n, real_t f);
			OrthoCamera(real_t l, real_t b, real_t r, real_t t);


			inline void SetPosition(Math::Vec3df new_position)
			{
				position = std::move(new_position);
				UpdateCameraMatrix();
			}


			inline const Math::Vec3df& GetPosition() const noexcept
			{
				return position;
			}


			inline void SetRotation(real_t new_rotation)
			{
				rotation = new_rotation;
				UpdateCameraMatrix();
			}

			inline real_t GetRotation() const noexcept
			{
				return rotation;
			}


			inline void SetPositionAndRotation(Math::Vec3df new_position, real_t new_rotation)
			{
				position = std::move(new_position);
				rotation = new_rotation;
				UpdateCameraMatrix();
			}


			inline const Math::Mat4df& GetProjectionView() const noexcept
			{
				return proj_view;
			}

			

		private:
			Math::Vec3df position;
			real_t rotation; //rotate around the z axis. counterclock for positive values.

			Math::Mat4df projection;
			Math::Mat4df view;
			Math::Mat4df proj_view; //read from right to left :).
			
			void UpdateCameraMatrix();
		};
	} //namespace Renderer 
} //namespace Gargantua
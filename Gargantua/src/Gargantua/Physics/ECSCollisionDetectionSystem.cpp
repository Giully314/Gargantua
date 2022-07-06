/*
Gargantua/Physics/ECSCollisionDetectionSystem.cpp
*/
#include "ECSCollisionDetectionSystem.hpp"



namespace Gargantua
{
	namespace Physics
	{
		bool ECSCollisionDetectionSystem::TestAABBvsAABB(const PositionComponent& pa, const QuadShapeComponent& a,
			const PositionComponent& pb, const QuadShapeComponent& b, CollisionDetectionComponent& ca)
		{
			Math::Vec2df distance = pb.position - pa.position;

			//Calculate half the extent for x
			real_t a_extent = (a.max.x - a.min.x) / 2.0f;
			real_t b_extent = (b.max.x - b.min.x) / 2.0f;

			real_t x_overlap = a_extent + b_extent - std::abs(distance.x);

			//SAT for x
			if (x_overlap > 0.0f)
			{
				//Calculate half the extent for y
				a_extent = (a.max.y - a.min.y) / 2.0f;
				b_extent = (b.max.y - b.min.y) / 2.0f;

				real_t y_overlap = a_extent + b_extent - std::abs(distance.y);

				//SAT for y
				if (y_overlap > 0.0f)
				{
					//which axis is axis of least penetration
					if (x_overlap < y_overlap)
					{
						if (distance.x < 0)
						{
							ca.normals.push_back(-ReferenceFrame::i_dir);
						}
						else
						{
							ca.normals.push_back(ReferenceFrame::i_dir);
						}

						ca.penetration_depths.push_back(x_overlap);

						return true;
					}
					else
					{
						if (distance.y < 0)
						{
							ca.normals.push_back(-ReferenceFrame::j_dir);
						}
						else
						{
							ca.normals.push_back(ReferenceFrame::j_dir);
						}

						ca.penetration_depths.push_back(y_overlap);

						return true;
					}
				}
			}
			return false;
		}


	} //namespace Physics
} //namespace Gargantua
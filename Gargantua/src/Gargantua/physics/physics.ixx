/*
* gargantua/physics/physics.ixx
* 
* This module implements a basic (for now) physics engine. Simple motion, collision detection
* and collision resolve. For now the only shape supported is a quad.
*/

export module gargantua.physics;


export import gargantua.physics.ecs_components;
export import gargantua.physics.ecs_functions;
export import gargantua.physics.physics_ecs_system;
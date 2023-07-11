/*
* gargantua/ecs/ecs.ixx
* 
* The entity component system (https://en.wikipedia.org/wiki/Entity_component_system)
* is a design pattern composed of 3 areas:
* 1) entity is an object inside the application.
* 2) components are data attached to an entity.
* 3) systems are functions that acts on components.
* 
* The 2 main strong motivations to use an ECS are modularity and performance.
* 
* Modularity: because of the division between the class entity and the data attached to an 
* entity we don't have the problems of the OOP design where we have a hierarchy of 
* classes from which to derive and where we could have problems of intersection between
* multiple base classes. A component can be attached/detached from an entity in every
* moment and so the behaviour can change at eny time.
* 
* Performance: components are stored in a contigous piece of memory. In this way we can
* maximize the cache usage and avoid to lookup in main memory. A problem with the OOP
* design is that most of the time we carry in the cache useless informations only because 
* they are near the data we are working on. For example imagine to have a class 
* with position velocity texture. If we want to update the position with velocity, 
* when the computer access to the class data most of the time it's going to get the texture
* too, wasting cache memory for useless data in that moment.
* With the components design, when we work with position and velocity we access only these
* 2 types and load in the cache (with a cache line) the next position and velocity that
* will be ready to be used in the next cycle.
*/

export module gargantua.ecs.ecs;

export import gargantua.ecs.entity;
export import gargantua.ecs.entity_manager;
export import gargantua.ecs.component_storage;
export import gargantua.ecs.component_manager;
export import gargantua.ecs.component_group;
export import gargantua.ecs.ecs_system;
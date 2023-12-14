/*
* gargantua/render/render.ixx
* 
* The module render defines the layer of interface for OpenGL. The implementation tries to keep in mind the 
* problems pointed out here (specially for RAII approach):
* https://www.khronos.org/opengl/wiki/Common_Mistakes#The_Object_Oriented_Language_Problem.
* One way to do that is to use unique_res/shared_res when creating OpenGL objects that must be passed around
* and use the stack for local usage.
*/

export module gargantua.render;

export import gargantua.render.opengl_object;
export import gargantua.render.vertex_buffer;
export import gargantua.render.index_buffer;
export import gargantua.render.render_info;
export import gargantua.render.vertex_array;
export import gargantua.render.shader;
export import gargantua.render.program;
export import gargantua.render.orthographic_camera;
export import gargantua.render.renderer_command;
export import gargantua.render.camera;
export import gargantua.render.texture;
export import gargantua.render.subtexture;
export import gargantua.render.renderer_system;
export import gargantua.render.shader_system;
export import gargantua.render.texture_system;
export import gargantua.render.ecs_components;
export import gargantua.render.ecs_functions;
export import gargantua.render.render_ecs_system;
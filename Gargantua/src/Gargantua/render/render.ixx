/*
* gargantua/render/render.ixx
* 
* The module render defines the layer of interface for OpenGL. The implementation tries to not 
* be object oriented for the problems pointed out here (https://www.khronos.org/opengl/wiki/Common_Mistakes#The_Object_Oriented_Language_Problem).
* 
*/

export module gargantua.render;

export import gargantua.render.opengl_object;
export import gargantua.render.buffer;
export import gargantua.render.render_info;
export import gargantua.render.vertex_array;
export import gargantua.render.shader;
export import gargantua.render.program;
export import gargantua.render.orthographic_camera;
export import gargantua.render.renderer_command;
export import gargantua.render.renderer_system;
export import gargantua.render.camera;
export import gargantua.render.texture2d;
export import gargantua.render.subtexture2d;
export import gargantua.render.texture2d_system; 
export import gargantua.render.functions;
export import gargantua.render.components;
export import gargantua.render.renderer_system;
export import gargantua.render.renderer2d_system;
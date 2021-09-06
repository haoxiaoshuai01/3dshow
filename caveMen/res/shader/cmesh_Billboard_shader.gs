#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 5) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

mat4 mvp;
in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;

vec4 npc_to_mvp(vec4 pos)
{
	return mvp*pos;
}

void main() {    
	
	 mvp =   projection * view * model;

	fColor = gs_in[0].color; 
    gl_Position =  npc_to_mvp(gl_in[0].gl_Position ); 
    EmitVertex();   

	fColor = gs_in[1].color; 
    gl_Position =   npc_to_mvp(gl_in[1].gl_Position );
    EmitVertex();
	
	fColor = gs_in[2].color; 
    gl_Position =  npc_to_mvp(gl_in[2].gl_Position);;
    EmitVertex();

    EndPrimitive();
}
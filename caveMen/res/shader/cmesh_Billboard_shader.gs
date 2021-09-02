#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;


void main() {    

	fColor = gs_in[0].color; 
    gl_Position = gl_in[0].gl_Position ; 
    EmitVertex();   
	fColor = gs_in[1].color; 
    gl_Position = gl_in[1].gl_Position ;
    EmitVertex();
	fColor = gs_in[2].color; 
    gl_Position = gl_in[2].gl_Position ;
    EmitVertex();
	fColor = gs_in[2].color; 
    gl_Position = vec4(-10.0f, -10.0f, 3.0f,1.0f);
    EmitVertex();
    EndPrimitive();
}
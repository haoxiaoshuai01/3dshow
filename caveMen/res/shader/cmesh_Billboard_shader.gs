#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 gCameraPos;
uniform vec3 gCameraUP;
mat4 mvp;
in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;
out vec2 TexCoord;

vec4 npc_to_mvp(vec4 pos)
{
	return mvp*pos;
}

void main() {    
	
	mvp =   projection * view;
	fColor = gs_in[0].color; 
	vec3 Pos = gl_in[0].gl_Position.xyz;

	vec3 toCamera = normalize(Pos - gCameraPos);
    vec3 right = cross(gCameraUP,toCamera);
	float len = 1.0f;
	vec3 P1 =  (Pos+len*0.5*right)+(len*0.5*gCameraUP);
	vec3 P2 = (Pos+len*0.5*right)+(-len*0.5*gCameraUP);
	vec3 P3 =  (Pos-len*0.5*right)+(len*0.5*gCameraUP);
	vec3 P4 =  (Pos-len*0.5*right)+(-len*0.5*gCameraUP);

    gl_Position = npc_to_mvp(vec4(P1,1.0f)); 
	TexCoord =vec2(1.0,1.0);
    EmitVertex();   

    gl_Position =  npc_to_mvp(vec4(P2,1.0f));
	TexCoord =vec2(1.0,0.0);
    EmitVertex();

    gl_Position =  npc_to_mvp(vec4(P3,1.0f));
	TexCoord =vec2(0.0,1.0);
    EmitVertex();

	gl_Position = npc_to_mvp(vec4(P4,1.0f));
	TexCoord =vec2(0.0,0.0);
    EmitVertex();

    EndPrimitive();
}
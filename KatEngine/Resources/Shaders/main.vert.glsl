#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec2 inTile;

out vec4 vPos;
out vec2 vUV;
out vec2 vTile;

uniform mat4 uViewProj;
uniform mat4 uModel;

void main() {
	gl_Position = uViewProj * uModel * vec4(inPos, 1.0);

	vPos = gl_Position;
	vUV = inUV;
	vTile = inTile;
}
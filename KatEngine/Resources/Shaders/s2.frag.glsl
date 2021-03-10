#version 450

out vec4 colorOut;

in vec2 vUV;

uniform sampler2D uTexture;
uniform int uTile;
uniform vec2 uTileSize;
uniform int uRowSize;

void main() {
	int x = uTile % uRowSize;
	int y = uTile / uRowSize;
	colorOut = texture(uTexture, vec2(uTileSize.x * x + vUV.x, uTileSize.y * y + vUV.y));
}
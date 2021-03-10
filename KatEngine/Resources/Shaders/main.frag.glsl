#version 450

out vec4 colorOut;

in vec2 vUV;
in vec2 vTile;

uniform sampler2D uTexture;
uniform vec2 uHighlightedTile;

void main() {
	colorOut = texture(uTexture, vUV);
	if (uHighlightedTile == vec2(int(vTile.x), int(vTile.y))) {
		colorOut = mix(colorOut, vec4(1, 1, 0, 1), 0.8f);
	}
}
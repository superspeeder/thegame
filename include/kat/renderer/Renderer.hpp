#pragma once

namespace kat {

	extern bool isGLADInit;

	void initGLAD();

	void clearFrame(float r, float g, float b, float a = 1.0f);
}
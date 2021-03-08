#pragma once

#include <kat/Application.hpp>

class GameApp : public kat::Application {
private:
protected:
	void render() override;
public:
	GameApp();
};
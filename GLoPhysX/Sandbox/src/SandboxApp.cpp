#include <iostream>

#include "glophysx.h"

class Sandbox : public GLOPHYSX::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

GLOPHYSX::Application* GLOPHYSX::CreateApplication() {
	return new Sandbox();
}
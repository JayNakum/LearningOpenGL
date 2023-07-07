#include "Vector.h"

class Sandbox : public Vector::Application
{

};

Vector::Application* Vector::createApplication()
{
	return new Sandbox();
}
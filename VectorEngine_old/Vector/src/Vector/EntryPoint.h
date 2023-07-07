#pragma once

#ifdef VECTOR_PLATFORM_WINDOWS

extern Vector::Application* Vector::createApplication();

// EntryPoint is a place from where Vector is created.
// All the Vector initialization takes place here.

// this will be the main function for any Vector Application.
// Client only calls createApplication() and returns the MainClass 
// that extends a Vector::Application
int main(int argc, char** argv)
{
	auto app = Vector::createApplication();
	app->run();
	delete app;
}

#endif // VECTOR_PLATFORM_WINDOWS
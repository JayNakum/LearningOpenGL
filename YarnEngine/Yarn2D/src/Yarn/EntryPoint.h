#pragma once

#ifdef YARN_PLATFORM_WINDOWS

extern Yarn::Application* Yarn::createApplication();


// EntryPoint is a place from where Yarn is created.
// All the Yarn initialization takes place here.

// this will be the main function for any Yarn Application.
// Client only calls createApplication() and returns the MainClass 
// that extends a Yarn::Application
int main(int argc, char** argv)
{
	Yarn::Log::init();
	YARN_CORE_TRACE("Initialized Log!");

	auto app = Yarn::createApplication();
	app->run();
	delete app;
}

#endif // YARN_PLATFORM_WINDOWS

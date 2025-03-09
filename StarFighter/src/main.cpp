#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "framework/Application.h"

int main()
{
	//allowcating on the heap.
	std::unique_ptr<st::Application> application = std::make_unique<st::Application>();
	application->Run();
}
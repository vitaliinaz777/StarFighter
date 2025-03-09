#include "main.h"
#include "framework/Application.h"

int main()
{
    st::Application* application = GetApplication();
    application->Run();
    delete application;
}
#pragma once


namespace st
{
    // forward decloration
    class Application;
}

// extern keyword is used to declare a function that is defined in another file
extern st::Application* GetApplication();
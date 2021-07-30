#include <iostream>

#include <application.h>

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    vui::Application app;
    app.Initialize();
    while (!app.Update())
    {
    }
    
}

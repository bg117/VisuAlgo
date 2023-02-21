#include "App.hpp"

#include <gtkmm.h>

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv);
    App  window;
    return app->run(window);
}

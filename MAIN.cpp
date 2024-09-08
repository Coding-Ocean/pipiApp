#include"../pipiLib/pch.h"
#include"../pipiLib/WINDOW.h"
#include"../pipiLib/GRAPHIC.h"

int MAIN()
{
    auto& w = WINDOW::instance();
    auto& g = GRAPHIC::instance();

    w.create(L"pipi");
    g.create();

    while (!w.quit()) {
        g.clear(0.25f,0.5f,0.9f);
        g.present();
    }

    g.destroy();
    w.destroy();
}
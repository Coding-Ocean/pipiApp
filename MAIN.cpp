#include"../pipiLib/pch.h"
#include"../pipiLib/WINDOW.h"
#include"../pipiLib/GRAPHIC.h"
#include"SQUARE.h"

int MAIN()
{
    auto& w = WINDOW::instance();
    auto& g = GRAPHIC::instance();
    w.create(L"pipi");
    g.create();

    SQUARE square(L"assets/penguin1.png");
    MATRIX world;
    float r = 0.0f;

    while (!w.quit()) {
        g.clear(0.25f,0.5f,0.9f);
        g.setPipeline();

        world.rotateY(r);
        r += 0.01f;
        square.update(world);
        square.draw();
        
        g.present();
    }

    g.destroy();
    w.destroy();
}
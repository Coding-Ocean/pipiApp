#include"../pipiLib/pch.h"
#include"../pipiLib/WINDOW.h"
#include"../pipiLib/GRAPHIC.h"
#include"STATIC_MESH.h"

int MAIN()
{
    auto& w = WINDOW::instance();
    auto& g = GRAPHIC::instance();
    w.create(L"pipi");
    g.create();

    STATIC_MESH mesh;
    MATRIX world;
    float r = 0.0f;

    while (!w.quit()) {
        g.clear(0.25f,0.5f,0.9f);
        g.setPipeline();

        world.rotateY(r);
        r += 0.01f;
        mesh.update(world);
        mesh.draw();
        
        g.present();
    }

    g.destroy();
    w.destroy();
}
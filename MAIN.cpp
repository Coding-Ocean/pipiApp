#include"../pipiLib/pch.h"
#include"../pipiLib/WINDOW.h"
#include"../pipiLib/GRAPHIC.h"
#include"../pipiLib/STATIC_MESH.h"

int MAIN()
{
    auto& w = WINDOW::instance();
    auto& g = GRAPHIC::instance();
    w.create(L"pipi");
    g.create();

    {
        FLOAT3 eye = { 0, 0, 8 }, focus = { 0, 0, 0 }, up = { 0, 1, 0 };
        g.setView(eye, focus, up);

        //mesh
        STATIC_MESH mesh;
        mesh.create("assets/cube.txt");
        MATRIX world;
        float r = 0.0f;

        while (!w.quit()) {
            //update
            world.identity();
            world.mulRotateY(r);
            world.mulRotateX(r/2);
            r += 0.01f;
            mesh.update(world);
            //draw
            g.clear(0.25f, 0.5f, 0.9f);
            g.setPipeline();
            mesh.draw();
            g.present();
        }
    }

    g.destroy();
    w.destroy();
}
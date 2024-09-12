#include"../pipiLib/pch.h"
#include"../pipiLib/WINDOW.h"
#include"../pipiLib/GRAPHIC.h"
#include"../pipiLib/STATIC_MESH.h"
#include"../pipiLib/primitive.h"

int MAIN()
{
    auto& w = WINDOW::instance();
    auto& g = GRAPHIC::instance();
    w.create(L"pipi");
    g.create();

    createVtxSphere(0.5f, 30);
    createVtxCube(0.5f);

    {
        FLOAT3 eye = { 0, 0, 2 }, focus = { 0, 0, 0 }, up = { 0, 1, 0 };
        g.setView(eye, focus, up);

        //mesh
        STATIC_MESH mesh;
        mesh.create("assets/sphere.txt");
        MATRIX world;
        float r = 0.0f;

        while (!w.quit()) {
            //update
            world.identity();
            //world.mulRotateX(0.1f);
            world.mulRotateY(r);
            //world.mulRotateX(0.5f);
            r += 0.01f;
            mesh.update(world);
            //draw
            g.clear(0.1f, 0.1f, 0.15f);
            g.setPipeline();
            mesh.draw();
            g.present();
        }
    }

    g.destroy();
    w.destroy();
}
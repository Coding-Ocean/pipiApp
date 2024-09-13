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

    createCubeText(0.5f/2);
    createSphereText(0.5f,48);

    {
        FLOAT3 eye = { 0, 1, 3 }, focus = { 0, 0, 0 }, up = { 0, 1, 0 };
        g.setView(eye, focus, up);

        //mesh
        STATIC_MESH mesh1;
        mesh1.createFromText(L"assets/cube.txt");
        STATIC_MESH mesh2;
        mesh2.createFromText(L"assets/sphere.txt");

        MATRIX world;
        float r = 0.0f;

        while (!w.quit()) 
        {
            //update
            world.identity();
            world.mulTranslate(0.8f, 0, 0);
            world.mulRotateZ(r);
            world.mulRotateY(r);
            mesh1.update(world);

            world.identity();
            world.mulTranslate(-0.8f, 0, 0);
            world.mulRotateZ(-23.4f * 3.141592f / 180);
            world.mulRotateY(r);
            mesh2.update(world);

            r += 0.01f;

            //draw
            g.clear(0.1f, 0.12f, 0.12f);
            g.setPipeline();
            mesh1.draw();
            mesh2.draw();
            g.present();
        }
    }

    g.destroy();
    w.destroy();
}
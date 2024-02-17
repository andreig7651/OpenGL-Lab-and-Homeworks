#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{   
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    count = 3;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    std::vector<VertexFormat> vertices1 =
    {
        VertexFormat(corner, glm::vec3(200, 0, 0)),
        VertexFormat(corner + glm::vec3(200, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(corner + glm::vec3(200, 200,  0), glm::vec3(1, 0, 0)),
    };

    std::vector<unsigned int> indices1 = { 0, 1, 2 };
    Mesh* triangle1 = new Mesh("triangle1");
    triangle1->InitFromData(vertices1, indices1);
    AddMeshToList(triangle1);

    //triangle2
    std::vector<VertexFormat> vertices2 =
    {
        VertexFormat(corner, glm::vec3(120, 0, 0)),
        VertexFormat(corner + glm::vec3(120, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(corner + glm::vec3(120, 120, 0), glm::vec3(1, 0, 0)),
    };

    std::vector<unsigned int> indices2 = {0, 1, 2};
    Mesh* triangle2 = new Mesh("triangle2");
    triangle2->InitFromData(vertices2, indices2);
    AddMeshToList(triangle2);

    //triangle3
    std::vector<VertexFormat> vertices3 =
    {
        VertexFormat(corner, glm::vec3(120, 0, 0)),
        VertexFormat(corner + glm::vec3(120, 0, 0), glm::vec3(1, 0, 0)),
        VertexFormat(corner + glm::vec3(120, 120, 0), glm::vec3(1, 0, 0)),
    };

    std::vector<unsigned int> indices3 = { 0, 1, 2 };
    Mesh* triangle3 = new Mesh("triangle3");
    triangle3->InitFromData(vertices3, indices3);
    AddMeshToList(triangle3);

    //circle

    Mesh* head = new Mesh("head");

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.emplace_back(glm::vec3(0.f, 0.f, 0.f));
    int numTriangles = 100, headRadius = 50;

    for (int i = 0; i < numTriangles; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numTriangles);//get the current angle 
        float x = headRadius * cosf(theta);//calculate the x component 
        float y = headRadius * sinf(theta);//calculate the y component

        vertices.emplace_back(glm::vec3(x, y, 0));
        indices.push_back(i);
    }
    indices.push_back(numTriangles);
    indices.push_back(1);

    head->InitFromData(vertices, indices);
    head->SetDrawMode(GL_TRIANGLE_FAN);
    AddMeshToList(head);

    

    std::vector<VertexFormat> vertices4 =
    {   
        VertexFormat(glm::vec3(0,0,0), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0,0,0) + glm::vec3(120, 0, 0), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0,0,0) + glm::vec3(120, 60, 0), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0,0,0) + glm::vec3(0, 60, 0), glm::vec3(0,1,0))
    };

    std::vector<unsigned int> indices4 = { 0, 1, 2, 3};

    Mesh* rectangle = new Mesh("rectangle");
    rectangle->SetDrawMode(GL_LINE_LOOP);
    rectangle->InitFromData(vertices4, indices4);
    AddMeshToList(rectangle);

    std::vector<VertexFormat> vertices5 =
    {
        VertexFormat(glm::vec3(0,0,0.01), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0,0,0.01) + glm::vec3(120, 0, 0), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0,0,0.01) + glm::vec3(120, 60, 0), glm::vec3(0,1,0)),
        VertexFormat(glm::vec3(0,0,0.01) + glm::vec3(0, 60, 0), glm::vec3(0,1,0))
    };

    Mesh* grass = new Mesh("grass");
    //grass->SetDrawMode(GL_LINE_LOOP);
    indices4.push_back(0);
    indices4.push_back(2);
    grass->InitFromData(vertices5, indices4);
    AddMeshToList(grass);
    
    std::vector<VertexFormat> vertices6 =
    {
        VertexFormat(glm::vec3(0,0,0), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(0,0,0) + glm::vec3(120, 0, 0), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(0,0,0) + glm::vec3(120, 60, 0), glm::vec3(0,0,0)),
        VertexFormat(glm::vec3(0,0,0) + glm::vec3(0, 60, 0), glm::vec3(0,0,0))
    };

    std::vector<unsigned int> indices6 = { 0, 1, 2, 3 };

    Mesh* black_rectangle = new Mesh("black_rectangle");
    black_rectangle->SetDrawMode(GL_LINE_LOOP);
    black_rectangle->InitFromData(vertices6, indices6);
    AddMeshToList(black_rectangle);


}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!
    if (lives >= 0) {
        glm::ivec2 resolution = window->GetResolution();
        time += deltaTimeSeconds;

        if (shoot == 1 && escape == 0) {
            rotation_angle = 180;
            translateY -= 40 * ySpeed * deltaTimeSeconds * sin(RADIANS(angle));
        }

        if (escape == 0 && shoot == 0) {
            translateX += 40 * xSpeed * deltaTimeSeconds * cos(RADIANS(angle));
            translateY += 40 * ySpeed * deltaTimeSeconds * sin(RADIANS(angle));

            if (translateX > 0.8 * resolution.x || translateX < 0) {
                angle = 180 - angle;
                rotation_angle = angle - 90;

            }
            else if (translateY > 0.8 * resolution.y || translateY < 0) {
                angle = (-1) * angle;
                rotation_angle = angle - 90;

            }
        }

        if (escape == 1 && shoot == 0) {
            translateY += 40 * ySpeed * deltaTimeSeconds * sin(RADIANS(angle));
            angle = 90;
        }

        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(60, 30);
        modelMatrix *= transform2D::Rotate(RADIANS(rotation_angle));
        modelMatrix *= transform2D::Translate(-60, -30);
        modelMatrix *= transform2D::Translate(150, 80);
        modelMatrix *= transform2D::Scale(0.5, 0.5);

        RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(60, 30);
        modelMatrix *= transform2D::Rotate(RADIANS(rotation_angle));
        modelMatrix *= transform2D::Translate(-60, -30);
        modelMatrix *= transform2D::Translate(142, 180);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        modelMatrix *= transform2D::Rotate(-20);
        modelMatrix *= transform2D::Translate(120, 120);

        angularStep += deltaTimeSeconds * 1.5f;
        if (angularStep >= 1.5708f || angularStep <= -1.5708f) {
            angularStep = 0.f;
        }

        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Translate(-120, -120);
        RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(60, 30);
        modelMatrix *= transform2D::Rotate(RADIANS(rotation_angle));
        modelMatrix *= transform2D::Translate(-60, -30);
        modelMatrix *= transform2D::Translate(285, 70);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        modelMatrix *= transform2D::Rotate(3.14f / 2.5f);
        modelMatrix *= transform2D::Translate(120, 120);
        modelMatrix *= transform2D::Rotate(-angularStep);
        modelMatrix *= transform2D::Translate(-120, -120);
        RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(60, 30);
        modelMatrix *= transform2D::Rotate(RADIANS(rotation_angle));
        modelMatrix *= transform2D::Translate(-60, -30);
        modelMatrix *= transform2D::Translate(255, 205);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(60, 30);
        modelMatrix *= transform2D::Rotate(RADIANS(rotation_angle));
        modelMatrix *= transform2D::Translate(-60, -30);
        modelMatrix *= transform2D::Translate(255, 210);
        modelMatrix *= transform2D::Scale(0.5, 0.5);
        modelMatrix *= transform2D::Scale(0.2f, 0.5f);

        RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Translate(60, 30);
        modelMatrix *= transform2D::Rotate(RADIANS(rotation_angle));
        modelMatrix *= transform2D::Translate(-60, -30);
        modelMatrix *= transform2D::Translate(290, 50);
        modelMatrix *= transform2D::Rotate(3.14f / 2.f);
        modelMatrix *= transform2D::Scale(2, 2.5);

        RenderMesh2D(meshes["black_rectangle"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(0, 0);
        modelMatrix *= transform2D::Scale(12, 4);
        RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

        float init = 1150;
        for (int i = 0; i < count; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(init, 650);
            modelMatrix *= transform2D::Rotate(3.14f / 2.f);
            modelMatrix *= transform2D::Scale(0.5, 0.5);
            RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
            init += 50;
        }

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1020, 600);
        modelMatrix *= transform2D::Scale(2, 0.5);
        RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

        if (inc != 0.f && inc <= 2.2f) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1260, 600);
            modelMatrix *= transform2D::Scale(-inc, 0.5);
            RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);
        }

        if (inc > 2.2f) {
            inc = 0.f;
        }

        init = 950;
        for (int i = 0; i < lives; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(init, 670);
            //modelMatrix *= transform2D::Rotate(3.14 / 2);
            modelMatrix *= transform2D::Scale(0.5, 0.5);
            RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
            init += 60;
        }

        if (count == 0 || time >= 10.f && escape == 0) {
            lives -= 1;
            angle = 15;
            time = 0;
            count = 3;
            xSpeed = 20.f;
            ySpeed = 7.f;
            rotation_angle = 0;
            escape = 1;
        }

        if (translateY >= resolution.y) {
            escape = 0;
            translateX = 0;
            translateY = 0;
            count = 3;
            angle = 15;
            rotation_angle = 0;
        }

        if (translateY <= 0) {
            translateX = 0;
            translateY = 0;
            count = 3;
            angle = 15;
            rotation_angle = 0;
            shoot = 0;
        }

    }

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if ((mouseX <= 130 + translateX || mouseX >= 290 + translateX)) {
            if (mouseY <= 430 + translateY || mouseY >= 670 + translateY)
                count--;
        }
        else {
            shoot = 1;
            time = 0.f;
            inc += 0.2f;
            level++;
            if (level % 5 == 0) {
                xSpeed = xSpeed + xSpeed / 5.f;
                ySpeed = ySpeed + ySpeed / 5.f;
            }
        }

    }
    
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

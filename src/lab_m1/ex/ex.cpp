#include "lab_m1/Ex/Ex.h"

#include <vector>
#include <string>
#include <iostream>
#include "lab_m1/Tema2/transform3D_tema2.h"

using namespace std;
using namespace m1;

#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Ex::Ex()
{
}


Ex::~Ex()
{
}


void Ex::Init()
{
    initialCamOX = 0;
    initialCamOY = 2;
    initialCamOZ = 3.5f;
    camera = new implement::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    points[0] = glm::vec3(-0.12, 0, 0.18);
    points[1] = glm::vec3(-0.42, 0, 0.56);
    points[2] = glm::vec3(-0.64, 0, 0.82);
    points[3] = glm::vec3(-0.92, 0, 1.18);
    points[4] = glm::vec3(-1.22, 0, 1.5);
    points[5] = glm::vec3(-1.6, 0, 1.9);
    points[6] = glm::vec3(-2, 0, 2);
    points[7] = glm::vec3(-2.32, 0, 2.18);
    points[8] = glm::vec3(-2.64, 0, 2.12);
    points[9] = glm::vec3(-3, 0, 2);
    points[10] = glm::vec3(-3.04, 0, 1.64);
    points[11] = glm::vec3(-3.44, 0, 1.64);
    points[12] = glm::vec3(-3.9, 0, 1.4);
    points[13] = glm::vec3(-4.52, 0, 1.68);
    points[14] = glm::vec3(-5, 0, 2);
    points[15] = glm::vec3(-5.38, 0, 1.9);
    points[16] = glm::vec3(-5.6, 0, 1.4);
    points[17] = glm::vec3(-5.56, 0, 0.94);
    points[18] = glm::vec3(-5.92, 0, 0.54);
    points[19] = glm::vec3(-6.32, 0, 0.44);
    points[20] = glm::vec3(-6.32, 0, -0.16);
    points[21] = glm::vec3(-6.22, 0, -0.5);
    points[22] = glm::vec3(-5.78, 0, -0.62);
    points[23] = glm::vec3(-5.36, 0, -0.8);
    points[24] = glm::vec3(-4.82, 0, -0.76);
    points[25] = glm::vec3(-4.2, 0, -0.68);
    points[26] = glm::vec3(-3.66, 0, -0.22);
    points[27] = glm::vec3(-3.48, 0, 0.5);
    points[28] = glm::vec3(-2.98, 0, 0.54);
    points[29] = glm::vec3(-2.62, 0, 0.44);
    points[30] = glm::vec3(-2.32, 0, 0.16);
    points[31] = glm::vec3(-1.96, 0, -0.24);
    points[32] = glm::vec3(-1.2, 0, -0.44);
    points[33] = glm::vec3(-0.72, 0, -0.52);
    points[34] = glm::vec3(-0.26, 0, -0.52);

    //car
    {
        vector<VertexFormat> verticesCar
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(0, 0, -1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(1, 0, -1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(0, 1, -1), glm::vec3(1.0f, 0.5f, 0.31f)),
            VertexFormat(glm::vec3(1, 1, -1), glm::vec3(1.0f, 0.5f, 0.31f)),

        };

        vector<unsigned int> indicesCar =
        {
            0, 1, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4,
        };

        meshes["car"] = new Mesh("generated car");
        meshes["car"]->InitFromData(verticesCar, indicesCar);
    }

    //ground
    {
        vector<VertexFormat> verticesGround
        {
            VertexFormat(glm::vec3(0, 0, 500), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(500, 0, 500), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(0, 0, 500), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(500, 0, 500), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(500, 0, 0), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.68f, 1.0f, 0.68f)),
            VertexFormat(glm::vec3(500, 0, 0), glm::vec3(0.68f, 1.0f, 0.68f)),

        };

        vector<unsigned int> indicesGround =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };

        meshes["ground"] = new Mesh("generated ground");
        meshes["ground"]->InitFromData(verticesGround, indicesGround);
    }

    //treeTop
    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 1.5), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(1.5, 0, 1.5), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0, 1.5, 1.5), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(1.5, 1.5, 1.5), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(1.5, 0, 0), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0, 1.5, 0), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(1.5, 1.5, 0), glm::vec3(0.035f, 0.47f, 0.41f),glm::vec3(0, 1, 0),glm::vec2(1)),
        };
        vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4, };
        meshes["treeTop"] = new Mesh("generated treeTop");
        meshes["treeTop"]->InitFromData(vertices, indices);
    }


    //treeBottom
    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0.5), glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0.5, 0, 0.5), glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0, 1.5, 0.5),  glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0.5, 1.5, 0.5),  glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0, 0, 0),  glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0.5, 0, 0),  glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0, 1.5, 0),  glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)),
            VertexFormat(glm::vec3(0.5, 1.5, 0),  glm::vec3(0.82f, 0.41f, 0.11f),glm::vec3(0, 1, 0),glm::vec2(1)), };
        vector<unsigned int> indices = {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4, };
        meshes["treeBottom"] = new Mesh("generated treeBottom");
        meshes["treeBottom"]->InitFromData(vertices, indices);
    }
    
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
}

void Ex::RenderScene() {

    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D_tema2::Translate(-184, 0, -30);
    RenderMesh(meshes["ground"], shaders["VertexColor"], modelMatrix);

    //calculate points for path
    for (int i = 0; i < 35; i++) {
        float xD, zD;
        xD = points[i + 1].x - points[i].x;
        zD = points[i + 1].z - points[i].z;
        glm::vec3 D = points[i + 1] - points[i];
        glm::vec3 P = cross(D, UP);
        pointsRed[i] = points[i] + distRed * P;
        pointsBlue[i] = points[i] - distBlue * P;
    }

    for (int i = 0; i < 34; i++) {
        vector<VertexFormat> verticesPath{
          VertexFormat(glm::vec3(pointsRed[i].x, 0.1, pointsRed[i].z), glm::vec3(0.54f, 0.27f, 0.07f)),
          VertexFormat(glm::vec3(pointsBlue[i].x, 0.1, pointsBlue[i].z), glm::vec3(0.54f, 0.27f, 0.07f)),
          VertexFormat(glm::vec3(pointsRed[i + 1].x, 0.1, pointsRed[i + 1].z), glm::vec3(0.54f, 0.27f, 0.07f)),
          VertexFormat(glm::vec3(pointsBlue[i + 1].x, 0.1, pointsBlue[i + 1].z), glm::vec3(0.54f, 0.27f, 0.07f)),

        };
        vector<unsigned int> indicesPath = {
                0,1,3,
                0,2,3,
        };
        meshes["path"] = new Mesh("generated path");
        meshes["path"]->InitFromData(verticesPath, indicesPath);
        modelMatrix = glm::mat4(1);
       
        modelMatrix *= transform3D_tema2::Scale(20, 2, 20);
        RenderMesh(meshes["path"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        if (i >= 0 && i <= 15) {
            glm::mat4 modelMatrixCopy = modelMatrix;
            modelMatrix *= transform3D_tema2::Translate(pointsRed[i].x * 20 - 1, 0, pointsRed[i].z * 20 - 1);
            RenderMesh(meshes["treeBottom"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform3D_tema2::Translate(-0.5, 1.53, -0.5);
            RenderMesh(meshes["treeTop"], shaders["VertexColor"], modelMatrix);
            modelMatrixCopy *= transform3D_tema2::Translate(pointsBlue[i].x * 20 + 1, 0, pointsBlue[i].z * 20 + 1);
            RenderMesh(meshes["treeBottom"], shaders["VertexColor"], modelMatrixCopy);
            modelMatrixCopy *= transform3D_tema2::Translate(-0.5, 1.53, -0.5);
            RenderMesh(meshes["treeTop"], shaders["VertexColor"], modelMatrixCopy);
        }
        else {
            glm::mat4 modelMatrixCopy = modelMatrix;
            modelMatrix *= transform3D_tema2::Translate(pointsRed[i].x * 20 + 1, 0, pointsRed[i].z * 20 + 1);
            RenderMesh(meshes["treeBottom"], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform3D_tema2::Translate(-0.5, 1.53, -0.5);
            RenderMesh(meshes["treeTop"], shaders["VertexColor"], modelMatrix);
            modelMatrixCopy *= transform3D_tema2::Translate(pointsBlue[i].x * 20 - 1, 0, pointsBlue[i].z * 20 - 1);
            RenderMesh(meshes["treeBottom"], shaders["VertexColor"], modelMatrixCopy);
            modelMatrixCopy *= transform3D_tema2::Translate(-0.5, 1.53, -0.5);
            RenderMesh(meshes["treeTop"], shaders["VertexColor"], modelMatrixCopy);
        }
        

    }

    vector<VertexFormat> verticesPath{
          VertexFormat(glm::vec3(pointsRed[34].x, 0.1, pointsRed[34].z), glm::vec3(0.54f, 0.27f, 0.07f)),
          VertexFormat(glm::vec3(pointsBlue[34].x, 0.1, pointsBlue[34].z), glm::vec3(0.54f, 0.27f, 0.07f)),
          VertexFormat(glm::vec3(pointsRed[0].x, 0.1, pointsRed[0].z), glm::vec3(0.54f, 0.27f, 0.07f)),
          VertexFormat(glm::vec3(pointsBlue[0].x, 0.1, pointsBlue[0].z), glm::vec3(0.54f, 0.27f, 0.07f)),

    };

    vector<unsigned int> indicesPath = {
            0,1,3,
            0,2,3,
    };

    meshes["path"] = new Mesh("generated path");
    meshes["path"]->InitFromData(verticesPath, indicesPath);
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D_tema2::Scale(20, 2, 20);
    RenderMesh(meshes["path"], shaders["VertexColor"], modelMatrix);

}



void Ex::FrameStart()
{
    //Sets the blue sky
    glClearColor(0, 0.74, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Ex::Update(float deltaTimeSeconds)
{
    RenderScene();

    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D_tema2::Translate(translateX, translateY, translateZ);
    camera->MoveForward(-translateZ);
    camera->TranslateRight(translateX);

    modelMatrix *= transform3D_tema2::Translate(0, 0.3, 0);
    modelMatrix *= transform3D_tema2::Translate(0.5, 0, 0);
    modelMatrix *= transform3D_tema2::RotateOY(rotation_angle_OY);
    modelMatrix *= transform3D_tema2::Translate(-0.5, 0, 0);

    camera->MoveForward(initialCamOZ);
    camera->RotateFirstPerson_OY(rotation_angle_OY);
    camera->MoveForward(-initialCamOZ);
    RenderMesh(meshes["car"], shaders["VertexColor"], modelMatrix);
    
    //viewport
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    RenderScene();

    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    //ground
    modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D_tema2::Translate(translateX, translateY, translateZ);
    camera->MoveForward(-translateZ);
    camera->TranslateRight(translateX);

    modelMatrix *= transform3D_tema2::Translate(0, 0.3, 0);
    modelMatrix *= transform3D_tema2::Translate(0.5, 0, 0);
    modelMatrix *= transform3D_tema2::RotateOY(rotation_angle_OY);
    modelMatrix *= transform3D_tema2::Translate(-0.5, 0, 0);

    camera->MoveForward(initialCamOZ);
    camera->RotateFirstPerson_OY(rotation_angle_OY);
    camera->MoveForward(-initialCamOZ);
    RenderMesh(meshes["car"], shaders["VertexColor"], modelMatrix);

    
}


void Ex::FrameEnd()
{
    // DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Ex::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Ex::OnInputUpdate(float deltaTime, int mods)
{

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float speed = 8.0f;
        if (window->KeyHold(GLFW_KEY_W)) {
            translateZ -= speed * cos(rotation_angle_OY) * deltaTime;
            translateX -= speed * sin(rotation_angle_OY) * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            if (window->KeyHold(GLFW_KEY_W)) {
                rotation_angle_OY += deltaTime;
            }
            else if (window->KeyHold(GLFW_KEY_S)) {
                rotation_angle_OY -= deltaTime;
            }
            else {
                rotation_angle_OY += deltaTime;
            }
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            translateZ += speed * cos(rotation_angle_OY) * deltaTime;
            translateX += speed * sin(rotation_angle_OY) * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            if (window->KeyHold(GLFW_KEY_W)) {
                rotation_angle_OY -= deltaTime;
            }
            else if (window->KeyHold(GLFW_KEY_S)) {
                rotation_angle_OY += deltaTime;
            }
            else {
                rotation_angle_OY -= deltaTime;
            }
        }

    }

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->MoveForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->MoveForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }
    }



}


void Ex::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }


}


void Ex::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Ex::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);

        }
    }
}


void Ex::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Ex::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Ex::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Ex::OnWindowResize(int width, int height)
{
}
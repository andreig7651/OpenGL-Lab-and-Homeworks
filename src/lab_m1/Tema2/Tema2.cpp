#include "lab_m1/Tema2/Tema2.h"

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


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

    fill_percent1 = 0;
    fill_percent2 = 0;
    copy_fill_percent1 = 0;
    copy_fill_percent2 = 0;
    steps = 30;
    obj_pos1 = { 0,0,0 };
    obj_pos2 = { 0,0,0 };
    copy_obj_pos1 = { 0,0,0 };
    copy_obj_pos2 = { 0,0,0 };
    offset1 = -0.7f;
    copy_offset1 = -0.7f;
    offset2 = 0.0f;
    copy_offset2 = 0.0f;
    start1 = rand() % 17;
    start2 = rand() % 17;
    copy_start1 = start1;
    copy_start2 = start2;


    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,        1, 3, 2,
            2, 3, 7,        2, 7, 6,
            1, 7, 3,        1, 5, 7,
            6, 7, 4,        7, 5, 4,
            0, 4, 1,        1, 4, 5,
            2, 6, 4,        0, 2, 4,
        };

        meshes["cube"] = new Mesh("cube");
        meshes["cube"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0.18, 0.54, 0.12)),
            VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0.18, 0.54, 0.12)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,        1, 3, 2,
            2, 3, 7,        2, 7, 6,
            1, 7, 3,        1, 5, 7,
            6, 7, 4,        7, 5, 4,
            0, 4, 1,        1, 4, 5,
            2, 6, 4,        0, 2, 4,
        };

        meshes["tree1"] = new Mesh("tree1");
        meshes["tree1"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(1, -1,  1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(0.40, 0.26, 0.11)),
            VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0.40, 0.26, 0.11)),
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,        1, 3, 2,
            2, 3, 7,        2, 7, 6,
            1, 7, 3,        1, 5, 7,
            6, 7, 4,        7, 5, 4,
            0, 4, 1,        1, 4, 5,
            2, 6, 4,        0, 2, 4,
        };

        meshes["tree2"] = new Mesh("tree2");
        meshes["tree2"]->InitFromData(vertices, indices);
    }

    camera = new implemented::Camera_tema2();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    // A -> R
    //A
    points[0] = glm::vec3(-148.65, 0, 7.11);
    //B
    points[1] = glm::vec3(-130.91, 0, -10.97);
    //C
    points[2] = glm::vec3(-100.18, 0, -15.44);
    //D
    points[3] = glm::vec3(-74.47, 0, 0);
    //E
    points[4] = glm::vec3(-48.49, 0, -2.26);
    //F
    points[5] = glm::vec3(-26.53, 0, -14.58);
    //G
    points[6] = glm::vec3(3.47, 0, -19.67);
    //H
    points[7] = glm::vec3(29.18, 0, -9.76);
    //I
    points[8] = glm::vec3(42.92, 0, 7.92);
    //J
    points[9] = glm::vec3(40.96, 0, 31.75);
    //K
    points[10] = glm::vec3(20.61, 0, 48.89);
    //L
    points[11] = glm::vec3(-7.25, 0, 56.93);
    //M
    points[12] = glm::vec3(-28.94, 0, 49.7);
    //N
    points[13] = glm::vec3(-57.86, 0, 48.89);
    //O
    points[14] = glm::vec3(-75.27, 0, 59.6);
    //P
    points[15] = glm::vec3(-96.43, 0, 67.91);
    //Q
    points[16] = glm::vec3(-123.48, 0, 60.94);
    //R
    points[17] = glm::vec3(-144.1, 0, 40.32);

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 500), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(500, 0, 500), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(0, 0, 500), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(500, 0, 500), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(500, 0, 0), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.07, 0.79, 0.09)),
            VertexFormat(glm::vec3(500, 0, 0), glm::vec3(0.07, 0.79, 0.09)),

        };

        vector<unsigned int> indices =
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

        meshes["ground"] = new Mesh("ground");
        meshes["ground"]->InitFromData(vertices, indices);
    }

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

}


void Tema2::RenderScene(implemented::Camera_tema2* camera) {

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D_tema2::Translate(-300, -1, -50);
    RenderMesh(meshes["ground"], shaders["VertexColor"], modelMatrix, camera);

    //calculate points for path
    for (int i = 0; i <= 17; i++) {
        if (i != 17) {
            glm::vec3 D = points[i + 1] - points[i];
            glm::vec3 P = cross(D, glm::vec3(0, 1, 0));
            red_points[i] = points[i] + distRed * P;
            blue_points[i] = points[i] - distBlue * P;
            tree_red_points[i] = points[i] + (distRed + 0.3f) * P;
            tree_blue_points[i] = points[i] - (distBlue + 0.3f) * P; 
            car_red_points[i] = points[i] + (distRed - 0.1f) * P;
            car_blue_points[i] = points[i] - (distBlue - 0.1f) * P;
        }
        else {
            glm::vec3 D = points[0] - points[17];
            glm::vec3 P = cross(D, glm::vec3(0, 1, 0));
            red_points[17] = points[17] + distRed * P;
            blue_points[17] = points[17] - distBlue * P;
            tree_red_points[17] = points[17] + (distRed + 0.3f) * P;
            tree_blue_points[17] = points[17] - (distBlue + 0.3f) * P;
            car_red_points[17] = points[17] + (distRed - 0.1f) * P;
            car_blue_points[17] = points[17] - (distBlue - 0.1f) * P;
        }
    }

    for (int i = 0; i <= 17; i++) {
        if (i != 17) {
            vector<VertexFormat> vertices{
              VertexFormat(red_points[i], glm::vec3(0.18, 0.31, 0.34)),
              VertexFormat(blue_points[i], glm::vec3(0.18, 0.31, 0.34)),
              VertexFormat(red_points[i + 1], glm::vec3(0.18, 0.31, 0.34)),
              VertexFormat(blue_points[i + 1], glm::vec3(0.18, 0.31, 0.34)),

            };
            vector<unsigned int> indices = {
                    0,1,3,
                    0,2,3,
            };
            meshes["path"] = new Mesh("path");
            meshes["path"]->InitFromData(vertices, indices);
            modelMatrix = glm::mat4(1);

        }
        else {
            vector<VertexFormat> vertices{
            VertexFormat(red_points[17], glm::vec3(0.18, 0.31, 0.34)),
            VertexFormat(blue_points[17], glm::vec3(0.18, 0.31, 0.34)),
            VertexFormat(red_points[0], glm::vec3(0.18, 0.31, 0.34)),
            VertexFormat(blue_points[0], glm::vec3(0.18, 0.31, 0.34)),

            };

            vector<unsigned int> indices = {
                0,1,3,
                0,2,3,
            };

            meshes["path"] = new Mesh("path");
            meshes["path"]->InitFromData(vertices, indices);
            
        }

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D_tema2::Scale(0.5, 0.5, 0.5);
        modelMatrix *= transform3D_tema2::Translate(-40, 0, -30);
        RenderMesh(meshes["path"], shaders["VertexColor"], modelMatrix, camera);

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D_tema2::Translate((tree_red_points[i].x  - 40) / 2, 0, (tree_red_points[i].z - 30) / 2);
        modelMatrix *= transform3D_tema2::Scale(0.75, 0.75, 0.75);
        modelMatrix *= transform3D_tema2::Translate(0, 2, 0);
        RenderMesh(meshes["tree1"], shaders["VertexColor"], modelMatrix, camera);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D_tema2::Translate((tree_red_points[i].x - 40) / 2, 0, (tree_red_points[i].z - 30) / 2);
        modelMatrix *= transform3D_tema2::Scale(0.25, 1, 0.25);
        RenderMesh(meshes["tree2"], shaders["VertexColor"], modelMatrix, camera);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D_tema2::Translate((tree_blue_points[i].x - 40) / 2, 0, (tree_blue_points[i].z - 30) / 2);
        modelMatrix *= transform3D_tema2::Scale(0.75, 0.75, 0.75);
        modelMatrix *= transform3D_tema2::Translate(0, 2, 0);
        RenderMesh(meshes["tree1"], shaders["VertexColor"], modelMatrix, camera);

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D_tema2::Translate((tree_blue_points[i].x - 40) / 2, 0, (tree_blue_points[i].z - 30) / 2);
        modelMatrix *= transform3D_tema2::Scale(0.25, 1, 0.25);
        RenderMesh(meshes["tree2"], shaders["VertexColor"], modelMatrix, camera);

    }  
}

void Tema2::RenderObstacle(glm::vec3 *obj_pos ,int *ind, glm::vec3 *points, int *fill, int *steps, float *offset, Mesh *mesh, Shader *shader, implemented::Camera_tema2* camera)
{   
    glm::mat4 modelMatrix = glm::mat4(1);
    if (*ind == 17) {
        if (*fill == 0) {
            (*obj_pos).x = (points[17].x - 40) / 2 + *offset;
            (*obj_pos).y = 0;
            (*obj_pos).z = (points[17].z - 30) / 2 + *offset;
        }
        (*fill)++;
        (*obj_pos).x += ((points[0].x - 40) / 2 - (points[17].z - 30) / 2) / *steps;
        (*obj_pos).y = 0;
        (*obj_pos).z += ((points[0].x - 40) / 2 - (points[17].z - 30) / 2) / *steps;

        if (*fill == *steps) {
            *ind = 0;
            *fill = 0;
        }

        modelMatrix *= transform3D_tema2::Translate((*obj_pos).x, 0.2, (*obj_pos).z);
        modelMatrix *= transform3D_tema2::Scale(0.25, 0.25, 0.25);
        RenderMesh(mesh, shader, modelMatrix, camera);

    }
    else {
        if (*fill == 0) {
            (*obj_pos).x = (points[*ind].x - 40) / 2 + *offset;
            (*obj_pos).y = 0;
            (*obj_pos).z = (points[*ind].z - 30) / 2 + *offset;
        }
        (*fill)++;
        (*obj_pos).x += ((points[*ind + 1].x - 40) / 2 - (points[*ind].x - 40) / 2) / *steps;
        (*obj_pos).y = 0;
        (*obj_pos).z += ((points[*ind + 1].z - 30) / 2 - (points[*ind].z - 30) / 2) / *steps;

        if (*fill == *steps) {
            *ind = *ind + 1;
            *fill = 0;
        }

        modelMatrix *= transform3D_tema2::Translate((*obj_pos).x, 0.2, (*obj_pos).z);
        modelMatrix *= transform3D_tema2::Scale(0.25, 0.25, 0.25);
        RenderMesh(mesh, shader, modelMatrix, camera);
    }
}

void Tema2::FrameStart()
{   
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.07, 0.34, 0.79, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    RenderScene(camera);

    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    glm::mat4 modelMatrix2 = glm::mat4(1);
    modelMatrix2 *= transform3D_tema2::Translate(translateX, translateY, translateZ);
    camera->MoveForward(-translateZ);
    camera->TranslateRight(translateX);

    modelMatrix2 *= transform3D_tema2::Translate(0, 0.5, 0);
    modelMatrix2 *= transform3D_tema2::Translate(0.5, 0, 0);
    modelMatrix2 *= transform3D_tema2::RotateOY(rotation_angle_OY);
    modelMatrix2 *= transform3D_tema2::Translate(-0.5, 0, 0);
    modelMatrix2 *= transform3D_tema2::Scale(0.25, 0.25, 0.25);

    camera->MoveForward(3.5f);
    camera->RotateFirstPerson_OY(rotation_angle_OY);
    camera->MoveForward(-3.5f);
    RenderMesh(meshes["cube"], shaders["VertexColor"], modelMatrix2, camera);

    RenderObstacle(&obj_pos1 ,&start1, car_red_points, &fill_percent1, &steps, &offset1, meshes["cube"], shaders["VertexColor"], camera);
    RenderObstacle(&obj_pos2, &start2, car_blue_points, &fill_percent2, &steps, &offset2, meshes["cube"], shaders["VertexColor"], camera);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(1000, 20, miniViewportArea.width, miniViewportArea.height);
    implemented::Camera_tema2* camera2;
    camera2 = new implemented::Camera_tema2();
    camera2->Set(glm::vec3(translateX, 10, translateZ), glm::vec3(translateX, 0, translateZ), glm::vec3(-1, 0, -1));
    RenderScene(camera2);
    
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= transform3D_tema2::Translate(translateX, translateY, translateZ);

    modelMatrix *= transform3D_tema2::Translate(0, 0.5, 0);
    modelMatrix *= transform3D_tema2::Translate(0.5, 0, 0);
    modelMatrix *= transform3D_tema2::RotateOY(rotation_angle_OY);
    modelMatrix *= transform3D_tema2::Translate(-0.5, 0, 0);
    modelMatrix *= transform3D_tema2::Scale(0.25, 0.25, 0.25);

    RenderMesh(meshes["cube"], shaders["VertexColor"], modelMatrix, camera2);

    RenderObstacle(&copy_obj_pos1, &copy_start1, car_red_points, &copy_fill_percent1, &steps, &copy_offset1, meshes["cube"], shaders["VertexColor"], camera2);
    RenderObstacle(&copy_obj_pos2, &copy_start2, car_blue_points, &copy_fill_percent2, &steps, &copy_offset2, meshes["cube"], shaders["VertexColor"], camera2);
    copy_obj_pos1 = obj_pos1;
    copy_obj_pos2 = obj_pos2;
    copy_start1 = start1;
    copy_start2 = start2;
    copy_fill_percent1 = fill_percent1;
    copy_fill_percent2 = fill_percent2;
    copy_offset1 = offset1;
    copy_offset2 = offset2;
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera_tema2* camera)
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


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float speed = 6.0f;
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


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

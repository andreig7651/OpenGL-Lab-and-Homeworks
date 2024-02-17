#include "lab_m1/lab11/lab11.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab11::Lab11()
{
}


Lab11::~Lab11()
{
}


void Lab11::Init()
{
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab11", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab11", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Light & material properties
    {   
        lightPosition2 = glm::vec3(0, 1, 1);
        lightPosition = glm::vec3(0, 1, 1);
        lightDirection = glm::vec3(0, -1, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;

        typeOfLight = 0;
        angleOX = 0.f;
        angleOY = 0.f;
        cutoffAngle = 30.f;
    }
}


void Lab11::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab11::Update(float deltaTimeSeconds)
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 1, 0));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.25, 0.75, 0.75));
    }

    // Render ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix);

    }

    // Render the point light in the scene
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition2);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }
}


void Lab11::FrameEnd()
{
    DrawCoordinateSystem();
}


void Lab11::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light properties
    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

    int light_position2 = glGetUniformLocation(shader->program, "light_position2");
    glUniform3f(light_position2, lightPosition2.x, lightPosition2.y, lightPosition2.z);

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    // TODO(student): Set any other shader uniforms that you need
    GLint type = glGetUniformLocation(shader->program, "type_of_light");
    glUniform1i(type, typeOfLight);

    GLint cut_off_angle = glGetUniformLocation(shader->program, "cut_off_angle");
    glUniform1f(cut_off_angle, cutoffAngle);


    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab11::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control light position using on W, A, S, D, E, Q
        if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;

        if (window->KeyHold(GLFW_KEY_I)) lightPosition2 -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_J)) lightPosition2 -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_K)) lightPosition2 += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_L)) lightPosition2 += right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_U)) lightPosition2 += up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_O)) lightPosition2 -= up * deltaTime * speed;

        // TODO(student): Set any other keys that you might need
        if (window->KeyHold(GLFW_KEY_UP))
        {
            angleOX += deltaTime * speed;
        }
        if (window->KeyHold(GLFW_KEY_DOWN))
        {
            angleOX -= deltaTime * speed;
        }
        if (window->KeyHold(GLFW_KEY_LEFT))
        {
            angleOY += deltaTime * speed;
        }
        if (window->KeyHold(GLFW_KEY_RIGHT))
        {
            angleOY -= deltaTime * speed;
        }

        if (window->KeyHold(GLFW_KEY_R))
        {
            cutoffAngle += deltaTime * ANGLE_SPEEDUP;
            cutoffAngle = cutoffAngle > 360.f ? 360.f : cutoffAngle;
        }
        if (window->KeyHold(GLFW_KEY_T))
        {
            cutoffAngle -= deltaTime * ANGLE_SPEEDUP;
            cutoffAngle = cutoffAngle < 0.f ? 0.f : cutoffAngle;
        }

        glm::mat4 turn = glm::mat4(1);
        turn = glm::rotate(turn, angleOY, glm::vec3(0, 1, 0));
        turn = glm::rotate(turn, angleOX, glm::vec3(1, 0, 0));

        lightDirection = glm::vec3(0, -1, 0);
        lightDirection = glm::vec3(turn * glm::vec4(lightDirection, 0));
    }
}


void Lab11::OnKeyPress(int key, int mods)
{
    // Add key press event

    // TODO(student): Set keys that you might need
    if (key == GLFW_KEY_F)
        typeOfLight = !typeOfLight;

}


void Lab11::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab11::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab11::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab11::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab11::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab11::OnWindowResize(int width, int height)
{
}
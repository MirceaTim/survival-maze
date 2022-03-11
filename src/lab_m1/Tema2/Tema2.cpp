#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

//functii de verificare a directiilor disponibile in crearea labirintului
int checkleft(int x, int y, int m[15][15]) {
    if (y == 1) return 0;
    if (m[x][y - 1] == 1 || m[x - 1][y - 1] == 1 || m[x + 1][y - 1] == 1 || m[x - 1][y - 2] == 1 || m[x][y - 2] == 1 || m[x + 1][y - 2] == 1
        || m[x][y - 1] == 3 || m[x - 1][y - 1] == 3 || m[x + 1][y - 1] == 3 || m[x - 1][y - 2] == 3 || m[x][y - 2] == 3 || m[x + 1][y - 2] == 3) return 0;
    else return 1;
}
int checkright(int x, int y, int m[15][15]) {
    if (y == 13) return 0;
    if (m[x][y + 1] == 1 || m[x - 1][y + 1] == 1 || m[x + 1][y + 1] == 1 || m[x - 1][y + 2] == 1 || m[x][y + 2] == 1 || m[x + 1][y + 2] == 1
        || m[x][y + 1] == 3 || m[x - 1][y + 1] == 3 || m[x + 1][y + 1] == 3 || m[x - 1][y + 2] == 3 || m[x][y + 2] == 3 || m[x + 1][y + 2] == 3) return 0;
    else return 1;
}
int checkdown(int x, int y, int m[15][15]) {
    if (x == 13) return 0;
    if (m[x + 1][y] == 1 || m[x + 1][y - 1] == 1 || m[x + 1][y + 1] == 1 || m[x + 2][y - 1] == 1 || m[x + 2][y] == 1 || m[x + 2][y + 1] == 1
        || m[x + 1][y] == 3 || m[x + 1][y - 1] == 3 || m[x + 1][y + 1] == 3 || m[x + 2][y - 1] == 3 || m[x + 2][y] == 3 || m[x + 2][y + 1] == 3) return 0;
    else return 1;
}
int checkup(int x, int y, int m[15][15]) {
    if (x == 1) return 0;
    if (m[x - 1][y] == 1 || m[x - 1][y - 1] == 1 || m[x - 1][y + 1] == 1 || m[x - 2][y - 1] == 1 || m[x - 2][y] == 1 || m[x - 2][y + 1] == 1
        || m[x - 1][y] == 3 || m[x - 1][y - 1] == 3 || m[x - 1][y + 1] == 3 || m[x - 2][y - 1] == 3 || m[x - 2][y] == 3 || m[x - 2][y + 1] == 3) return 0;
    else return 1;
}

//functia de creare a unui mesh pe baza indicilor si a vertecsilor 
Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    glBindVertexArray(0);
    CheckOpenGLError();
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

//functie pentru ilustrarea unui cub cu o anumita culoare
void Tema2::CreateCube(const char* name, glm::vec3 color) {
    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(1, 0, 1), color),
        VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(1, 0, 0), color),
        VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 1, 0), color),
        VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 1), color),
        VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0, 1, 1), color),
        VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 1, 0), color),
        VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0, 0, 1), color),
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

    Tema2::CreateMesh(name, vertices, indices);
}
void Tema2::Init()
{
    //crearea mesh-urilor necesare
    CreateCube("cube", glm::vec3(1, 1, 0));
    CreateCube("cube2", glm::vec3(0.2, 0.8, 0.2));
    CreateCube("cube3", glm::vec3(0.8, 0.2, 0.2));
    CreateCube("skin", glm::vec3(0.33, 0.31, 0.28));

    FoV = 40.f;
    zNear = 0.01;
    zFar = 200;
    persp = true;
    left = .01f;
    right = 10.f;
    bottom = .01f;
    top = 10.f;
    thirdPerson = true;
    projectile_time = 0;
    angleX = 0;
    angleY = 0;
    xstart = 0;
    ystart = 0;
    injuryTimer = 1;
    health = 100;
    timeLeft = 300;

    projectiles = {};
    enemies = {};


    //algoritmul de creare a labirintului, prin backtracking
    //0 pe o casuta reprezinta un perete, 1 drum liber, 2 pozitia de start, 3 casuta cu inamici
    m[15][15] = {};
    int parentx[15][15] = {};
    int parenty[15][15] = {};
    srand(time(NULL));
    int x, y;
    //pozitia de start aleasa aleator din cateva variante
    xstart = (rand() % 3) + 6;
    ystart = (rand() % 3) + 6;
    x = xstart; y = ystart;
    int x1, y1, ok, checkifstarted = 0, enemyCounter = 1, controlNumber;
    x1 = x; y1 = y;
    m[xstart][ystart] = 1;
    int dir;
    while (1 == 1) {
        enemyCounter++;
        if (enemyCounter % 3 == 0) controlNumber = 3;
        else controlNumber = 1;
        if (x == xstart && y == ystart && checkifstarted == 1) {
            if (!checkleft(xstart, ystart, m) && !checkright(xstart, ystart, m) && !checkup(xstart, ystart, m) && !checkdown(xstart, ystart, m)) {
                break;
            }
        }
        checkifstarted = 1;
        if (!checkleft(x, y, m) && !checkright(x, y, m) && !checkup(x, y, m) && !checkdown(x, y, m)) {
            x1 = x;
            y1 = y;
            x = parentx[x1][y1];
            y = parenty[x1][y1];
        }
        else {
            ok = 0;
            while (ok == 0) {
                dir = rand() % 4;
                if (dir == 2 && checkleft(x, y, m) == 1) {
                    ok = 1;
                    parentx[x][y - 1] = x;
                    parenty[x][y - 1] = y;
                    m[x][y - 1] = controlNumber;
                    y--;
                }
                if (dir == 1 && checkright(x, y, m) == 1) {
                    ok = 1;
                    parentx[x][y + 1] = x;
                    parenty[x][y + 1] = y;
                    m[x][y + 1] = controlNumber;
                    y++;
                }
                if (dir == 0 && checkup(x, y, m) == 1) {
                    ok = 1;
                    parentx[x - 1][y] = x;
                    parenty[x - 1][y] = y;
                    m[x - 1][y] = controlNumber;
                    x--;
                }
                if (dir == 3 && checkdown(x, y, m) == 1) {
                    ok = 1;
                    parentx[x + 1][y] = x;
                    parenty[x + 1][y] = y;
                    m[x + 1][y] = controlNumber;
                    x++;

                }
            }
        }
    }
    //pozitionarea initiala a jucatorului
    m[xstart][ystart] = 2;

    camera = new implemented::Camera();

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            //pozitionarea peretilor
            if (m[i][j] != 1 && m[i][j] != 2 && m[i][j] != 3) {
                m[i][j] = 0;
            }
            //pozitionarea initiala a camerei
            if (m[i][j] == 2) {
                camera->Set(glm::vec3(i + 0.2, 0.2, j + 0.2), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
            }
            //crearea si pozitionarea inamicilor
            if (m[i][j] == 3) {
                Enemy* e1 = new Enemy(i, j, i - 0.41, j - 0.41, 0, 0, 1);
                enemies.push_back(*e1);

                Enemy* e2 = new Enemy(i, j, i - 0.41, j + 0.41, 0, 0, 2);
                enemies.push_back(*e2);

                Enemy* e3 = new Enemy(i, j, i + 0.41, j - 0.41, 0, 0, 3);
                enemies.push_back(*e3);

                Enemy* e4 = new Enemy(i, j, i + 0.41, j + 0.41, 0, 0, 4);
                enemies.push_back(*e4);

            }
        }
        printf("\n");
    }

    //crearea unui numar aleator de iesiri valide din labirint
    int numberOfExits = (rand() % 3) + 1;
    while (numberOfExits) {
        dir = rand() % 4;
        int tile = rand() % 15;
        if (dir == 0) {
            if (m[1][tile] == 1 || m[1][tile] == 3) {
                m[0][tile] = 1;
                numberOfExits--;
            }
        }
        if (dir == 1) {
            if (m[13][tile] == 1 || m[13][tile] == 3) {
                m[14][tile] = 1;
                numberOfExits--;
            }
        }
        if (dir == 2) {
            if (m[tile][1] == 1 || m[tile][1] == 3) {
                m[tile][0] = 1;
                numberOfExits--;
            }
        }
        if (dir == 3) {
            if (m[tile][13] == 1 || m[tile][13] == 3) {
                m[tile][14] = 1;
                numberOfExits--;
            }
        }
    }

    //mesh-uri simple si matricea de proiectie
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
    projectionMatrix = glm::perspective(RADIANS(FoV), window->props.aspectRatio, zNear, zFar);
}

void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    injuryTimer += deltaTimeSeconds;
    timeLeft -= deltaTimeSeconds;
    //daca ramanem fara timp, jocul se incheie
    if (timeLeft <= 0) {
        printf("Time's up! Game over!");
        exit(0);
    }
    //daca am reusit cu succes sa iesim din perimetrul labirintului, jocul se incheie
    if (camera->GetTargetPosition().x < -0.5 || camera->GetTargetPosition().x > 14.5 || camera->GetTargetPosition().z < -0.5 || camera->GetTargetPosition().z > 14.5) {
        printf("Congratulations! You win!");
        exit(0);
    }

    //desenarea podelei
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(7, 0, 7));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(15, 0.1, 15));
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    //desenarea peretilor
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (m[i][j] == 0) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(i, 0.55, j));
                RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
            }
        }
    }
    
    //calcularea traiectoriei si desenarea proiectilelor
    projectile_time += deltaTimeSeconds;
    for (int i = 0; i < projectiles.size(); ++i) {
        if (!projectiles[i].disabled) {
            projectiles[i].time_elapsed += deltaTimeSeconds;
            projectiles[i].projectilePosition += projectiles[i].forward * deltaTimeSeconds * (float) 5.0;
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, projectiles[i].projectilePosition);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f));
            RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
            if (projectiles[i].time_elapsed > 3) {
                projectiles[i].disabled = 1;
            }
        }
    }
    //calcularea traiectoriei si desenarea inamicilor
    for (int i = 0; i < enemies.size(); ++i) {
        if (!enemies[i].disabled) {
            if (enemies[i].xpos < enemies[i].x - 0.4 && enemies[i].ypos < enemies[i].y - 0.4) enemies[i].dir = 1;
            else if (enemies[i].xpos < enemies[i].x - 0.4 && enemies[i].ypos > enemies[i].y + 0.4) enemies[i].dir = 2;
            else if (enemies[i].xpos > enemies[i].x + 0.4 && enemies[i].ypos < enemies[i].y - 0.4) enemies[i].dir = 3;
            else if (enemies[i].xpos > enemies[i].x + 0.4 && enemies[i].ypos > enemies[i].y + 0.4) enemies[i].dir = 4;

            if (enemies[i].dir == 1) enemies[i].ypos += deltaTimeSeconds;
            if (enemies[i].dir == 2) enemies[i].xpos += deltaTimeSeconds;
            if (enemies[i].dir == 3) enemies[i].xpos -= deltaTimeSeconds;
            if (enemies[i].dir == 4) enemies[i].ypos -= deltaTimeSeconds;

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(enemies[i].xpos, 0, enemies[i].ypos));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 1.f, 0.1f));
            
            //inamicii vor avea culori diferite in functie de cate proiectile au incasat
            if (enemies[i].numberHits == 0) RenderMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix);
            else if (enemies[i].numberHits == 1) RenderMesh(meshes["cube"], shaders["VertexNormal"], modelMatrix);
            else if (enemies[i].numberHits == 2) RenderMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix);
        }
    }

    //desenarea elementelor HUD
    //dreptunghi health wireframe
    angleY = angleY - 0.7;
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0.062f, -0.1f, 0.15f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.062f, -0.1f, 0.15f));
    modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(-5), glm::vec3(0, 0, 1));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.062, 0.1f, -0.15f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 0.02f, 0.1f));
    RenderMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix);

    //dreptunghi time wireframe
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0.062f, -0.1f, -0.15f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.062f, -0.1f, -0.15f));
    modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(-5), glm::vec3(0, 0, 1));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.062, 0.1f, 0.15f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 0.02f, 0.1f));
    RenderMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix);

    //dreptunghi time
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0.06f, -0.1f, -0.15f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.06f, -0.1f, -0.15f));
    modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(-5), glm::vec3(0, 0, 1));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.06, 0.1f, 0.15f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 0.02f, timeLeft / 300 * 0.1f));
    RenderMesh(meshes["cube"], shaders["VertexNormal"], modelMatrix);

    //dreptunghi health
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0.06f, -0.1f, 0.15f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.06f, -0.1f, 0.15f));
    modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, RADIANS(-5), glm::vec3(0, 0, 1));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.06, 0.1f, -0.15f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 0.02f, health / 100 * 0.1f));
    RenderMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix);
    angleY = angleY + 0.7;

    if (thirdPerson)
    {
        angleY = angleY - 0.7;

        //desenarea personajului
        //abdomen
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.1f, 0.1f));
        RenderMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix);

        //maini
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0, 0, 0.062f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.062f));
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -0.062f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.1f, 0.02f));
        RenderMesh(meshes["skin"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0, 0, -0.062f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -0.062f));
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.062f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.1f, 0.02f));
        RenderMesh(meshes["skin"], shaders["VertexNormal"], modelMatrix);

        //picioare
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0, 0.07f, 0.03f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.03f));
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -0.03f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.12f, 0.03f));
        RenderMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0, 0.07f, -0.03f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -0.03f));
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0.03f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.12f, 0.03f));
        RenderMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix);

        //cap
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() - glm::vec3(0, -0.07f, 0));
        modelMatrix = glm::rotate(modelMatrix, angleY, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.04f, 0.04f));
        RenderMesh(meshes["skin"], shaders["VertexNormal"], modelMatrix);
        angleY = angleY + 0.7;
    }

    //verificarea coliziunilor dintre proiectile si pereti
    for (int j = 0; j < 15; ++j) {
        for (int k = 0; k < 15; ++k) {
            if (m[j][k] == 0) {
                for (int i = 0; i < projectiles.size(); ++i) {
                    if (!projectiles[i].disabled) {
                        float x = max((float) (j - 0.5), min(projectiles[i].projectilePosition.x, (float) (j + 0.5)));
                        float y = max((float)0.1, min(projectiles[i].projectilePosition.y, (float)1.1));
                        float z = max((float) (k - 0.5), min(projectiles[i].projectilePosition.z, (float) (k + 0.5)));
                        float dist = sqrt((x - projectiles[i].projectilePosition.x) * (x - projectiles[i].projectilePosition.x) +
                            (y - projectiles[i].projectilePosition.y) * (y - projectiles[i].projectilePosition.y) +
                            (z - projectiles[i].projectilePosition.z) * (z - projectiles[i].projectilePosition.z));
                       
                        if (dist < 0.032) {
                            projectiles[i].disabled = 1;
                        }
                    }
                }
            }
        }
    }
    glm::vec3 corner1 = camera->GetTargetPosition() + glm::vec3(0.026f * cos(angleY - 0.7) - 0.073f * sin(angleY - 0.7), 0.05f, 0.026f * sin(angleY - 0.7) + 0.073f * cos(angleY - 0.7));
    glm::vec3 corner2 = camera->GetTargetPosition() + glm::vec3(0.026f * cos(angleY - 0.7) + 0.073f * sin(angleY - 0.7), 0.05f, 0.026f * sin(angleY - 0.7) - 0.073f * cos(angleY - 0.7));
    glm::vec3 corner3 = camera->GetTargetPosition() + glm::vec3(-0.026f * cos(angleY - 0.7) - 0.073f * sin(angleY - 0.7), 0.05f, -0.026f * sin(angleY - 0.7) + 0.073f * cos(angleY - 0.7));
    glm::vec3 corner4 = camera->GetTargetPosition() + glm::vec3(-0.026f * cos(angleY - 0.7) + 0.073f * sin(angleY - 0.7), 0.05f, -0.026f * sin(angleY - 0.7) - 0.073f * cos(angleY - 0.7));

    for (int i = 0; i < enemies.size(); ++i) {
        if (!enemies[i].disabled) {
            for (int j = 0; j < projectiles.size(); ++j) {
                if (!projectiles[j].disabled) {
                    //verificarea coliziunilor dintre proiectile si inamici
                    float x = max(enemies[i].xpos, min(projectiles[j].projectilePosition.x, (float)(enemies[i].xpos + 0.1)));
                    float y = max((float)0.1, min(projectiles[j].projectilePosition.y, (float)1.1));
                    float z = max(enemies[i].ypos, min(projectiles[j].projectilePosition.z, (float)(enemies[i].ypos + 0.1)));
                    float dist = sqrt((x - projectiles[j].projectilePosition.x) * (x - projectiles[j].projectilePosition.x) +
                        (y - projectiles[j].projectilePosition.y) * (y - projectiles[j].projectilePosition.y) +
                        (z - projectiles[j].projectilePosition.z) * (z - projectiles[j].projectilePosition.z));
                    if (dist < 0.032) {
                        projectiles[j].disabled = 1;
                        enemies[i].numberHits++;
                    }
                    if (enemies[i].numberHits == 3) {
                        enemies[i].disabled = 1;
                    }
                }
            }
            //verificarea coliziunilor dintre jucator si inamici
            if ((corner1.x >= enemies[i].xpos && corner1.x <= enemies[i].xpos + 0.1 && corner1.z >= enemies[i].ypos && corner1.z <= enemies[i].ypos + 0.1) ||
                (corner2.x >= enemies[i].xpos && corner2.x <= enemies[i].xpos + 0.1 && corner2.z >= enemies[i].ypos && corner2.z <= enemies[i].ypos + 0.1) ||
                (corner3.x >= enemies[i].xpos && corner3.x <= enemies[i].xpos + 0.1 && corner3.z >= enemies[i].ypos && corner3.z <= enemies[i].ypos + 0.1) ||
                (corner4.x >= enemies[i].xpos && corner4.x <= enemies[i].xpos + 0.1 && corner4.z >= enemies[i].ypos && corner4.z <= enemies[i].ypos + 0.1))
            {
                if (injuryTimer > 1) {
                    health -= 20;
                    injuryTimer = 0;
                }
                if (health == 0) {
                    printf("You died! Game over!\n");
                    exit(0);
                }
            }
        }
    }
}

void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    mesh->Render();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
        //viteza de miscare
        float cameraSpeed = 0.3f;
        //se calculeaza pozitiile colturilor abdomenului jucatorului
        glm::vec3 corner1 = camera->GetTargetPosition() + glm::vec3(0.026f * cos(angleY - 0.7) - 0.073f * sin(angleY - 0.7), 0.05f, 0.026f * sin(angleY - 0.7) + 0.073f * cos(angleY - 0.7));
        glm::vec3 corner2 = camera->GetTargetPosition() + glm::vec3(0.026f * cos(angleY - 0.7) + 0.073f * sin(angleY - 0.7), 0.05f, 0.026f * sin(angleY - 0.7) - 0.073f * cos(angleY - 0.7));
        glm::vec3 corner3 = camera->GetTargetPosition() + glm::vec3(-0.026f * cos(angleY - 0.7) - 0.073f * sin(angleY - 0.7), 0.05f, -0.026f * sin(angleY - 0.7) + 0.073f * cos(angleY - 0.7));
        glm::vec3 corner4 = camera->GetTargetPosition() + glm::vec3(-0.026f * cos(angleY - 0.7) + 0.073f * sin(angleY - 0.7), 0.05f, -0.026f * sin(angleY - 0.7) - 0.073f * cos(angleY - 0.7));
        //se verifica o posibila coliziune cu peretele la miscarea in fata, in caz contrar executandu-se miscarea
        if (window->KeyHold(GLFW_KEY_W)) {
            int okup = 1;
            corner1 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * cameraSpeed * deltaTime;
            corner2 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * cameraSpeed * deltaTime;
            corner3 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * cameraSpeed * deltaTime;
            corner4 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * cameraSpeed * deltaTime;
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (m[i][j] == 0) {
                        if ((corner1.x >= (i - 0.5) && corner1.x <= (i + 0.5) && corner1.z >= (j - 0.5) && corner1.z <= (j + 0.5)) ||
                            (corner2.x >= (i - 0.5) && corner2.x <= (i + 0.5) && corner2.z >= (j - 0.5) && corner2.z <= (j + 0.5)) ||
                            (corner3.x >= (i - 0.5) && corner3.x <= (i + 0.5) && corner3.z >= (j - 0.5) && corner3.z <= (j + 0.5)) ||
                            (corner4.x >= (i - 0.5) && corner4.x <= (i + 0.5) && corner4.z >= (j - 0.5) && corner4.z <= (j + 0.5))) {
                            okup = 0;
                        }
                    }
                }
            }
            if (okup == 1) {
                camera->MoveForward(cameraSpeed * deltaTime);
            }
        }
        //se verifica o posibila coliziune cu peretele la miscarea in stanga, in caz contrar executandu-se miscarea
        if (window->KeyHold(GLFW_KEY_A)) {
            int okst = 1;
            corner1 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * -cameraSpeed * deltaTime;
            corner2 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * -cameraSpeed * deltaTime;
            corner3 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * -cameraSpeed * deltaTime;
            corner4 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * -cameraSpeed * deltaTime;
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (m[i][j] == 0) {
                        if ((corner1.x >= (i - 0.5) && corner1.x <= (i + 0.5) && corner1.z >= (j - 0.5) && corner1.z <= (j + 0.5)) ||
                            (corner2.x >= (i - 0.5) && corner2.x <= (i + 0.5) && corner2.z >= (j - 0.5) && corner2.z <= (j + 0.5)) ||
                            (corner3.x >= (i - 0.5) && corner3.x <= (i + 0.5) && corner3.z >= (j - 0.5) && corner3.z <= (j + 0.5)) ||
                            (corner4.x >= (i - 0.5) && corner4.x <= (i + 0.5) && corner4.z >= (j - 0.5) && corner4.z <= (j + 0.5))) {
                            okst = 0;
                        }
                    }
                }
            }
            if (okst == 1) {
                camera->MoveRight(-cameraSpeed * deltaTime);
            }
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            //se verifica o posibila coliziune cu peretele la miscarea in spate, in caz contrar executandu-se miscarea
            int okdown = 1;
            corner1 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * -cameraSpeed * deltaTime;
            corner2 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * -cameraSpeed * deltaTime;
            corner3 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * -cameraSpeed * deltaTime;
            corner4 += glm::normalize(glm::vec3(camera->forward.x, 0, camera->forward.z)) * -cameraSpeed * deltaTime;
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (m[i][j] == 0) {
                        if ((corner1.x >= (i - 0.5) && corner1.x <= (i + 0.5) && corner1.z >= (j - 0.5) && corner1.z <= (j + 0.5)) ||
                            (corner2.x >= (i - 0.5) && corner2.x <= (i + 0.5) && corner2.z >= (j - 0.5) && corner2.z <= (j + 0.5)) ||
                            (corner3.x >= (i - 0.5) && corner3.x <= (i + 0.5) && corner3.z >= (j - 0.5) && corner3.z <= (j + 0.5)) ||
                            (corner4.x >= (i - 0.5) && corner4.x <= (i + 0.5) && corner4.z >= (j - 0.5) && corner4.z <= (j + 0.5))) {
                            okdown = 0;
                        }
                    }
                }
            }
            if (okdown == 1) {
                camera->MoveForward(-cameraSpeed * deltaTime);
            }
        }
        //se verifica o posibila coliziune cu peretele la miscarea in dreapta, in caz contrar executandu-se miscarea
        if (window->KeyHold(GLFW_KEY_D)) {
            int okdr = 1;
            corner1 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * cameraSpeed * deltaTime;
            corner2 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * cameraSpeed * deltaTime;
            corner3 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * cameraSpeed * deltaTime;
            corner4 += glm::normalize(glm::vec3(camera->right.x, 0, camera->right.z)) * cameraSpeed * deltaTime;
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (m[i][j] == 0) {
                        if ((corner1.x >= (i - 0.5) && corner1.x <= (i + 0.5) && corner1.z >= (j - 0.5) && corner1.z <= (j + 0.5)) ||
                            (corner2.x >= (i - 0.5) && corner2.x <= (i + 0.5) && corner2.z >= (j - 0.5) && corner2.z <= (j + 0.5)) ||
                            (corner3.x >= (i - 0.5) && corner3.x <= (i + 0.5) && corner3.z >= (j - 0.5) && corner3.z <= (j + 0.5)) ||
                            (corner4.x >= (i - 0.5) && corner4.x <= (i + 0.5) && corner4.z >= (j - 0.5) && corner4.z <= (j + 0.5))) {
                            okdr = 0;
                        }
                    }
                }
            }
            if (okdr == 1) {
                camera->MoveRight(cameraSpeed * deltaTime);
            }
        }
}

void Tema2::OnKeyPress(int key, int mods)
{
    //prin tasta CTRL, modificam punctul de vedere al camerei
    if (key == GLFW_KEY_LEFT_CONTROL)
    {
        //se intra in modul atac first-person, si se aduce camera la nivelul player-ului
        if (thirdPerson) {
            thirdPerson = 0;
            camera->position = camera->GetTargetPosition();
            camera->firstPerson = 1;
        }
        //se intra in modul third-person, si se retrage camera
        else if (!thirdPerson) {
            camera->RotateFirstPerson_OX(-angleX);
            thirdPerson = 1;
            camera->position = camera->ReturnCamera();
            camera->firstPerson = 0;
            angleX = 0;
        }
    }
    //prin apasarea tastei SPACE, se lanseaza un proiectil
    if (key == GLFW_KEY_SPACE)
    {
        if (!thirdPerson) {
            if (projectile_time > 0.5) {
                Projectile* p = new Projectile(0, camera->forward, camera->position, 0);
                projectiles.push_back(*p);
                projectile_time = 0;
            }
        }
    }

}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    //rotatia camerei, pentru a fi rotita camera, trebuie tinut apasat pe click dreapta
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        //sensitivitatea mouse-ului
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;
        //miscarea camerei in first person
        if (!thirdPerson) {
            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
            angleY += -deltaX * sensivityOY;
            angleX += -deltaY * sensivityOX;
        }
        //in third person, se verifica daca prin miscarea mouse-ului, jucatorul intra in coliziune cu peretii
        if (thirdPerson) {
            glm::vec3 corner1 = camera->GetTargetPosition() + glm::vec3(0.026f * cos(angleY - 0.7) - 0.073f * sin(angleY - 0.7), 0.05f, 0.026f * sin(angleY - 0.7) + 0.073f * cos(angleY - 0.7));
            glm::vec3 corner2 = camera->GetTargetPosition() + glm::vec3(0.026f * cos(angleY - 0.7) + 0.073f * sin(angleY - 0.7), 0.05f, 0.026f * sin(angleY - 0.7) - 0.073f * cos(angleY - 0.7));
            glm::vec3 corner3 = camera->GetTargetPosition() + glm::vec3(-0.026f * cos(angleY - 0.7) - 0.073f * sin(angleY - 0.7), 0.05f, -0.026f * sin(angleY - 0.7) + 0.073f * cos(angleY - 0.7));
            glm::vec3 corner4 = camera->GetTargetPosition() + glm::vec3(-0.026f * cos(angleY - 0.7) + 0.073f * sin(angleY - 0.7), 0.05f, -0.026f * sin(angleY - 0.7) - 0.073f * cos(angleY - 0.7));
            int ok = 1;
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (m[i][j] == 0) {
                        if ((corner1.x >= (i - 0.5) && corner1.x <= (i + 0.5) && corner1.z >= (j - 0.5) && corner1.z <= (j + 0.5)) ||
                            (corner2.x >= (i - 0.5) && corner2.x <= (i + 0.5) && corner2.z >= (j - 0.5) && corner2.z <= (j + 0.5)) ||
                            (corner3.x >= (i - 0.5) && corner3.x <= (i + 0.5) && corner3.z >= (j - 0.5) && corner3.z <= (j + 0.5)) ||
                            (corner4.x >= (i - 0.5) && corner4.x <= (i + 0.5) && corner4.z >= (j - 0.5) && corner4.z <= (j + 0.5))) {
                            ok = 0;
                        }
                    }
                }
            }
            //daca nu, se roteste camera
            if (ok == 1) {
                camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
                angleY += -deltaX * sensivityOY;
            }
            //se verifica daca intra camera in pereti
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (m[i][j] == 0) {
                        if ((camera->GetCameraPosition().x >= (i - 0.5) && camera->GetCameraPosition().x <= (i + 0.5)) && (camera->GetCameraPosition().z >= (j - 0.5) && camera->GetCameraPosition().z <= (j + 0.5))) {
                            camera->RotateThirdPerson_OY(deltaX * sensivityOY);
                            angleY += deltaX * sensivityOY;
                        }
                    }
                }
            }
        }
    }
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
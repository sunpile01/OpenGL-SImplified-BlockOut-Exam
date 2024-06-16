/**
* @file AssignmentApplication.cpp
* @author Aleklsander Solhaug
*/

#include "BlockOutApplication.h"
#include <iostream>
#include <Camera.h>
#include <PerspectiveCamera.h>
#include <OrtographicCamera.h>
#include <Shader.h>
#include <RenderCommands.h>
#include <GeometricTools.h>
#include "Shader.cpp"
#include <TextureManager.h>
#include "KeyboardInput.cpp"

/**
* @brief Constructor that passes the name and version to GLFWApplication
* 
* @param name - Name of the application
* @param version - Current version of the application
* @see GLFWApplication::GLFWApplication(...)
*/
Assignment::Assignment(const std::string name, const std::string version) 
                                             :  GLFWApplication(name, version){}

/**
* @brief Destructor that closes the application
* @see  GLFWApplication::~GLFWApplication()
*/
Assignment::~Assignment() { GLFWApplication::~GLFWApplication(); }

/**
* @brief Parses the command line arguments so they are available in the code
* @see GLFWApplication::ParseArguments(...)
*/
unsigned int Assignment::ParseArguments(int argc, char** argv) {
    GLFWApplication::ParseArguments(argc, argv);
    return 0;
}

/**
* @brief Initializes the application
* @see GLFWApplication::Init()
*/
unsigned Assignment::Init() {
    GLFWApplication::Init();
    return 0;
}

/**
* @brief Creates a new cube with the initial position
* 
* @param translationVectors - vector with the position of all the cubes
* @param numObjects - Number of placed cubes + the active cube in the game
* @param modeMatrices - Model matrices of all the cubes
* @param cubeScale - Scaling of the cube
* @param cubeRotation - Rotation of the cube
* @param initTranslation - Startposition for the new cube
* @param translationMatrices - All the translation matrices
*/
void createNewCube(std::vector <glm::vec3>& translationVectors, int& numObjects, 
     std::vector <glm::mat4>& modelMatrices, const glm::mat4& cubeScale, 
     const glm::mat4& cubeRotation, const glm::vec3 initTranslation, 
                                    std::vector <glm::mat4>& translationMatrices) {
    numObjects++;
    glm::vec3 newTranslationVector = initTranslation;
    translationVectors.push_back(initTranslation);
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translationVectors[numObjects-1]);
    translationMatrices.push_back(translationMatrix);
    modelMatrices.push_back(cubeScale * cubeRotation * translationMatrices[numObjects - 1]);
}

/**
* @brief Sets a unique color for each section of the tunnel
* 
* @param translationVector - The location of the cube to be drawn
* @param numObjects - Number of placed cubes + the active cube in the game
* @param colors - Array with all the different section colors
* 
* @return glm::vec4 - Vector with the color for the cube
*/
glm::vec4 setLevelColor(const glm::vec3 translationVector, const int numObjects, const glm::vec4 colors[]) {
    int indexColor = 0;
    float sectionSize = 1.0f / 10.0f;
    bool sectionFound = false;
    float currentSection = -0.5f;                           //Starts at the end of the tunnel
    float nextSection = currentSection + sectionSize;
    while (!sectionFound){      //translationvector.z will always be between to "sections"  
        // if correct section is found
        if (translationVector.z > currentSection && translationVector.z < nextSection) {
            return colors[indexColor];                      //return the unique color  
        }
        indexColor++;                                       //increase color index
        currentSection += sectionSize;                      //move one section up
        nextSection += sectionSize;
    }
}

/**
* @brief Creates everything that you can visibly see within the application
*/
unsigned Assignment::Run() const {
    //Size of the walls
    glm::vec2 tunnelWallsSize{ 5, 10 };
    glm::vec2 endWallSize{ 5, 5 };
    
    //Creating the geometry for all the walls
    auto tunnelWall = GeometricTools::UnitGridGeometry2DWTCoords(tunnelWallsSize.x, tunnelWallsSize.y);
    auto tunnelWallTopology = GeometricTools::UnitGridTopologyTriangles(tunnelWallsSize.x, tunnelWallsSize.y);

    auto endWall = GeometricTools::UnitGridGeometry2DWTCoords(endWallSize.x, endWallSize.y);
    auto endWallTopology = GeometricTools::UnitGridTopologyTriangles(endWallSize.x, endWallSize.y);

    auto cube = GeometricTools::UnitCube3D24WNormals;
    auto cubeTopology = GeometricTools::UnitCube3DTopologyTriangles24;
    //This cube is for the moving light
    auto cube1 = GeometricTools::UnitCube3D;
    auto cubeTopology1 = GeometricTools::UnitCubeTopology;

    //Sizing down the cubes
    for (int i = 0; i < cube.size(); i++)
        cube[i] /= 10;

    //Creating the buffers and the vertexArray for the cube, and binding the buffers to the vertexArray 
    auto cubeIndexBuffer = std::make_shared<IndexBuffer>(cubeTopology.data(),
        cubeTopology.size());
    auto cubeBufferLayout = BufferLayout({ {ShaderDataType::Float3, "cubePosition"},
                                            {ShaderDataType::Float3, "cubeNormal"} });
    auto cubeVertexBuffer = std::make_shared<VertexBuffer>(cube.data(),
                                                           cube.size() * sizeof(cube[0]));
    cubeVertexBuffer->SetLayout(cubeBufferLayout);
    auto cubeVertexArray = std::make_shared<VertexArray>();
    cubeVertexArray->AddVertexBuffer(cubeVertexBuffer, cubeBufferLayout);
    cubeVertexArray->SetIndexBuffer(cubeIndexBuffer);
    cubeVertexArray->Unbind();

    //Creating the buffers and the vertexArray for the tunnel walls, and binding the buffers to the vertexArray 
    auto tunnelWallIndexBuffer = std::make_shared<IndexBuffer>(tunnelWallTopology.data(),
        tunnelWallTopology.size());
    auto tunnelWallBufferLayout = BufferLayout({ {ShaderDataType::Float2, "tunnelWall1Position"},
                                                            {ShaderDataType::Float2, "tunnelWall1TextureCords"} });
    auto tunnelWallVertexBuffer = std::make_shared<VertexBuffer>(tunnelWall.data(),
                                                            tunnelWall.size() * sizeof(tunnelWall[0]));
    tunnelWallVertexBuffer->SetLayout(tunnelWallBufferLayout);
    auto tunnelWallvertexArray = std::make_shared<VertexArray>();
    tunnelWallvertexArray->AddVertexBuffer(tunnelWallVertexBuffer, tunnelWallBufferLayout);
    tunnelWallvertexArray->SetIndexBuffer(tunnelWallIndexBuffer);
    tunnelWallvertexArray->Unbind();

    //Creating the buffers and the vertexArray for the end walls, and binding the buffers to the vertexArray 
    auto endWallIndexBuffer1 = std::make_shared<IndexBuffer>(endWallTopology.data(), endWallTopology.size());
    auto endWallBufferLayout1 = BufferLayout({ {ShaderDataType::Float2, "endWall1Position"},
                                                                {ShaderDataType::Float2, "endWallTextureCords"} });
    auto endWallVertexBuffer1 = std::make_shared<VertexBuffer>(endWall.data(),
                                                            endWall.size() * sizeof(endWall[0]));
    endWallVertexBuffer1->SetLayout(endWallBufferLayout1);
    auto endWallvertexArray = std::make_shared<VertexArray>();
    endWallvertexArray->AddVertexBuffer(endWallVertexBuffer1, endWallBufferLayout1);
    endWallvertexArray->SetIndexBuffer(endWallIndexBuffer1);
    endWallvertexArray->Unbind();

    //Creating all the shaders
    auto tunnelWallShader = std::make_shared<Shader>(tunnelWallVertexShaderSrc.c_str(), tunnelWallFragmentShaderSrc.c_str());
    auto endWallShader = std::make_shared<Shader>(endWallVertexShaderSrc.c_str(), endWallFragmentShaderSrc.c_str());
    auto cubeShader = std::make_shared<Shader>(cubeVertexShaderSrc.c_str(), cubeFragmentShaderSrc.c_str());
    
    //Colors for the walls and cubes
    glm::vec4 squareColorA = { 1.0f, 1.0f, 1.0f, 1.0f };
    glm::vec4 squareColorB = { 0.0f, 0.0f, 0.0f, 1.0f };
    glm::vec4 cubeColorA = { 1.0f, 0.0f, 0.0f, 1.0f };
    glm::vec4 cubeColorB = { 0.0f, 0.0f, 1.0f, 0.4f };
    glm::vec4 cubeColorC = { 0.0f, 1.0f, 0.0f, 1.0f };
    glm::vec4 cubeColors[8]{ {0.8f, 0.7f, 0.3f, 1.0f},
                             {0.0f, 1.0f, 0.0f, 1.0f},
                             {0.5f, 0.5f, 0.5f, 1.0f},
                             {1.0f, 0.0f, 1.0f, 1.0f},
                             {1.0f / 5.0f, 4.0f / 5.0f, 4.0f / 5.0f, 1.0f},
                             {0.0f, 0.0f, 0.0f, 1.0f},
                             {51.0f / 255.0f, 0.0f, 25.0f / 255.0f, 1.0f},
                             {1.0f, 165.0f / 255.0f, 0.0f, 1.0f}, };
    //Setting light properties that will not change during runtime
    glm::vec4 lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    float ambientStrengthCube = 4.0f;    //High to highlight the different section colors
    float ambientStrengthWalls = 0.695f;
    float specularStrength = 0.5f;
    float diffuseStrengthWall = 0.65f;
    float diffuseStrengthCube = 0.5f;

    //Uploading variables that wont change during runtime to the tunnelWall shader
    tunnelWallShader->setUniformFloat2("u_gridSize", tunnelWallsSize);
    tunnelWallShader->SetUniform4fVector("u_colorA", squareColorA);
    tunnelWallShader->SetUniform4fVector("u_colorB", squareColorB);
    tunnelWallShader->setUniformFloat("u_specularStrength", specularStrength);
    tunnelWallShader->SetUniform4fVector("u_lightColor", lightColor);
    tunnelWallShader->setUniformFloat("u_ambientStrength", ambientStrengthWalls);
    tunnelWallShader->setUniformFloat("u_diffuseStrength", diffuseStrengthWall);

    //Uploading variables that wont change during runtime to the endWall shader
    endWallShader->setUniformFloat2("u_gridSize", endWallSize);
    endWallShader->SetUniform4fVector("u_colorA", squareColorA);
    endWallShader->SetUniform4fVector("u_colorB", squareColorB);
    endWallShader->setUniformFloat("u_specularStrength", specularStrength);
    endWallShader->SetUniform4fVector("u_lightColor", lightColor);
    endWallShader->setUniformFloat("u_ambientStrength", ambientStrengthWalls);
    endWallShader->setUniformFloat("u_diffuseStrength", diffuseStrengthWall);

    //Uploading variables that wont change during runtime to the cube shader
    cubeShader->SetUniform4fVector("u_color", cubeColorA);
    cubeShader->setUniformFloat("u_specularStrength", specularStrength);
    cubeShader->SetUniform4fVector("u_lightColor", lightColor);
    cubeShader->setUniformFloat("u_ambientStrength", ambientStrengthCube);
    cubeShader->setUniformFloat("u_diffuseStrength", diffuseStrengthCube);

    //Get the view and projection matrices and uplaod the projection to the shaders
    //Since it wont change during runtime
    PerspectiveCamera* camera2 = new PerspectiveCamera
                                        (GLFWApplication::m_width, GLFWApplication::m_height, { 0.0f, 2.0f, 12.0f });
    glm::vec3 cameraPosition = camera2->GetPosition();
    glm::mat4 projMatrix = camera2->GetProjectionMatrix();
    glm::mat4 viewMatrix = camera2->GetViewMatrix();
    tunnelWallShader->SetUniformMatrix4fv("u_projMatrix", projMatrix);
    tunnelWallShader->setUniform3fVector("u_cameraPosition", cameraPosition);
    endWallShader->SetUniformMatrix4fv("u_projMatrix", projMatrix);
    endWallShader->setUniform3fVector("u_cameraPosition", cameraPosition);
    cubeShader->SetUniformMatrix4fv("u_projMatrix", projMatrix);
    cubeShader->setUniform3fVector("u_cameraPosition", cameraPosition);

    //Sett bindings for textures so they can be used by shaders
    //Wall texture image was retrieved from:
    //PNG Designed By CHENXIN from https://pngtree.com/freepng/wall-texture_945927.html?sol=downref&id=bef
    //Cube texture designed by MartinStr from https://pixabay.com/photos/bubbles-water-bubbly-bubbling-230014/
    TextureManager* textures = TextureManager::GetInstance();
    textures->LoadTexture2DRGBA("chessBoardTexture",
        std::string(TEXTURE_DIR) + std::string("wallTexture.png"), 0);
    textures->LoadCubeMapRGBA("cubeTexture",
        std::string(TEXTURE_DIR) + std::string("water_texture.png"), 1);


    //Struct with the properties needed for the model matrix
    struct tunnelMatrixProperties {
        glm::mat4 Rotation = glm::mat4(1.0f);
        glm::mat4 Translation = glm::mat4(1.0f);
        glm::mat4 Scale = glm::mat4(1.0f);
    };

    tunnelMatrixProperties tunnelMatrixes[4];  //the properties for each tunnel wall        
    glm::mat4 modelTunnelWall[4];              //1 model matrix for each of the four tunnel walls
    float rotation = 90.0f;                    //Rotation for all the walls   
    float offsetY = 0.0f;                      //Correct y offset for the walls
    for (int i = 0; i < 4; i++)               //Initializing the matrices to the identity matrix
        modelTunnelWall[i] = glm::mat4(1.0f);
    glm::mat4 idMatrix = glm::mat4(1.0f);

    //Giving each tunnel wall the correct rotation around the correct axis to form a tunnel
    tunnelMatrixes[0].Rotation = glm::rotate(idMatrix,glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
    tunnelMatrixes[1].Rotation = glm::rotate(idMatrix,glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    tunnelMatrixes[1].Rotation *= glm::rotate(idMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    tunnelMatrixes[2].Rotation = glm::rotate(idMatrix,glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
    tunnelMatrixes[3].Rotation = glm::rotate(idMatrix,glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    tunnelMatrixes[3].Rotation *= glm::rotate(idMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    for (int i = 0; i < 4; i++) {                                           
        if (i == 0 || i == 2)                                                                        //Top and bottom walls
            tunnelMatrixes[i].Translation = glm::translate(idMatrix, glm::vec3(0.0f, 0.0f, -offsetY));
        else if(i ==1)                                                                               //right wall
            tunnelMatrixes[i].Translation = glm::translate(idMatrix, glm::vec3(0.5f, 0.0f, 0.5f));   //y z x
        else                                                                                         //left wall
            tunnelMatrixes[i].Translation = glm::translate(idMatrix, glm::vec3(0.5f, 0.0f, -0.5f));  //y z x

        tunnelMatrixes[i].Scale = glm::scale(idMatrix, glm::vec3(4.0f, 4.0f, 12.0f));                //scale for each wall
        //Calculating the modelMatrix for each wall
        modelTunnelWall[i] = tunnelMatrixes[i].Scale * tunnelMatrixes[i].Rotation * tunnelMatrixes[i].Translation;
        offsetY += (i == 2) ? -0.5f : 0.5f;
    }

    float centerOffsetZ = 1.0f / 20.0f;         //Offset so cube it is not in the middle of two squares
    float nextSquareZ = 1.0f / 10.0f;           //Offset to the next square in z direction
    float centerOffsetY = 1.0f / 20.0f;         //Same as first

    //Calculating model matrix for end wall and sending it to its shader
    auto endWallModelMatrix = glm::mat4(1.0f);
    auto endWallRotation = glm::rotate(endWallModelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    auto endWallTranslation = glm::translate(endWallModelMatrix, glm::vec3(0.5f, 0.0f, -0.5f));
    auto endWallScale = glm::scale(endWallModelMatrix, glm::vec3(4.0f, 4.0f, 12.0f));
    endWallModelMatrix = endWallScale * endWallRotation * endWallTranslation;
    endWallShader->SetUniformMatrix4fv("u_modelMatrix", endWallModelMatrix);

    //Vectors where new properties for the modelMatrix will be sent for each new cube
    std::vector <glm::vec3> translationVectors;
    std::vector <glm::mat4> translationMatrices;
    std::vector <glm::mat4> modelMatrices;
    //Translating to the starting point for all new cubes
    glm::vec3 initTranslation = glm::vec3(0.0f, centerOffsetY, 0.5f  - centerOffsetZ);
    translationVectors.push_back(initTranslation);

    auto cubeModelMatrix = glm::mat4(1.0f);
    auto cubeRotation = glm::rotate(cubeModelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //Because we have scaled the x y and z differently, the z value for the cubes vertex normals
    //Need to be scaled in proportion to the x and y values so 3/2, this is done in geometricTools.h
    auto cubeScale = glm::scale(cubeModelMatrix, glm::vec3(8.0f, 8.0f, 12.0f));
    //offset from being in the middle of two squares to being in one single square
    auto cubeTranslation = glm::translate(cubeModelMatrix, glm::vec3(initTranslation)); 
    //Pushback the properties of the first cube to the vectors.
    translationMatrices.push_back(cubeTranslation);
    cubeModelMatrix = cubeScale * cubeRotation * cubeTranslation;
    modelMatrices.push_back(cubeModelMatrix);


    RenderCommands::SetSolidMode();
    glEnable(GL_DEPTH_TEST);                   //Discard non visible fragments
    glEnable(GL_BLEND);                        //Needed when lighting is not in place 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //clear color
    glm::vec4 gray = { 20.0f / 255.0f, 20.0f / 255.0f, 20.0f / 255.0f, 1.0f };
    glm::vec3 normalVTunnelWall[4];       //vertex normals for lighting 
    //Must be the same relation as they are scaled x and y is 4 z is 12 therefore z = 3x for vertex normals
    normalVTunnelWall[0] = { 0.0f, 1.0f, -3.0f };    
    normalVTunnelWall[1] = { 0.0f, 1.0f, -3.0f };
    normalVTunnelWall[2] = { 0.0f, 1.0f, 3.0f };
    normalVTunnelWall[3] = { 0.0f, 1.0f, 3.0f };
    glm::vec3 normalEndWall = { 0.0f, 0.0f, -3.0f }; 
   
    float lastTime = 0.0f;
    float dt = 0.0f;                     //time since last frame
    float currentTime = 0.0f; 
    float rotation1 = 0.0f;
    float timer = 0.0f;                 //Used to move block down after set time    
    float translationVectorZ = 0.0f;
    int setLight = 0;
    int numObjects = 1.0;
    int setTextures = 0;
    int posOrNeg = 1;
    int posOrNeg2 = 1;
    int posOrNeg3 = 1;
    int u_invertLight = 0;
    bool keyPressed = false;
    bool newCube = false;
    bool cubeMoved = false;
    glm::vec3 lightSourcePos = { 0.0f, 2.0f, 8.0f };
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 1);                     //Makes broder lines thicker
    RenderCommands::SetClearColor(gray);
    while (!glfwWindowShouldClose(GLFWApplication::m_window))
    {
        //Calculate time since last frame and add it to timer
        currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;
        timer += dt;
        glfwPollEvents();
        RenderCommands::Clear();
        //sets the viewMatrix for this frame
        glm::mat4 viewMatrix = camera2->GetViewMatrix();

        //Makes the position of the lightsource interpolate between start and end of tunnel
        if (lightSourcePos.z < -6 || lightSourcePos.z > 6) {
            posOrNeg = -posOrNeg;
            if (posOrNeg == -1)
                lightSourcePos.z = -5.975f;
            else lightSourcePos.z = 5.975f;
        }
        if (lightSourcePos.z >= -6) 
            lightSourcePos.z -= dt * posOrNeg * 4;

        //Day and night cycle for the walls
        if (ambientStrengthWalls < 0.1f || ambientStrengthWalls > 0.7f) {
            posOrNeg2 = -posOrNeg2;
            if (posOrNeg2 == -1)
                ambientStrengthWalls = 0.104f;
            else ambientStrengthWalls = 0.697f;
        }
        if (ambientStrengthWalls >= 0.1f)
            ambientStrengthWalls -= dt/7.0f * posOrNeg2;
        
        //Handles the different key inputs fromt he keyboard
        keyBoardInput(GLFWApplication::m_window, keyPressed, setTextures, setLight, cubeMoved, 
                                                        translationVectors, translationMatrices, numObjects);
        
        //Moving cube one square down after a set timer
        if (timer > 2.0f) {           
            timer = 0;          
            int indexLast = translationVectors.size() - 1;      //Index of current active square
            if (translationVectors[numObjects - 1].z > -0.5f + nextSquareZ) {   //In bounds
                //Updates the vector and matrices for that cube with the values of moving on section down 
                translationVectors[numObjects - 1] = glm::vec3(translationVectors[indexLast].x,
                                    translationVectors[indexLast].y, translationVectors[indexLast].z - nextSquareZ);
                translationMatrices[numObjects - 1] = glm::translate(idMatrix, translationVectors[numObjects - 1]);
                modelMatrices[numObjects - 1] = cubeScale * cubeRotation * translationMatrices[numObjects - 1];
            }
        }
        //updates model matrix with new translation matrix after key was pressed
        if (cubeMoved && timer < 2) {       
            modelMatrices[numObjects - 1] = cubeScale * cubeRotation * translationMatrices[numObjects - 1];
            timer = 0;
            cubeMoved = false;
        }

        if (translationVectors[numObjects - 1].z <= -0.5f + nextSquareZ ) { //If cube reached endWall
            createNewCube(translationVectors, numObjects, modelMatrices,    //create new cube 
                                    cubeScale, cubeRotation, initTranslation, translationMatrices);
            timer = 0;
        }

        for (int i = 0; i < numObjects-1; i++) {
            //Checks if a block is trying to be placed above the highest section
            if (translationVectors[i].z >= 0.45f) {
                std::cout << "You managed to place: " << 
                        translationVectors.size()-2 << " blocks before losing!";
                return EXIT_SUCCESS;                             //Game is over 
            }
            //If a block tries to invade another blocks space on the z axis
            //Create a new cube which turns the block trying to invade solid
            if (translationVectors[numObjects - 1].z <= translationVectors[i].z + nextSquareZ + 0.03f &&
                translationVectors[numObjects - 1].x == translationVectors[i].x &&
                translationVectors[numObjects - 1].y == translationVectors[i].y) {
                timer = 0;
                createNewCube(translationVectors, numObjects, modelMatrices,
                cubeScale, cubeRotation, initTranslation, translationMatrices);
            }
        }

        //Set the tunnel Wall variables that are changed in runtime
        tunnelWallShader->setInt("u_setLight", setLight);
        tunnelWallShader->setUniform3fVector("u_lightSourcePosition", lightSourcePos);
        tunnelWallShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);
        tunnelWallShader->setInt("u_setTextures", setTextures);
        tunnelWallShader->setUniformFloat("u_ambientStrength", ambientStrengthWalls);
        //Draw the tunnel walls with their respective normals and model matrix
        for (int i = 0; i < 4; i++) {
            tunnelWallShader->Bind(); 
            tunnelWallShader->setUniform3fVector("u_normal", normalVTunnelWall[i]);
            tunnelWallShader->SetUniformMatrix4fv("u_modelMatrix", modelTunnelWall[i]);
            tunnelWallvertexArray->Bind();
            RenderCommands::DrawIndex(tunnelWallvertexArray, GL_TRIANGLES);
        }

        //Set the end wall variables that are changed in runtime and draw it
        endWallShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);
        endWallShader->setInt("u_setLight", setLight);
        endWallShader->setInt("u_setTextures", setTextures);
        endWallShader->setUniform3fVector("u_lightSourcePosition", lightSourcePos);
        endWallShader->setUniform3fVector("u_normal", normalEndWall);
        endWallShader->setUniformFloat("u_ambientStrength", ambientStrengthWalls);
        endWallvertexArray->Bind();
        RenderCommands::DrawIndex(endWallvertexArray, GL_TRIANGLES);

        //Set the cube variables that apply to all cubes        
        cubeShader->SetUniformMatrix4fv("u_viewMatrix", viewMatrix);
        cubeShader->setInt("u_setLight", setLight);
        cubeShader->setInt("u_setTextures", setTextures);
        cubeShader->setUniform3fVector("u_lightSourcePosition", lightSourcePos);
        for (int i = 0; i < numObjects; i++) {
            //Send the z coordinate of the cube to the shader
            translationVectorZ = translationVectors[i].z;   
            cubeShader->setUniformFloat("u_translationVectorZ", translationVectorZ);
            //Set the modelMatrix for the cube to be drawn
            cubeShader->SetUniformMatrix4fv("u_modelMatrix", modelMatrices[i]);
            cubeVertexArray->Bind();
            
            if (i < numObjects - 1) {               //All the solid cubes
                //Set color according to what level the cube is on
                cubeColorC = setLevelColor(translationVectors[i], numObjects, cubeColors);
                cubeShader->SetUniform4fVector("u_color", cubeColorC);
                RenderCommands::DrawIndex(cubeVertexArray, GL_TRIANGLES);   //Draw as solid
               
                RenderCommands::SetWireframeMode();                     
                cubeShader->SetUniform4fVector("u_color", cubeColorA); 
                RenderCommands::DrawIndex(cubeVertexArray, GL_TRIANGLES); //Draw as wireframe
                RenderCommands::SetSolidMode();
            }
            else {                                  //The active cube
                cubeShader->SetUniform4fVector("u_color", cubeColorB);
                RenderCommands::DrawIndex(cubeVertexArray, GL_TRIANGLES);   //Draw as solid

                RenderCommands::SetWireframeMode();
                cubeShader->SetUniform4fVector("u_color", cubeColorA);
                RenderCommands::DrawIndex(cubeVertexArray, GL_TRIANGLES);   //Draw as wireframe
                RenderCommands::SetSolidMode();
            }
        }

        //Set All the properties for the lightsource cube 
        if (setLight) {
            glm::mat4 lightTranslation = glm::translate(glm::mat4(1.0f), lightSourcePos);
            cubeShader->SetUniformMatrix4fv("u_modelMatrix", glm::scale(glm::mat4(1.0f), glm::vec3{ 1.0f, 1.0f, 1.0f }) *
                glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * lightTranslation);
            cubeShader->SetUniform4fVector("u_color", lightColor);
            RenderCommands::DrawIndex(cubeVertexArray, GL_TRIANGLES);
        }
        
        glfwSwapBuffers(GLFWApplication::m_window);
        // Exit the loop if escape is pressed
        if (glfwGetKey(GLFWApplication::m_window, GLFW_KEY_Q) == GLFW_PRESS) break;
    }
    return EXIT_SUCCESS;
}


//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/Graphics/Shader.hpp"
#include "SFML/OpenGL.hpp" 
#include <iostream> 
  
 
#include "Terrain.h"
#include "Camera.h"




int main() 
{ 
    // Create the main window 
    
    int width=600,height=600;
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "SFML OpenGL"); 
    // Create a clock for measuring time elapsed     
    sf::Clock Clock; 

	Camera camera;
    camera.Init(); //create a camera
      
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
   
    //// Setup a perspective projection & Camera position 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
     
    //set up a 3D Perspective View volume
    gluPerspective(90.f, (float)width/height, 1.f, 300.0f);//fov, aspect, zNear, zFar 
 



	//load & bind the shader
	sf::Shader shader;
	if(!shader.loadFromFile("vertex.glsl","fragment.glsl")){
        exit(1);
    }
	sf::Shader::bind(&shader);

	Terrain terrain;
	terrain.Init();
    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                App.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                App.close(); 
             
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::D)){
                camera.MoveLeftRight(+1);
            }

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
                camera.MoveLeftRight(-1);
            }
 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W)){
                camera.MoveForwardBack(1);
            }
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S)){
                camera.MoveForwardBack(-1);
            }
 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right)){
                camera.TurnRightLeft(1);
            }
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left)){
                camera.TurnRightLeft(-1);
            }
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up)){
                camera.TurnUpDown(1);
            }
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down)){
                camera.TurnUpDown(-1);
 
            }
    
        } 
           
        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   
        // Apply some transformations 
        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 


		camera.ViewingTransform();

		static float ang=0.0;
		//TODO:probably should remove this in final
		glRotatef(ang*2,0,1,0);//spin about y-axis
		

		ang+=0.01f;

		terrain.Draw();

		   
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
   
    return EXIT_SUCCESS; 
}

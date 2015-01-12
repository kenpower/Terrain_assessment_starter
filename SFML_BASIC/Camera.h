#pragma comment(lib,"assimp.lib")
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



class Camera{
    static aiVector3D zero,yaxis,zaxis;
public:
    aiVector3D position;
    aiVector3D forward;
    aiVector3D up;
 
    float forwardSpeed;
    float roationSpeed;
     
    Camera():forwardSpeed(0.5f),roationSpeed(0.1f){}
 
    void Init(aiVector3D& p=zero, aiVector3D& f=zaxis, aiVector3D& u=yaxis){
        position=p;
        forward=f;
        up=u;
         
    }
 
    void MoveLeftRight(int dir){ //Dir=+1=>Right, dir=-1=> Left
            //TODO
    }
 
    void MoveForwardBack(int dir){ //Dir=+1=>Forward, dir=-1=> Back
 
        position+=(forward*(forwardSpeed*dir));
    }
 
    void TurnRightLeft(int dir){ //Dir=+1=>Right, dir=-1=> Left
        //TODO
    }
         
    void TurnUpDown(int dir){ //Dir=+1=>Up, dir=-1=> Down
        //TODO
    }
 
    void ViewingTransform(){
        gluLookAt(	position.x,position.y,position.z,// camera position
					forward.x,forward.y,forward.z, //look at this point //TODO: BUG here!! what is it ??
					0,1,0); //camera up
    }
 
};
 
aiVector3D Camera::zero(0.0f);
aiVector3D Camera::yaxis(0.0f,1.0f,0.0f);
aiVector3D Camera::zaxis(0.0f,0.0f,1.0f);
#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Material.h"
#include "PointLight.h"
#include "PeriodicPlane.h"

using namespace std;
using namespace rt;

void addBubble( Scene& scene, Point3 c, Real r, Material transp_m )
{
  Material revert_m = transp_m;
  std::swap( revert_m.in_refractive_index, revert_m.out_refractive_index );
  Sphere* sphere_out = new Sphere( c, r, transp_m );
  Sphere* sphere_in  = new Sphere( c, r-0.02f, revert_m );
  scene.addObject( sphere_out );
  scene.addObject( sphere_in );
}

int main(int argc, char** argv)
{
  // Read command lines arguments.
  QApplication application(argc,argv);
  
  // Creates a 3D scene
  Scene scene;
  
  // Light at infinity
  Light* light0 = new PointLight( GL_LIGHT0, Point4( 0,0,1,0 ),
                                    Color( 1.0, 1.0, 1.0 ) );
  Light* light1 = new PointLight( GL_LIGHT1, Point4( 7,5,15,1 ),
                                  Color( 1.0, 1.0, 1.0 ) );
  scene.addLight( light0 );
  scene.addLight( light1 );

  // Un sol noir et blanc
  //PeriodicPlane* pplane = new PeriodicPlane( Point3( 0, 0, 0 ), Vector3( 5, 0, 0 ), Vector3( 0, 5, 0 ),
      //Material::whitePlastic(), Material::emerald(), 0.05f );

// Un sol noir et blanc
 // PeriodicPlane* pplane = new PeriodicPlane( Point3( -10, 0, 0 ), Vector3( 0, 2, 0 ), Vector3( 0, 0, 4 ),
     // Material::whitePlastic(), Material::emerald(), 0.025f );
  // Objects
<<<<<<< HEAD
  Sphere* sphere1 = new Sphere( Point3( 3, 0, 0), 3.0, Material::emerald() );
  Sphere* sphere2 = new Sphere( Point3( -3, 0, 0), 3.0, Material::emerald() );
  Sphere* sphere4 = new Sphere( Point3( 0, 0, 3), 3.0, Material::emerald() );
  Sphere* sphere5 = new Sphere( Point3( 0, -3, 0), 3.0, Material::emerald() );
  Sphere* sphere7 = new Sphere( Point3( 0, 3, 0), 3.0, Material::emerald() );
  Sphere* sphere8 = new Sphere( Point3( 30, 0, 0), 20.0, Material::bronze() );
  Sphere* sphere9 = new Sphere( Point3( 0, 0, -3), 3.0, Material::emerald() );

=======
  Sphere* sphere1 = new Sphere( Point3( 5, 5, 2), 2.0, Material::bronze() );
  Sphere* sphere2 = new Sphere( Point3( 0, 4, 1), 1.0, Material::emerald() );
>>>>>>> 1bc0ea0eac6d6da1f17ca80eef13d9c483078e8a
  //Sphere* sphere3 = new Sphere( Point3( 6, 6, 0), 3.0, Material::whitePlastic() );
  //scene.addObject( pplane );
  scene.addObject( sphere1 );
  scene.addObject( sphere2 );
<<<<<<< HEAD
  scene.addObject( sphere4 );
  scene.addObject( sphere5 );
  scene.addObject( sphere7 );
  scene.addObject( sphere8 );
  scene.addObject( sphere9 );



  //addBubble( scene, Point3( 0, 0, 0 ), 8.0, Material::glass() );


=======
  
  /*
  addBubble( scene, Point3( -5, 4, -1 ), 2.0, Material::glass() );
  addBubble( scene, Point3( 15, 18, 15 ), 6.0, Material::glass() );
  addBubble( scene, Point3( 10, 2, 1 ), 2.0, Material::glass() );
  addBubble( scene, Point3( 8, 8, -1 ), 4.0, Material::glass() );
  addBubble( scene, Point3( 5, 5, 0 ), 4.0, Material::glass() );
  addBubble( scene, Point3( 19, 2, 10 ), 3.0, Material::glass() );
  addBubble( scene, Point3( 21, 12, 18 ), 5.0, Material::glass() );
  */
>>>>>>> 1bc0ea0eac6d6da1f17ca80eef13d9c483078e8a
  // Instantiate the viewer.
  Viewer viewer;
  // Give a name
  viewer.setWindowTitle("Ray-tracer preview");

  // Sets the scene
  viewer.setScene( scene );

  // Make the viewer window visible on screen.
  viewer.show();
  // Run main loop.

  application.exec();
  return 0;
}

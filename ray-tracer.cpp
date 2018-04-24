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
#include "WaterPlane.h"

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
  
  // Soleil
  Light* light0 = new PointLight( GL_LIGHT0, Point4( 15, -6, 7, 1),Color( 1.0, 1.0, 1.0) );
  //Light* light1 = new PointLight( GL_LIGHT1, Point4( 0, 0, 1, 1),Color( 0.8, 0.8, 0.8) );

  scene.addLight( light0 );
  //scene.addLight( light1 );

  // Un sol noir et blanc
  //PeriodicPlane* pplane = new PeriodicPlane( Point3( 0, 0, -1 ), Vector3( 5, 0, 0 ), Vector3( 0, 5, 0 ),
  //Material::whitePlastic(), Material::blackMatter(), 0.1f );

  //L'ocean
  WaterPlane* wplane = new WaterPlane( Point3( 0, 0, 0 ), Vector3( 5, 0, 0 ), Vector3( 0, 5, 0 ),
    Material::blueWater(), 0.2f, M_PI, 5.0f, 0.3f );

  //Sable
  Sphere* sphere0 = new Sphere( Point3( 0, 0,-95), 100, Material::sand() );

  // 1er palmier
  Sphere* sphere8 = new Sphere( Point3( 6, 0, 3), 1.0, Material::bronze() );
  Sphere* sphere10 = new Sphere( Point3( 6.5, 0, 4), 1.0, Material::bronze() );
  Sphere* sphere11 = new Sphere( Point3( 7, 0, 5), 1.0, Material::bronze() );
  Sphere* sphere12 = new Sphere( Point3( 7.5, 0, 6), 1.0, Material::bronze() );
  Sphere* sphere13 = new Sphere( Point3( 7.7, 0, 7), 1.0, Material::bronze() );
  Sphere* sphere14 = new Sphere( Point3( 7.8, 0, 8), 1.0, Material::bronze() );
  Sphere* sphere15 = new Sphere( Point3( 7.8, 0, 9), 1.0, Material::bronze() );
  Sphere* sphere16 = new Sphere( Point3( 7.8, 0, 10), 1.0, Material::emerald() );
  Sphere* sphere17 = new Sphere( Point3( 8.8, 0, 10), 1.0, Material::emerald() );
  Sphere* sphere18 = new Sphere( Point3( 7.8, 1, 10), 1.0, Material::emerald() );
  Sphere* sphere19 = new Sphere( Point3( 7.8, -1, 10), 1.0, Material::emerald() );
  Sphere* sphere20 = new Sphere( Point3( 6.8, 0, 10), 1.0, Material::emerald() );
  Sphere* sphere21 = new Sphere( Point3( 9.8, 0, 10), 1.0, Material::emerald() );
  Sphere* sphere22 = new Sphere( Point3( 7.8, 2, 10), 1.0, Material::emerald() );
  Sphere* sphere23 = new Sphere( Point3( 7.8, -2, 10), 1.0, Material::emerald() );
  Sphere* sphere24 = new Sphere( Point3( 5.8, 0, 10), 1.0, Material::emerald() );
  Sphere* sphere25 = new Sphere( Point3( 10.8, 0, 9.5), 1.0, Material::emerald() );
  Sphere* sphere26 = new Sphere( Point3( 7.8, 3, 9.5), 1.0, Material::emerald() );
  Sphere* sphere27 = new Sphere( Point3( 7.8, -3, 9.5), 1.0, Material::emerald() );
  Sphere* sphere28 = new Sphere( Point3( 4.8, 0, 9.5), 1.0, Material::emerald() );

  //2eme palmier
  Sphere* sphere29 = new Sphere( Point3( 6, -10, 3), 1.0, Material::bronze() );
  Sphere* sphere30 = new Sphere( Point3( 6.5, -10, 4), 1.0, Material::bronze() );
  Sphere* sphere31 = new Sphere( Point3( 7, -10, 5), 1.0, Material::bronze() );
  Sphere* sphere32 = new Sphere( Point3( 7.5, -10, 6), 1.0, Material::bronze() );
  Sphere* sphere33 = new Sphere( Point3( 7.7, -10, 7), 1.0, Material::bronze() );
  Sphere* sphere34 = new Sphere( Point3( 7.8, -10, 8), 1.0, Material::bronze() );
  Sphere* sphere35 = new Sphere( Point3( 7.8, -10, 9), 1.0, Material::bronze() );
  Sphere* sphere36 = new Sphere( Point3( 7.8, -10, 10), 1.0, Material::emerald() );
  Sphere* sphere37 = new Sphere( Point3( 8.8, -10, 10), 1.0, Material::emerald() );
  Sphere* sphere38 = new Sphere( Point3( 7.8, -9, 10), 1.0, Material::emerald() );
  Sphere* sphere39 = new Sphere( Point3( 7.8, -11, 10), 1.0, Material::emerald() );
  Sphere* sphere40 = new Sphere( Point3( 6.8, -10, 10), 1.0, Material::emerald() );
  Sphere* sphere41 = new Sphere( Point3( 9.8, -10, 10), 1.0, Material::emerald() );
  Sphere* sphere42 = new Sphere( Point3( 7.8, -8, 10), 1.0, Material::emerald() );
  Sphere* sphere43 = new Sphere( Point3( 7.8, -12, 10), 1.0, Material::emerald() );
  Sphere* sphere44 = new Sphere( Point3( 5.8, -10, 10), 1.0, Material::emerald() );
  Sphere* sphere45 = new Sphere( Point3( 10.8, -10, 9.5), 1.0, Material::emerald() );
  Sphere* sphere46 = new Sphere( Point3( 7.8, -7, 9.5), 1.0, Material::emerald() );
  Sphere* sphere47 = new Sphere( Point3( 7.8, -13, 9.5), 1.0, Material::emerald() );
  Sphere* sphere48 = new Sphere( Point3( 4.8, -10, 9.5), 1.0, Material::emerald() );

  //scene.addObject( pplane );
  scene.addObject( wplane );
  scene.addObject( sphere0 );
  scene.addObject( sphere8 );
  scene.addObject( sphere10 );
  scene.addObject( sphere11 );
  scene.addObject( sphere12 );
  scene.addObject( sphere13 );
  scene.addObject( sphere14 );
  scene.addObject( sphere15 );
  scene.addObject( sphere16 );
  scene.addObject( sphere17 );
  scene.addObject( sphere18 );
  scene.addObject( sphere19 );
  scene.addObject( sphere20 );
  scene.addObject( sphere21 );
  scene.addObject( sphere22 );
  scene.addObject( sphere23 );
  scene.addObject( sphere24 );
  scene.addObject( sphere25 );
  scene.addObject( sphere26 );
  scene.addObject( sphere27 );
  scene.addObject( sphere28 );
  scene.addObject( sphere29 );
  scene.addObject( sphere30 );
  scene.addObject( sphere30 );
  scene.addObject( sphere30 );
  scene.addObject( sphere31 );
  scene.addObject( sphere32 );
  scene.addObject( sphere33 );
  scene.addObject( sphere34 );
  scene.addObject( sphere35 );
  scene.addObject( sphere36 );
  scene.addObject( sphere37 );
  scene.addObject( sphere38 );
  scene.addObject( sphere39 );
  scene.addObject( sphere40 );
  scene.addObject( sphere41 );
  scene.addObject( sphere42 );
  scene.addObject( sphere43 );
  scene.addObject( sphere44 );
  scene.addObject( sphere45 );
  scene.addObject( sphere46 );
  scene.addObject( sphere47 );
  scene.addObject( sphere48 );

  //addBubble( scene, Point3( 34, -10, 5), 1.0, Material::glass() );

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

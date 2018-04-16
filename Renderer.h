/**
@file Renderer.h
@author JOL
*/
#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Color.h"
#include "Image2D.h"
#include "Ray.h"

/// Namespace RayTracer
namespace rt {

  struct Background {
    virtual Color backgroundColor( const Ray& ray ) = 0;
  };

  struct MyBackground : public Background {
    Color backgroundColor( const Ray& ray )
    {
      Color result = Color( 0.0, 0.0, 0.0 );
      Real z = ray.direction[2];
      if(z < 0.0f) {
        Real x = -0.5f * ray.direction[ 0 ] / z;
        Real y = -0.5f * ray.direction[ 1 ] / z;
        Real d = sqrt( x*x + y*y );
        Real t = std::min( d, 30.0f ) / 30.0f;
        x -= floor( x );
        y -= floor( y );

        if ( ( ( x >= 0.5f ) && ( y >= 0.5f ) ) || ( ( x < 0.5f ) && ( y < 0.5f ) ) )
          result += (1.0f - t)*Color( 0.2f, 0.2f, 0.2f ) + t * Color( 1.0f, 1.0f, 1.0f );
        else
          result += (1.0f - t)*Color( 0.4f, 0.4f, 0.4f ) + t * Color( 1.0f, 1.0f, 1.0f );
      } else if(z < 0.5f){
        z *= 2;
        return Color(1, 1, 1) * (1.0f - z) + Color(0.0,0.0,1.0) * z;
      } else {
        z = (z - 0.5f) * 2;
        return Color(0.0,0.0,1.0) * (1.0f - z) + Color(0.0,0.0,0.0) * z;
      }
    
      return result;
    }
  };

  inline void progressBar( std::ostream& output,
                           const double currentValue, const double maximumValue)
  {
    static const int PROGRESSBARWIDTH = 60;
    static int myProgressBarRotation = 0;
    static int myProgressBarCurrent = 0;
    // how wide you want the progress meter to be
    double fraction = currentValue /maximumValue;
    
    // part of the progressmeter that's already "full"
    int dotz = static_cast<int>(floor(fraction * PROGRESSBARWIDTH));
    if (dotz > PROGRESSBARWIDTH) dotz = PROGRESSBARWIDTH;
    
    // if the fullness hasn't changed skip display
    if (dotz == myProgressBarCurrent) return;
    myProgressBarCurrent = dotz;
    myProgressBarRotation++;
    
    // create the "meter"
    int ii=0;
    output << "[";
    // part  that's full already
    for ( ; ii < dotz;ii++) output<< "#";
    // remaining part (spaces)
    for ( ; ii < PROGRESSBARWIDTH;ii++) output<< " ";
    static const char* rotation_string = "|\\-/";
    myProgressBarRotation %= 4;
    output << "] " << rotation_string[myProgressBarRotation]
           << " " << (int)(fraction*100)<<"/100\r";
    output.flush();
  }
  
  /// This structure takes care of rendering a scene.
  struct Renderer {

    /// The scene to render
    Scene* ptrScene;
     // On rajoute un pointeur vers un objet Background
    Background* ptrBackground;
    /// The origin of the camera in space.
    Point3 myOrigin;
    /// (myOrigin, myOrigin+myDirUL) forms a ray going through the upper-left
    /// corner pixel of the viewport, i.e. pixel (0,0)
    Vector3 myDirUL;
    /// (myOrigin, myOrigin+myDirUR) forms a ray going through the upper-right
    /// corner pixel of the viewport, i.e. pixel (width,0)
    Vector3 myDirUR;
    /// (myOrigin, myOrigin+myDirLL) forms a ray going through the lower-left
    /// corner pixel of the viewport, i.e. pixel (0,height)
    Vector3 myDirLL;
    /// (myOrigin, myOrigin+myDirLR) forms a ray going through the lower-right
    /// corner pixel of the viewport, i.e. pixel (width,height)
    Vector3 myDirLR;

    int myWidth;
    int myHeight;

    Renderer() : ptrScene( 0 ), ptrBackground(0) {}
    Renderer( Scene& scene ) : ptrScene( &scene ) {
      ptrBackground = new MyBackground();
    }
    void setScene( rt::Scene& aScene ) { ptrScene = &aScene; }
    
    void setViewBox( Point3 origin, 
                     Vector3 dirUL, Vector3 dirUR, Vector3 dirLL, Vector3 dirLR )
    {
      myOrigin = origin;
      myDirUL = dirUL;
      myDirUR = dirUR;
      myDirLL = dirLL;
      myDirLR = dirLR;
    }

    void setResolution( int width, int height )
    {
      myWidth  = width;
      myHeight = height;
    }


    /// The main rendering routine
    void render( Image2D<Color>& image, int max_depth )
    {
      std::cout << "Rendering into image ... might take a while." << std::endl;
      image = Image2D<Color>( myWidth, myHeight );
      for ( int y = 0; y < myHeight; ++y ) 
        {
          Real    ty   = (Real) y / (Real)(myHeight-1);
          progressBar( std::cout, ty, 1.0 );
          Vector3 dirL = (1.0f - ty) * myDirUL + ty * myDirLL;
          Vector3 dirR = (1.0f - ty) * myDirUR + ty * myDirLR;
          dirL        /= dirL.norm();
          dirR        /= dirR.norm();
          for ( int x = 0; x < myWidth; ++x ) 
            {
              Real    tx   = (Real) x / (Real)(myWidth-1);
              Vector3 dir  = (1.0f - tx) * dirL + tx * dirR;
              Ray eye_ray  = Ray( myOrigin, dir, max_depth );
              Color result = trace( eye_ray );
              image.at( x, y ) = result.clamp();
            }
        }
      std::cout << "Done." << std::endl;
    }


    /// The rendering routine for one ray.
    /// @return the color for the given ray.
    Color trace( const Ray& ray )
    {
      assert( ptrScene != 0 );

      GraphicalObject* obj_i = 0; // pointer to intersected object
      Point3           p_i;       // point of intersection

      // Look for intersection in this direction.
      Real ri = ptrScene->rayIntersection( ray, obj_i, p_i );
      // Nothing was intersected
      
      if ( ri >= 0.0f ) return background(ray); // some background color
      
      return illumination(ray, obj_i, p_i);
    }

    Vector3 reflect( const Vector3& W, Vector3 N ) const {
        return W - 2 * W.dot(N) * N;
    }

    // Affiche les sources de lumières avant d'appeler la fonction qui
    // donne la couleur de fond.
    Color background( const Ray& ray )
    {
      Color result = Color( 0.0, 0.0, 0.0 );
      for ( Light* light : ptrScene->myLights )
        {
          Real cos_a = light->direction( ray.origin ).dot( ray.direction );
          if ( cos_a > 0.99f )
            {
              Real a = acos( cos_a ) * 360.0 / M_PI / 8.0;
              a = std::max( 1.0f - a, 0.0f );
              result += light->color( ray.origin ) * a * a;
            }
        }
      if ( ptrBackground != 0 ) result += ptrBackground->backgroundColor( ray );
      return result;
    }

    /// Calcule l'illumination de l'objet \a obj au point \a p, sachant que l'observateur est le rayon \a ray.
    Color illumination( const Ray& ray, GraphicalObject* obj, Point3 p ) {
      Material mat = obj->getMaterial(p);
      Color result = Color( 0.0, 0.0, 0.0 );
      Vector3 V = ray.direction;

      for(std::vector<Light*>::iterator it = ptrScene->myLights.begin(), itE = ptrScene->myLights.end(); it != itE; ++it) {
        Vector3 direction = (*it)->direction(ray.direction);
        Vector3 normal = obj->getNormal(p);
        Vector3 W = reflect(V, normal);
        Ray rayLight(p, direction);
        Color light = (*it)->color(p);

        Color shad = shadow(rayLight, light);

        Real coss = normal.dot(direction) / (normal.norm() * direction.norm());
        if(coss < 0) coss = 0;

        Real cossB = W.dot(direction) / (W.norm() * direction.norm());
        if(cossB < 0) cossB = 0;

        Real spec = std::pow(cossB, mat.shinyness);

        result += (*it)->color(p) * mat.diffuse * coss;
        result += (*it)->color(p) * mat.specular * spec;

        result = result * shad;
      }

      result += mat.ambient;

      return result;
    }

    Color shadow( const Ray& ray, Color light_color ) {
      Point3 origin_ray = ray.origin;
      GraphicalObject* obj_i = 0; // pointer to intersected object
      Point3           p_i;       // point of intersection
      
      while(light_color.max() > 0.003f) {
        origin_ray += ray.direction * 0.001f;

        Ray rayDecale(origin_ray, ray.direction, ray.depth);

        Real intersect = ptrScene->rayIntersection(rayDecale, obj_i, p_i);

        if(intersect < 0.0f) {
          Material mat = obj_i->getMaterial(p_i);

          light_color = light_color * mat.diffuse * mat.coef_refraction;
          
          origin_ray = p_i;
        } else {
          break;
        }
      }

      return light_color;
    }
  };

} // namespace rt

#endif // #define _RENDERER_H_

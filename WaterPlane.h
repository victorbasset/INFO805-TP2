#include "GraphicalObject.h"
#include <math.h>       /* modf */

/// Namespace RayTracer
namespace rt {

  struct WaterPlane : public GraphicalObject 
  {
    /// Creates a periodic infinite plane passing through \a c and
    /// tangent to \a u and \a v. Then \a w defines the width of the
    /// band around (0,0) and its period to put material \a band_m,
    /// otherwise \a main_m is used.
    WaterPlane( Point3 c, Vector3 u, Vector3 v, Material main_m, 
        Real amplitude, Real propagation, Real lambda, Real phase) {
      this->c = c;
      this->u = u;
      this->v = v;
      this->main_m = main_m;
      this->amplitude = amplitude;
      this->propagation = propagation;
      this->lambda = lambda;
      this->phase = phase;

      direction = Vector2(
            u[0] * cos(propagation) + u[1] * sin(propagation), 
            -u[0] * sin(propagation) + u[1] * cos(propagation)
        );
        std::cout << sin(propagation) << std::endl;
    };

    void coordinates( Point3 p, Real& x, Real& y) {
      x = u[0] + v[0] + p[0];
      y = u[1] + v[1] + p[1];
    }

    void init( Viewer& /* viewer */ ) {}

    void draw( Viewer& /* viewer */ ) {
      glBegin( GL_TRIANGLES );
      glColor3f(0.5, 0, 0);
      glVertex3f(-1000.0, -1000.0, 0.0);
      glVertex3f(-1000.0, 1000.0, 0.0);
      glVertex3f(1000.0, -1000.0, 0.0);

      glEnd();

      glBegin( GL_TRIANGLES );
      glColor3f(0, 0.5, 0);
      glVertex3f(-1000.0, 1000.0, 0.0);
      glVertex3f(1000.0, 1000.0, 0.0);
      glVertex3f(1000.0, -1000.0, 0.0);

      glEnd();
    }

    Vector3 getNormal( Point3 p ) {
        Vector3 vx = u;
        Vector3 vy = v;

        Real txy = p[0] * cos(propagation) + p[1] * sin(propagation);
        Real fxy = (2 * M_PI * txy) / lambda + phase;
            
        for(int i = 0; i < 20; ++i) {
            vx += Vector3(1, 0, -(2 * M_PI * amplitude * cos(propagation) * sin(fxy))/lambda);
            vy += Vector3(0, 1, -(2 * M_PI * amplitude * sin(propagation) * sin(fxy))/lambda);
        }

        Vector3 normal = vx.cross(vy);
        
        return normal / normal.norm();
    }

    Material getMaterial( Point3 p ) {
      return main_m;
    }

    Real rayIntersection( const Ray& ray, Point3& p ) {
      Vector3 n = getNormal(c);
      Vector3 w = ray.direction / ray.direction.norm();
      Real nw = n.dot(w);
      Real tmp;
      Vector3 n0w0 = c - ray.origin;
    
      if(nw == 0) {
        if(n.dot(n0w0) == 0) {
          tmp = 0;
          p = ray.origin + w * tmp;

          return -1.0f;
        } else {
          return 1.0f;
        }
      } else {
        tmp = n0w0.dot(n) / nw;
        p = ray.origin + w * tmp;
      }
      
      return tmp >=0 ? -1.0f : 1.0f;
    }
  
  public:
    Point3 c;
    Vector3 u, v;
    Vector2 direction;
    Material main_m;
    Real amplitude, propagation, lambda, phase;
  };
}
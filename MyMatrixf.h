#ifndef MYMATRIXF_H
#define MYMATRIXF_H

#include <osg/Matrixf>
#include <osg/Vec3f>

class MyMatrixf : public osg::Matrixf
{
public:
  MyMatrixf(const osg::Matrixf& mat) :
  osg::Matrixf(mat)
  {
    
  }
  inline void preMultTranslate( const osg::Vec3f& v )
 {
     for (unsigned i = 0; i < 3; ++i)
     {
         float tmp = v[i];
         if (tmp == 0)
             continue;
         _mat[3][0] += tmp*_mat[i][0];
         _mat[3][1] += tmp*_mat[i][1];
         _mat[3][2] += tmp*_mat[i][2];
         _mat[3][3] += tmp*_mat[i][3];
     }
 }
 
 inline void postMultTranslate( const osg::Vec3d& v )
 {
     for (unsigned i = 0; i < 3; ++i)
     {
         double tmp = v[i];
         if (tmp == 0)
             continue;
         _mat[0][i] += tmp*_mat[0][3];
         _mat[1][i] += tmp*_mat[1][3];
         _mat[2][i] += tmp*_mat[2][3];
         _mat[3][i] += tmp*_mat[3][3];
     }
 }
};

#endif // MYMATRIXF_H

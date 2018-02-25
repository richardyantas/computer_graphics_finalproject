
#pragma once

#include <LMesh.h>
#include <LMeshBuilder.h>

#include "TCommon.h"
#include <vector>

#define TERRAIN1D_DEFAULT_MIN_LENGTH    3.0f
#define TERRAIN1D_DEFAULT_MAX_LENGTH    4.0f
#define TERRAIN1D_DEFAULT_DEPTH         2.0f
#define TERRAIN1D_DEFAULT_MIN_BUMPS     3
#define TERRAIN1D_DEFAULT_MAX_BUMPS     7
#define TERRAIN1D_DEFAULT_MIN_HEIGHT    1
#define TERRAIN1D_DEFAULT_MAX_HEIGHT    2

using namespace std;

namespace tysoc
{

    struct TBoxVoxelInfo
    {
        engine::LVec3 center;
        engine::LVec3 size;
        engine::LVec3 direction;
        engine::LVec3 up;
    };

    class TTerrain1DPatchVoxels
    {

        private :

        // TODO: Reimplement this in a better simpler optimized way
        // maybe just write the outline in a single buffer, like a lego piece
        // and maybe just use planes instead of boxes. Check which is better.

        // graphics part of the voxels - just boxes for now
        vector< engine::LMesh* > m_gVoxels;
        // physics part of the voxels
        vector< btRigidBody* > m_pVoxels;


        // // base outline given by 4 points ( used in camera checks in some cases )
        // // p1 -------- p2
        // //   |        |
        // //   |        |
        // // p0 -------- p3
        // engine::LVec3 m_p0;
        // engine::LVec3 m_p1;
        // engine::LVec3 m_p2;
        // engine::LVec3 m_p3;

        engine::LVec3 m_start;
        engine::LVec3 m_direction;
        engine::LVec3 m_up;

        int m_numBumps;
        float m_patchLength;
        vector< float > m_bumpsPos;
        vector< float > m_bumpsHeight;

        void _buildBoxVoxel( const TBoxVoxelInfo& boxVoxelInfo );

        public :

        TTerrain1DPatchVoxels( engine::LVec3 start,
                               engine::LVec3 direction,
                               engine::LVec3 up,
                               float pMinLength = TERRAIN1D_DEFAULT_MIN_LENGTH, 
                               float pMaxLength = TERRAIN1D_DEFAULT_MAX_LENGTH, 
                               float pDepth = TERRAIN1D_DEFAULT_DEPTH, 
                               float pMinHeight = TERRAIN1D_DEFAULT_MIN_HEIGHT,
                               float pMaxHeight = TERRAIN1D_DEFAULT_MAX_HEIGHT,
                               int minBumps = TERRAIN1D_DEFAULT_MIN_BUMPS, 
                               int maxBumps = TERRAIN1D_DEFAULT_MAX_BUMPS );
        ~TTerrain1DPatchVoxels();

        vector< engine::LMesh* > getVoxelsGraphics() { return m_gVoxels; }
        vector< btRigidBody* > getVoxelsPhysics() { return m_pVoxels; }

        float patchLength() { return m_patchLength; }

        void setMaterial( const engine::LVec3& ambient,
                          const engine::LVec3& diffuse,
                          const engine::LVec3& specular,
                          float shininess );

    };



}
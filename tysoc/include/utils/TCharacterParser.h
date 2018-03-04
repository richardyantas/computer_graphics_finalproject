
#pragma once

#include <TCommon.h>
#include <string>
#include <iostream>
#include <fstream>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

namespace tysoc
{

    struct TCharacterJointData
    {
        string name;

        glm::vec3 pivot;
        glm::vec3 axis;

        int jointType;
        int parentId;

        float linkStiffness;
        float loLimit;
        float hiLimit;
    };

    struct TCharacterShapeData
    {
        string name;
        string shape;

        glm::mat4 localTransform;

        float mass;
        float param0;
        float param1;
        float param2;

        TVec3 color;
    };


    struct TCharacterDrawData
    {
        string name;
        string shape;

        glm::mat4 localTransform;

        float param0;
        float param1;
        float param2;

        TVec3 color;
    };

    struct TCharacterPDControllerData
    {
        string name;

        float Kp;
        float Kd;
        float torqueLimit;
        float targetAngle;
        bool useWorldCoordinates;
    };

    struct TCharacterNodeData
    {
        string name;
        int resId;

        TCharacterJointData         jointData;
        TCharacterShapeData         shapeData;
        TCharacterDrawData          drawData;
        TCharacterPDControllerData  pdcData;
    };

    struct TCharacterNode
    {
        string name;
        int id;

        TCharacterNode* parent;
        vector< TCharacterNode* > children;
        TCharacterNodeData data;
    };

    class TCharacterParser
    {

        static bool _parseJoints( vector< TCharacterNodeData >& dataResources, json root );
        static bool _parseShapes( vector< TCharacterNodeData >& dataResources, json root );
        static bool _parseGraphics( vector< TCharacterNodeData >& dataResources, json root );
        static bool _parsePDCdata( vector< TCharacterNodeData >& dataResources, json root );


        static void _processNode( TCharacterNode* node, const vector< TCharacterNodeData >& dataResources );
        
        static bool _parseResources( vector< TCharacterNodeData >& dataResources, const json& root );
        static bool _buildTree( TCharacterNode& tree, const vector< TCharacterNodeData >& dataResources );
        static bool _loadJson( TCharacterNode& tree, const json& root );

        public :

        static bool parseCharacter( TCharacterNode& tree, const string& charFileName );


    };

}
//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _SHAPE_VECTOR_H_
#define _SHAPE_VECTOR_H_

#ifndef _SCENE_OBJECT_H_
#include "2d/sceneobject/sceneObject.h"
#endif

//-----------------------------------------------------------------------------

class ShapeVector : public SceneObject
{
    typedef SceneObject			Parent;

protected:
    ColorF                  mLineColor;
    ColorF                  mFillColor;
    bool                    mFillMode;
    Vector2                 mPolygonScale;          ///< Polygon Scale.
    Vector<Vector2>         mPolygonBasisList;      ///< Polygon Basis List.
    Vector<Vector2>         mPolygonLocalList;      ///< Polygon Local List.
    bool                    mIsCircle;
    F32                     mCircleRadius;
    bool                    mFlipX;
    bool                    mFlipY;

public:
    ShapeVector();
    ~ShapeVector();

    static void initPersistFields();

    /// Polygon Configuration.
    void setPolyScale( const Vector2& scale );
    void setPolyPrimitive( const U32 polyVertexCount );
    void setPolyCustom( const U32 polyVertexCount, const char* pCustomPolygon );

    /// Rendering Attributes.
    void setLineColorString( const char* lineColour );
    void setLineColor( const ColorF& lineColour );
    void setLineAlpha( const F32 alpha );
    void setFillColorString( const char* fillColour );
    void setFillColor( const ColorF& fillColour );
    void setFillAlpha( const F32 alpha );
    void setFillMode( const bool fillMode );
    void setIsCircle( const bool isCircle );
    void setCircleRadius( F32 radius );

    /// Retrieval.
    U32 getPolyVertexCount( void ) { return U32(mPolygonBasisList.size()); };
    const char* getPoly( void );
    const char* getWorldPoly( void );
    inline const Vector2* getPolyBasis( void ) const         { return &(mPolygonBasisList[0]); };
    bool getFillMode( void );
    const char* getLineColor( void );
    const char* getFillColor( void );
    bool getIsCircle( void );
    F32 getCircleRadius ( void );
    Vector2 getBoxFromPoints( void );

    /// Internal Crunchers.
    void generateLocalPoly( void );

    void renderCircleShape(Vector2 position, F32 radius);
    void renderPolygonShape(U32 vertexCount);

    /// Render flipping.
    inline void setFlip( const bool flipX, const bool flipY )   { mFlipX = flipX; mFlipY = flipY; generateLocalPoly(); }
    inline void setFlipX( const bool flipX )                    { setFlip( flipX, mFlipY ); }
    inline void setFlipY( const bool flipY )                    { setFlip( mFlipX, flipY ); }
    inline bool getFlipX(void) const                            { return mFlipX; }
    inline bool getFlipY(void) const                            { return mFlipY; }
    virtual void setSize( const Vector2& size );

    /// Core.
    virtual bool onAdd();
    virtual void onRemove();
    virtual void sceneRender( const SceneRenderState* pSceneRenderState, const SceneRenderRequest* pSceneRenderRequest, BatchRender* pBatchRenderer );
    virtual bool validRender( void ) const { return (mPolygonLocalList.size() > 0 || mIsCircle); }
    virtual bool shouldRender( void ) const { return true; }

    /// Render batching.
    virtual bool isBatchRendered( void ) { return false; }

    /// Clone support
    void copyTo(SimObject* obj);

    /// Declare Console Object.
    DECLARE_CONOBJECT(ShapeVector);

protected:
    static bool setPolyList(void* obj, const char* data)
    {
       //Vector2 poly[b2_maxPolygonVertices];
       U32 count = Utility::mGetStringElementCount(data) >> 1;
       //for (U32 i = 0; i < count; i++)
       //   poly[i] = Utility::mGetStringElementVector(data, i * 2);

       static_cast<ShapeVector*>(obj)->setPolyCustom(count, data);
       return false;
    }
    static bool writePolyList( void* obj, StringTableEntry pFieldName ) { return static_cast<ShapeVector*>(obj)->mPolygonBasisList.size() > 0; }

    static bool setLineColor(void* obj, const char* data) { static_cast<ShapeVector*>(obj)->setLineColorString(data); return false; }
    static bool writeLineColor( void* obj, StringTableEntry pFieldName ) { return static_cast<ShapeVector*>(obj)->mLineColor != ColorF(1.0f,1.0f,1.0f,1.0f); }
    static bool setFillColor(void* obj, const char* data) { static_cast<ShapeVector*>(obj)->setFillColorString(data); return false; }
    static bool writeFillColor( void* obj, StringTableEntry pFieldName ) { return static_cast<ShapeVector*>(obj)->mFillColor != ColorF(0.5f,0.5f,0.5f,1.0f); }
    static bool setFillMode(void* obj, const char* data) { static_cast<ShapeVector*>(obj)->setFillMode(dAtob(data)); return false; }
    static bool writeFillMode( void* obj, StringTableEntry pFieldName ) { return static_cast<ShapeVector*>(obj)->mFillMode == true; }
    static bool setIsCircle(void* obj, const char* data) { static_cast<ShapeVector*>(obj)->setIsCircle(dAtob(data)); return false; }
    static bool writeIsCircle( void* obj, StringTableEntry pFieldName ) { return static_cast<ShapeVector*>(obj)->mIsCircle == true; }
    static bool setCircleRadius(void* obj, const char* data) { static_cast<ShapeVector*>(obj)->setCircleRadius(dAtof(data)); return false; }
    static bool writeCircleRadius( void* obj, StringTableEntry pFieldName ) { return static_cast<ShapeVector*>(obj)->mIsCircle != 1; }
};

#endif // _SHAPE_VECTOR_H_

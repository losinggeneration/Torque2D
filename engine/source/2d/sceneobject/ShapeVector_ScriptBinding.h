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

ConsoleMethod(ShapeVector, setPolyScale, void, 3, 3, "(widthScale / [heightScale]) - Sets the polygon scale.\n"
              "@param width/heightScale The scale values of the given polygon. If no height is specified, the widthScale value is repeated.\n"
              "@return No return value.")
{
    // Calculate Element Count.
    const U32 elementCount = Utility::mGetStringElementCount( argv[2] );

    // Check Parameters.
    if ( elementCount < 1 )
    {
        Con::warnf("ShapeVector::setPolyScale() - Invalid number of parameters!");
        return;
    }

    // Fetch Width Scale.
    Vector2 scale;
    scale.x = dAtof(Utility::mGetStringElement(argv[2],0));
    // Use Fixed-Aspect for Scale if Height-Scale not specified.
    if ( elementCount == 2 )
    {
        // Specified Height Scale.
        scale.y = dAtof(Utility::mGetStringElement(argv[2],1));
    }
    else
    {
        // Fixed-Aspect Scale.
        scale.y = scale.x;
    }

    // Set Polygon Scale.
    object->setPolyScale( scale );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setPolyPrimitive, void, 3, 3, "(vertexCount) Sets a regular polygon primitive.\n"
              "@return No return value.")
{
    // Set Polygon Primitive.
    object->setPolyPrimitive( dAtoi(argv[2]) );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setPolyCustom, void, 4, 4, "(poly-count, poly-Definition$) Sets Custom Polygon.\n"
              "@return No return value.")
{
    // Set Collision Poly Custom.
    object->setPolyCustom( dAtoi(argv[2]), argv[3] );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getPoly, const char*, 2, 2, "() Gets Polygon.\n"
                                                          "@return (poly-Definition) The vertices of the polygon in object space.")
{
   // Get Collision Poly Count.
    
   return object->getPoly();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getWorldPoly, const char*, 2, 2, "() Gets Polygon points in world space.\n"
                                                          "@return (poly-Definition) The vertices of the polygon in world space.")
{
   // Get Collision Poly Count.
    
   return object->getWorldPoly();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setLineColour, void, 3, 3, "(R / G / B / [A]) Sets the Rendering Line Color (identical to setLineColor).\n"
              "@param R/G/B/[A] Color values (0.0f - 1.0f) formatted as (\"Red Green Blue [Alpha]\"). Alpha is optional.\n"
              "@return No return value.")
{
    // Set Line Color.
    object->setLineColorString( argv[2] );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setLineColor, void, 3, 3, "(R / G / B / [A]) - Sets the Rendering Line Color(identical to setLineColor).\n"
              "@param R/G/B/[A] Color values (0.0f - 1.0f) formatted as (\"Red Green Blue [Alpha]\"). Alpha is optional.\n"
              "@return No return value.")
{
    // Set Line Color.
    object->setLineColorString( argv[2] );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getLineColor, const char*, 2, 2, "() Gets the Rendering Line Color.\n"
              "@return Returns the fill color as a string formatted with \"Red Green Blue Alpha\"")
{
    return object->getLineColor();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setLineAlpha, void, 3, 3, "(alpha) Sets the Rendering Line Alpha (transparency).\n"
              "@param alpha The alpha value.\n"
              "@return No return value.")
{
    // Set Line Alpha.
    object->setLineAlpha( dAtof(argv[2]) );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFillColour, void, 3, 3, "(R / G / B / [A]) Sets the Rendering Fill Color (identical to setFillColor).\n"
              "@param R/G/B/[A] Color values (0.0f - 1.0f) formatted as (\"Red Green Blue [Alpha]\"). Alpha is optional.\n"
              "@return No return value."
              )
{
    // Set Fill Color.
    object->setLineColorString( argv[2] );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFillColor, void, 3, 3, "(R / G / B / [A]) - Sets the Rendering Fill Color (identical to setFillColour).\n"
              "@param R/G/B/[A] Color values (0.0f - 1.0f) formatted as (\"Red Green Blue [Alpha]\"). Alpha is optional.\n"
              "@return No return value.")
{
    // Set Fill Color.
    object->setFillColorString( argv[2] );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getFillColor, const char*, 2, 2, "() Gets the Rendering Fill Color.\n"
              "@return Returns the fill color as a string formatted with \"Red Green Blue Alpha\"")
{
    return object->getFillColor();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFillAlpha, void, 3, 3, "(alpha) Sets the Rendering Fill Alpha (transparency).\n"
              "@param alpha The alpha value.\n"
              "@return No return value.")
{
    // Set Fill Alpha.
    object->setFillAlpha( dAtof(argv[2]) );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFillMode, void, 3, 3, "(fillMode?) Sets the Rendering Fill Mode.\n"
              "@return No return value.")
{
    // Set Fill Mode.
    object->setFillMode( dAtob(argv[2]) );
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getFillMode, bool, 2, 2, "() Gets the Rendering Fill Mode.\n"
              "@return The fill mode as a boolean value.")
{
    return object->getFillMode();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setIsCircle, void, 3, 3, "(isCircle?) Sets whether this shape is a circle or not.\n"
              "@return The fill mode as a boolean value.")
{
    object->setIsCircle(dAtob(argv[2]));
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getIsCircle, bool, 2, 2, "() Returns whether this shape is a circle or not.\n"
              "@return The fill mode as a boolean value.")
{
    return object->getIsCircle();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getCircleRadius, bool, 2, 2, "() Returns the radius of the shape if it is a circle.\n"
              "@return The fill mode as a boolean value.")
{
    return object->getCircleRadius();
}

//----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setCircleRadius, void, 3, 3, "(radius) Changes the radius of the shape if it is a circle.\n"
              "@return The fill mode as a boolean value.")
{
    object->setCircleRadius(dAtof(argv[2]));
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getVertexCount, S32, 2, 2, "() Get the number of vertices on a polygon shape.\n")
{
    return object->getPolyVertexCount();
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getBoxFromPoints, const char*, 2, 2, "() Get a box (\"width height\") that wraps around the poly vertices")
{
    Vector2 box = object->getBoxFromPoints();

    // Create Returnable Buffer.
    char* pBuffer = Con::getReturnBuffer(32);
    
    // Format Buffer.
    dSprintf(pBuffer, 32, "%g %g", box.x, box.y);
    
    // Return box width and height.
    return pBuffer;
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFlip, void, 4, 4,  "(bool flipX, bool flipY) Sets shape flipping for each axis.\n"
                                                "@param flipX Whether or not to flip the shape along the x (horizontal) axis.\n"
                                                "@param flipY Whether or not to flip the shape along the y (vertical) axis.\n"
                                                "@return No return value.")
{
    // Set Flip.
    object->setFlip( dAtob(argv[2]), dAtob(argv[3]) );
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getFlip, const char*, 2, 2,   "() Gets the flip for each axis.\n"
                                                        "@return (bool flipX/bool flipY) Whether or not the shape is flipped along the x and y axis.")
{
    // Create Returnable Buffer.
    char* pBuffer = Con::getReturnBuffer(32);

    // Format Buffer.
    dSprintf(pBuffer, 32, "%d %d", object->getFlipX(), object->getFlipY());

    // Return Buffer.
    return pBuffer;
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFlipX, void, 3, 3,     "(bool flipX) Sets whether or not the shape is flipped horizontally.\n"
                                                    "@param flipX Whether or not to flip the shape along the x (horizontal) axis."
                                                    "@return No return value.")
{
    // Set Flip.
    object->setFlipX( dAtob(argv[2]) );
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, setFlipY, void, 3, 3,     "(bool flipY) Sets whether or not the shape is flipped vertically.\n"
                                                    "@param flipY Whether or not to flip the shape along the y (vertical) axis."
                                                    "@return No return value.")
{
    // Set Flip.
    object->setFlipY( dAtob(argv[2]) );
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getFlipX, bool, 2, 2,     "() Gets whether or not the shape is flipped horizontally.\n"
                                                    "@return (bool flipX) Whether or not the shape is flipped along the x axis.")
{
   return object->getFlipX();
}

//-----------------------------------------------------------------------------

ConsoleMethod(ShapeVector, getFlipY, bool, 2, 2,     "() Gets whether or not the shape is flipped vertically."
                                                    "@return (bool flipY) Whether or not the shape is flipped along the y axis.")
{
   return object->getFlipY();
}
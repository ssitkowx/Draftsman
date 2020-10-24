///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "Display.h"
#include "Rectangle.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Display::Display (const Config_t v_config) : config (v_config) {}

bool Display::DrawBitmap (Bitmap & v_bitmap)
{
    Rectangle rect  = {};
    rect.Dimension  = v_bitmap.Dimension;
    rect.Coordinate = v_bitmap.Coordinate;

    uint8_t maxRects = calculate (v_bitmap.Dimension);
    if (maxRects == ONE) { sendLines (v_bitmap); }
    else
    {
        uint16_t yPos   = ZERO;
        uint16_t height = ZERO;
        for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
        {
            if (rectNum == maxRects) { height = v_bitmap.Dimension.Height - yPos; }
            else                     { height = v_bitmap.Dimension.Width * config.LinesPerTransfer / config.Dimension.Width; }

            v_bitmap.Coordinate.Y     = yPos + v_bitmap.Coordinate.Y;
            v_bitmap.Dimension.Height = height;

            sendLines (v_bitmap);
            yPos = yPos + height;
        }
    }

    return true;
}

bool Display::validate (const Rectangle & v_rect)
{
    return (((v_rect.Coordinate.X + v_rect.Dimension.Width)  > config.Dimension.Width)  ||
            ((v_rect.Coordinate.Y + v_rect.Dimension.Height) > config.Dimension.Height)) ? false : true;
}

uint8_t Display::calculate (const Rectangle::Dimensions & v_dimensions)
{
    double rects         = (v_dimensions.Width * v_dimensions.Height) / (config.Dimension.Width * config.LinesPerTransfer);
    double aditionalRect = (v_dimensions.Width * v_dimensions.Height) % (config.Dimension.Width * config.LinesPerTransfer);
    uint8_t maxRects     = static_cast <uint8_t> (rects);

    return (aditionalRect > ZERO) ? ++maxRects : maxRects;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

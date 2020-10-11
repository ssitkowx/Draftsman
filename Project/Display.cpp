///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "Utils.h"
#include <memory.h>
#include "Display.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool Display::DrawRect (const Rectangle & v_rect, const EColors eColor)
{
    if (validateRect (v_rect) == false) { return false; }

    std::vector <uint16_t> rectData (v_rect.Dimension.Width * Config.LinesPerTransfer * sizeof (uint16_t), (getColor (eColor) << EIGHT_BITS) + getColor (eColor));
    Rectangle rect   = v_rect;
    rect.Data        = rectData.data ();
    uint8_t maxRects = calculateRects (rect.Dimension.Height);

    if (maxRects == ONE) { sendLines (rect); }
    else
    {
        uint16_t yPos   = ZERO;
        uint16_t height = ZERO;
        for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
        {
            if (rectNum == maxRects) { height = v_rect.Dimension.Height - yPos; }
            else                     { height = Config.LinesPerTransfer; }

            rect.Coordinate.Y     = yPos + v_rect.Coordinate.Y;
            rect.Dimension.Height = height;

            sendLines (rect);
            yPos = yPos + height;
        }
    }

    return true;
}

bool Display::validateRect (const Rectangle & v_rect)
{
    return (((v_rect.Coordinate.X + v_rect.Dimension.Width)  > Config.Dimension.Width)  ||
            ((v_rect.Coordinate.Y + v_rect.Dimension.Height) > Config.Dimension.Height)) ? false : true;
}

uint8_t Display::calculateRects (const uint16_t v_height)
{
    double  rects    = v_height / Config.LinesPerTransfer;
    uint8_t maxRects = static_cast <uint8_t> (rects);

    return ((v_height % Config.LinesPerTransfer) != ZERO) ? ++maxRects : maxRects;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

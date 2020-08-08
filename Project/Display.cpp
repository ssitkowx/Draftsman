///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <memory.h>
#include "Display.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool Display::DrawRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const Display::EColors eColor)
{
    if (validateRect (v_xPos, v_yPos, v_width, v_length) == false) { return false; }

    const uint16_t rectLen  = Config.Width * Config.MaxLinesPerTransfer;
    uint16_t rect [rectLen] = { };
    memset (rect, getColor (eColor), rectLen * sizeof (uint16_t));
    uint8_t maxRects = calculateRects (v_length);

    if (maxRects == ONE) { sendLines (v_xPos, v_yPos, v_width, v_length, static_cast <uint16_t *> (rect)); }
    else
    {
        uint16_t yPos   = v_yPos;
        uint16_t length = ZERO;
        for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
        {
            if (rectNum == maxRects) { length = v_length + v_yPos - yPos; }
            else
            {
                length = Config.MaxLinesPerTransfer;
                yPos   = yPos + length;
            }

            sendLines (v_xPos, yPos, v_width, length, static_cast <uint16_t *> (rect));
        }
    }

    return true;
}

bool Display::validateRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length)
{
    return (((v_xPos + v_width)  > Config.Width)  ||
            ((v_yPos + v_length) > Config.Length)) ? false : true;
}

uint8_t Display::calculateRects (const uint16_t v_length)
{
    double  rects    = v_length / Config.MaxLinesPerTransfer;
    uint8_t maxRects = static_cast <uint8_t> (rects);

    return ((v_length % Config.MaxLinesPerTransfer) != ZERO) ? ++maxRects : maxRects;
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

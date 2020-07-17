#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Display
{
    static constexpr char * MODULE = (char *)"Display";

    public:
        enum EColors
        {
            eBlack,
            eWhite,
            eRed,
            eLime,
            eBlue,
            eYellow,
            eCyan,
            eMagneta,
            eSilver,
            eGray,
            eMaroon,
            eOlive,
            eGreen,
            ePurple,
            eTeal,
            eNavy
        };

        Display          () = default;
        virtual ~Display () = default;

        virtual void DrawRect    (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const EColors eColor) = 0;
        virtual void DrawText    (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len   , const EColors eColor) = 0;
        virtual void DrawPicture (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len)                          = 0;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

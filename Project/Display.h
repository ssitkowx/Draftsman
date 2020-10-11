#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include "Rectangle.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class Display
{
    static constexpr char * MODULE = (char *)"Display";

    public:
        enum class EColors
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

        struct Configuration
        {
            uint16_t   LinesPerTransfer;
            Rectangle::Dimensions Dimension;
        };

        const Configuration Config;

        explicit Display (const Configuration v_config) : Config (v_config) { }
        virtual ~Display () = default;

        bool            DrawRect       (const Rectangle & v_rect, const EColors eColor);
        virtual bool    DrawBitmap     (const Rectangle & v_rect                      ) = 0;

    protected:
        virtual void    sendLines      (const Rectangle &v_rect                       ) = 0;
        virtual uint8_t getColor       (const Display::EColors eColor                 ) = 0;

    protected:
        bool            validateRect   (const Rectangle & v_rect);
        uint8_t         calculateRects (const uint16_t v_height);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

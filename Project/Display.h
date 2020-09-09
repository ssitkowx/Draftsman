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

        struct Dimensions
        {
            uint16_t Width;
            uint16_t Height;
        };

        struct Configuration
        {
            uint16_t   LinesPerTransfer;
            Dimensions Dimension;
        };

        struct Coordinates
        {
            uint16_t X;
            uint16_t Y;
        };

        struct Rect
        {
            uint16_t *  Data;
            Coordinates Coordinate;
            Dimensions  Dimension;
        };

        const Configuration Config;

        explicit Display (const Configuration v_config) : Config (v_config) { }
        virtual ~Display () = default;

        bool            DrawRect       (const Rect v_rect, const EColors eColor);
        virtual bool    DrawBitmap     (const Rect v_rect                      ) = 0;

    protected:
        virtual void    sendLines      (const Rect v_rect                      ) = 0;
        virtual uint8_t getColor       (const Display::EColors eColor          ) = 0;

    protected:
        bool            validateRect   (const Rect v_rect);
        uint8_t         calculateRects (const uint16_t v_height);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include "Bitmap.h"

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

        struct Config_t
        {
            uint16_t              LinesPerTransfer;
            Rectangle::Dimensions Dimension;
        };

        Display (const Config_t v_config);
        virtual ~Display () = default;

        virtual bool    DrawText   (const std::string & v_text, Rectangle::Coordinates v_coordinates) { /* todo */ return false; }
        virtual bool    DrawBitmap (Bitmap & v_bitmap                                               );

    protected:
        virtual void    sendLines  (const Bitmap & v_rect                     ) = 0;
        virtual uint8_t getColor   (const Display::EColors v_eColor           ) = 0;

        bool            validate   (const Rectangle & v_rect                  );
        uint8_t         calculate  (const Rectangle::Dimensions & v_dimensions);

    private:
        const Config_t config;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

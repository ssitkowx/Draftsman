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

        struct Configuration
        {
            uint8_t  RectNumbers;
            uint16_t Length;
            uint16_t Width;
            uint16_t MaxLinesPerTransfer;
        };

        const Configuration Config;

        Display (const Configuration v_config) : Config (v_config) { }
        virtual ~Display () = default;

        bool            DrawRect       (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const EColors eColor         );
        virtual bool    DrawText       (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len   , const EColors eColor         ) = 0;
        virtual bool    DrawPicture    (const uint16_t v_xPos, const uint16_t v_yPos, const uint8_t & data  , const uint16_t v_len                                  ) = 0;

    protected:
        virtual void    sendLines      (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length, const uint16_t * const v_data) = 0;
        virtual uint8_t getColor       (const Display::EColors eColor                                                                                               ) = 0;

    private:
        bool            validateRect   (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_width, const uint16_t v_length);
        uint8_t         calculateRects (const uint16_t v_length);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

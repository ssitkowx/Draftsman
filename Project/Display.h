#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include "Utils.h"
#include "Bitmap.h"
#include "Rectangle.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class Display
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

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

        Display (const Config_t v_config) : config (v_config) { }

        bool DrawText   (const std::string & v_text, Rectangle::Coordinates v_coordinates) { /* todo */ return false; }
        bool DrawBitmap (Bitmap & v_bitmap)
        {
            Rectangle rect = {};
            rect.Dimension = v_bitmap.Dimension;
            rect.Coordinate = v_bitmap.Coordinate;

            if (validate (rect) == false) { return false; }

            uint8_t maxRects = calculate (v_bitmap.Dimension);
            if (maxRects == ONE) { sendLines (v_bitmap); }
            else
            {
                uint16_t yPos = ZERO;
                uint16_t height = ZERO;
                for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
                {
                    if (rectNum == maxRects) { height = v_bitmap.Dimension.Height - yPos; }
                    else { height = v_bitmap.Dimension.Width * config.LinesPerTransfer / config.Dimension.Width; }

                    v_bitmap.Coordinate.Y = yPos + v_bitmap.Coordinate.Y;
                    v_bitmap.Dimension.Height = height;

                    sendLines (v_bitmap);
                    yPos = yPos + height;
                }
            }

            return true;
        };

    protected:
        void    sendLines  (const Bitmap & v_rect          ) { derivedType.sendLines (v_rect); }
        uint8_t getColor   (const Display::EColors v_eColor) { derivedType.getColor  (v_eColor); }

    private:
        const Config_t config;
        ~Display () = default;

        virtual bool validate (const Rectangle & v_rect)
        {
            return (((v_rect.Coordinate.X + v_rect.Dimension.Width) >= config.Dimension.Width) ||
                    ((v_rect.Coordinate.Y + v_rect.Dimension.Height) >= config.Dimension.Height)) ? false : true;
        }

        uint8_t calculate (const Rectangle::Dimensions & v_dimensions)
        {
            double rects         = (v_dimensions.Width * v_dimensions.Height) / (config.Dimension.Width * config.LinesPerTransfer);
            double aditionalRect = (v_dimensions.Width * v_dimensions.Height) % (config.Dimension.Width * config.LinesPerTransfer);
            uint8_t maxRects     = static_cast <uint8_t> (rects);
            return (aditionalRect > ZERO) ? ++maxRects : maxRects;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

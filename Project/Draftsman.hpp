#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include "Utils.hpp"
#include "Bitmap.hpp"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class Draftsman
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

    public:
        struct Config_t
        {
            uint16_t           LinesPerTransfer;
            Bitmap::Dimensions Dimension;
        };

        explicit Draftsman  (const Config_t vConfig) : config (vConfig) { }
        void     DrawText   (std::string_view vText, const Bitmap::Coordinates vCoordinates) { derivedType.DrawText (vText, vCoordinates); }
        bool     DrawBitmap (Bitmap vBitmap)
        {
            if (validate (vBitmap) == false) { return false; }

            const uint8_t maxRects = calculate (vBitmap.Dimension);
            if (maxRects == ONE) { sendLines (vBitmap); }
            else
            {
                uint16_t       height       = ZERO;
                const uint16_t bitmapHeight = vBitmap.Dimension.Height;
                for (uint8_t rectNum = ONE; rectNum <= maxRects; rectNum++)
                {
                    vBitmap.Coordinate.Y = vBitmap.Coordinate.Y + height;
                    vBitmap.Data         = &vBitmap.Data [vBitmap.Dimension.Width * height];

                    if (rectNum == maxRects) { height = bitmapHeight - (maxRects - ONE) * height; }
                    else                     { height = config.LinesPerTransfer * config.Dimension.Width / vBitmap.Dimension.Width; }

                    vBitmap.Dimension.Height = height;
                    sendLines (vBitmap);
                }
            }

            return true;
        };

    protected:
        void sendLines (const Bitmap & vRect) { derivedType.sendLines (vRect); }

    private:
        const Config_t config;

        bool validate (const Bitmap & v_bitmap) const
        {
            return (((v_bitmap.Coordinate.X + v_bitmap.Dimension.Width) > config.Dimension.Width) ||
                    ((v_bitmap.Coordinate.Y + v_bitmap.Dimension.Height) > config.Dimension.Height)) ? false : true;
        }

        uint8_t calculate (const Bitmap::Dimensions & vDimensions) const
        {
            const double  rects         = (vDimensions.Width * vDimensions.Height) / (config.Dimension.Width * config.LinesPerTransfer);
            const double  aditionalRect = (vDimensions.Width * vDimensions.Height) % (config.Dimension.Width * config.LinesPerTransfer);
            uint8_t maxRects            = static_cast <uint8_t> (rects);
            return (aditionalRect > ZERO) ? ++maxRects : maxRects;
        }

        ~Draftsman () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
